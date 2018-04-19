
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog
// include file declare
#include "EditEx.h"
#include "DialogEx.h"
#include "buttonEx.h"
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog
// CONSTANTS declare
#if !defined(AFX_EDITDLG_H__E7A1C1E7_BA06_448C_98FF_213BC896466B__INCLUDED_)
#define AFX_EDITDLG_H__E7A1C1E7_BA06_448C_98FF_213BC896466B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
/////////////////////////////////////////////////////////////////////////////
// enum declare
enum{
	MORE_TIME = 1,
	MORE_DATE,
	MORE_MELODY,
	MORE_SELECT};

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialogEx
{
// Construction
public:
	CEditDlg(CWnd* pParent = NULL);   // standard constructor
	CEditDlg( CStringArray*	pArrColumn, 
			  CMapStringToString* pMapDataType,
		      CMapStringToString* pMapDataValue, 
			  CMapStringToString* pMapHelpInfo = NULL,
			  CWnd* pParent = NULL );
			  


// attribute
public:
	CBrush					m_bkBrush;
	COLORREF				m_bkCr;

	CMapStringToString*		m_pMapHelpInfo;
	CMapStringToString*		m_pMapDataType;
	CStringArray*			m_pArrColumn;
	CMapStringToString*		m_pMapDataValue;

	CString					m_strTitle;

	int						m_nCurSel;

	int						m_nMoreType;
// operator
public:
	void					JudgeCanMore(CString strColumn, CString strType );
	CString					GetDefaultValue( CString strKey );
	BOOL					IsAllValueValid( );
	BOOL					SelChangeListTo( int nNewSel );
	void					SetEditTypeAndData( );
	void					SetHelpInfo( );
	void					SetDlgTitle( CString strTitle ){ m_strTitle = strTitle; }

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDITDLG };
	CBitmapButton	m_btStop;
	CBitmapButton	m_btPause;
	CBitmapButton	m_btPlay;
	CButtonEx	m_ctrMore;
	CButtonEx	m_ctrOK;
	CButtonEx	m_ctrCancel;
	CStatic		m_ctrColumnName;
	CStatic		m_ctrHelpInfo;
	CListBox	m_ctrListValue;
	CEditEx		m_ctrEdit;
	CListBox	m_ctrListColumn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeColumnlist();
	afx_msg void OnSetfocusColumnlist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMore();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnDblclkColumnlist();
	//}}AFX_MSG
	afx_msg LRESULT OnUpCtrKeyDown(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnDownCtrKeyDown(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnEnterCtrKeyDown(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnCtrlEnterDown(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnShiftEnterDown(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__E7A1C1E7_BA06_448C_98FF_213BC896466B__INCLUDED_)
