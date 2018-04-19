/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
// CONSTANTS declare
#if !defined(AFX_LOGINDLG_H__5C6074A5_8451_4B37_BD77_3A75506F2516__INCLUDED_)
#define AFX_LOGINDLG_H__5C6074A5_8451_4B37_BD77_3A75506F2516__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "DialogEx.h"
#include "ButtonEx.h"

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{

// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	CLoginDlg(CMapStringToString *pMapUserPSD, CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGINDLG };
	CStatic	m_ctrLogBmp;
	CButtonEx	m_btHelp;
	CButtonEx	m_ctrOK;
	CButtonEx	m_ctrCancel;

	CComboBox	m_ctrCombo;
	CString		m_strPSD;
	CString		m_strUser;
	//}}AFX_DATA

// attribute
public:
	CMapStringToString*		m_pMapUserPSD;
	COLORREF				m_bkCr;
	CBrush					m_bkBrush;
// operator
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHelp();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__5C6074A5_8451_4B37_BD77_3A75506F2516__INCLUDED_)
