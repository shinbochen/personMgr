// PersonMgrListView.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "PersonMgrListView.h"
#include "ctrlExt.h"
#include "MenuEx.h"
#include "MainFrm.h"
#include "EditDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView

IMPLEMENT_DYNCREATE(CPersonMgrListView, CListView)

CPersonMgrListView::CPersonMgrListView(){
	m_crBack = RGB( 250, 250, 250 );
	m_bAsc = TRUE;
	m_nSortedCol = -1;
}

CPersonMgrListView::~CPersonMgrListView(){

}


BEGIN_MESSAGE_MAP(CPersonMgrListView, CListView)
	//{{AFX_MSG_MAP(CPersonMgrListView)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(IDC_INSERT, OnInsert1)
	ON_COMMAND(IDC_DELETE, OnDelete1)
	ON_COMMAND(IDC_MODIFY, OnModify1)
	ON_COMMAND(IDC_REFRESH, OnRefresh1)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(IDC_EMAIL, OnEmail)
	ON_COMMAND(IDC_BROWSE, OnBrowse)
	ON_UPDATE_COMMAND_UI(IDC_EMAIL, OnUpdateEmail)
	ON_UPDATE_COMMAND_UI(IDC_BROWSE, OnUpdateBrowse)
	ON_COMMAND(IDC_COPYEMAIL, OnCopyemail)
	ON_COMMAND(IDC_COPYWEB, OnCopyweb)
	ON_COMMAND(IDC_REQUERY, OnRefresh1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView drawing

void CPersonMgrListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView diagnostics

#ifdef _DEBUG
void CPersonMgrListView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonMgrListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonMgrDoc* CPersonMgrListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonMgrDoc)));
	return (CPersonMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers

void CPersonMgrListView::OnInitialUpdate(){

	CListView::OnInitialUpdate();
	
	GetDocument()->m_pListView = this;
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// create
int CPersonMgrListView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CListCtrlEx&		listCtrl = (CListCtrlEx&)GetListCtrl();
	CHeaderCtrl*		pHeadCtrl = listCtrl.GetHeaderCtrl();

	listCtrl.SetExtendedStyle( listCtrl.GetExtendedStyle() |
							   LVS_EX_TRACKSELECT | 
							   LVS_EX_FULLROWSELECT | 
							   LVS_EX_GRIDLINES |
							   LVS_EX_SUBITEMIMAGES );
	listCtrl.SetTextBkColor( m_crBack );	

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// create
BOOL CPersonMgrListView::PreCreateWindow(CREATESTRUCT& cs) {

	cs.style |= LVS_REPORT |/* LVS_NOSORTHEADER |*/ LVS_SINGLESEL | LVS_SHOWSELALWAYS;	
	return CListView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// create
void CPersonMgrListView::InitView(){

	CPersonMgrDoc*		pDoc = GetDocument();
	CListCtrlEx&		listCtrl = (CListCtrlEx&)GetListCtrl();
	CString				strKey;
	int					nCnt = 0;
	int					nLen = 0;
	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );

	EraseList();
	if( pDoc->m_nType == NONE ){
		return;
	}

	nLen = pDoc->m_arrColumn.GetSize();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		strKey = pDoc->m_arrColumn.GetAt( nCnt );
		strKey = pFrame->GetDispPhrase( strKey );
		listCtrl.AddColumn( strKey, nCnt );
	}
	m_nColumn = nLen;
	Refresh();
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// erase the previous list
void CPersonMgrListView::EraseList(){

	CListCtrlEx			&listCtrl= (CListCtrlEx &)GetListCtrl();

	listCtrl.DeleteAllItems();
	while( listCtrl.DeleteColumn( 0 ) );
	UpdateWindow();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// erase the previous list
void CPersonMgrListView::Refresh(){

	CPersonMgrDoc*		pDoc = GetDocument();
	CListCtrlEx			&listCtrl= (CListCtrlEx &)GetListCtrl();
	CDaoRecordset*		pRecordSet = NULL;
	int					nItem = 0;
	int					nSubItem = 0;

	if( IsIconic() ){
		return;
	}
	ASSERT( pDoc->m_pDaoDB != NULL );
	pRecordSet = pDoc->m_pDaoRecordSet;

	listCtrl.DeleteAllItems();

	if( pDoc->m_nType == NONE ){
		return;
	}

	if( pRecordSet->IsOpen() == TRUE ){
		pRecordSet->Close();
	}

	// open the table use the current cmd
	pRecordSet->m_strFilter.Empty();
	try{
		if( pDoc->m_nType == INPUT ){

			CString				strFilter;
			CDaoTableDef		tableDef( pDoc->m_pDaoDB );

			strFilter = pDoc->GetFilterString();

			tableDef.Open( pDoc->m_curTable );
			pRecordSet->m_strFilter = strFilter;
			pRecordSet->m_strSort = GetSortString();
			strFilter.Format( "select * from [%s] ", pDoc->m_curTable );
			pRecordSet->Open( dbOpenDynaset, strFilter );
			
			//pRecordSet->Open( &tableDef, dbOpenDynaset );
			strFilter = pRecordSet->GetSQL();

		}
		else{

			CDaoQueryDef		queryDef( pDoc->m_pDaoDB );

			queryDef.Open( pDoc->m_curTable );
			if( queryDef.GetParameterCount() > 0 ){
				int					nCnt, nLen;
				CString				strKey;
				CString				strValue;

				GetPreDataValue( pDoc->m_arrParam, -1 );

				CEditDlg editDlg( &pDoc->m_arrParam, 
								  &pDoc->m_mapParamToDataType,
								  &m_mapDataValue, 
								  &pDoc->m_mapParamToHelpInfo );
				editDlg.SetDlgTitle( "Parameter Input..." );

				if( editDlg.DoModal() != IDOK ){
					return;
				}
				
				nLen = pDoc->m_arrParam.GetSize();
				for( nCnt = 0; nCnt < nLen; nCnt++ ){

					COleVariant			varValue;
					short				nDataType;

					nDataType = pDoc->m_arrParamType.GetAt( nCnt );
					strKey = pDoc->m_arrParam.GetAt( nCnt );
					strValue = m_mapDataValue[strKey];
					
					if( GetVariantFromString( varValue, nDataType, strValue ) == FALSE ){
						MessageBox( "parameter not valid" );
						return;
					}
					queryDef.SetParamValue( nCnt, varValue );
				}
				pRecordSet->Open( &queryDef );
			}
			else{
				pRecordSet->Open( &queryDef );
			}
		}

		pRecordSet->MoveFirst();
		while( pRecordSet->IsEOF() == FALSE ){

			int				nCnt = 0;		
			COleVariant		varValue;
			CString			strValue;
			CDaoFieldInfo	fieldInfo;
			BOOL			bSimpleTime;
			
			nSubItem = 0;

			for ( nCnt = 0; nSubItem < m_nColumn; nCnt++ ){
				
				pRecordSet->GetFieldValue( nCnt, varValue );
				pRecordSet->GetFieldInfo( nCnt, fieldInfo );
				
				bSimpleTime = pDoc->IsSimpleTimeType( fieldInfo.m_strName, 
													  fieldInfo.m_nType );

				if( fieldInfo.m_strName.CollateNoCase( "ID" ) != 0 ){
					strValue = ChangeVariantToString( varValue, bSimpleTime );
					listCtrl.AddItem( nItem, nSubItem, strValue );
					nSubItem++;
				}
			}		
			nItem++;
			pRecordSet->MoveNext();
		}

		m_nSum = nItem;
		//设置状态栏最左端pane为0的字符。
		CString			strStatus;

		strStatus.Format( "Loaded %d records", nItem );
		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		pFrame->SetMessageText(strStatus);
	}
	catch(CDaoException *pExcp)	{   
		AfxMessageBox( pExcp->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION );
		pExcp->Delete();
		return ;
	}
	AdjustColumnWidths();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// Auto Adjust Column Width
void CPersonMgrListView::AdjustColumnWidths(){

	CListCtrl&			listCtrl = (CListCtrl&)GetListCtrl();
	CHeaderCtrl*		pHeadCtl = listCtrl.GetHeaderCtrl();
	int					nLen = 0;
	
	nLen = pHeadCtl->GetItemCount();
	for( int nCnt = 0; nCnt<nLen; nCnt++){
		listCtrl.SetColumnWidth(nCnt,/*LVSCW_AUTOSIZE |*/ LVSCW_AUTOSIZE_USEHEADER );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// update delete
void CPersonMgrListView::OnUpdateDeleteL(CCmdUI *pCmdUI){

	pCmdUI->Enable( CanDelete() );
	return;

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// update Modify
void CPersonMgrListView::OnUpdateModifyL(CCmdUI *pCmdUI){

	pCmdUI->Enable( CanModify() );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// update insert
void CPersonMgrListView::OnUpdateInsertL(CCmdUI *pCmdUI){
	
	pCmdUI->Enable( CanInsert() );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// update insert
void CPersonMgrListView::OnUpdateRefresh(CCmdUI *pCmdUI){

	pCmdUI->Enable( CanRefresh( ) );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// insert new record
void CPersonMgrListView::OnInsert(){


	CPersonMgrDoc*		pDoc = GetDocument();
	CDaoRecordset*		pRecordSet = pDoc->m_pDaoRecordSet;
	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd();

	ASSERT( pRecordSet != NULL );

	GetPreDataValue( pDoc->m_arrColumn, -1 );

	CEditDlg			editDlg( &pDoc->m_arrColumn,
								 &pDoc->m_mapColumnToDataType,
								 &m_mapDataValue,
								 &pDoc->m_mapColumnToHelpInfo );
	editDlg.SetDlgTitle( "New Record..." );

	if( editDlg.DoModal() == IDOK ){

		CString			strColumn;
		CString			strValue;

		int				nCnt, nLen;

		try{
			pRecordSet->AddNew();
			
			nLen = pDoc->m_arrColumn.GetSize();
			ASSERT( nLen > 0 );

			for( nCnt = 0; nCnt < nLen; nCnt++ ){
				COleVariant			varValue;
				short				nDataType;

				strColumn = pDoc->m_arrColumn.GetAt( nCnt );
				strValue = m_mapDataValue[strColumn];
				nDataType = pDoc->m_arrColumnType.GetAt( nCnt );
				if( GetVariantFromString( varValue, nDataType, strValue ) == FALSE ){
					MessageBox( "Data value not valid" );
					return;
				}

				pRecordSet->SetFieldValue( strColumn, varValue );
			}
			pRecordSet->Update();
		}
		catch( CDaoException *pExcp ){
			AfxMessageBox( pExcp->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION );
			pExcp->Delete();
			return ;
		}
		Refresh();
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// modify record
void CPersonMgrListView::OnModify(){

	CListCtrlEx&		listCtrl = (CListCtrlEx&)GetListCtrl();
	CPersonMgrDoc*		pDoc = GetDocument();
	CDaoRecordset*		pRecordSet = pDoc->m_pDaoRecordSet;
	int					nRow;

	ASSERT( pRecordSet != NULL );
	nRow = listCtrl.GetNextItem( -1, LVNI_SELECTED );
	// ASSERT( nRow != -1 );
	if( nRow == -1 ){
		return;
	}

	GetPreDataValue( pDoc->m_arrColumn, nRow );

	CEditDlg			editDlg( &pDoc->m_arrColumn,
								 &pDoc->m_mapColumnToDataType,
								 &m_mapDataValue,
								 &pDoc->m_mapColumnToHelpInfo );
	editDlg.SetDlgTitle( "Modify Record..." );

	if( editDlg.DoModal() == IDOK ){

		CString			strColumn;
		CString			strValue;

		int				nCnt, nLen;

		try{
			pRecordSet->MoveFirst();
			for( nCnt = 0; nCnt < nRow; nCnt++ ){
				pRecordSet->MoveNext();		
			}
			pRecordSet->Edit();
			
			nLen = pDoc->m_arrColumn.GetSize();
			ASSERT( nLen > 0 );

			for( nCnt = 0; nCnt < nLen; nCnt++ ){
				COleVariant			varValue;
				short				nDataType;

				strColumn = pDoc->m_arrColumn.GetAt( nCnt );
				strValue = m_mapDataValue[strColumn];
				nDataType = pDoc->m_arrColumnType.GetAt( nCnt );
				if( GetVariantFromString( varValue, nDataType, strValue ) == FALSE ){
					MessageBox( "Data value not valid" );
					return;
				}

				pRecordSet->SetFieldValue( strColumn, varValue );
			}
			pRecordSet->Update();
		}
		catch( CDaoException *pExcp ){
			AfxMessageBox( pExcp->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION );
			pExcp->Delete();
			return ;
		}
		Refresh();
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// delete the current record
void CPersonMgrListView::OnDelete(){

	int					nRow;
	CListCtrlEx&		listCtrl = (CListCtrlEx&)GetListCtrl();
	CPersonMgrDoc*		pDoc = GetDocument();
	CDaoRecordset*		pRecordSet = pDoc->m_pDaoRecordSet;

	if( pRecordSet->IsOpen() == FALSE ){
		return;
	}

	ASSERT( pRecordSet != NULL );
	/*if( pRecordSet->IsDeleted() == FALSE){
		MessageBox(	"Sorry, you don't allow delete this item", 
					"Delete Reject",
					MB_OK| MB_ICONHAND );
		return;
	}*/

	nRow = listCtrl.GetNextItem( -1, LVNI_SELECTED );
	// ASSERT( nRow != -1 );
	if( nRow == -1 ){
		return;
	}

	if( MessageBox(	"Are you Sure delete the select item?", 
					"Delete Caution",
					MB_YESNO|MB_ICONHAND ) == IDYES ){
		try{
			pRecordSet->MoveFirst();
			for( int nCnt = 0; nCnt < nRow; nCnt++ ){
				pRecordSet->MoveNext();
			}
			pRecordSet->Delete();
		}
		catch( CDaoException *pExcp ){
			AfxMessageBox( pExcp->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION );
			pExcp->Delete();
			return ;
		}
		Refresh();
	}	
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// get the current select item value
// if nItem = -1 then only clear buffer
void CPersonMgrListView::GetPreDataValue(CStringArray &arrColumn, int nItem){

	int				nCnt, nLen;
	CString			strKey, strValue;
	CListCtrlEx&	listCtrl = (CListCtrlEx&)GetListCtrl();

	m_mapDataValue.RemoveAll();

	nLen = arrColumn.GetSize( );
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		strKey = arrColumn.GetAt( nCnt );
		if ( nItem == -1 ){
			strValue = " ";
		}
		else{
			strValue = listCtrl.GetItemText( nItem, nCnt );
		}
		m_mapDataValue.SetAt( strKey, strValue );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// mouse right click
void CPersonMgrListView::OnRButtonDown(UINT nFlags, CPoint point) {

	CPersonMgrDoc*			pDoc = GetDocument();
	CMainFrame*				pFrame = (CMainFrame*)AfxGetMainWnd( );


	CListView::OnRButtonDown(nFlags, point);

	CMenu				Menu;
	CMenu*				pSubMenu;

	ClientToScreen( &point );

	if( pDoc->m_nType == NONE ){
		return;
	}
	else if( pDoc->m_nType == QUERY ){
		pSubMenu = new CMenu();

		pSubMenu->CreatePopupMenu( );
		pSubMenu->AppendMenu( MF_STRING, IDC_REQUERY, pFrame->GetDispPhrase("&Re-Query") );
		pSubMenu->AppendMenu( MF_STRING, IDC_REFRESH, pFrame->GetDispPhrase("Refresh\tF5") );
	}
	else{

		pSubMenu = new CMenu();

		pSubMenu->CreatePopupMenu( );

		if( CanRefresh() ){
			pSubMenu->AppendMenu( MF_STRING, IDC_REFRESH, pFrame->GetDispPhrase("Refresh\tF5") );
		}
		if( CanInsert() ){
			pSubMenu->AppendMenu( MF_STRING, IDC_INSERT, pFrame->GetDispPhrase("New\tCtrl+I") );
		}
		if( CanModify() ){
			pSubMenu->AppendMenu( MF_STRING, IDC_MODIFY, pFrame->GetDispPhrase("Modify\tCtrl+M") );
		}
		if( CanDelete() ){
			pSubMenu->AppendMenu( MF_STRING, IDC_DELETE, pFrame->GetDispPhrase("Delete\tCtrl+D") );
		}
		if( CanEmail() ){
			pSubMenu->AppendMenu(MF_SEPARATOR, 0);
			pSubMenu->AppendMenu(MF_STRING, IDC_EMAIL, pFrame->GetDispPhrase("&Email To"));
			pSubMenu->AppendMenu(MF_STRING, IDC_COPYEMAIL, pFrame->GetDispPhrase("Copy Email Addr\tCtrl+E" ));
		}
		if( CanBrowse() ){
			pSubMenu->AppendMenu(MF_SEPARATOR, 0);
			pSubMenu->AppendMenu(MF_STRING, IDC_BROWSE, pFrame->GetDispPhrase("&Web Browser"));
			pSubMenu->AppendMenu(MF_STRING, IDC_COPYWEB, pFrame->GetDispPhrase("Copy Website Addr\tCtrl+B" ));
		}
	}

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_LEFTBUTTON, point.x, point.y, this );
	pSubMenu->DestroyMenu( );
	
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
// mouse right click
void CPersonMgrListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult){

	OnModify();
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView message handlers
void CPersonMgrListView::OnInsert1() {
	OnInsert();
}
void CPersonMgrListView::OnDelete1() {
	OnDelete();
}

void CPersonMgrListView::OnModify1() {
	OnModify();
}

void CPersonMgrListView::OnRefresh1() {
	Refresh();
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanRefresh(){
	return TRUE;
	return CanInsert();
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanInsert(){

	CPersonMgrDoc*			pDoc = GetDocument();

	if( pDoc->m_nType == INPUT ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanDelete(){
	return  CanModify();
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanModify(){

	CPersonMgrDoc*			pDoc = GetDocument();
	CListCtrlEx&			listCtrl = (CListCtrlEx&)GetListCtrl();
	int						nRow;

	if( pDoc->m_nType == NONE || pDoc->m_nType == QUERY ){
		return FALSE;
	}
	else{
		nRow = listCtrl.GetNextItem( -1, LVNI_SELECTED );
		if( nRow == -1  ){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	
	//LV_KEYDOWN*		pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	if( nChar == VK_DELETE ){
		OnDelete();
	}
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::OnEraseBkgnd(CDC* pDC) {

	CRect			rect;
	if( IsIconic() ){
		return TRUE;
	}
	GetClientRect( &rect );
	pDC->FillSolidRect( &rect, m_crBack );
	return TRUE;	
	//return CListView::OnEraseBkgnd(pDC);
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult){

	NM_LISTVIEW*	pNMListView = (NM_LISTVIEW*)pNMHDR;
	CMainFrame*		pFrame = NULL;
	CPersonMgrDoc*	pDoc = GetDocument();

	*pResult = 0;
	if( pDoc->m_nType != INPUT ){
		return;
	}

	if( pNMListView->iSubItem == m_nSortedCol ){
		m_bAsc = !m_bAsc;
	}
	else{
		m_bAsc = TRUE;
		m_nSortedCol = pNMListView->iSubItem;
	}
	pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->Refresh();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
CString CPersonMgrListView::GetSortString( ){
	
	CString			strSort;
	CListCtrlEx&	listCtrl = (CListCtrlEx&)GetListCtrl();
	LVCOLUMN		lvColumn;
	TCHAR			szColumnName[256];
	CString			strColumnName;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	if( m_nSortedCol == -1 ){
		strSort.Empty();		
	}
	else{
		lvColumn.mask = LVCF_TEXT;
		lvColumn.cchTextMax = 255;
		lvColumn.pszText = szColumnName;
		listCtrl.GetColumn( m_nSortedCol, &lvColumn );
		strColumnName = szColumnName;

		strColumnName = pFrame->GetReversePhrase( strColumnName );
		strSort.Format( "[%s]", strColumnName );
		if( m_bAsc ){
			strSort += _T(" ASC ");
		}
		else{
			strSort += _T(" DESC ");
		}
	}
	return strSort;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnEmail() {
	CString					strEmail;
	CPersonMgrDoc*			pDoc = GetDocument();

	strEmail = GetEmail( );
	if( strEmail.IsEmpty() ){
		MessageBox( "No Email address!" );
	}
	else{
		pDoc->SendEmail( strEmail );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnUpdateEmail(CCmdUI* pCmdUI) {

	pCmdUI->Enable( CanEmail() );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanEmail(){

	BOOL					bFlag = FALSE;
	CPersonMgrDoc*			pDoc = GetDocument();
	CString					strInfo;

	strInfo.LoadString( IDS_ENABLEEMAIL );
	if( strInfo.Find( pDoc->m_curTable ) == -1 ){
		bFlag = FALSE;
	}
	else{
		bFlag = CanModify();
	}
	return bFlag;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
CString CPersonMgrListView::GetEmail(){

	CPersonMgrDoc*			pDoc = GetDocument();
	CString					strKeyColumn;
	CString					strValue;

	strKeyColumn = GetKeyColumn( IDS_ENABLEEMAIL );
	strValue = GetCurSelValueFromKeyCol( strKeyColumn );
	return strValue;

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
CString CPersonMgrListView::GetWebSite(){

	CPersonMgrDoc*			pDoc = GetDocument();
	CString					strKeyColumn;
	CString					strValue;

	strKeyColumn = GetKeyColumn( IDS_ENABLEWEB );
	strValue = GetCurSelValueFromKeyCol( strKeyColumn );
	return strValue;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnBrowse() {

	CString					strWebSite;
	CPersonMgrDoc*			pDoc = GetDocument();

	strWebSite = GetWebSite( );
	if( strWebSite.IsEmpty() ){
		MessageBox( "No Website address!" );
	}
	else{
		pDoc->OpenInternet( strWebSite );
	}
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
void CPersonMgrListView::OnUpdateBrowse(CCmdUI* pCmdUI) {
	pCmdUI->Enable( CanBrowse() );
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
BOOL CPersonMgrListView::CanBrowse(){

	BOOL					bFlag = FALSE;
	CPersonMgrDoc*			pDoc = GetDocument();
	CString					strInfo;

	strInfo.LoadString( IDS_ENABLEWEB );
	if( strInfo.Find( pDoc->m_curTable ) == -1 ){
		bFlag = FALSE;
	}
	else{
		bFlag = CanModify();
	}
	return bFlag;	

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// 根据给定资源得到当前表的的关键列
CString CPersonMgrListView::GetKeyColumn(UINT nID){

	int						nLen;
	CString					strInfo;
	CPersonMgrDoc*			pDoc = GetDocument();

	strInfo.LoadString( nID );
	nLen = strInfo.Find( pDoc->m_curTable );
	ASSERT( nLen != -1 );

	strInfo = strInfo.Mid( nLen );

	nLen = strInfo.Find(":");
	strInfo = strInfo.Mid( nLen + 1 );
	nLen = strInfo.Find(";");
	strInfo = strInfo.Left( nLen );	
	return strInfo;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// 根据给定列名得到当前所选值
CString CPersonMgrListView::GetCurSelValueFromKeyCol(CString strKeyCol){
	
	CListCtrlEx&			listCtrl = (CListCtrlEx&)GetListCtrl();
	int						nRow;
	int						nCol;
	CString					strValue;

	nRow = listCtrl.GetNextItem( -1, LVNI_SELECTED );
	if( nRow == -1  ){
		strValue.Empty();
	}
	else{
		nCol = FindColFromName( strKeyCol );
		if( nCol == -1){
			strValue.Empty();
		}
		else{
			strValue = listCtrl.GetItemText( nRow, nCol );
		}
	}
	return strValue;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// 根据给定列名得到列的项目数
int CPersonMgrListView::FindColFromName(CString strColName){

	CListCtrlEx&			listCtrl = (CListCtrlEx&)GetListCtrl();
	CHeaderCtrl*			pHeadCtrl = listCtrl.GetHeaderCtrl();
	LVCOLUMN				lvColumn;
	CMainFrame*				pFrame = (CMainFrame*)AfxGetMainWnd();

	TCHAR					szColumnName[256];
	CString					strColumnName;
	int						nLen;
	int						nCnt;

	nLen = pHeadCtrl->GetItemCount( );

	lvColumn.mask = LVCF_TEXT;
	lvColumn.cchTextMax = 255;
	lvColumn.pszText = szColumnName;

	for( nCnt = 0; nCnt < nLen ; nCnt++ ){
		
		listCtrl.GetColumn( nCnt, &lvColumn );
		strColumnName = szColumnName;
		strColumnName = pFrame->GetReversePhrase( strColumnName );
		if( strColumnName == strColName ){
			return nCnt;
		}
	}
	return -1;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// 得到email 到clipboard
void CPersonMgrListView::OnCopyemail() {

	if( CanEmail() == FALSE ){
		return;
	}

	if( OpenClipboard( ) == FALSE ){
		MessageBox( "Open Clipboard Fail!" );
	}
	else{
		HANDLE				hMem;
		LPVOID				lpVoid;
		CString				strEmail;
		int					nLen;

		strEmail = GetEmail();
		nLen = strEmail.GetLength( );		
		
		EmptyClipboard(); 

		hMem = GlobalAlloc( GMEM_MOVEABLE, nLen+10 );
		lpVoid = GlobalLock( hMem );
		_tcscpy( LPTSTR(lpVoid), strEmail.GetBuffer( 0 ) );
		GlobalUnlock( hMem );

		SetClipboardData( CF_TEXT, hMem );
		CloseClipboard(); 
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// 得到website 到clipboard
void CPersonMgrListView::OnCopyweb() {

	if( CanBrowse() == FALSE ){
		return;
	}

	if( OpenClipboard( ) == FALSE ){
		MessageBox( "Open Clipboard Fail!" );
	}
	else{
		HANDLE				hMem;
		LPVOID				lpVoid;
		CString				strWeb;
		int					nLen;

		strWeb = GetWebSite();
		nLen = strWeb.GetLength( );		
		
		EmptyClipboard(); 

		hMem = GlobalAlloc( GMEM_MOVEABLE, nLen+10 );
		lpVoid = GlobalLock( hMem );
		_tcscpy( LPTSTR(lpVoid), strWeb.GetBuffer( 0 ) );
		GlobalUnlock( hMem );

		SetClipboardData( CF_TEXT, hMem );
		CloseClipboard(); 
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView function
// print
void CPersonMgrListView::PrintBody(int nStartY, CDC *pDC, CPrintInfo *pInfo){
	int				nStart;
	int				nMaxItem;
	CListCtrl		&ctlList = GetListCtrl();
	CHeaderCtrl		*pHeadCtrl = ctlList.GetHeaderCtrl();
	CPersonMgrDoc	*pDoc = GetDocument();
	int				nLeft;			// 左边开始打印的起点
	int				nRight;	
	int				nMaxCol=0;
	int				nStartX =0;
	int				nWidth = 0;
	CSize			nSize;
	CRect			nRect;


	LOGFONT			logFont;
	pDC->GetCurrentFont()->GetLogFont(&logFont);

	
	// 显示head信息
	nLeft = LEFT_BOARDLINE * pDoc->m_nPerMMPixel;
	nRight = nLeft + pDoc->m_nXMaxPixel;

	
	nStartX = nLeft;

	TCHAR	szColumnName[COLUMNVALUEMAX+1];
	nMaxCol	= pHeadCtrl->GetItemCount();

	LVCOLUMN	lvColumn;
	lvColumn.mask = LVCF_TEXT;
	lvColumn.cchTextMax = COLUMNVALUEMAX;
	lvColumn.pszText = szColumnName;

	// 显示列名与一横线
	for(int nIndex = 0; (nIndex <nMaxCol) && (nStartX < nRight); nIndex++){

		ctlList.GetColumn(nIndex, &lvColumn);
		CString		strColumnName;
		strColumnName = szColumnName;
		// 显示此字符串所需的尺寸
		nSize = pDC->GetTextExtent(strColumnName);
		nWidth = ctlList.GetColumnWidth(nIndex) * 10;

		if(nStartX + nWidth > nRight){
			nRect.SetRect(nStartX, nStartY, nRight, nStartY+nSize.cy);
		}
		else{
			nRect.SetRect(nStartX, nStartY, nStartX+nWidth, nStartY+nSize.cy);
		}
		pDC->DrawText(strColumnName, &nRect, DT_BOTTOM|DT_LEFT|DT_SINGLELINE);
		if(nStartX + nSize.cx > nRight){
			pDoc->DrawLine(pDC, nStartX, nStartY+nSize.cy+LINE_HEIGHT, nRight,
					nStartY+nSize.cy+LINE_HEIGHT, PS_SOLID);
		}
		else{
			pDoc->DrawLine(pDC, nStartX, nStartY+nSize.cy+LINE_HEIGHT, nStartX+nSize.cx,
					nStartY+nSize.cy+LINE_HEIGHT, PS_SOLID);
		}
		nStartX += nWidth;
	}
	nStartX = nLeft;
	nStartY += nSize.cy + LINE_HEIGHT*2;

	// 显示行值
	nMaxItem = ctlList.GetItemCount();
	nStart = pInfo->m_nCurPage-1;
	nStart = nStart * pDoc->m_nRowPerPage;
	ASSERT( nStart <= nMaxItem);


	TCHAR		szItem[COLUMNVALUEMAX+1];
	LVITEMA		lvItem;
	lvItem.mask = LVIF_TEXT ;
	//lvItem.iItem = m_iItem;
	lvItem.pszText = szItem;
	lvItem.cchTextMax = COLUMNVALUEMAX;

	for(nIndex = 0; (nIndex< pDoc->m_nRowPerPage) && (nIndex+nStart)< nMaxItem; nIndex++){
		lvItem.iItem = nStart+nIndex;

		for(int nColIndex =0; (nColIndex <nMaxCol) && (nStartX < nRight); nColIndex++){
			CString				strItem;

			lvItem.iSubItem = nColIndex;
			ctlList.GetItem(&lvItem);
			strItem = szItem;

			nSize = pDC->GetTextExtent(strItem);
			nWidth = ctlList.GetColumnWidth(nColIndex)*10;
			if(nStartX + nWidth > nRight){
				nRect.SetRect(nStartX, nStartY, nRight, nStartY+nSize.cy);
			}
			else{
				nRect.SetRect(nStartX, nStartY, nStartX+nWidth, nStartY+nSize.cy);
			}			
			pDC->DrawText(strItem, &nRect, DT_BOTTOM|DT_LEFT|DT_SINGLELINE);
			nStartX += nWidth;
		}		
		nStartX = nLeft;
		nStartY += pDoc->m_nTextHeight;
	}
	return;
}
