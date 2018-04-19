// PersonMgrTitleView.cpp : implementation file
//
// include file declare 
#include "stdafx.h"
#include "PersonMgr.h"
#include "PersonMgrTitleView.h"

#include "NMUserDlg.h"
#include "AlarmDlg.h"
#include "SDSetupDlg.h"
#include "RegDlg.h"
#include "picture.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView

IMPLEMENT_DYNCREATE(CPersonMgrTitleView, CView)

CPersonMgrTitleView::CPersonMgrTitleView()
{
}

CPersonMgrTitleView::~CPersonMgrTitleView()
{
}


BEGIN_MESSAGE_MAP(CPersonMgrTitleView, CView)
	//{{AFX_MSG_MAP(CPersonMgrTitleView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView drawing

void CPersonMgrTitleView::OnDraw(CDC* pDC){
	
	if( IsIconic() ){
		return;
	}

	CPersonMgrDoc*		pDoc = GetDocument();
	CRect				nRect;
	CRect				rect;
	CString				strPath;
	CPicture			pic;
	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );

	strPath = GetModulePath()+"\\Title.jpg";

	GetClientRect( &nRect );
	rect = nRect;

	if( rect.Width() > 460 ){
		rect.DeflateRect( (rect.Width()-460)/2, 0,
						  (rect.Width()-460)/2, 0);
	}

	if( rect.Height() > 50 ){
		rect.bottom=rect.top+50;
	}
	
	if( pic.Load(strPath) == TRUE ){ 
		pic.Render( pDC, &rect );
	}
	nRect.top += 34;

	strPath = pFrame->GetDispPhrase("Current Function");
	strPath +=":";
	strPath += pFrame->GetDispPhrase(pDoc->m_curTable);

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 0, 0, 255 ) );

	CFont			font;
	CFont*			pOldFont;

	font.CreatePointFont( 80, "Arial black" );

	pOldFont = pDC->SelectObject( &font );
	pDC->DrawText( strPath, &nRect, DT_VCENTER|DT_CENTER );
	pDC->SelectObject( pOldFont );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView diagnostics

#ifdef _DEBUG
void CPersonMgrTitleView::AssertValid() const
{
	CView::AssertValid();
}

void CPersonMgrTitleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPersonMgrDoc* CPersonMgrTitleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonMgrDoc)));
	return (CPersonMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers

void CPersonMgrTitleView::OnInitialUpdate() {

	CView::OnInitialUpdate();
	CPersonMgrDoc*		pDoc = GetDocument();
	
	pDoc->m_pTitleView = this;
	pDoc->JudgeRegister();
	pDoc->SetSomeStatus();
	SetTimer( IDC_ALARMTIMER, 1000, NULL ); 
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
BOOL CPersonMgrTitleView::OnEraseBkgnd(CDC* pDC) {
	
	if( IsIconic() ){
		return TRUE;
	}

	return CView::OnEraseBkgnd(pDC);
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// add user or change the current Password 
// delete user
void CPersonMgrTitleView::AddOrModifyUser( int nType ){

	CPersonMgrDoc*		pDoc = GetDocument();
	CNMUserDlg			dlg( &pDoc->m_mapUserToPassword, nType );
	// add new user
	if( nType == CHGPSD ){
		dlg.SetUser( pDoc->m_strUser );
	}	
	if( dlg.DoModal() == IDOK ){	
		if( nType == NEWUSER ){
			if( pDoc->AddUser( dlg.m_strUser, dlg.m_strNewPSD ) == TRUE ){
				MessageBox( "Add User Success!" );
			}
		}
		else if( nType == CHGPSD ){
			if( pDoc->ChgUserPSD( dlg.m_strUser, dlg.m_strNewPSD ) == TRUE ){
				MessageBox( "Change the Password Success!" );
			}
		}
		else if( nType == DELETEUSER ){
			if( pDoc->DeleteUser( dlg.m_strUser ) == TRUE ){
				MessageBox( "Delete User Success!" );
			}
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// alarm change
void CPersonMgrTitleView::OnTimer(UINT nIDEvent) {

	CPersonMgrDoc*		pDoc = GetDocument();
	CString				strPlanNote, strWeekNote, strDayNote;
	CString				strPlanMelody, strWeekMelody, strDayMelody;
	BOOL				bPlanFlag, bWeekFlag, bDayFlag;
	CAlarmDlg*			pDlg;
	CWnd*				pWnd;
	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );

	if( pDoc->m_bLogin == FALSE ){
		return;
	}
	pWnd = GetDesktopWindow( );


	if( nIDEvent == IDC_ALARMTIMER ){
		pDoc->IsShutDownTime();

		bPlanFlag = pDoc->IsPlanTaskAlarm( strPlanNote, strPlanMelody );
		bWeekFlag = pDoc->IsWeekAlarm( strWeekNote, strWeekMelody );
		bDayFlag = pDoc->IsDayAlarm( strDayNote, strDayMelody );
		
		if( bPlanFlag ){
			pDlg = new CAlarmDlg( pFrame->GetDispPhrase("Plan Task"), 
								  strPlanNote, 
								  strPlanMelody,
								  NULL );
			pDlg->Create( IDD_ALARMDLG, NULL );
			pDlg->ShowWindow( SW_SHOW );
		}
		if( bWeekFlag ){
			pDlg = new CAlarmDlg( pFrame->GetDispPhrase("Alarm By Week"), 
								  strWeekNote, 
								  strWeekMelody,
								  NULL );
			pDlg->Create( IDD_ALARMDLG, NULL );
			pDlg->ShowWindow( SW_SHOW );
		}
		if( bDayFlag ){
			pDlg = new CAlarmDlg( pFrame->GetDispPhrase("Alarm By Day"), 
								  strDayNote, 
								  strDayMelody,
								  NULL );
			pDlg->Create( IDD_ALARMDLG, NULL );
			pDlg->ShowWindow( SW_SHOW );
		}
	}
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// set auto power off
void CPersonMgrTitleView::SetAutoShutDown(){

	CPersonMgrDoc*			pDoc = GetDocument();

	CSDSetupDlg				setupDlg( pDoc->m_strTime, pDoc->m_bAutoShutDown );

	if( setupDlg.DoModal() == IDOK ){
		pDoc->m_strTime = setupDlg.m_strTime;
		pDoc->m_bAutoShutDown = (setupDlg.m_nEnable == 0) ? TRUE : FALSE;
		pDoc->SetPrivateInfo();
		pDoc->SetSomeStatus();
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// 
void CPersonMgrTitleView::SetRegister(){

	// V1.08 modify
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// 
BOOL CPersonMgrTitleView::IsLogin(){

	CPersonMgrDoc*		pDoc = GetDocument( );
	return pDoc->m_bLogin;
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// 
int CPersonMgrTitleView::GetPrintHeight(){
	
	int					iHeight = 0;
	CPersonMgrDoc*		pDoc = GetDocument();

	// 公司名与主题
	iHeight = CO_FONTSIZE * 2;
	// 日期与页数
	iHeight += pDoc->m_nTextHeight;
	// 画一根线
	iHeight += LINE_HEIGHT + 10;
	return	iHeight;

}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView message handlers
// 
int CPersonMgrTitleView::PrintBody(int nStartY, CDC *pDC, CPrintInfo *pInfo){

	int				iY = 0;
	int				iX = 0;
	CPersonMgrDoc*	pDoc = GetDocument();
	CRect			nRect;
	CFont			font;
	CFont			*pOldFont;
	CString			strValue;
	int				nLeft;
	int				nRight;

	font.CreatePointFont(CO_FONTSIZE, "Arial", pDC);
	pOldFont = pDC->SelectObject(&font);
	nLeft = UP_BOARDLINE * pDoc->m_nPerMMPixel;
	nRight = nLeft + pDoc->m_nXMaxPixel;

	LOGFONT			logFont;
	pDC->GetCurrentFont()->GetLogFont(&logFont);

	// Person Info manager
	nRect.top = nStartY + iY;
	nRect.left = nLeft;
	nRect.bottom = nStartY + iY + CO_FONTSIZE;
	nRect.right = nRight;
	strValue = "Person Infomation Manager System";
	pDC->DrawText(strValue, &nRect, DT_SINGLELINE|DT_CENTER);
	iY += CO_FONTSIZE;
	// title 信息
	nRect.top = nStartY + iY;
	nRect.bottom = nStartY + iY + CO_FONTSIZE;
	strValue = pDoc->m_curTable;
	pDC->DrawText(strValue, &nRect, DT_SINGLELINE|DT_CENTER);
	iY += CO_FONTSIZE;
	pDC->SelectObject(pOldFont);
	// 时间信息	
	strValue = _T("Date: ");
	CTime	nTime = CTime::GetCurrentTime();
	strValue += nTime.Format("%Y-%m-%d");
	pDC->TextOut(nLeft, nStartY + iY, strValue);
	// 页次信息	
	strValue.Format("Page: %d of %d", pInfo->m_nCurPage, pInfo->GetMaxPage());
	CSize			nSize;
	nSize = pDC->GetTextExtent(strValue);
	iX = nRight - nSize.cx;
	pDC->TextOut(iX, nStartY + iY, strValue);	
	iY += pDoc->m_nTextHeight;

	pDoc->DrawLine(pDC, nLeft, iY+nStartY+LINE_HEIGHT, 
		nRight, iY+nStartY+LINE_HEIGHT, PS_SOLID, 10);

	iY += LINE_HEIGHT + 20;
	return	iY;
}
