// EditEx.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditEx

CEditEx::CEditEx(){

	m_bkCr = RGB( 199, 192, 223 );
	m_textCr = RGB( 0, 0, 255 );
	m_bkBrush.CreateSolidBrush( m_bkCr );
	m_nKeyStatus = 0;
	m_nEditType = ALL_TYPE;	
	
}

CEditEx::~CEditEx(){

}


BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	//{{AFX_MSG_MAP(CEditEx)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers

HBRUSH CEditEx::CtlColor(CDC* pDC, UINT nCtlColor){

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( m_textCr );
	pDC->SetBkColor( m_bkCr );
	return m_bkBrush;

}

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// Set the new Edit type
int CEditEx::SetEditType(CString strEditType){

	int			nOldType;

	nOldType = m_nEditType;
	
	if( strEditType.CompareNoCase( "BOOL" ) == 0 ){
		SetLimitText( 1 );
		m_nEditType = BOOL_TYPE;
		m_strWaring = "Invalid Character, this only accept [1] or [0]. (1=Yes; 0=No)";
	}
	else if( strEditType.CompareNoCase( "BYTE" ) == 0 ){
		SetLimitText( 3 );
		m_nEditType = BYTE_TYPE;
		m_strWaring = "Invalid Character, this only accept [0]~[9]";
	}
	else if( strEditType.CompareNoCase( "INTEGER" ) == 0 ){
		SetLimitText( 6 );
		m_nEditType = INTEGER_TYPE;
		m_strWaring = "Invalid Character, this only accept [0]~[9]";
	}
	else if( strEditType.CompareNoCase( "LONG" ) == 0 ){
		SetLimitText( 9 );
		m_nEditType = LONG_TYPE;
		m_strWaring = "Invalid Character, this only accept [0]~[9]";
	}
	else if( strEditType.CompareNoCase( "DECIMAL" ) == 0 ){
		SetLimitText( 38 );
		m_nEditType = DECIMAL_TYPE;
		m_strWaring = "Invalid Character, this only accept [-],[.],[0]~[9]!(Ex:-99.99)";
	}
	else if( strEditType.CompareNoCase( "DATETIME" ) == 0 ){
		SetLimitText( 19 );
		m_nEditType = DATETIME_TYPE;
		m_strWaring = "Invalid Character, this only accept [space],[-],[:],[0]~[9]!(Ex:2003-12-31 23:59:59)";
	}
	else if( strEditType.CompareNoCase( "SIMPLETIME" ) == 0 ){
		SetLimitText( 8 );
		m_nEditType = SIMPLETIME_TYPE;
		m_strWaring = "Invalid Character, this only accept [:],[0]~[9]!(Ex:23:59:59)";
	}
	else {	

		CString			strInfo;
		int				nCnt;

		m_nEditType = ALL_TYPE;

		strEditType.MakeUpper();
		nCnt = strEditType.Find( "STRING:" );
		if( nCnt >= 0 ){
			strInfo = strEditType.Mid( nCnt );
			if( strInfo.IsEmpty() == TRUE ){
				SetLimitText( 65536 );				
			}
			else{
				nCnt = atoi( strInfo.GetBuffer( 8 ) );
				strInfo.ReleaseBuffer();
				SetLimitText( nCnt );
			}
		}
		else{
			SetLimitText( 65536 );
		}
	}	
	return nOldType;
}
/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// press char
void CEditEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	BOOL		bFlag = FALSE;
	CString		strText;
	int			nStart;
	int			nEnd;

	GetSel( nStart, nEnd );
	GetWindowText( strText );

	if( nChar != VK_BACK){
		switch( m_nEditType ) {
		case BOOL_TYPE:
			if( nChar != '0' && nChar != '1' ){
				bFlag = TRUE;
			}
			break;

		case BYTE_TYPE:
			if( !isdigit( nChar ) ){
				bFlag = TRUE;
			}
			break;

		case INTEGER_TYPE:
		case LONG_TYPE:
			if( !isdigit( nChar ) && nChar != '-' ){
				bFlag = TRUE;
			}
			else{
				if( nChar == '-' && nStart != 0 ){
					bFlag = TRUE;
				}
			}
			break;

		case DECIMAL_TYPE:
			if( !isdigit( nChar ) && nChar != '-' && nChar != '.' ){
				bFlag = TRUE;
			}
			else{
				if( nChar == '-' ){
					if( nStart != 0 ){
						// 前一个可能是货币
						if( nStart == 1){
							if(	strText.GetAt(0) == _T('$') ){
								bFlag = FALSE;
							}	
							else{
								bFlag = TRUE;
							}
						}
						else{
							bFlag = TRUE;
						}
					}
				}
				else if( nChar == '.' ){
					if( strText.Find( '.' ) != -1 ){
						bFlag = TRUE;
					}
				}
			}
			break;
		case DATETIME_TYPE:
			if( !isdigit( nChar ) && nChar != '-' && nChar != ':' &&
				nChar != ' ' ){
				bFlag = TRUE;
			}
			break;
		case SIMPLETIME_TYPE:
			if( !isdigit( nChar ) && nChar != ':' ){
				bFlag = TRUE;
			}
			break;
		default:
			break;
		}
	}
	if( bFlag == TRUE ){
		MessageBox( m_strWaring, "Input Error", MB_ICONWARNING | MB_OK );
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// key down
void CEditEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	CWnd*		pWnd = GetParent();

	if(nChar == VK_UP){
		pWnd->PostMessage(WM_UPKEY);
		return;
	}
	else if( nChar == VK_DOWN){
		pWnd->PostMessage(WM_DOWNKEY);
		return;
	}
	else if( nChar == VK_RETURN){
		if( m_nKeyStatus & CTRL_FLAG ){
			pWnd->PostMessage(WM_CTRLENTER);	
		}
		else if( m_nKeyStatus & SHIFT_FLAG ){
			pWnd->PostMessage(WM_SHIFTENTER);	
		}
		else{
			pWnd->PostMessage(WM_ENTERKEY);
		}
		m_nKeyStatus = 0;
		return;
	}
	else if( nChar == VK_CONTROL){
		m_nKeyStatus |= CTRL_FLAG;
	}
	else if( nChar == VK_SHIFT){
		m_nKeyStatus |= SHIFT_FLAG;
	}
	RedrawWindow();
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// key up
void CEditEx::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {

	if( nChar == VK_CONTROL){
		m_nKeyStatus &= ~CTRL_FLAG;
	}
	else if( nChar == VK_SHIFT){
		m_nKeyStatus &= ~SHIFT_FLAG;
	}
	RedrawWindow();
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}
/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// 判断当前编辑值是否合理，合理则返加TRUE
// 如果不合理，询问客户是否放弃，放弃编辑：返回TRUE; strValue = "GIVEUPEDITVALUE"
// 如果不合理，且客户要重新编辑，则清空buffer,返回FALSE;
BOOL CEditEx::GetValue(CString &strValue){

	CString				strNotify;

	if( CheckValue( strNotify ) == TRUE ){
		GetWindowText( strValue );
		return TRUE;
	}
	else{
		CString				strWarning;
		strWarning = "Input data don't suitable the system:\n";
		strWarning += strNotify;
		strWarning += ".\n";
		strWarning += "Press YES button try again or Press NO give up?";

		if( MessageBox( strWarning, 
						"Input Data Error", 
						MB_ICONQUESTION | MB_YESNO ) == IDNO ){
			strValue = "GIVEUPEDITVALUE";
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// 判断当前编辑值是否合理，合理则返加TRUE
BOOL CEditEx::CheckValue( CString& strNotify ){

	BOOL			bFlag = TRUE;
	long			lValue = 0;
	CString			strText;
	CString			strWarning;

	strNotify.Empty();
	GetWindowText( strText );
	lValue = atol( strText.GetBuffer(0) );
	strText.ReleaseBuffer();

	switch( m_nEditType ) {
	case BOOL_TYPE:
		bFlag = TRUE;
		break;
	case BYTE_TYPE:
		if( lValue < 0 || lValue > 255 ){
			strNotify = "This Value Must large than 0 and less than 256";
			bFlag = FALSE;
		}
		else{
			bFlag = TRUE;
		}
		break;
	case INTEGER_TYPE:
		if( lValue < -32768 || lValue > 32768 ){
			strNotify = "This Value Must large than -32768 and less than 32768";
			bFlag = FALSE;
		}
		else{
			bFlag = TRUE;
		}
		break;
	case LONG_TYPE:
		if( lValue < -200000 || lValue > 200000 ){
			strNotify = "This Value Must large than -2147483648 and less than 2147483648";
			bFlag = FALSE;
		}
		else{
			bFlag = TRUE;
		}
		break;
	case DECIMAL_TYPE:
		bFlag = TRUE;
		break;
	case DATETIME_TYPE:
		if( CheckDateValid( strText, strWarning ) == FALSE ){
			strNotify = "Date Format must same as YEAR-MONTH-DAY HH:MM:SS, And ";
			strNotify += strWarning;
			bFlag = FALSE;
		}
		else{
			bFlag = TRUE;
		}
		break;
	case SIMPLETIME_TYPE:
		if( CheckTimeValid( strText, strWarning ) == FALSE ){
			strNotify = "Time Format must same as HH:MM:SS, And ";
			strNotify += strWarning;
			bFlag = FALSE;
		}
		else{
			bFlag = TRUE;
		}
		break;
	default:
		bFlag = TRUE;
		break;
	}
	return bFlag;
}

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// 判断当前编辑值是否合理，合理则返加TRUE
BOOL CEditEx::CheckDateValid(CString strDate, CString &strWaring){

	BOOL			bFlag = TRUE;
	int				nChar = '-';
	int				nCnt = 0;
	int				nFmt = 0;
	int				nValue;
	CString			strTmp;

	if( strDate.IsEmpty() ){
		return TRUE;
	}
	while( (nCnt = strDate.Find( nChar ) ) != -1 ){
		
		strTmp = strDate.Left( nCnt );
		strDate = strDate.Mid( nCnt + 1 );

		nValue = atoi( strTmp.GetBuffer(0) );
		strTmp.ReleaseBuffer();

		switch( nFmt ){
		case 0:			// year
			if( nValue < 1900 || nValue > 9999 ){
				strWaring = "Year Value must be 1900 ~ 9999";
				return FALSE;
			}
			break;
		case 1:			// month
			if( nValue < 1 || nValue > 12 ){
				strWaring = "Month Value must be 1 ~ 12";
				return FALSE;
			}
			nChar = ' ';
			break;
		case 2:			// day
			if( nValue < 1 || nValue > 31 ){
				strWaring = "Day Value must be 1 ~ 31";
				return FALSE;
			}
			nChar = ':';
			break;
		case 3:			// hour
			if( nValue < 0 || nValue > 23 ){
				strWaring = "Hour Value must be 0 ~ 23";
				return FALSE;
			}
			break;
		case 4:			// Minute
			if( nValue < 0 || nValue > 59 ){
				strWaring = "Minute Value must be 0 ~ 59";
				return FALSE;
			}
			break;
		case 5:			// Second
			if( nValue < 0 || nValue > 59 ){
				strWaring = "Second Value must be 0 ~ 59";
				return FALSE;
			}
			break;
		default:
			strWaring = "unknow error occur";
			return FALSE;
		}
		nFmt++;
	}
	strTmp = strDate;
	nValue = atoi( strTmp.GetBuffer(0) );
	strTmp.ReleaseBuffer();

	switch( nFmt ){
	case 0:			// year
		if( nValue < 1980 || nValue > 9999 ){
			strWaring = "Year Value must be 1980 ~ 9999";
			return FALSE;
		}
		break;
	case 1:			// month
		if( nValue < 1 || nValue > 12 ){
			strWaring = "Month Value must be 1 ~ 12";
			return FALSE;
		}
		nChar = ' ';
		break;
	case 2:			// day
		if( nValue < 1 || nValue > 31 ){
			strWaring = "Day Value must be 1 ~ 31";
			return FALSE;
		}
		nChar = ':';
		break;
	case 3:			// hour
		if( nValue < 0 || nValue > 23 ){
			strWaring = "Hour Value must be 0 ~ 23";
			return FALSE;
		}
		break;
	case 4:			// Minute
		if( nValue < 0 || nValue > 59 ){
			strWaring = "Minute Value must be 0 ~ 59";
			return FALSE;
		}
		break;
	case 5:			// Second
		if( nValue < 0 || nValue > 59 ){
			strWaring = "Second Value must be 0 ~ 59";
			return FALSE;
		}
		break;
	default:
		strWaring = "unknow error occur";
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers
// 判断当前编辑值是否合理，合理则返加TRUE
BOOL CEditEx::CheckTimeValid(CString strTime, CString& strWaring){

	BOOL			bFlag = TRUE;
	int				nCnt = 0;
	int				nFmt = 0;
	int				nValue;
	CString			strTmp;

	if( strTime.IsEmpty() == TRUE ){
		return TRUE;
	}
	while( (nCnt = strTime.Find( ':' ) ) != -1 ){
		
		strTmp = strTime.Left( nCnt );
		strTime = strTime.Mid( nCnt + 1 );

		nValue = atoi( strTmp.GetBuffer(0) );
		strTmp.ReleaseBuffer();

		switch( nFmt ){
		case 0:			// Hour
			if( nValue < 0 || nValue > 23 ){
				strWaring = "Hour Value must be 0 ~ 23";
				return FALSE;
			}
			break;
		case 1:			// Minute
			if( nValue < 0 || nValue > 59 ){
				strWaring = "Minute Value must be 0 ~ 59";
				return FALSE;
			}
			break;
		case 3:			// Second
			if( nValue < 0 || nValue > 59 ){
				strWaring = "Second Value must be 0 ~ 59";
				return FALSE;
			}
			break;
		default:
			strWaring = "unknow error occur";
			return FALSE;
		}
		nFmt++;
	}
	strTmp = strTime;
	nValue = atoi( strTmp.GetBuffer(0) );
	strTmp.ReleaseBuffer();

	switch( nFmt ){
	case 0:			// hour
		if( nValue < 0 || nValue > 23 ){
			strWaring = "Hour Value must be 0 ~ 23";
			return FALSE;
		}
		break;
	case 1:			// Minute
		if( nValue < 0 || nValue > 59 ){
			strWaring = "Minute Value must be 0 ~ 59";
			return FALSE;
		}
		break;
	case 2:			// Second
		if( nValue < 0 || nValue > 59 ){
			strWaring = "Second Value must be 0 ~ 59";
			return FALSE;
		}
		break;
	default:
		strWaring = "unknow error occur";
		return FALSE;
	}
	return TRUE;
}
