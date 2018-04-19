// PersonMgrQueryView.cpp : implementation file
//

#include "stdafx.h"
#include "PersonMgr.h"
#include "PersonMgrQueryView.h"
#include "mainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView

IMPLEMENT_DYNCREATE(CPersonMgrQueryView, CFormView)

CPersonMgrQueryView::CPersonMgrQueryView()
	: CFormView(CPersonMgrQueryView::IDD){
	//{{AFX_DATA_INIT(CPersonMgrQueryView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_crBack = RGB( 250, 250, 250 );
	m_bkBrush.CreateSolidBrush( m_crBack );
}

CPersonMgrQueryView::~CPersonMgrQueryView()
{
}

void CPersonMgrQueryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPersonMgrQueryView)
	DDX_Control(pDX, IDC_EXCUTE, m_btnExcute);
	DDX_Control(pDX, IDC_COMBO3, m_ctrComboBox3);
	DDX_Control(pDX, IDC_COMBO2, m_ctrComboBox2);
	DDX_Control(pDX, IDC_COMBO1, m_ctrComboBox1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPersonMgrQueryView, CFormView)
	//{{AFX_MSG_MAP(CPersonMgrQueryView)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_EXCUTE, OnExcute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView diagnostics

#ifdef _DEBUG
void CPersonMgrQueryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPersonMgrQueryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPersonMgrDoc* CPersonMgrQueryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonMgrDoc)));
	return (CPersonMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers

void CPersonMgrQueryView::OnInitialUpdate() {

	CString			strInfo;

	CFormView::OnInitialUpdate();


	m_mapQueryInfo.RemoveAll();
	GetDocument()->m_pQueryView = this;
	strInfo.LoadString( IDS_QUERY_TYPE );

	// 初始化操作符
	while( strInfo.Find( _T(',') ) != -1 ){
		int				nLen;
		CString			strKey;
		CString			strValue;

		nLen = strInfo.Find( _T(',') );
		strValue = strInfo.Left( nLen );
		strInfo = strInfo.Mid( nLen + 1 );
	
		nLen = strValue.Find( _T(':') );
		strKey = strValue.Left( nLen );
		strValue = strValue.Mid( nLen +1 );

		m_mapQueryInfo.SetAt( strKey, strValue );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// initall view 
void CPersonMgrQueryView::InitView(){
	
	
	if( IsIconic() ){
		return;
	}

	CPersonMgrDoc*			pDoc = GetDocument();
	CMainFrame*				pFrame = (CMainFrame*)AfxGetMainWnd( );
	CString					strData;

	if( pDoc->m_nType == INPUT ){

		ShowView();
		DeleteItemFromCombo();

		strData = pFrame->GetDispPhrase( "Filtered by" );
		GetDlgItem(IDC_COLUMN1)->SetWindowText( strData );
		strData = pFrame->GetDispPhrase( "Operate" );
		GetDlgItem(IDC_COLUMN2)->SetWindowText( strData );
		strData = pFrame->GetDispPhrase( "Value" );
		GetDlgItem(IDC_COLUMN3)->SetWindowText( strData );

		// 得到列名的显示字符(中文或英文)	

		SetComboDataFromMapString( IDC_COMBO1, &pDoc->m_mapColumnToDataType );
		SetComboDataFromMapString( IDC_COMBO2, &m_mapQueryInfo );
	}
	else{
		HideView();
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// hide the current view 
void CPersonMgrQueryView::HideView(){

	CSplitterWnd*		pWnd = NULL;

	pWnd = (CSplitterWnd*)GetParent();
	HideAllItem( );
	pWnd->SetRowInfo( 1, 0, 0 );
	pWnd->RecalcLayout();
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// show the current view 
void CPersonMgrQueryView::ShowView(){

	CSplitterWnd*		pWnd = NULL;

	pWnd = (CSplitterWnd*)GetParent();
	ShowAllItem( );
	pWnd->SetRowInfo( 1, ONECOLUMNHEIGH, 0 );
	pWnd->RecalcLayout();
	return;

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// hide the all item
void CPersonMgrQueryView::HideAllItem(){

	GetDlgItem(IDC_COLUMN1)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_COLUMN2)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_COLUMN3)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_COMBO1)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_COMBO2)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_COMBO3)->ShowWindow( SW_HIDE );
	GetDlgItem(IDC_EXCUTE)->ShowWindow( SW_HIDE );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// show the all item
void CPersonMgrQueryView::ShowAllItem(){

	GetDlgItem(IDC_COLUMN1)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_COLUMN2)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_COLUMN3)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_COMBO1)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_COMBO2)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_COMBO3)->ShowWindow( SW_SHOW );
	GetDlgItem(IDC_EXCUTE)->ShowWindow( SW_SHOW );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// clear the comboBox
