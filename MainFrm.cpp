// MainFrm.cpp : implementation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
// include file
#include "stdafx.h"
#include "PersonMgr.h"

#include "MainFrm.h"

#include "PersonMgrTreeView.h"
#include "PersonMgrTitleView.h"
#include "PersonMgrQueryView.h"
#include "PersonMgrListView.h"
#include "PersonMgrDoc.h"

#include "NMUserDlg.h"
#include "TimeDlg.h"
#include "DateDlg.h"
#include "SDSetupDlg.h"


#include "picture.h"

#include <winuser.h>

//BOOL		bFlag = TRUE;
/////////////////////////////////////////////////////////////////////////////
// CONSTATNS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		WM_TRAYMESSAGE	WM_USER+103
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDC_REFRESH, OnRefresh)
	ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateDelete)
	ON_UPDATE_COMMAND_UI(IDC_INSERT, OnUpdateInsert)
	ON_UPDATE_COMMAND_UI(IDC_MODIFY, OnUpdateModify)
	ON_COMMAND(IDC_DELETE, OnDelete)
	ON_COMMAND(IDC_INSERT, OnInsert)
	ON_COMMAND(IDC_MODIFY, OnModify)
	ON_UPDATE_COMMAND_UI(IDC_REFRESH, OnUpdateRefresh)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_COMMAND(IDC_ADDUSER, OnAdduser)
	ON_COMMAND(IDC_CHGPSD, OnChgpsd)
	ON_COMMAND(IDC_CALCULATOR, OnCalculator)
	ON_COMMAND(IDC_SHUTDOWN, OnShutdown)
	ON_COMMAND(IDC_DELETEUSER, OnDeleteuser)
	ON_COMMAND(IDC_SETUP_AUTOSD, OnSetupAutosd)
	ON_COMMAND(IDC_REGISTER, OnRegister)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND( )
	ON_MESSAGE(WM_TRAYMESSAGE,OnTray)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_NCPAINT()
	ON_WM_ACTIVATE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_COMMAND(IDC_HELPINFO, OnHelp)
	ON_UPDATE_COMMAND_UI(IDC_CHINESE, OnUpdateChinese)
	ON_UPDATE_COMMAND_UI(IDC_ENGLISH, OnUpdateEnglish)
	ON_COMMAND(IDC_ENGLISH, OnEnglish)
	ON_COMMAND(IDC_CHINESE, OnChinese)
	ON_COMMAND(IDC_DYNAMIC, OnDynamic)
	ON_UPDATE_COMMAND_UI(IDC_DYNAMIC, OnUpdateDynamic)
	ON_UPDATE_COMMAND_UI(IDC_REGISTER, OnUpdateRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_REGISTER,
	ID_INDICATOR_AUTO,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame(){

}

CMainFrame::~CMainFrame(){

}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame member function
// oncreate
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(
		m_wndStatusBar.CommandToIndex(ID_INDICATOR_AUTO),
		ID_INDICATOR_AUTO,
		0,
		200);
	// TODO: Delete these three lines if you don't want the toolbar to
	// be dockable
	// m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	// EnableDocking(CBRS_ALIGN_ANY);
	// DockControlBar(&m_wndToolBar);

	CString				strVersion;	
	HICON				hIcon;

	m_nMenu.AttachMenu(GetMenu()->m_hMenu, &m_wndToolBar, CSize(16,8) );
	
	strVersion.LoadString( IDS_VERSION );
	SetTitle( strVersion );

	GetShutDownPrivilege();
	hIcon = AfxGetApp()->LoadIcon( IDI_TRAYICON );
	m_oTray.Creat( this, WM_TRAYMESSAGE, "PersonMgr System", hIcon,1);

	// 得到中英文对照的短语
	InitPhrase( );
	// 设为英文
	SetLangID( 1 );
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs){
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// create the client

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext){
	
	if( !m_parSplitWnd.CreateStatic( this, 1, 2 ) ){
		TRACE0("Failed to create the parent splitter!");
		return FALSE;
	}

	if( !m_parSplitWnd.CreateView(	0, 
								0, 
								pContext->m_pNewViewClass, 
								CSize(140,400), 
								pContext ) ){
		TRACE0("Failed to create the Treeview splitter!");
		return FALSE;
	}

	if( !m_subSplitWnd.CreateStatic( &m_parSplitWnd, 
								3, 
								1, 
								WS_CHILD | WS_VISIBLE,
								m_parSplitWnd.IdFromRowCol( 0, 1 ) ) ){
		TRACE0("Failed to create the subtract splitter!");
		return FALSE;
	}

	if( !m_subSplitWnd.CreateView(	0, 
								0, 
								RUNTIME_CLASS(CPersonMgrTitleView),
								CSize(100, 50 ), 
								pContext ) ){
		TRACE0("Failed to create the Title view!");
		return FALSE;
	}

	if( !m_subSplitWnd.CreateView(	1, 
								0, 
								RUNTIME_CLASS(CPersonMgrQueryView),
								CSize(100, 40 ), 
								pContext ) ){
		TRACE0("Failed to create the Query view!");
		return FALSE;
	}

	if( !m_subSplitWnd.CreateView(	2, 
								0, 
								RUNTIME_CLASS(CPersonMgrListView),
								CSize(100, 100 ), 
								pContext ) ){
		TRACE0("Failed to create the List view!");
		return FALSE;
	}
	

	SetActiveView( (CView*) m_parSplitWnd.GetPane(0,0) );
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// Refresh the current function
void CMainFrame::OnRefresh() {

	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );
	pListView->Refresh(); 
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// Refresh the current function
void CMainFrame::Refresh() {
	OnRefresh();
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// delete the current select item
void CMainFrame::OnDelete() {
	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );
	pListView->OnDelete();
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// insert the new record
void CMainFrame::OnInsert() {
	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );
	pListView->OnInsert();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// modify the current select item
void CMainFrame::OnModify() {
	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );
	pListView->OnModify();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// add new user
void CMainFrame::OnAdduser() {
	CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pTitleView->AddOrModifyUser( NEWUSER );
	return;
	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// modify the current user password
void CMainFrame::OnChgpsd() {
	CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pTitleView->AddOrModifyUser( CHGPSD );
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// delete user
void CMainFrame::OnDeleteuser() {
	CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pTitleView->AddOrModifyUser( DELETEUSER );
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// setup auto power off
void CMainFrame::OnSetupAutosd() {

	CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pTitleView->SetAutoShutDown();
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// whether enable delete
void CMainFrame::OnUpdateDelete(CCmdUI* pCmdUI){

	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );
	pListView->OnUpdateDeleteL( pCmdUI );
	return;	
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// whether enable insert
void CMainFrame::OnUpdateInsert(CCmdUI* pCmdUI){

	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );	
	pListView->OnUpdateInsertL( pCmdUI );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// whether enable insert
void CMainFrame::OnUpdateRefresh(CCmdUI* pCmdUI) {

	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );	
	pListView->OnUpdateRefresh( pCmdUI );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
// whether enable modify
void CMainFrame::OnUpdateModify(CCmdUI* pCmdUI){

	CPersonMgrListView*		pListView = NULL;

	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );	
	pListView->OnUpdateModifyL( pCmdUI );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// 
void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!nIDCtl) {
		m_nMenu.MeasureItem(lpMeasureItemStruct);
		return;
	}
	
	CMainFrame::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
/////////////////////////////////////////////////////////////////////////////
// owner draw
void CMainFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!nIDCtl) {
		m_nMenu.DrawItem(lpDrawItemStruct);
		return;
	}
	
	CMainFrame::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
/////////////////////////////////////////////////////////////////////////////
// open calculator
void CMainFrame::OnCalculator(){
	
	ShellExecute( this->m_hWnd, "open", "calc.exe", NULL, NULL, SW_SHOWNORMAL );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// shut down the system
void CMainFrame::OnShutdown() {
	if( ::ExitWindowsEx( EWX_FORCE | EWX_SHUTDOWN | EWX_POWEROFF, 0 ) == TRUE ){
		SendMessage( WM_CLOSE );
	}
	else{
		MessageBox( "Shutdown Fail!");
	}
	return;
}
void CMainFrame::AutoShutDown(){
	OnShutdown();
}

/////////////////////////////////////////////////////////////////////////////
// Register system
void CMainFrame::OnRegister() {

	// V1.08 modify
	/*CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pTitleView->SetRegister( );*/
	return;	
}
void CMainFrame::Register(){

	// V1.08 modify
	// OnRegister();
}

// V1.08 modify

void CMainFrame::OnUpdateRegister(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// 得到关机权利
void CMainFrame::GetShutDownPrivilege(){

	// on Win NT give ourselves the privilege to shutdown the system
	HANDLE				hToken;
	TOKEN_PRIVILEGES	tp;
	LUID				luid;
	::OpenProcessToken( GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) ;
	::LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &luid );
	tp.PrivilegeCount           = 1;
	tp.Privileges[0].Luid       = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	::AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// 销掉托盘
void CMainFrame::OnClose() {
	
	m_oTray.~CTray();
	CFrameWnd::OnClose();
}
///////////////////////////////////////////////////////////////////////
// 最小化窗口
void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam){
	if( nID == SC_MINIMIZE || nID == SC_CLOSE ){
		ShowWindow(SW_SHOWMINIMIZED);
		ShowWindow(SW_HIDE);  
	}
	else{
		CFrameWnd::OnSysCommand(nID, lParam);
	}
}

//////////////////////////////////////////////////////////////////////
// 响应用户单击tray
int CMainFrame::OnTray(WPARAM wParam,LPARAM lParam){
	CPersonMgrTitleView*		pTitleView = NULL;

	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );

	if( pTitleView->IsLogin() == FALSE ){
		return 0;
	}
	if(UINT(lParam)==WM_RBUTTONDOWN){
		CPoint			pos;
		CMenu			menu;
		
		GetCursorPos(&pos);
		menu.CreatePopupMenu( );
		menu.AppendMenu(MF_STRING, IDC_REGISTER, "&Register" );
		menu.AppendMenu(MF_SEPARATOR, 0);
		menu.AppendMenu(MF_STRING, IDC_SHUTDOWN, "&Shut Down" );
		menu.AppendMenu(MF_SEPARATOR, 0);
		menu.AppendMenu(MF_STRING, ID_APP_EXIT ,"E&xit" );

		menu.TrackPopupMenu( TPM_RIGHTALIGN, pos.x, pos.y, this );

	}
	else if( UINT(lParam)==WM_LBUTTONDBLCLK ||
			 UINT(lParam)==WM_LBUTTONDOWN ){
		ShowWindow( SW_SHOW );
		ShowWindow( SW_SHOWMAXIMIZED );
	}
	return 1;
}
//////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnUpdateFilePrint(CCmdUI* pCmdUI) {
	//pCmdUI->Enable( TRUE );
	return;
}	
//////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) {
	//pCmdUI->Enable( TRUE );
	return;
}
//////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) {
	//pCmdUI->Enable( TRUE );
	return;
}

//////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnFilePrint() {
	CPersonMgrTreeView*		pTreeView = NULL;

	pTreeView = (CPersonMgrTreeView*)m_parSplitWnd.GetPane( 0, 0 );
	pTreeView->SendMessage( WM_COMMAND, ID_FILE_PRINT );	
}
//////////////////////////////////////////////////////////////////////
//
void CMainFrame::PopulateTreeView() {
	CPersonMgrTreeView*		pTreeView = NULL;

	pTreeView = (CPersonMgrTreeView*)m_parSplitWnd.GetPane( 0, 0 );
	pTreeView->PopulateTree( );	
}
//////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnFilePrintPreview() {
	CPersonMgrTreeView*		pTreeView = NULL;

	pTreeView = (CPersonMgrTreeView*)m_parSplitWnd.GetPane( 0, 0 );
	pTreeView->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW );
}
//////////////////////////////////////////////////////////////////////
// 重画框架
void CMainFrame::OnNcPaint() {

	CFrameWnd::OnNcPaint( );

	/*CWindowDC*		pDC = (CWindowDC*)GetWindowDC( );
	if( pDC != NULL ){
		DrawCaption( pDC );
		DrawBottom( pDC );
		DrawLeftBoard( pDC );
		DrawMenu( pDC );
		DrawRightBoard( pDC );
		ReleaseDC( pDC );
	}*/
	
	return;
}
//////////////////////////////////////////////////////////////////////
// 得到标题栏的宽度与高度（尺寸）不是位置
/*void CMainFrame::GetCaptionRect(CRect &rect){

	GetWindowRect( &rect );

	rect.bottom = rect.top + GetSystemMetrics( SM_CYSIZE )+4;

}
void CMainFrame::DrawCaption( CWindowDC*	pDC ){
	
	CRect			rect,rectWnd;
	CString			strCaption;
	CRect			rect2;
	int				i,r,g,b;

	GetWindowRect( &rectWnd );
	GetCaptionRect( rect );


	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );

	rect2 = rect;
	rect2.bottom = rect2.top+3;

	for( i = 0; i<rect2.Height(); i++ ){
		
		
		r= BKRCOLOR + (i*25);
		g= BKGCOLOR + (i*18);
		b= BKBCOLOR + (i*17);

		if( r > 255 )		r = 255;
		if( g > 255 )		g = 255;
		if( b > 255 )		b = 255;
		
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		CPen *old = pDC->SelectObject(&pen);
		pDC->MoveTo( rect2.left+1, rect2.bottom-i );
		pDC->LineTo( rect2.right-2, rect2.bottom-i );
		pDC->SelectObject(old);
	}

	rect.top += 4;
	rect.right -= 58;
	if( bFlag == TRUE ){
		r = 0xa6;
		g = 0xCA;
		b = 0xF0;
		int		nStep = 0;
		nStep = rect.Width()/89;
		for( i = 0; i< rect.Width(); i++ ){
				
			if( (i%nStep) == 0 ){
				r++;
				g++;
				b++;

				if( r > 255 )		r = 255;
				if( g > 255 )		g = 255;
				if( b > 255 )		b = 255;
			}
			
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo( rect.right-i, rect.top );
			pDC->LineTo( rect.right-i, rect.bottom );
			pDC->SelectObject(old);
		}
	}
	else{
		pDC->FillSolidRect( &rect, RGB( 191, 191, 191 ) );
	}

	// Draw Text 
	CBitmap				bitmap,*pBitmap;
	CDC					dc;


	bitmap.LoadBitmap( IDB_TRAY );

	dc.CreateCompatibleDC( pDC );
	pBitmap = dc.SelectObject( &bitmap );
	bitmap.Detach();

	pDC->BitBlt( rect.left+6, rect.top+1, 16, 16,
		&dc, 0, 0, SRCCOPY );
	dc.SelectObject( pBitmap );
	dc.DeleteDC();

	GetWindowText( strCaption );
	rect.OffsetRect( 25, 2 );
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB(172,172,172) );
	pDC->DrawText( strCaption, rect, DT_LEFT|DT_VCENTER );
	rect.OffsetRect( -2, -1 );
	pDC->SetTextColor( RGB(0,0,0) );
	pDC->DrawText( strCaption, rect, DT_LEFT|DT_VCENTER );
	return;
}
//////////////////////////////////////////////////////////////////////
// 得到button的宽度与高度（尺寸）不是位置
void CMainFrame::GetButtonRect(CRect &rect){
	
	GetWindowRect( &rect );
	rect.top += GetSystemMetrics( SM_CYFRAME )+1;
	rect.bottom = rect.top + GetSystemMetrics( SM_CYSIZE ) - 4;
	rect.left = rect.right - GetSystemMetrics( SM_CXFRAME ) -
				(GetSystemMetrics( SM_CXSIZE ) - 1)*3;
	rect.right -= (GetSystemMetrics( SM_CXFRAME ) + 2);

	return;
}

void CMainFrame::DrawSystemButton(CWindowDC*	pDC){

	CRect			rect,rectWnd;

	GetWindowRect( &rectWnd );
	GetButtonRect( rect );


	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );
	pDC->FillSolidRect( &rect, RGB(200,0,0) );
	return;
}
//////////////////////////////////////////////////////////////////////
// 得到left board的宽度与高度（尺寸）不是位置
void CMainFrame::GetLeftBoardRect(CRect &rect){

	GetWindowRect( &rect );
	rect.right = rect.left + GetSystemMetrics( SM_CXFRAME )-1;
	return;
}

void CMainFrame::DrawLeftBoard(CWindowDC*	pDC){
	CRect			rect,rectWnd;

	
	GetWindowRect( &rectWnd );
	GetLeftBoardRect( rect );


	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );

	for( int i = 0; i< rect.Width(); i++ ){
		int			r,g,b;
		
		r= BKRCOLOR + (i*30);
		g= BKGCOLOR + (i*30);
		b= BKBCOLOR + (i*30);

		if( r > 255 )		r = 255;
		if( g > 255 )		g = 255;
		if( b > 255 )		b = 255;
		
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		CPen *old = pDC->SelectObject(&pen);
		pDC->MoveTo( rect.right-i, rect.top+3 );
		pDC->LineTo( rect.right-i, rect.bottom-(4-i) );
		pDC->SelectObject(old);
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// 得到right board的宽度与高度（尺寸）不是位置
void CMainFrame::GetRightBoardRect(CRect &rect){
	GetWindowRect( &rect );
	rect.left = rect.right - GetSystemMetrics( SM_CXFRAME );
	return;	
}
void CMainFrame::DrawRightBoard(CWindowDC*	pDC){
	CRect			rect,rectWnd;


	GetWindowRect( &rectWnd );
	GetRightBoardRect( rect );

	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );

	for( int i = 0; i<rect.Width(); i++ ){
		int			r,g,b;
		
		r= BKRCOLOR - (i*50);
		g= BKGCOLOR - (i*50);
		b= BKBCOLOR - (i*50);

		if( r < 0 )		r = 0;
		if( g < 0 )		g = 0;
		if( b < 0 )		b = 0;
		
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		CPen *old = pDC->SelectObject(&pen);
		pDC->MoveTo( rect.left+i, rect.top+(3-i) );
		pDC->LineTo( rect.left+i, rect.bottom-(4-i) );
		pDC->SelectObject(old);
	}
	return;

}
//////////////////////////////////////////////////////////////////////
// 得到bottom board的宽度与高度（尺寸）不是位置
void CMainFrame::GetBottomRect(CRect &rect){
	GetWindowRect( &rect );
	rect.top = rect.bottom - GetSystemMetrics( SM_CXFRAME );
	return;	
}

void CMainFrame::DrawBottom(CWindowDC*	pDC){
	CRect			rect,rectWnd;

	GetWindowRect( &rectWnd );
	GetBottomRect( rect );


	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );
	
	for( int i = 0; i<rect.Height(); i++ ){
		int			r,g,b;
		
		r= BKRCOLOR - (i*50);
		g= BKGCOLOR - (i*50);
		b= BKBCOLOR - (i*50);

		if( r < 0 )		r = 0;
		if( g < 0 )		g = 0;
		if( b < 0 )		b = 0;
		
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		CPen *old = pDC->SelectObject(&pen);
		pDC->MoveTo( rect.left+2, rect.top+i );
		pDC->LineTo( rect.right-1, rect.top+i );
		pDC->SelectObject(old);
	}
	return;

}
//////////////////////////////////////////////////////////////////////
// 得到Menu的宽度与高度（尺寸）不是位置
void CMainFrame::GetMenuRect(CRect &rect){

	
	GetWindowRect( &rect );
	rect.top = rect.top + GetSystemMetrics( SM_CYFRAME ) + 
			   GetSystemMetrics( SM_CYSIZE );
	rect.bottom = rect.top + GetSystemMetrics( SM_CYMENU )+1;
	rect.left +=  (GetSystemMetrics( SM_CXFRAME ));
	rect.right -= GetSystemMetrics( SM_CXFRAME );
	if( rect.right < rect.left ){
		rect.right = rect.left;
	}
	
	return;	
}

void CMainFrame::DrawMenu(CWindowDC*	pDC){
	CRect			rect,rectWnd;
	CString			strPath;
	CPicture		pic;

	GetWindowRect( &rectWnd );
	GetMenuRect( rect );


	rect.OffsetRect(  -rectWnd.left, -rectWnd.top );
	
	rect.left += 284;
	rect.right = 1028;
	rect.bottom += 25;
	strPath = GetModulePath( )+"\\board.jpg";
	if( pic.Load( strPath ) == TRUE ){
		pic.Render( pDC, &rect );
	}		
	else{
		pDC->FillRect(&rect,&CBrush(RGB(212,208,200)) );
	}	
	
	return;

}*/
//////////////////////////////////////////////////////////////////////
// 
void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {

	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	/*if( nState == WA_INACTIVE ){
		bFlag = FALSE;
	}
	OnNcPaint( );
	bFlag = TRUE;*/
	return;
}
//////////////////////////////////////////////////////////////////////
// 
void CMainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI) {
	pCmdUI->Enable( FALSE );
	return;
}
//////////////////////////////////////////////////////////////////////
// 
void CMainFrame::OnHelp() {

	CString			strPath;

	strPath = GetModulePath( ) +"\\PersonMgrHelp.chm";
	/*if( HtmlHelp(NULL,
		(LPCSTR)strPath, 
		HH_DISPLAY_TOPIC, 
		NULL) == NULL ){
		AfxMessageBox( "Can't find PersonMgrHelp.chm!" );
	
	}*/
	return;
}
//////////////////////////////////////////////////////////////////////
// CMainFrame member function
// 得到中英文对应的文档
BOOL CMainFrame::InitPhrase( ){

	CString				strPath;
	CFile				file;
	char				tChar;
	BOOL				bFindLineChange = FALSE;
	DWORD				dwLen = 0;
	DWORD				dwCnt = 0;
	CString				strData;
	CString				strEn;
	int					res = 0;

	m_mapPhrase.RemoveAll( );

	strPath = GetModulePath()+"\\phrase.dat";
	

	if( file.Open( strPath, CFile::modeRead ) == FALSE ){
		return FALSE;
	}
	dwLen = file.GetLength( );

	for( dwCnt = 0; dwCnt < dwLen; dwCnt++){
		file.Read(&tChar, 1 );
		if( bFindLineChange == FALSE ){
			if( (tChar == 0x0D) || (tChar == 0x0A) ){
				bFindLineChange = TRUE;	
			}
			else{
				strData += tChar;
			}
		}
		else{
			if( (tChar != 0x0D) && (tChar != 0x0A) ){

				bFindLineChange = FALSE;
				res = strData.Find("==");
				if( res != -1 ){
					strData.TrimLeft( );
					strData.TrimRight( );
					strEn = strData.Left( res );
					strData = strData.Mid( res+2 );
					m_mapPhrase.SetAt( strEn, strData );
				}

				strData = tChar;
			}
		}
	}

	res = strData.Find("==");
	if( res != -1 ){
		strData.TrimLeft( );
		strData.TrimRight( );
		strEn = strData.Left( res );
		strData = strData.Mid( res+2 );
		m_mapPhrase.SetAt( strEn, strData );
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////
// CMainFrame member function
// 得到中英文对应的短语
CString CMainFrame::GetDispPhrase( CString strEn ){

	CString			strData;

	if( GetLangID() == 0 ){
		return strEn;
	}

	if(m_mapPhrase.Lookup( strEn, strData) == TRUE ){
		return strData;
	}
	else{
		return strEn;
	}
}
//////////////////////////////////////////////////////////////////////
// 得到反转的字符
CString	CMainFrame::GetReversePhrase( CString strReverse ){

	POSITION		pos = NULL;
	CString			strKey;
	CString			strValue;
	
	if( GetLangID() == 0 ){
		return strReverse;
	}

	pos = m_mapPhrase.GetStartPosition();

	while( pos != NULL ){
		m_mapPhrase.GetNextAssoc( pos, strKey, strValue );
		if( strValue == strReverse ){
			return strKey;
		}
	}
	return strReverse;
}
//////////////////////////////////////////////////////////////////////
// 从ID中load字符串并转换
CString CMainFrame::LoadStringA( int nID ){

	CString			strData;

	strData.LoadString( nID );
	return GetDispPhrase( strData );
}
//////////////////////////////////////////////////////////////////////
// 设置语言状态
void CMainFrame::OnUpdateChinese(CCmdUI* pCmdUI){
	pCmdUI->Enable( TRUE );
	pCmdUI->SetCheck( GetLangID() );
}
//////////////////////////////////////////////////////////////////////
// 设置语言状态
void CMainFrame::OnUpdateEnglish(CCmdUI* pCmdUI) {
	pCmdUI->Enable( TRUE );
	pCmdUI->SetCheck( GetLangID() ? FALSE:TRUE );
}
//////////////////////////////////////////////////////////////////////
// 设置语言状态
void CMainFrame::OnEnglish(){
	if( GetLangID() == 1 ){
		SetLangID( 0 );	
		Reset( );
	}
}
//////////////////////////////////////////////////////////////////////
// 设置语言状态
void CMainFrame::OnChinese(){
	if( GetLangID() == 0 ){
		SetLangID( 1 );	
		Reset( );
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// 动态对话
void CMainFrame::OnDynamic() {
	SetDynamicDlg( !IsDynamicDlg() );	
}

void CMainFrame::OnUpdateDynamic(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck( IsDynamicDlg() );
}

//////////////////////////////////////////////////////////////////////
// 重新显示
void CMainFrame::Reset( ){
	
	CPersonMgrListView*		pListView = NULL;
	CPersonMgrTitleView*	pTitleView = NULL;
	CPersonMgrQueryView*	pQueryView = NULL;

	PopulateTreeView( );


	pTitleView = (CPersonMgrTitleView*)m_subSplitWnd.GetPane( 0, 0 );
	pQueryView = (CPersonMgrQueryView*)m_subSplitWnd.GetPane( 1, 0 );
	pListView = (CPersonMgrListView*)m_subSplitWnd.GetPane( 2, 0 );

	pTitleView->Invalidate();
	pQueryView->InitView();
	//pListView->InitView();
	ShowWindow(SW_HIDE);
	ShowWindow( SW_SHOW );
	return;
}
