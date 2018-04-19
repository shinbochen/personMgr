/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog
// CONSTANTS declare
#if !defined(AFX_ALARMDLG_H__930E7E8C_F02D_4D45_B233_143FEB20369E__INCLUDED_)
#define AFX_ALARMDLG_H__930E7E8C_F02D_4D45_B233_143FEB20369E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog
#include "DialogEx.h"
#include "ButtonEx.h"

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog
// global variable declare
static int  s_nCnt;
/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog

class CAlarmDlg : public CDialogEx {
// Construction
public:
	CAlarmDlg(CWnd* pParent = NULL);   // standard constructor
	CAlarmDlg(CString strType, CString strNote, CString strMelody, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmDlg)
	enum { IDD = IDD_ALARMDLG };
	CButtonEx	m_ctrCancel;
	CString		m_strAlarmType;
	CString		m_strNote;
	CString		m_strTime;
	//}}AFX_DATA

public:
	CString		m_strMelody;
	COLORREF	m_bkCr;
	CBrush		m_bkBrush;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDLG_H__930E7E8C_F02D_4D45_B233_143FEB20369E__INCLUDED_)
