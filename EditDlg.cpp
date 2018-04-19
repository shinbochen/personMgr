// EditDlg.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "EditDlg.h"
#include "Mainfrm.h"

#include "DateDlg.h"
#include "TimeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDlg::IDD, pParent){
	//{{AFX_DATA_INIT(CEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_pMapHelpInfo = NULL;
	m_pMapDataType = NULL;
	m_pArrColumn = NULL;
	m_pMapDataValue = NULL;
	m_strTitle.Empty();
}

CEditDlg::CEditDlg( CStringArray*	pArrColumn, 
			  CMapStringToString* pMapDataType,
		      CMapStringToString* pMapDataValue, 
			  CMapStringToString* pMapHelpInfo,
			  CWnd* pParent ): CDialogEx(CEditDlg::IDD, pParent){

	m_pArrColumn = pArrColumn;
	m_pMapDataType = pMapDataType;
	m_pMapDataValue = pMapDataValue;
	m_pMapHelpInfo = pMapHelpInfo;
	m_strTitle.Empty();
	return;
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_STOP, m_btStop);
	DDX_Control(pDX, IDC_PAUSE, m_btPause);
	DDX_Control(pDX, IDC_PLAY, m_btPlay);
	DDX_Control(pDX, IDC_MORE, m_ctrMore);
	DDX_Control(pDX, IDOK, m_ctrOK);
	DDX_Control(pDX, IDCANCEL, m_ctrCancel);
	DDX_Control(pDX, IDC_COLUMNNAME, m_ctrColumnName);
	DDX_Control(pDX, IDC_HELPINFO, m_ctrHelpInfo);
	DDX_Control(pDX, IDC_VALUELIST, m_ctrListValue);
	DDX_Control(pDX, IDC_EDIT, m_ctrEdit);
	DDX_Control(pDX, IDC_COLUMNLIST, m_ctrListColumn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_LBN_SELCHANGE(IDC_COLUMNLIST, OnSelchangeColumnlist)
	ON_LBN_SETFOCUS(IDC_COLUMNLIST, OnSetfocusColumnlist)
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_MORE, OnMore)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_LBN_SELCHANGE(IDC_VALUELIST, OnSelchangeColumnlist)
	ON_LBN_SETFOCUS(IDC_VALUELIST, OnSetfocusColumnlist)
	ON_LBN_DBLCLK(IDC_COLUMNLIST, OnDblclkColumnlist)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPKEY, OnUpCtrKeyDown)
	ON_MESSAGE(WM_DOWNKEY, OnDownCtrKeyDown)
	ON_MESSAGE(WM_ENTERKEY, OnEnterCtrKeyDown)
	ON_MESSAGE(WM_CTRLENTER, OnCtrlEnterDown)
	ON_MESSAGE(WM_SHIFTENTER, OnShiftEnterDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers
// initial dialog
BOOL CEditDlg::OnInitDialog(){
	
	ASSERT( m_pArrColumn != NULL );
	ASSERT( m_pMapDataType != NULL );
	ASSERT( m_pMapDataValue != NULL );
	
	m_nMoreType = 0;
	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_bkBrush.CreateSolidBrush( m_bkCr );

	CDialogEx::OnInitDialog();

	int				nLen;
	int				nCnt;
	CString			strKey;
	CString			strValue;
	CString			strDataType;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	// set bitmap button
	m_btPlay.LoadBitmaps( IDB_PLAY, IDB_PLAY1 );
	m_btPause.LoadBitmaps( IDB_PAUSE );
	m_btStop.LoadBitmaps( IDB_STOP, IDB_STOP1 );

	GetDlgItem(IDC_S_COLUMN)->GetWindowText( strKey );
	strKey = pFrame->GetDispPhrase( strKey );
	GetDlgItem(IDC_S_COLUMN)->SetWindowText( strKey );
	

	GetDlgItem(IDC_S_VALUE)->GetWindowText( strKey );
	strKey = pFrame->GetDispPhrase( strKey );
	GetDlgItem(IDC_S_VALUE)->SetWindowText( strKey );
	
	GetDlgItem(IDC_S_HELPINFO)->GetWindowText( strKey );
	strKey = pFrame->GetDispPhrase( strKey );
	GetDlgItem(IDC_S_HELPINFO)->SetWindowText( strKey );

	if( m_strTitle.IsEmpty() == FALSE ){
		SetWindowText( pFrame->GetDispPhrase(m_strTitle) );
	}

	// set the column list
	nLen = m_pArrColumn->GetSize();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		strKey = m_pArrColumn->GetAt( nCnt );

		m_ctrListColumn.AddString( pFrame->GetDispPhrase( strKey ) );

		if( m_pMapDataValue->Lookup( strKey, strValue ) == FALSE ){
			strValue = " ";			
		}
		if( m_pMapDataType ){
			m_pMapDataType->Lookup( strKey, strDataType );
			if( strDataType.CompareNoCase( "BOOL" ) == 0 ){
				if( strValue.CompareNoCase( "Yes" ) == 0 ){
					strValue = "1";
				}
				else{
					strValue = "0";
				}	
				m_pMapDataValue->SetAt( strKey, strValue );
			}
		}
		if( strValue == " " ){
			// 根据所给列的类型设定预设值
			strValue = GetDefaultValue( strKey );			
			m_pMapDataValue->SetAt( strKey, strValue );
		}
		m_ctrListValue.AddString( strValue );
	}
	m_nCurSel = 0;
	m_ctrListColumn.SetCurSel( 0 );
	m_ctrListValue.SetCurSel( 0 );
	SetEditTypeAndData();
	SetHelpInfo();
	m_ctrEdit.SetFocus();

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// 根据所给列的类型设定预设值
CString CEditDlg::GetDefaultValue(CString strKey){

	CString			strDataType;
	CString			strValue;
	CTime			time;

	time = CTime::GetCurrentTime();

	if( m_pMapDataType == NULL ){
		strValue = " ";
		return strValue;
	}

	m_pMapDataType->Lookup( strKey, strDataType );

	if( strDataType.CompareNoCase("BOOL") == 0 ){
		strValue = "1";
	}
	else if( strDataType.CompareNoCase("BYTE") == 0 ){
		strValue = "0";
	}
	else if( strDataType.CompareNoCase("INTEGER") == 0 ){
		strValue = "0";
	}
	else if( strDataType.CompareNoCase("LONG") == 0 ){
		strValue = "0";
	}
	else if( strDataType.CompareNoCase("DECIMAL") == 0 ){
		strValue = "0.00";
	}
	else if( strDataType.CompareNoCase("DATETIME") == 0 ){		
		strValue = time.Format("%Y-%m-%d");
	}
	else if( strDataType.CompareNoCase("SIMPLETIME") == 0 ){
		strValue = time.Format("%H:%M:%S");
	}
	else{
		strValue = " ";
	}
	return strValue;

}
/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// Set the current column info
void CEditDlg::SetHelpInfo(){

	CString			strKey;
	CString			strValue;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	m_ctrListColumn.GetText( m_nCurSel, strKey );
	strKey = pFrame->GetReversePhrase( strKey );

	if(m_pMapHelpInfo == NULL){
		m_ctrHelpInfo.SetWindowText( pFrame->GetDispPhrase("No any help info!") );
	}
	else{
		m_pMapHelpInfo->Lookup( strKey, strValue );
		m_ctrHelpInfo.SetWindowText( strValue );
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// Set the current column edit type
void CEditDlg::SetEditTypeAndData(){

	CString			strKey;
	CString			strValue;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	GetDlgItem(IDC_PLAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PAUSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MORE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MORE)->EnableWindow(FALSE);


	m_ctrListColumn.GetText( m_nCurSel, strKey );
	strKey = pFrame->GetReversePhrase( strKey );

	if( m_pMapDataType == NULL ){
		m_ctrEdit.SetEditType( "STRING:65536" );
		strValue.Empty();
	}
	else{
		m_pMapDataType->Lookup( strKey, strValue );
		m_ctrEdit.SetEditType( strValue );
	}
	JudgeCanMore( strKey, strValue );

	m_ctrColumnName.SetWindowText( pFrame->GetDispPhrase(strKey) );
	if( m_pMapDataValue == NULL ){
		ASSERT( FALSE );
		m_ctrEdit.SetWindowText( "ERROR" );
	}
	else{
		m_pMapDataValue->Lookup( strKey, strValue );
		m_ctrEdit.SetWindowText( strValue );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// 判断是否有更多信息
void CEditDlg::JudgeCanMore(CString strColumn, CString strType){

	BOOL				bFlag = FALSE;
	// 
	if( strType.CompareNoCase("SIMPLETIME") == 0 ){
		m_nMoreType = MORE_TIME;
		bFlag = TRUE;
	}
	else if( strType.CompareNoCase("DATETIME") == 0 ){
		m_nMoreType = MORE_DATE;
		bFlag = TRUE;
	}
	else if( strType.Find("STRING") != -1 ){
		strColumn.MakeUpper();
		if( strColumn.Find("MELODY") != -1 ){
			bFlag = TRUE;
			m_nMoreType = MORE_MELODY;
			GetDlgItem(IDC_PLAY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STOP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PLAY)->EnableWindow( );
			GetDlgItem(IDC_STOP)->EnableWindow( );
		}
		else{
			m_nMoreType = 0;
		}
	}
	else{
		m_nMoreType = 0;
	}
	if( bFlag == TRUE ){
		GetDlgItem(IDC_MORE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MORE)->EnableWindow();
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// the column list have change
void CEditDlg::OnSelchangeColumnlist(){

	int			nNewSel;

	nNewSel = m_ctrListColumn.GetCurSel();
	SelChangeListTo( nNewSel );
	
}
/////////////////////////////////////////////////////////////////////////////
// CEditDlg function
// set the new select
BOOL CEditDlg::SelChangeListTo(int nNewSel){

	ASSERT( nNewSel >= 0 );

	CString				strKey;
	CString				strOldValue;
	CString				strNewValue;
	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );

	OnStop();
	//if( m_nCurSel == nNewSel ){
	//	m_ctrListValue.SetCurSel( m_nCurSel );
	//	return;
	//}

	m_ctrListColumn.GetText(m_nCurSel, strKey);
	strKey = pFrame->GetReversePhrase( strKey );

	m_pMapDataValue->Lookup( strKey, strOldValue );

	// 编辑值不正确，且用户确认其重新编辑
	if( m_ctrEdit.GetValue( strNewValue ) == FALSE ){
		m_ctrListValue.SetCurSel( m_nCurSel );
		m_ctrEdit.SetFocus();
		return FALSE;
	}
	// 编辑值不正确，用户放弃编辑值 (strNewValue == GIVEUPEDITVALUE)
	// 编辑值正确，用户取回其值
	else{
		if( strNewValue != "GIVEUPEDITVALUE" ){
			m_pMapDataValue->SetAt( strKey, strNewValue );
			m_ctrListValue.DeleteString( m_nCurSel );
			m_ctrListValue.InsertString( m_nCurSel, strNewValue );
		}

		m_nCurSel = nNewSel;		

		m_ctrListColumn.SetCurSel( m_nCurSel );
		m_ctrListValue.SetCurSel( m_nCurSel );

		SetEditTypeAndData();
		SetHelpInfo();
		m_ctrEdit.SetFocus();
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// 响应由编辑框给出的消息
LRESULT CEditDlg::OnUpCtrKeyDown(WPARAM wParam, LPARAM lParam){

	int				nMaxItem;
	int				nNewSel;

	nMaxItem = m_ctrListColumn.GetCount();
	nNewSel = m_nCurSel-1;
	if(nNewSel <0 ){
		nNewSel = nMaxItem-1;
	}
	SelChangeListTo( nNewSel );
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
// 响应由编辑框给出的消息
LRESULT CEditDlg::OnDownCtrKeyDown(WPARAM wParam, LPARAM lParam){

	int				nMaxItem;
	int				nNewSel;

	nMaxItem = m_ctrListColumn.GetCount();
	nNewSel = m_nCurSel+1;
	if(nNewSel >= nMaxItem ){
		nNewSel = 0;
	}
	SelChangeListTo( nNewSel );
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
// 响应由编辑框给出的消息
LRESULT CEditDlg::OnEnterCtrKeyDown(WPARAM wParam, LPARAM lParam){

	int				nMaxItem;
	int				nNewSel;

	nMaxItem = m_ctrListColumn.GetCount();
	nNewSel = m_nCurSel+1;
	if(nNewSel >= nMaxItem ){
		nNewSel = 0;
	}
	SelChangeListTo( nNewSel );
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
// 响应由编辑框给出的消息
LRESULT CEditDlg::OnCtrlEnterDown(WPARAM wParam, LPARAM lParam){
	//OnOK();
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
// 响应由编辑框给出的消息
LRESULT CEditDlg::OnShiftEnterDown(WPARAM wParam, LPARAM lParam){
	//OnDetail();
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
// while the column list or value list get the focus
void CEditDlg::OnSetfocusColumnlist() {

	//m_ctrEdit.SetFocus();
	return;	
}
///////////////////////////////////////////////////////////////////////////////
// while the column list or value list get the focus
HBRUSH CEditDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){

	if( pWnd->GetDlgCtrlID() != IDC_EDIT ){
		pDC->SetBkMode( TRANSPARENT );
		if( pWnd->GetDlgCtrlID() == IDC_HELPINFO ){
			pDC->SetTextColor( RGB( 255, 0, 0 ) );
		}
		if( pWnd->GetDlgCtrlID() == IDC_COLUMNNAME ){
			pDC->SetTextColor( RGB( 0, 0, 255 ) );
		}
		return m_bkBrush;
	}
	else{
		HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);	
		return hbr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// while the column list or value list get the focus
void CEditDlg::OnOK() {
	
	if( SelChangeListTo( m_ctrListColumn.GetCurSel() ) == FALSE ){
		return;
	}	
	if( IsAllValueValid() == FALSE ){
		return;
	}
	CDialogEx::OnOK();
}
///////////////////////////////////////////////////////////////////////////////
// while the column list or value list get the focus
BOOL CEditDlg::IsAllValueValid(){

	int				nCnt;
	int				nLen;
	CString			strKey, strValue, strHelpInfo;

	nLen = m_pArrColumn->GetSize();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		
		strKey = m_pArrColumn->GetAt( nCnt );
		m_pMapHelpInfo->Lookup( strKey, strHelpInfo );
		if( strHelpInfo.Find( "not allow null value" ) != -1 ){
			m_pMapDataValue->Lookup( strKey, strValue );
			if( strKey.IsEmpty( ) ){
				return FALSE;
			}
		}
	}
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
// the right button down
void CEditDlg::OnRButtonDown(UINT nFlags, CPoint point) {	
	CDialogEx::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////////////////////////////////////////////
// the right button down
void CEditDlg::OnDblclkColumnlist(){
	OnMore();	
}
///////////////////////////////////////////////////////////////////////////////
// the right button down
void CEditDlg::OnMore() {

	CString				strText;

	m_ctrEdit.GetWindowText( strText );

	if( m_nMoreType == MORE_DATE ){
		CDateDlg		dateDlg;

		if( dateDlg.DoModal() == IDOK ){
			m_ctrEdit.SetWindowText( dateDlg.GetDateString() );
		}
	}
	else if( m_nMoreType == MORE_TIME ){
		CTimeDlg		timeDlg( strText );

		if( timeDlg.DoModal() == IDOK ){
			m_ctrEdit.SetWindowText( timeDlg.GetTimeString() );
		}
	}
	else if( m_nMoreType == MORE_MELODY ){
		CFileDialog		fileDlg( TRUE, 
								 "Sound Files",
								 "*.wav",
								 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
								 "Sound Files (*.wav)",
								 this );
		if( fileDlg.DoModal() == IDOK ){
			m_ctrEdit.SetWindowText( fileDlg.GetPathName() );
		}
	}
	return;
}
///////////////////////////////////////////////////////////////////////////////
// the right button down
void CEditDlg::OnPlay(){
	CString			strText;

	if( m_nMoreType == MORE_MELODY ){
		m_ctrEdit.GetWindowText( strText );
		sndPlaySound( strText, SND_ASYNC|SND_LOOP );
	}
	
}
///////////////////////////////////////////////////////////////////////////////
// the right button down
void CEditDlg::OnStop() {
	sndPlaySound( NULL, SND_ASYNC|SND_LOOP );
}
