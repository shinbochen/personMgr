// PersonMgrTreeView.h : interface of the CPersonMgrTreeView class
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "PersonMgrDoc.h"
#include "CtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_PERSONMGRTREEVIEW_H__AAFD4417_5CD3_4F7C_8AC8_C959EDEFB1AD__INCLUDED_)
#define AFX_PERSONMGRTREEVIEW_H__AAFD4417_5CD3_4F7C_8AC8_C959EDEFB1AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPersonMgrTreeView : public CTreeView
{
protected: // create from serialization only
	CPersonMgrTreeView();
	DECLARE_DYNCREATE(CPersonMgrTreeView)

// Attributes
public:
	// save the root item
	CTreeCursor			m_tRoot;

	CTreeCursor			m_tAccount;
	CTreeCursor			m_tPlan;
	CTreeCursor			m_tContact;
	CTreeCursor			m_tFamily;
	CTreeCursor			m_tCall;

	CTreeCursor			m_tOther;
	// save the current select item
	CTreeCursor			m_tItemSel;		
	COLORREF			m_crBack;
	COLORREF			m_crText;
	
// Operations
public:
	CPersonMgrDoc*	GetDocument();
	BOOL			CompareStringOnID( UINT nID, LPCTSTR lpStr1, LPCTSTR lpStr2 );
	CTreeCursor		FindTreeCurByStrID( UINT nID );
	void			AddItem( CString strFunc, UINT nID, BOOL bFlag );
	BOOL			IsBePartOf( LPCTSTR lpszValue, UINT nID );
	void			AddItem( CString strFunc, BOOL bFlag );
	void			PopulateTree( );
	virtual			~CPersonMgrTreeView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMgrTreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPersonMgrTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersonMgrTreeView.cpp
inline CPersonMgrDoc* CPersonMgrTreeView::GetDocument()
   { return (CPersonMgrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMGRTREEVIEW_H__AAFD4417_5CD3_4F7C_8AC8_C959EDEFB1AD__INCLUDED_)
