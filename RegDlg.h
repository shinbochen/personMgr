/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_REGDLG_H__797A5F96_C675_4B71_923F_833B3E620466__INCLUDED_)
#define AFX_REGDLG_H__797A5F96_C675_4B71_923F_833B3E620466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#include "dialogex.h"
#include "buttonex.h"
#include "superLink.h"
/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialogEx{
// Construction
public:
	CRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REGDLG };
	CButtonEx	m_btOK;
	CButtonEx	m_btCancel;
	CString	m_strRegCode;
	//}}AFX_DATA

// attribute
public:
	COLORREF			m_bkCr;
	CBrush				m_bkBrush;
	CSuperLink			m_ctrWebsite;
	CSuperLink			m_ctrEmail;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__797A5F96_C675_4B71_923F_833B3E620466__INCLUDED_)
