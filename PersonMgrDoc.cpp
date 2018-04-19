// PersonMgrDoc.cpp : implementation of the CPersonMgrDoc class
//
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"

#include "PersonMgrDoc.h"
#include "MainFrm.h"

#include "PersonMgrListView.h"
#include "PersonMgrQueryView.h"
#include "PersonMgrTitleView.h"
#include "PersonMgrTreeView.h"
#include "LoginDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc
// extern function declare
extern CString	ChangeVariantToString( COleVariant& varValue, BOOL bFlag );
extern BOOL		GetVariantFromString( COleVariant& varValue, 
									short nDataType, 
									CString strValue );
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc

IMPLEMENT_DYNCREATE(CPersonMgrDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonMgrDoc, CDocument)
	//{{AFX_MSG_MAP(CPersonMgrDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc construction/destruction

CPersonMgrDoc::CPersonMgrDoc(){

	m_pDaoDB = NULL;
	m_pDaoRecordSet = NULL;
	m_pTitleView = NULL;
	m_pQueryView = NULL;
	m_pListView = NULL;
	m_pTreeView = NULL;

	m_bAutoShutDown = FALSE;
	m_bLogin = FALSE;
}

CPersonMgrDoc::~CPersonMgrDoc(){

}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc open document
BOOL CPersonMgrDoc::OnNewDocument(){

	CString			strDBName;


	if ( !CDocument::OnNewDocument() ){
		AfxMessageBox("Open File Fail!");
		return FALSE;
	}
	InitUserData( );


	m_pDaoDB = new CDaoDatabase(  );
	strDBName = GetDBName();

	try{
		m_pDaoDB->Open( strDBName ,FALSE, FALSE, ";pwd=SHINBOCH" );
	}
	catch( CDaoException *pException ){
		AfxMessageBox("Sorry,Open DAO File Fail! Please contact the author");
		AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
						MB_ICONEXCLAMATION );
		pException->Delete();
		delete m_pDaoDB;
		m_pDaoDB = NULL;
		delete pException;
		return FALSE;
	}
	m_pDaoRecordSet = new CDaoRecordset( m_pDaoDB );

	// Get the table info
	CDaoTableDefInfo	tableInfo;
	int					nLen;
	int					nCnt;

	nLen = m_pDaoDB->GetTableDefCount();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		
		m_pDaoDB->GetTableDefInfo( nCnt, tableInfo );
		if( tableInfo.m_lAttributes & dbSystemObject )
			continue;
		m_arrTable.Add( tableInfo.m_strName );
	}
	// Get the query info
	CDaoQueryDefInfo	queryInfo;
	nLen = m_pDaoDB->GetQueryDefCount();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		
		m_pDaoDB->GetQueryDefInfo( nCnt, queryInfo );
		m_arrQuery.Add( queryInfo.m_strName );
	}

	CString			strTitle;
	strTitle = ":)";
	/*
	CMainFrame*		pFrame;

	pFrame = (CMainFrame*)AfxGetMainWnd();		
	//strTitle = pFrame->GetDispPhrase("PIM System");*/

	SetTitle( strTitle );
	GetUserPsdInfo();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc close document
