#if !defined(AFX_BUTTONEX_H__3ABB5C01_A83A_4DFB_AB1B_499802EF088F__INCLUDED_)
#define AFX_BUTTONEX_H__3ABB5C01_A83A_4DFB_AB1B_499802EF088F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonEx window

class CButtonEx : public CButton
{
// Construction
public:
	CButtonEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_nTimer;
	void DrawButton( COLORREF  crBack, COLORREF crText);
	virtual ~CButtonEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonEx)
	afx_msg void OnMove(int x, int y);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONEX_H__3ABB5C01_A83A_4DFB_AB1B_499802EF088F__INCLUDED_)