void CPersonMgrQueryView::DeleteItemFromCombo(CComboBox *pCombo){

	int				nLen = 0;
	int				nCnt = 0;

	pCombo->SetWindowText("");

	nLen = pCombo->GetCount( );
	for(nCnt = nLen-1; nCnt >= 0; nCnt-- ){
		pCombo->DeleteString( nCnt );
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// clear all comboBox
void CPersonMgrQueryView::DeleteItemFromCombo(){

	CComboBox*		pCombo = NULL;

	pCombo = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	DeleteItemFromCombo( pCombo );

	pCombo = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	DeleteItemFromCombo( pCombo );

	pCombo = (CComboBox*)GetDlgItem( IDC_COMBO3 );
	DeleteItemFromCombo( pCombo );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// use the mapstring full the ComboBox
void CPersonMgrQueryView::SetComboDataFromMapString(UINT nID, 
													CMapStringToString *pMapString){
	POSITION		pos = NULL;
	CString			strKey;
	CString			strValue;
	CComboBox*		pCombo = NULL;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	pCombo = (CComboBox*)GetDlgItem( nID );
	pos = pMapString->GetStartPosition();

	while( pos != NULL ){
		pMapString->GetNextAssoc( pos, strKey, strValue );
		if( strKey.IsEmpty() == FALSE ){
			strKey = pFrame->GetDispPhrase( strKey );
			pCombo->AddString( strKey );
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// Get Current Filter String
CString CPersonMgrQueryView::GetFilterString(){

	CString			strFilter;
	CString			strColumn;
	CString			strKey;
	CString			strOperator;
	CString			strValue;
	CString			strType;
	CPersonMgrDoc*	pDoc = GetDocument();
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	UpdateData();
	m_ctrComboBox1.GetWindowText( strColumn );
	m_ctrComboBox2.GetWindowText( strKey );
	m_ctrComboBox3.GetWindowText( strValue );
	

	strColumn = pFrame->GetReversePhrase( strColumn );
	strKey = pFrame->GetReversePhrase( strKey );

	m_mapQueryInfo.Lookup( strKey, strOperator );

	pDoc->m_mapColumnToDataType.Lookup( strColumn, strType );
	if( strOperator.IsEmpty() ){
		strOperator = strKey;
	}

	if( strColumn.IsEmpty() || 
		strOperator.IsEmpty() || 
		strValue.IsEmpty() ){

		strFilter.Empty();
	}
	else{
		if( strType.Find("STRING") >= 0 ){
			strFilter.Format(" [%s] %s '%s'", strColumn, strOperator, strValue );
		}
		else if( strType.Find("DATETIME") >= 0 ||
			strType.Find("SIMPLETIME") >= 0 ){
			strFilter.Format(" [%s] %s #%s#", strColumn, strOperator, strValue );
		}
		else if( strType.Find("BOOL") >= 0 ){
			if( strValue.CompareNoCase("1") == 0 || strValue.CompareNoCase("0") == 0){
				if( strValue.CompareNoCase("1") == 0 ){
					strValue = "true";
				}
				else{
					strValue = "false";
				}
				strFilter.Format(" [%s] %s %s", strColumn, strOperator, strValue );				
			}
			else{
				MessageBox("Sorry, This is bool type, and the value only allow 1(Yes) or 0(No)!");
				GetDlgItem(IDC_COMBO3)->SetFocus();
				strFilter.Empty();
				return strFilter;
			}
		}
		else{
			strFilter.Format(" [%s] %s %s", strColumn, strOperator, strValue );
		}
	}
	return strFilter;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
// Get Current Filter String
HBRUSH CPersonMgrQueryView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){
	
	UINT				nID;

	nID = pWnd->GetDlgCtrlID();

	pDC->SetBkMode( TRANSPARENT );

	if( nID == IDC_COLUMN1 || nID == IDC_COLUMN2 || nID == IDC_COLUMN3 ){
		pDC->SetTextColor( RGB( 180, 0, 0 ) );
	}
	else{
		pDC->SetTextColor( RGB( 0, 0, 200 ) );
	}

	return m_bkBrush;
	// HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	// return hbr;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView message handlers
void CPersonMgrQueryView::OnExcute(){

	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->Refresh();
}
