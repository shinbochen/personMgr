// StatusBarEx.h: interface for the CStatusBarEx class.
//
//////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_STATUSBAREX_H__BE1BDFD0_F482_4995_AC1B_C980161E383D__INCLUDED_)
#define AFX_STATUSBAREX_H__BE1BDFD0_F482_4995_AC1B_C980161E383D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////
// Class declare
class CStatusBarEx : public CStatusBar  
{
public:
	
	DECLARE_DYNCREATE(CStatusBarEx)
	CStatusBarEx();
	virtual ~CStatusBarEx();

public:
	COLORREF	m_BKCr;
	CBrush		m_BKBrush;

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarEx)	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_STATUSBAREX_H__BE1BDFD0_F482_4995_AC1B_C980161E383D__INCLUDED_)
