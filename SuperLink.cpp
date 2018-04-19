// SuperLink.cpp : implementation file
//

#include "stdafx.h"
#include "PersonMgr.h"
#include "SuperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperLink

CSuperLink::CSuperLink()
{
	m_bClicked=FALSE;     
	m_bcaptured=FALSE;

	m_crClicked = RGB(255, 0, 255);
	m_crMoveOn = RGB(255, 0, 0);
	m_crOrdinary = RGB(0, 0, 255);
	m_crText = m_crOrdinary;    

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf); 
	m_lf.lfUnderline = TRUE;     
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf); 
	ASSERT(bCreated);

	m_hCursor=NULL;       
}

CSuperLink::CSuperLink(COLORREF crClicked, COLORREF crMoveOn, COLORREF crOordinary)
{
	m_bClicked=FALSE;     
	m_bcaptured=FALSE;

	m_crClicked = crClicked;
	m_crMoveOn = crMoveOn;
	m_crOrdinary = crOordinary;
	m_crText = m_crOrdinary;    

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf); 
	m_lf.lfUnderline = TRUE;     
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf); 
	ASSERT(bCreated);

	m_hCursor=NULL;       
}

CSuperLink::~CSuperLink()
{
	m_font.DeleteObject();  
}


BEGIN_MESSAGE_MAP(CSuperLink, CStatic)
	//{{AFX_MSG_MAP(CSuperLink)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperLink message handlers

HBRUSH CSuperLink::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor){
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
	}
	HBRUSH hBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE)); 
	return hBrush;
}

void CSuperLink::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bClicked=TRUE;         
	m_crText=m_crClicked;  
	RedrawWindow();
	if(m_linktext!="")  
		ShellExecute(NULL, "open", m_linktext, NULL, NULL, SW_SHOWNORMAL);  
	
	CStatic::OnLButtonDown(nFlags, point);
}

BOOL CSuperLink::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CSuperLink::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture(); 
	POINT mpoint;   
	GetCursorPos(&mpoint);
	CRect rect;
	GetWindowRect(&rect); 
	if(!rect.PtInRect(mpoint))
	{
		m_bcaptured=FALSE;
		ReleaseCapture();
		MouseLeave();
		return;
	} 

	if(m_bcaptured)
		return;
	m_bcaptured=TRUE;
    MouseEnter();
	ReleaseCapture();
	
	CStatic::OnMouseMove(nFlags, point);
}

BOOL CSuperLink::SetLinkAddress(CString strLink)
{
	if(strLink.Find("http")!=-1)
		m_linktext = strLink;
	else if(strLink.Find("@")!=-1)
		m_linktext = "mailto:" + strLink;
	else
	{
		MessageBox("Error: wrong superlink format");
		m_linktext="";
		return FALSE;
	}
	return TRUE;
}

void CSuperLink::MouseLeave(void)
{
	m_crText = m_bClicked ? m_crClicked : m_crOrdinary;
	RedrawWindow();
}

void CSuperLink::MouseEnter(void)
{
	m_crText = m_bClicked ? m_crClicked : m_crMoveOn;
	RedrawWindow();
}

void CSuperLink::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}

void CSuperLink::SetSuperLink(BOOL setlink)
{
	if (setlink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);
}

