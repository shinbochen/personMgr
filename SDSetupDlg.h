///////////////////////////////////////////////////////////////////////
// include file declare
#include "ButtonEx.h"
#include "EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_SDSETUPDLG_H__25B968E8_EE91_45A4_A109_876FAAC93C67__INCLUDED_)
#define AFX_SDSETUPDLG_H__25B968E8_EE91_45A4_A109_876FAAC93C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg dialog

class CSDSetupDlg : public CDialog
{
// Construction
public:
	CSDSetupDlg(CWnd* pParent = NULL);   // standard constructor
	CSDSetupDlg(CString strTime, BOOL bOn, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSDSetupDlg)
	enum { IDD = IDD_SDSETUPDLG };
	CComboBox	m_ctrComBox;
	CEditEx		m_ctrEdit;
	CButtonEx	m_btOK;
	CButtonEx	m_btCancel;
	CButtonEx	m_btSetTime;
	int			m_nEnable;
	CString		m_strTime;
	//}}AFX_DATA

// attribute
public:
	COLORREF	m_bkCr;
	CBrush		m_bkBrush;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSDSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEdittime();
	afx_msg void OnSettime();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDSETUPDLG_H__25B968E8_EE91_45A4_A109_876FAAC93C67__INCLUDED_)
