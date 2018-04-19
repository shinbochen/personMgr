#if !defined(AFX_DIALOGEX_H__72E86D14_DE1F_4AAE_957B_DD5BBB020AA9__INCLUDED_)
#define AFX_DIALOGEX_H__72E86D14_DE1F_4AAE_957B_DD5BBB020AA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog

class CDialogEx : public CDialog
{
// Construction
public:
	CDialogEx(UINT nID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogEx)
	//enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	CRect		m_nRect;
	int			m_nX;
	int			m_nY;
	int			m_nX2;
	int			m_nY2;

	int			m_nType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEX_H__72E86D14_DE1F_4AAE_957B_DD5BBB020AA9__INCLUDED_)
