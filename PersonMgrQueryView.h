/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "PersonMgrDoc.h"
#include "buttonEx.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_PERSONMGRQUERYVIEW_H__4FBA6FD6_82B7_4DBC_89E7_B472EF5DD3AB__INCLUDED_)
#define AFX_PERSONMGRQUERYVIEW_H__4FBA6FD6_82B7_4DBC_89E7_B472EF5DD3AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonMgrQueryView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrQueryView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPersonMgrQueryView : public CFormView
{
protected:
	CPersonMgrQueryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPersonMgrQueryView)

// Form Data
public:
	//{{AFX_DATA(CPersonMgrQueryView)
	enum { IDD = IDD_QUERYDLG };
	CButtonEx	m_btnExcute;
	CComboBox	m_ctrComboBox3;
	CComboBox	m_ctrComboBox2;
	CComboBox	m_ctrComboBox1;
	//}}AFX_DATA

// Attributes
public:
	COLORREF			m_crBack;
	CBrush				m_bkBrush;
	CMapStringToString	m_mapQueryInfo;

// Operations
public:
	CString				GetFilterString( );
	void				SetComboDataFromMapString( UINT nID, CMapStringToString *pMapString);
	void				DeleteItemFromCombo( );
	void				DeleteItemFromCombo( CComboBox* pCombo );
	void				ShowView( );
	void				ShowAllItem( );
	void				HideAllItem( );
	void				HideView( );
	void				InitView( );
	CPersonMgrDoc*		GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMgrQueryView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPersonMgrQueryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPersonMgrQueryView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnExcute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersonMgrTreeView.cpp
inline CPersonMgrDoc* CPersonMgrQueryView::GetDocument()
   { return (CPersonMgrDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMGRQUERYVIEW_H__4FBA6FD6_82B7_4DBC_89E7_B472EF5DD3AB__INCLUDED_)
