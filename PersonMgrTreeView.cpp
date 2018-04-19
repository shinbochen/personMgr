// PersonMgrTreeView.cpp : implementation of the CPersonMgrTreeView class
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"

#include "PersonMgrDoc.h"
#include "PersonMgrTreeView.h"
#include "PersonMgrListView.h"
#include "PersonMgrTitleView.h"

#include "MainFrm.h"

#include "ctrlExt.h"
#include "atldbcli.h"
#include "atldbsch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView

IMPLEMENT_DYNCREATE(CPersonMgrTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CPersonMgrTreeView, CTreeView)
	//{{AFX_MSG_MAP(CPersonMgrTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView construction/destruction

CPersonMgrTreeView::CPersonMgrTreeView(){
	m_crBack = RGB( 192, 192, 192 );
	m_crText = RGB( 0, 0, 255 );
}

CPersonMgrTreeView::~CPersonMgrTreeView(){

}

BOOL CPersonMgrTreeView::PreCreateWindow(CREATESTRUCT& cs){

	cs.style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView drawing

void CPersonMgrTreeView::OnDraw(CDC* pDC){
	CPersonMgrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView Message Handle
// after the document initall;
void CPersonMgrTreeView::OnInitialUpdate(){
	CTreeView::OnInitialUpdate();

	CMainFrame*			pFrame = NULL;
	CTreeCtrlEx&		treeCtrl = (CTreeCtrlEx&)GetTreeCtrl();

	GetDocument()->m_pTreeView = this;

	pFrame = (CMainFrame*)AfxGetMainWnd();
	treeCtrl.SetBkColor( m_crBack );
	treeCtrl.SetTextColor( m_crText );

	pFrame->SetLangID( GetDocument()->m_nLangID );
	pFrame->SetDynamicDlg( GetDocument()->m_bDynamic );
	PopulateTree();
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView printing
// �ڿ�ʼ��ӡ�ĵ�֮ǰ,���ƻ��ʼ����ӡ�Ի���

BOOL CPersonMgrTreeView::OnPreparePrinting(CPrintInfo* pInfo){
	// default preparation
	return DoPreparePrinting(pInfo);
}
// ��ʼһ�δ�ӡ��ҵ������ͼ���豸�ӿ�
void CPersonMgrTreeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo){
	
	
	int				nMaxPage;
	int				nPageActualWidht;				// ֽ�ſ����mmΪ��λ
	int				nPageActualHeight;				// ֽ�Ÿ߶���mmΪ��λ
	int				nPagePixelWidth;				// ÿһҳWidth, in pixels
	int				nPagePixelHeight;				// ÿһҳHeight, in pixels
	int				nY = 0;
	CPersonMgrDoc	*pDoc = GetDocument();
	CListCtrl&		listCtrl = pDoc->m_pListView->GetListCtrl();
	TEXTMETRIC		TextMetric;	

	pDC->SetMapMode(MM_TEXT);
	// ListView���õĴ�yin����ĸ߶�
	pDC->GetTextMetrics( &TextMetric );
	pDoc->m_nTextHeight = TextMetric.tmHeight + 20;

	// �õ�ֽ�ŵ�ʵ�ʸ߿��(��mmΪ��λ)
	nPageActualWidht = pDC->GetDeviceCaps(HORZSIZE);
	nPageActualHeight = pDC->GetDeviceCaps(VERTSIZE);
	nPagePixelWidth = pDC->GetDeviceCaps(HORZRES);
	nPagePixelHeight = pDC->GetDeviceCaps(VERTRES);

	pDoc->m_nPerMMPixel = nPagePixelWidth / nPageActualWidht;
	pDoc->m_nXMaxPixel = nPagePixelWidth - 
		(LEFT_BOARDLINE + RIGHT_BOARDLINE)* (pDoc->m_nPerMMPixel);
	pDoc->m_nYMaxPixel = nPagePixelHeight - 
		(UP_BOARDLINE + DOWN_BOARDLINE)* (pDoc->m_nPerMMPixel);
	

	// ��ʾ��ͷ��Title����ĸ߶�
	nY = pDoc->m_pTitleView->GetPrintHeight();
	// ��ʾ�̶�������ĸ߶�
	// nY += pDoc->GetFixItemHeight();
	// ��ʾ�̶���β��(���Ʊ��)����ĸ߶�
	// nY += GetTailHeight();
	// �������������󻭵�һ����
	nY += pDoc->m_nTextHeight + LINE_HEIGHT*2;
	nY = pDoc->m_nYMaxPixel - nY;

	pDoc->m_nRowPerPage = nY / pDoc->m_nTextHeight;	
	
	int				nSumItem = 0;
	nSumItem = listCtrl.GetItemCount();
	nMaxPage = nSumItem / pDoc->m_nRowPerPage;
	if(nSumItem % pDoc->m_nRowPerPage){
		nMaxPage ++;
	}
	if(nMaxPage == 0){
		nMaxPage = 1;
	}
	pInfo->SetMaxPage(nMaxPage);
	return;
}
// ��ֹ��ӡ,���ͷ�ͼ����ӿ�
void CPersonMgrTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
// ���ÿҳ�Ĵ�ӡ��Ԥ ÿҳ�ĵ������
void CPersonMgrTreeView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
	
	CPersonMgrDoc		*pDoc = NULL;
	int					nStartY = 0;
	CFont				nFont;
	CFont				*pOldFont;

	nFont.CreatePointFont(120, "Arail", pDC);

	pOldFont = pDC->SelectObject(&nFont);

	pDoc = GetDocument();
	nStartY = UP_BOARDLINE * pDoc->m_nPerMMPixel;
	
	nStartY += pDoc->m_pTitleView->PrintBody(nStartY, pDC, pInfo);
	//nStartY += pDoc->m_pTitleView->PrintBody(nStartY, pDC, pInfo);
	pDoc->m_pListView->PrintBody(nStartY, pDC, pInfo);

	pDC->SelectObject(pOldFont);
	CTreeView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView diagnostics

#ifdef _DEBUG
void CPersonMgrTreeView::AssertValid() const{
	CTreeView::AssertValid();
}

void CPersonMgrTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CPersonMgrDoc* CPersonMgrTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonMgrDoc)));
	return (CPersonMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// create
int CPersonMgrTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CTreeCtrl&		treeCtrl = GetTreeCtrl();
	CImageList		imageList;

	imageList.Create( IDB_TREEVIEW, 19, 0, RGB(255, 255, 255) );
	imageList.SetBkColor( GetSysColor(COLOR_WINDOW) );
	treeCtrl.SetImageList( &imageList, TVSIL_NORMAL );
	imageList.Detach( );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// populate tree view
void CPersonMgrTreeView::PopulateTree(){

	USES_CONVERSION;

	int					nLen;
	int					nCnt;
	CPersonMgrDoc*		pDoc = GetDocument();
	CTreeCtrlEx&		treeCtrl = (CTreeCtrlEx &)GetTreeCtrl();
	CString				strInfo;
	CMainFrame*			pFrame;
	CString				strData;

	pFrame = (CMainFrame*)AfxGetMainWnd( );

	treeCtrl.DeleteAllItems();

	strInfo = pFrame->LoadStringA( IDS_ROOT );
	m_tRoot = treeCtrl.GetRootItem().AddHead( strInfo, IID_ROOT);
	strInfo = pFrame->LoadStringA( IDS_ACCOUNT );
	m_tAccount = m_tRoot.AddTail(strInfo, IID_ACCOUNT );
	strInfo = pFrame->LoadStringA( IDS_PLAN );
	m_tPlan = m_tRoot.AddTail(strInfo, IID_PLAN );
	strInfo = pFrame->LoadStringA( IDS_CONTACT );
	m_tContact = m_tRoot.AddTail(strInfo, IID_CONTACT );
	strInfo = pFrame->LoadStringA( IDS_FAMILY );
	m_tFamily = m_tRoot.AddTail(strInfo, IID_FAMILY );
	strInfo = pFrame->LoadStringA( IDS_CALL );
	m_tCall = m_tRoot.AddTail( strInfo, IID_CALL );


	nLen = pDoc->m_arrTable.GetSize();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){

		strInfo = pDoc->m_arrTable.GetAt( nCnt );
		strData = pFrame->GetDispPhrase( strInfo );

		AddItem( strInfo, TRUE );
	}

	nLen = pDoc->m_arrQuery.GetSize();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){

		strInfo = pDoc->m_arrQuery.GetAt( nCnt );
		strData = pFrame->GetDispPhrase( strInfo );

		AddItem( strInfo, FALSE );
	}	
	m_tRoot.Expand( );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// node select change
void CPersonMgrTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) {

	NM_TREEVIEW*		pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CPersonMgrDoc*		pDoc = GetDocument();
	UINT				nImageID;
	CTreeCtrlEx&		treeCtrl = (CTreeCtrlEx &)GetTreeCtrl();	
	CMainFrame*			pFrame = NULL;
	CString				strCurTable;

	pFrame = (CMainFrame*)AfxGetMainWnd();

	m_tItemSel = treeCtrl.GetSelectedItem();
	nImageID = m_tItemSel.GetImageID();

	strCurTable = m_tItemSel.GetText();
	strCurTable = pFrame->GetReversePhrase( strCurTable );

	pDoc->m_curTable = strCurTable;

	switch( nImageID ){
	case IID_TABLE:
		pDoc->SetEditType( INPUT );
		break;
	case IID_QUERY:
		pDoc->SetEditType( QUERY );
		break;
	default:
		pDoc->SetEditType( NONE );
		break;
	}
	pDoc->InitallColumnName( );
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// Erase Background
BOOL CPersonMgrTreeView::OnEraseBkgnd(CDC* pDC) {

	
	if( IsIconic() ){
		return TRUE;
	}

	CRect			rect;
	
	GetClientRect( &rect );
	pDC->FillSolidRect( &rect, m_crBack );
	return TRUE;
	//return CTreeView::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// Add this Function declare by strFunc to the treeView
void CPersonMgrTreeView::AddItem(CString strFunc, BOOL bFlag){

	UINT		stringID[]={
				IDS_ACCOUNT_CATALOG,
				IDS_PLAN_CATALOG,
				IDS_CONTACT_CATALOG,
				IDS_FAMILY_CATALOG,
				IDS_CALL_CATALOG};
	int			nCnt = 0;


	// if this function don't need display then return;
	if( IsBePartOf( strFunc, IDS_UNDISP_CATALOG ) ){
		return;
	}

	for( nCnt = 0; nCnt < sizeof(stringID)/sizeof(UINT); nCnt++ ){

		if( IsBePartOf( strFunc, stringID[nCnt] ) == TRUE ){
			AddItem( strFunc, stringID[nCnt], bFlag );
			return;
		}
	}
	AddItem( strFunc, IDS_OTHER_CATALOG, bFlag );
	return;
}
//////////////////////////////////////////////////////////////////////
// if the StringID nID include lpszvalue then return true
// else reverse
BOOL CPersonMgrTreeView::IsBePartOf(LPCTSTR lpszValue, UINT nID){
	
	int				nCutLen = 0;
	CString			strInfo;
	CString			strTmp, strTest;
	BOOL			bFlag = FALSE;

	strInfo.LoadString(nID);
	strInfo.MakeUpper();
	strTmp = lpszValue;
	strTmp.MakeUpper();
	nCutLen = strInfo.Find( strTmp );

	if( nCutLen == -1 ){
		bFlag = FALSE;
	}
	else{
		bFlag = TRUE;
		// �ж�����Ƿ�','
		if(nCutLen != 0){
			strTest = strInfo.Mid( nCutLen-1, 1);
			if( strTest.CompareNoCase( "," ) != 0 ){
				bFlag = FALSE;
			}
		}
	}
	return bFlag;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// Add this Function declare by strFunc to the treeView
void CPersonMgrTreeView::AddItem(CString strFunc, UINT	stringID, BOOL bFlag){

	int				nCnt = 0;
	int				nImageID = 0;
	CString			strInfo;
	CTreeCursor		parTreeCursor;
	CTreeCursor		chdTreeCursor;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );
	HTREEITEM		hAfter = TVI_FIRST;

	// �ҵ���lpszName��Ŀ���Ӧ��imageID
	// nImageID = FindImageIDByStr( lpszName );
	if( bFlag == TRUE ){
		nImageID = IID_TABLE;
	}
	else{
		nImageID = IID_QUERY;
	}
	parTreeCursor = FindTreeCurByStrID( stringID );

	// ���ش˸���ĵ�һ����������û��������Ϊ0
	chdTreeCursor = parTreeCursor.GetChild();
	// ��û������ʱ��ֱ�Ӽ��ں�
	if( HTREEITEM( chdTreeCursor ) == NULL ){
		strFunc = pFrame->GetDispPhrase( strFunc );
		parTreeCursor.AddTail( strFunc, nImageID );
	}
	// ���������stringID��������
	else{
		
		while ( HTREEITEM( chdTreeCursor ) != NULL ){
			strInfo = chdTreeCursor.GetText();
			// �Ƚ���nstringID���ַ����У����ַ�����λ��
			// ���ǰ����ַ���(lpszName)��λ�ñȽϿ�ǰ��
			// �򷵻� -1 (lpszName - strInfo)
			if( CompareStringOnID( stringID, strFunc, strInfo) >=0 ){
				hAfter = HTREEITEM( chdTreeCursor );
			}
			// �õ���һ����Ŀ�α� �� �ַ���
			chdTreeCursor = chdTreeCursor.GetNextSibling();
		}

		strFunc = pFrame->GetDispPhrase( strFunc );
		parTreeCursor.InsertAfter( strFunc, hAfter, nImageID);
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTreeView message handlers
// �ҵ����ַ���ID���Ӧ��TreeCursor
CTreeCursor CPersonMgrTreeView::FindTreeCurByStrID( UINT nID ){
	
	CString				strInfo;
	CMainFrame*			pFrame;

	pFrame = (CMainFrame*)AfxGetMainWnd( );

	switch( nID ){
	case IDS_ACCOUNT_CATALOG:
		if( m_tAccount == NULL ){
			strInfo = pFrame->LoadStringA( IDS_ACCOUNT );
			m_tAccount = m_tRoot.AddHead(strInfo, IID_ACCOUNT );
		}
		return m_tAccount;
	case IDS_PLAN_CATALOG:
		if( m_tPlan == NULL ){
			strInfo = pFrame->LoadStringA( IDS_PLAN );
			m_tPlan = m_tRoot.AddTail(strInfo, IID_PLAN );
		}
		return m_tPlan;
	case IDS_CONTACT_CATALOG:
		if( m_tContact == NULL ){
			strInfo = pFrame->LoadStringA( IDS_CONTACT );
			m_tContact = m_tRoot.AddTail(strInfo, IID_CONTACT );
		}
		return m_tContact;
	case IDS_FAMILY_CATALOG:
		if( m_tFamily == NULL ){
			strInfo = pFrame->LoadStringA( IDS_FAMILY );
			m_tFamily = m_tRoot.AddTail(strInfo, IID_FAMILY );
		}
		return m_tFamily;
	case IDS_CALL_CATALOG:
		if( m_tCall == NULL ){
			strInfo = pFrame->LoadStringA( IDS_CALL );
			m_tFamily = m_tRoot.AddTail(strInfo, IID_CALL );
		}
		return m_tCall;
	case IDS_OTHER_CATALOG:
		if( m_tOther == NULL ){
			strInfo = pFrame->LoadStringA( IDS_OTHER );
			m_tOther = m_tRoot.AddTail(strInfo, IID_OTHER );
		}
		return m_tOther;
	default:
		ASSERT(FALSE);
		return m_tRoot;
	}	
}

///////////////////////////////////////////////////////////////////////////
// �Ƚ�lpstr1��lpstr2��nID��λ�� (�൱�� lpstr1 - lpstr2);
BOOL CPersonMgrTreeView::CompareStringOnID( UINT nID, 
										   LPCTSTR lpStr1, LPCTSTR lpStr2 ){
	CString			strInfo;
	int				nLen;
	int				nLen2;
	
	strInfo.LoadString( nID );
	nLen = strInfo.Find( lpStr1 );
	nLen2 = strInfo.Find( lpStr2 );

	return  (nLen - nLen2);
}
