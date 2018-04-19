/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog
// CONSTANTS declare
//{{AFX_INCLUDES()
#include "calendar.h"
//}}AFX_INCLUDES
#if !defined(AFX_DATEDLG_H__04EB7EC8_F35F_4CEF_8BF9_308A6AC3435D__INCLUDED_)
#define AFX_DATEDLG_H__04EB7EC8_F35F_4CEF_8BF9_308A6AC3435D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog
// include file declare
#include "DialogEx.h"
#include "ButtonEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog

class CDateDlg : public CDialogEx
{
// Construction
public:
	CString GetDateString( );
	CDateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDateDlg)
	enum { IDD = IDD_DATEDLG };
	CButtonEx	m_btSetTime;
	CButtonEx	m_ctrOK;
	CButtonEx	m_ctrCancel;
	CString	m_strTime;
	CCalendar	m_ctrCalendar;
	//}}AFX_DATA
public:
	CString		m_strDate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetTime();
	virtual void OnOK();
	afx_msg void OnDblClickCalendar1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEDLG_H__04EB7EC8_F35F_4CEF_8BF9_308A6AC3435D__INCLUDED_)