void CPersonMgrDoc::OnCloseDocument(){

	if( m_pDaoRecordSet != NULL ){
		m_pDaoRecordSet->Close();
		delete m_pDaoRecordSet;
		m_pDaoRecordSet = NULL;
	}
	if( m_pDaoDB != NULL ){
		m_pDaoDB->Close();
		delete m_pDaoDB;
		m_pDaoDB = NULL;
	}
	SetPrivateInfo( );
	CDocument::OnCloseDocument();
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc serialization
void CPersonMgrDoc::Serialize(CArchive& ar){
	if (ar.IsStoring())	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc diagnostics

#ifdef _DEBUG
void CPersonMgrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonMgrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// Get database name
CString CPersonMgrDoc::GetDBName(){

	CString		strPath;
	TCHAR		szName[255];

	if( GetCurrentDirectory( 254, szName ) > 0 ){
		strPath.Format( "%s", szName );
		strPath += "\\Person2.mdb";
	}
	else{
		strPath = "";
	}
	return strPath;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// Get the current table or query Column name
void CPersonMgrDoc::InitallColumnName(){

	ASSERT( m_pDaoDB != NULL );
	ASSERT( m_pTitleView != NULL );
	ASSERT( m_pQueryView != NULL );
	ASSERT( m_pListView != NULL );
	ASSERT( m_pTreeView != NULL );

	int				nLen;
	int				nCnt = 0;
	CDaoTableDef	tableDef( m_pDaoDB );
	CDaoQueryDef	queryDef( m_pDaoDB );
	CDaoFieldInfo	fieldInfo;

	//if( m_nType == NONE ){
	//	return;
	//}

	// clear the previous data
	EmptyArray( m_arrColumn );
	EmptyArray( m_arrColumnType );
	EmptyArray( m_arrParam );
	EmptyArray( m_arrParamType );

	EmptyMapString( m_mapColumnToDataType );
	EmptyMapString( m_mapColumnToHelpInfo );
	EmptyMapString( m_mapParamToDataType );
	EmptyMapString( m_mapParamToHelpInfo );

	// table column
	if( m_nType == INPUT ){

		tableDef.Open( m_curTable );
		nLen = tableDef.GetFieldCount();

		for( nCnt = 0; nCnt < nLen; nCnt++ ){

			tableDef.GetFieldInfo( nCnt, fieldInfo );
			GetColumnDataTypeAndHelpInfo( fieldInfo );
		}
	}
	// query column
	else if( m_nType == QUERY ){

		queryDef.Open( m_curTable );		
		nLen = queryDef.GetFieldCount(  );

		for( nCnt = 0; nCnt < nLen; nCnt++ ){

			queryDef.GetFieldInfo( nCnt, fieldInfo );
			GetColumnDataTypeAndHelpInfo( fieldInfo );
		}

		nLen = queryDef.GetParameterCount();
		for( nCnt = 0; nCnt < nLen; nCnt++ ){
			
			CDaoParameterInfo		paramInfo;

			queryDef.GetParameterInfo( nCnt, paramInfo );
			GetParamDataTypeAndHelpInfo( paramInfo );
		}

	}
	m_pTitleView->Invalidate();
	m_pQueryView->InitView();
	m_pListView->InitView();
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// 判断指定列是否是一个简单的时间类型，即只允许时间输入不需日期输入
BOOL CPersonMgrDoc::IsSimpleTimeType(CString strColumn, int nType){
	CString			strTmp;
	BOOL			bFlag;

	strTmp.LoadString( IDS_SIMPLETIMETYPE );
	if( (nType == dbDate) && (strTmp == strColumn) ){
		bFlag = TRUE;
	}
	else{
		bFlag = FALSE;
	}
	return bFlag;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// Get the column and the data type
// Get the Column and the Help info
void CPersonMgrDoc::GetColumnDataTypeAndHelpInfo(CDaoFieldInfo &fieldInfo){

	CString			strKey;
	CString			strValue;
	int				nType;
	BOOL			bSimpleTime = FALSE;

	strKey = fieldInfo.m_strName;
	nType = fieldInfo.m_nType;
	if ( strKey.CollateNoCase("ID") == 0 ){
		return;
	}

	bSimpleTime = IsSimpleTimeType( strKey, nType );
	if( bSimpleTime == TRUE ){
		nType = dbTime;
	}

	// Get column type
	if( m_nType == INPUT ){
		strValue = GetDataTypeString( nType, fieldInfo.m_lSize );
	}
	else{
		strValue = "";
	}
	m_arrColumn.Add( strKey );
	m_arrColumnType.Add( nType );
	m_mapColumnToDataType.SetAt( strKey, strValue );

	// Get column help info
	if( m_nType == INPUT ){
		
		strValue = GetHelpInfoString( nType, 
									  fieldInfo.m_lSize,
									  fieldInfo.m_bAllowZeroLength );

		m_mapColumnToHelpInfo.SetAt( strKey, strValue );
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// Get the parameter and the data type
// Get the parameter and the Help info
void CPersonMgrDoc::GetParamDataTypeAndHelpInfo(CDaoParameterInfo &paramInfo){
	
	CString			strKey;
	CString			strValue;

	strKey = paramInfo.m_strName;

	m_arrParam.Add( strKey );
	m_arrParamType.Add( paramInfo.m_nType );

	// get parameter type
	strValue = GetDataTypeString( paramInfo.m_nType );
	m_mapParamToDataType.SetAt( strKey, strValue );

	// get the help info
	strValue = GetHelpInfoString( paramInfo.m_nType );
	m_mapParamToHelpInfo.SetAt( strKey, strValue );
	
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// according the nDataType make the string
CString CPersonMgrDoc::GetDataTypeString(short nDataType, int nSize){

	CString			strValue;

	switch( nDataType ){
	case dbBoolean:				// Yes/No, same as TRUE/FALSE 
		strValue = "BOOL";
		break;
	case dbByte:				// Byte 
		strValue = "BYTE";	// 整数	
		break;
	case dbInteger:				// Short 
		strValue = "INTEGER";	// 整数	
		break;
	case dbLong:				// Long 
		strValue = "LONG";	// 整数	
		break;
	case dbCurrency:				// Currency; see MFC class COleCurrency 
	case dbSingle:				// Single 
	case dbDouble:				// Double 
		strValue = "DECIMAL";	// 小数
		break;
	case dbDate:					// Date/Time; see MFC class COleDateTime 
		strValue = "DATETIME";
		break;
	case dbTime:					// Date/Time; see MFC class COleDateTime 
		strValue = "SIMPLETIME";
		break;
	case dbText:				// Text; see MFC class CString 
	case dbLongBinary:			// Long Binary (OLE Object); you might want to use MFC class CByteArray instead of class CLongBinary as CByteArray is richer and easier to use. 
	case dbMemo:				// Memo; see MFC class CString
	default:
		strValue.Format("%s:%d","STRING", nSize);		
		break;
	}
	return strValue;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc commands
// according the nDataType make the help infostring
CString CPersonMgrDoc::GetHelpInfoString(short nDataType, int nSize, BOOL bAllowZero){

	CString			strValue;
	CString			strTmp;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	switch( nDataType ){
	case dbBoolean:				// Yes/No, same as TRUE/FALSE 
		strValue = pFrame->LoadStringA( IDS_BOOLHELPINFO );
		break;
	case dbByte:				// Byte 
		strValue = pFrame->LoadStringA( IDS_BYTEHELPINFO );
		break;
	case dbInteger:				// Short 
		strValue = pFrame->LoadStringA( IDS_SHORTHELPINFO );
		break;
	case dbLong:				// Long 
		strValue = pFrame->LoadStringA( IDS_LONGHELPINFO );
		break;
	case dbCurrency:			// Currency; see MFC class COleCurrency 
		strValue = pFrame->LoadStringA( IDS_CURRENCYHELPINFO );
		break;
	case dbSingle:				// Single 
		strValue = pFrame->LoadStringA( IDS_SINGLEHELPINFO );
		break;
	case dbDouble:				// Double 
		strValue = pFrame->LoadStringA( IDS_DOUBLEHELPINFO );
		break;
	case dbDate:				// Date/Time; see MFC class COleDateTime 
		strValue = pFrame->LoadStringA( IDS_DATEHELPINFO );
		break;
	case dbTime:				// simple time; only allow time but not date
		strValue = pFrame->LoadStringA( IDS_SIMPLETIMEHELPINFO );
		break;
	case dbMemo:				// Memo; see MFC class CString
		strValue = pFrame->LoadStringA( IDS_TEXTHELPINFO );

		strTmp.Format( "; Length: %d", 65536 );
		strValue += strTmp;
		break;

	case dbText:				// Text; see MFC class CString 
	case dbLongBinary:			// Long Binary (OLE Object); you might want to use MFC class CByteArray instead of class CLongBinary as CByteArray is richer and easier to use. 
	default:
		strValue = pFrame->LoadStringA( IDS_TEXTHELPINFO );

		strTmp.Format( "; Length: %d", nSize );
		strValue += strTmp;
		break;
	}
	if( bAllowZero == FALSE ){
		strValue += "; ";
		strValue += pFrame->GetDispPhrase("not allow null value");
	}			
	return strValue;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Get Current Filter String
CString CPersonMgrDoc::GetFilterString(){

	return m_pQueryView->GetFilterString();
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Get Current Filter String
BOOL CPersonMgrDoc::Login(){

	CLoginDlg		loginDlg( &m_mapUserToPassword );
	BOOL			bFlag = FALSE;
	CString			strWarning;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();

	while( 1 ){

		if( loginDlg.DoModal() == IDOK ){
			CString				strPSD;

			if (m_mapUserToPassword.Lookup( loginDlg.m_strUser, /*(LPCTSTR&)*/strPSD ) == FALSE ){
				strWarning.Format("Sorry, No this User! Please Check it!");
				if( AfxMessageBox(  strWarning, 
									MB_ICONINFORMATION| MB_RETRYCANCEL ) != IDRETRY ){
					bFlag = FALSE;
					break;	
				}
			}
			else{
				if( strPSD == loginDlg.m_strPSD ){
					bFlag = TRUE;
					m_strUser = loginDlg.m_strUser;
					pFrame->m_wndToolBar.SetUser( m_strUser );
					break;
				}
				else{
					strWarning.Format("Sorry, Password Error! Please Check it!");
					if( AfxMessageBox(  strWarning, 
										MB_ICONINFORMATION| MB_RETRYCANCEL ) != IDRETRY ){
						bFlag = FALSE;
						break;	
					}
				}
			}
		}
		else{
			bFlag = FALSE;
			break;
		}
	}
	return bFlag;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// from UserPSD get the password usd
void CPersonMgrDoc::GetUserPsdInfo(){

	CString			strCmd;
	CString			strKey;
	CString			strPSD;

	m_mapUserToPassword.RemoveAll();

	try{
		if( m_pDaoRecordSet->IsOpen() ){
			m_pDaoRecordSet->Close();
		}
		strCmd.Format( "select * from UserPSD" );
		m_pDaoRecordSet->Open( dbOpenDynaset, strCmd );

		m_pDaoRecordSet->MoveFirst();
		while( m_pDaoRecordSet->IsEOF() == FALSE ){
					
			COleVariant		varValue;

			m_pDaoRecordSet->GetFieldValue( 0, varValue );
			strKey = ChangeVariantToString( varValue, FALSE );
			m_pDaoRecordSet->GetFieldValue( 1, varValue );
			strPSD = ChangeVariantToString( varValue, FALSE );
			m_mapUserToPassword.SetAt( strKey, strPSD );

			m_pDaoRecordSet->MoveNext();
		}
	}
	catch( CDaoException *pException ){
		AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
						MB_ICONEXCLAMATION );
		pException->Delete();
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// add new User
BOOL CPersonMgrDoc::AddUser(CString strUser, CString strPSD){

	COleVariant		varValue;
	CString			strCmd;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );

	try{

		if( pRecordSet->IsOpen() ){
			pRecordSet->Close();
		}
		strCmd.Format( "select * from UserPSD" );
		pRecordSet->Open( dbOpenDynaset, strCmd );

		pRecordSet->AddNew();

		GetVariantFromString( varValue, dbText, strUser );
		pRecordSet->SetFieldValue( 0, varValue );
		GetVariantFromString( varValue, dbText, strPSD );
		pRecordSet->SetFieldValue( 1, varValue );

		pRecordSet->Update();
	}
	catch( CDaoException *pException ){
		AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
						MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
	delete pRecordSet;
	m_mapUserToPassword.SetAt( strUser, strPSD );
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// change the current Password
BOOL CPersonMgrDoc::ChgUserPSD(CString strUser, CString strPSD){

	COleVariant		varValue;
	CString			strCmd;
	CString			strKey;
	BOOL			bFlag = FALSE;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );

	try{

		if( pRecordSet->IsOpen() ){
			pRecordSet->Close();
		}
		strCmd.Format( "select * from UserPSD" );
		pRecordSet->Open( dbOpenDynaset, strCmd );

		pRecordSet->MoveFirst();
		while( pRecordSet->IsEOF() == FALSE ){
			pRecordSet->GetFieldValue( 0, varValue );
			strKey = ChangeVariantToString( varValue, FALSE );
			if( strKey == strUser ){
				bFlag = TRUE ;
				break;
			}
			pRecordSet->MoveNext();
		}
		if( bFlag == FALSE ){
			delete pRecordSet;
			return FALSE;
		}

		pRecordSet->Edit();

		GetVariantFromString( varValue, dbText, strPSD );
		pRecordSet->SetFieldValue( 1, varValue );

		pRecordSet->Update();
	}
	catch( CDaoException *pException ){
		AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
						MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
	delete pRecordSet;
	m_mapUserToPassword.SetAt( strUser, strPSD );
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// delete the current user
BOOL CPersonMgrDoc::DeleteUser(CString strUser){

	COleVariant		varValue;
	CString			strCmd;
	CString			strKey;
	BOOL			bFlag = FALSE;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );

	try{

		if( pRecordSet->IsOpen() ){
			pRecordSet->Close();
		}
		strCmd.Format( "select * from UserPSD" );
		pRecordSet->Open( dbOpenDynaset, strCmd );

		pRecordSet->MoveFirst();
		while( pRecordSet->IsEOF() == FALSE ){
			pRecordSet->GetFieldValue( 0, varValue );
			strKey = ChangeVariantToString( varValue, FALSE );
			if( strKey == strUser ){
				bFlag = TRUE ;
				break;
			}
			pRecordSet->MoveNext();
		}
		if( bFlag == FALSE ){
			delete pRecordSet;
			return FALSE;
		}

		pRecordSet->Delete();
	}
	catch( CDaoException *pException ){
		AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
						MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
	delete pRecordSet;
	m_mapUserToPassword.RemoveKey( strUser );
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// send Email
void CPersonMgrDoc::SendEmail( CString strMail ){

	CString				strCmd;

	if( strMail.Find("@") == -1 || strMail.Find(".") == -1 ){
		AfxMessageBox( "Email address not invalid!", MB_ICONEXCLAMATION );
		return;
	}
	if( strMail.Find("mailto:") == -1 ){
		strCmd = "mailto: "+ strMail;
	}
	ShellExecute(NULL, "Open", strCmd, NULL, NULL, SW_SHOWNORMAL);
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// open internet
void CPersonMgrDoc::OpenInternet(CString strWeb){

	CString				strCmd;

	strCmd = strWeb;
	strCmd.MakeLower();
	if( strCmd.Find("http://") == -1 ){
		strCmd = "http://"+strWeb;
	}
	ShellExecute(NULL, "Open", strCmd, NULL, NULL, SW_SHOWNORMAL);
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Plan Task Alarm
// PARAMETERS curDate DateTime;
// SELECT [Alarm Melody], [Plan Note]
// FROM [Plan Task]
// WHERE [Plan Time]=curDate And [Alarm Enable]=True;
BOOL CPersonMgrDoc::IsPlanTaskAlarm(CString &strNote, CString &strMelody){

	COleVariant		varValue;
	CString			strValue;
	CTime			time;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );
	CDaoQueryDef	queryDef( m_pDaoDB );

	time = CTime::GetCurrentTime();
	strValue = time.Format("%Y-%m-%d %H:%M:%S");	
		
	try{
		queryDef.Open( "QueryPlanTask" );
		GetVariantFromString( varValue, dbDate, strValue );
		queryDef.SetParamValue( 0, varValue );
		pRecordSet->Open( &queryDef );

		pRecordSet->MoveFirst();
		if( pRecordSet->IsEOF() == FALSE ){

			pRecordSet->GetFieldValue( 0, varValue );
			strMelody = ChangeVariantToString( varValue, FALSE );

			pRecordSet->GetFieldValue( 1, varValue );
			strNote = ChangeVariantToString( varValue, FALSE );			
			delete pRecordSet;
			return TRUE;
		}
		else{
			delete pRecordSet;
			return FALSE;
		}
	}
	catch( CDaoException *pException ){
		//AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
		//				MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Week Alarm
// SELECT [Week], [Time], [Alarm Melody], [Note]
// FROM [Alarm By Week]
// WHERE [Alarm Enable]=True;

BOOL CPersonMgrDoc::IsWeekAlarm(CString &strNote, CString &strMelody){
	
	COleVariant		varValue;
	COleDateTime	dateTime;
	CString			strWeek;
	CString			strCurWeek;
	BOOL			bFlag = FALSE;
	CTime			time;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );
	CDaoQueryDef	queryDef( m_pDaoDB );

	time = CTime::GetCurrentTime();
	strCurWeek = time.Format("%A");
	// 变成全部小写
	strCurWeek.MakeLower();

	try{
		queryDef.Open( "QueryWeekAlarm" );
		pRecordSet->Open( &queryDef );

		pRecordSet->MoveFirst();
		while( pRecordSet->IsEOF() == FALSE ){
			
			// get weekday
			pRecordSet->GetFieldValue( 0, varValue );
			strWeek = ChangeVariantToString( varValue, FALSE );

			if( strWeek.GetLength() >= 3 ){
				strWeek.MakeLower();

				if( strCurWeek.Find( strWeek ) != -1 ){
					// get the Time
					pRecordSet->GetFieldValue( 1, varValue );
					dateTime = varValue;

					if( dateTime.GetHour() == time.GetHour() &&
						dateTime.GetMinute() == time.GetMinute() &&
						dateTime.GetSecond() == time.GetSecond() ){

						pRecordSet->GetFieldValue( 2, varValue );
						strMelody = ChangeVariantToString( varValue, FALSE );

						pRecordSet->GetFieldValue( 3, varValue );
						strNote = ChangeVariantToString( varValue, FALSE );

						bFlag = TRUE;
						break;
					}
				}
			}
			pRecordSet->MoveNext();
		}
		if( bFlag == FALSE ){
			delete pRecordSet;
			return FALSE;
		}
		else{		
			delete pRecordSet;
			return TRUE;
		}
	}
	catch( CDaoException *pException ){
		//AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
		//				MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Day Alarm
// SELECT [Alarm By Day].Time, [Alarm By Day].[Alarm Melody], [Alarm By Day].Note
// FROM [Alarm By Day]
// WHERE ((([Alarm By Day].[Alarm Enable])=True));

BOOL CPersonMgrDoc::IsDayAlarm(CString &strNote, CString &strMelody){

	COleVariant		varValue;
	COleDateTime	dateTime;
	BOOL			bFlag = FALSE;
	CTime			time;
	CDaoRecordset*	pRecordSet = new CDaoRecordset( m_pDaoDB );
	CDaoQueryDef	queryDef( m_pDaoDB );

	time = CTime::GetCurrentTime();

	try{
		queryDef.Open( "QueryDayAlarm" );
		pRecordSet->Open( &queryDef );

		pRecordSet->MoveFirst();
		while( pRecordSet->IsEOF() == FALSE ){
			
			// get the Time
			pRecordSet->GetFieldValue( 0, varValue );
			dateTime = varValue;

			if( dateTime.GetHour() == time.GetHour() &&
				dateTime.GetMinute() == time.GetMinute() &&
				dateTime.GetSecond() == time.GetSecond() ){

				pRecordSet->GetFieldValue( 1, varValue );
				strMelody = ChangeVariantToString( varValue, FALSE );

				pRecordSet->GetFieldValue( 2, varValue );
				strNote = ChangeVariantToString( varValue, FALSE );

				bFlag = TRUE;
				break;
			}
			pRecordSet->MoveNext();
		}
		if( bFlag == FALSE ){
			delete pRecordSet;
			return FALSE;
		}
		else{		
			delete pRecordSet;
			return TRUE;
		}
	}
	catch( CDaoException *pException ){
		//AfxMessageBox(	pException->m_pErrorInfo->m_strDescription, 
		//				MB_ICONEXCLAMATION );
		pException->Delete();
		delete pRecordSet;
		return FALSE;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
BOOL CPersonMgrDoc::IsShutDownTime(){

	CTime			time;
	CString			strTime;
	CString			strTmp;
	int				nHour = 0, nMinute = 0, nSecond = 0;
	int				nPos;
	BOOL			bFlag = FALSE;

	time = CTime::GetCurrentTime();
	strTime = m_strTime;

	if( m_bAutoShutDown == FALSE ){
		return FALSE;
	}

	nPos = strTime.Find(':');
	if( nPos != -1 ){
		strTmp = strTime.Left( nPos );
		strTime = strTime.Mid( nPos + 1 );
		nHour = atoi( strTmp.GetBuffer(0) );
		strTmp.ReleaseBuffer();

		nPos = strTime.Find(':');
		if( nPos != -1 ){
			strTmp = strTime.Left( nPos );
			strTime = strTime.Mid( nPos + 1 );
			nMinute = atoi( strTmp.GetBuffer(0) );
			nSecond = atoi( strTime.GetBuffer(0) );

			strTmp.ReleaseBuffer();
			strTime.ReleaseBuffer();
		}
	}
	if( time.GetHour() == nHour &&
		time.GetMinute() == nMinute &&
		time.GetSecond() == nSecond ){
		bFlag =  TRUE;
	}
	else{
		bFlag =  FALSE;
	}
	if( bFlag == TRUE ){
		CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->AutoShutDown();
	}
	return bFlag;
}
////////////////////////////////////////////////////////////////////////////
// The system calls this to obtain the cursor to display while the user drags
// the minimized window.
// 初始化数据
void CPersonMgrDoc::InitUserData(){
	
	// 初始化数据
	CString			strAppName;
	CString			strKey;
	CString			strValue;
	int				nRes;

	strAppName = "PersonMgr";
	strKey = "Version";

	nRes = GetPrivateProfileString( strAppName, 
		strKey, 
		"",
		strValue.GetBuffer(101),
		100, 
		GetPrivateFileName() );

	strValue.ReleaseBuffer( );

	if( nRes != -1 ){
		strValue = strValue.Left(nRes);
	}
	// 初始化数据
	if( strValue.Find("PersonMgr") == -1 ){

		strValue = "PersonMgr V1.08";
		WritePrivateProfileString( strAppName, strKey, strValue, GetPrivateFileName() );
		SetPrivateInfo( );		
	}
	// 读数据
	else{
		GetPrivateInfo( );	
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Get Profile value
void CPersonMgrDoc::GetPrivateInfo(){

	CString			strAppName;
	CString			strKey;
	CString			strValue;


	strAppName = "Settings";

	strKey="AutoShutDown On/Off";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetPrivateFileName() );
	strValue.ReleaseBuffer( );	
	if( strValue.Find("ON") != -1 ){
		m_bAutoShutDown = TRUE;
	}
	else{
		m_bAutoShutDown = FALSE;
	}

	strKey="AutoShutDown Time";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetPrivateFileName() );
	strValue.ReleaseBuffer( );	
	m_strTime = strValue;


	strKey="LANG";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetPrivateFileName() );
	strValue.ReleaseBuffer( );	
	if( strValue.Find("EN") != -1 ){
		m_nLangID = 0;
	}
	else{
		m_nLangID = 1;
	}

	
	strKey="DYNAMICC";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetPrivateFileName() );
	strValue.ReleaseBuffer( );	
	if( strValue.Find("TRUE") != -1 ){
		m_bDynamic = TRUE;
	}
	else{
		m_bDynamic = FALSE;
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// Get Profile value
void CPersonMgrDoc::SetPrivateInfo(){

	CWinApp*		pApp = AfxGetApp();	
	CString			strAppName;
	CString			strKey;
	CString			strValue;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	strAppName = "Settings";
	strKey="AutoShutDown On/Off";
	if( m_bAutoShutDown == TRUE ){
		strValue = "ON";
	}
	else{
		strValue = "OFF";
	}
	WritePrivateProfileString( strAppName, strKey, strValue, GetPrivateFileName() );

	
	strKey="AutoShutDown Time";
	strValue = m_strTime;
	WritePrivateProfileString( strAppName, strKey, strValue, GetPrivateFileName() );

	if( pFrame != NULL ){

		strKey="LANG";
		if( pFrame->GetLangID() == 0 ){
			strValue = "EN";
		}
		else{
			strValue = "CH";
		}
		WritePrivateProfileString( strAppName, strKey, strValue, GetPrivateFileName() );

		strKey="DYNAMICC";
		if( pFrame->IsDynamicDlg() ){
			strValue = "TRUE";
		}
		else{
			strValue = "FALSE";
		}
		WritePrivateProfileString( strAppName, strKey, strValue, GetPrivateFileName() );
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
void CPersonMgrDoc::SetSomeStatus(){

	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
	CString			strText;

	if( m_bAutoShutDown == TRUE ){
		strText = "Auto Shut Down On " + m_strTime;
	}
	else{
		strText.Empty();
	}

	pFrame->m_wndStatusBar.SetPaneText( 
				pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_AUTO),
				strText );
	
	strText = "Registered!";

	pFrame->m_wndStatusBar.SetPaneText( 
			pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_REGISTER),
			strText );

	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
// V1.08 modify 取消注册机制
void CPersonMgrDoc::JudgeRegister(){
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
int CPersonMgrDoc::GetDayCount(CTime time){

	int				nCnt = 0;
	int				nYear, nMonth, nDay;

	nYear = time.GetYear();
	nMonth = time.GetMonth();
	nDay = time.GetDay();

	nYear -= 2003;
	nCnt = nYear * 365 + nMonth *30 + nDay;
	return nCnt;

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
void CPersonMgrDoc::EmptyArray(CStringArray& strArray){

	strArray.RemoveAll();
	strArray.FreeExtra();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
void CPersonMgrDoc::EmptyArray(CUIntArray& strArray){


	strArray.RemoveAll();
	strArray.FreeExtra();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
void CPersonMgrDoc::EmptyMapString(CMapStringToString& mapString){

	mapString.RemoveAll();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
void CPersonMgrDoc::DrawLine(CDC *pDC, int nLeft, int nTop, 
							 int nRight, int nBottom, int nPenStyle, int nWidth){
	CPen			nPen;
	CPen			*pOldPen;

	nPen.CreatePen(nPenStyle, nWidth, RGB(0,0,0));
	pOldPen = pDC->SelectObject(&nPen);
	pDC->MoveTo(nLeft, nTop);
	pDC->LineTo(nRight, nBottom);
	pDC->SelectObject(pOldPen);
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrDoc message handlers
// some status set
// ini文件的路径
CString	CPersonMgrDoc::GetPrivateFileName( void ){
	return GetModulePath()+"\\PersonMgr.ini";
}