/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "PersonMgrDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_PERSONMGRTITLEVIEW_H__0FF2A588_E090_4573_AB9B_46EAF5E2BEDF__INCLUDED_)
#define AFX_PERSONMGRTITLEVIEW_H__0FF2A588_E090_4573_AB9B_46EAF5E2BEDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonMgrTitleView.h : header file
//

#define			CO_FONTSIZE			180		//定义打yin公司名时的字体(像素)
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrTitleView view

class CPersonMgrTitleView : public CView
{
protected:
	CPersonMgrTitleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPersonMgrTitleView)

// Attributes
public:

// Operations
public:
	int				PrintBody(int nStartY, CDC *pDC, CPrintInfo *pInfo);
	int				GetPrintHeight( );
	BOOL			IsLogin( );
	void			SetRegister( );
	void			SetAutoShutDown( );
	void			AddOrModifyUser( int nType );
	CPersonMgrDoc*	GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMgrTitleView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPersonMgrTitleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPersonMgrTitleView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersonMgrTreeView.cpp
inline CPersonMgrDoc* CPersonMgrTitleView::GetDocument()
   { return (CPersonMgrDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMGRTITLEVIEW_H__0FF2A588_E090_4573_AB9B_46EAF5E2BEDF__INCLUDED_)
