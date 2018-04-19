/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "PersonMgrDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_PERSONMGRLISTVIEW_H__7508CC7E_1F62_4351_8E97_545757C7A934__INCLUDED_)
#define AFX_PERSONMGRLISTVIEW_H__7508CC7E_1F62_4351_8E97_545757C7A934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonMgrListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrListView view

class CPersonMgrListView : public CListView
{
protected:
	CPersonMgrListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPersonMgrListView)

// Attributes
public:
	BOOL				m_bAsc;
	int					m_nSortedCol;
	COLORREF			m_crBack;
	int					m_nColumn;
	CMapStringToString	m_mapDataValue;

	int					m_nSum;

// Operations
public:
	void PrintBody(int nStartY, CDC *pDC, CPrintInfo *pInfo);
	CString GetWebSite( );
	BOOL CanBrowse( );
	int FindColFromName( CString strColName );
	CString GetCurSelValueFromKeyCol( CString strKeyCol );
	CString GetKeyColumn( UINT nID );
	BOOL CanEmail( );
	CString GetEmail( );
	CString			GetSortString( );
	BOOL			CanRefresh( );
	BOOL			CanDelete( );
	BOOL			CanModify( );
	BOOL			CanInsert( );
	void			GetPreDataValue( CStringArray& arrColumn, int nItem );
	void			OnModify( );
	void			OnInsert( );
	void			OnDelete( );
	void			OnUpdateRefresh(CCmdUI* pCmdUI);
	void			OnUpdateModifyL(CCmdUI* pCmdUI);
	void			OnUpdateInsertL(CCmdUI* pCmdUI);
	void			OnUpdateDeleteL(CCmdUI* pCmdUI);
	void			AdjustColumnWidths( );
	void			Refresh( );
	void			EraseList( );
	void			InitView( );
	CPersonMgrDoc*	GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMgrListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPersonMgrListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPersonMgrListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsert1();
	afx_msg void OnDelete1();
	afx_msg void OnModify1();
	afx_msg void OnRefresh1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEmail();
	afx_msg void OnBrowse();
	afx_msg void OnUpdateEmail(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrowse(CCmdUI* pCmdUI);
	afx_msg void OnCopyemail();
	afx_msg void OnCopyweb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersonMgrTreeView.cpp
inline CPersonMgrDoc* CPersonMgrListView::GetDocument()
   { return (CPersonMgrDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMGRLISTVIEW_H__7508CC7E_1F62_4351_8E97_545757C7A934__INCLUDED_)
