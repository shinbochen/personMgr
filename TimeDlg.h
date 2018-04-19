/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog
#if !defined(AFX_TIMEDLG_H__02780114_6D5E_48C4_A527_38A1C93C1A49__INCLUDED_)
#define AFX_TIMEDLG_H__02780114_6D5E_48C4_A527_38A1C93C1A49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "ButtonEx.h"

enum{
	HOUR_FOCUS = 1,
	MINUTE_FOCUS = 2,
	SECOND_FOCUS = 4 };

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

class CTimeDlg : public CDialog
{
// Construction
public:
	CTimeDlg(CWnd* pParent = NULL);   // standard constructor
	CTimeDlg(CString strEmpty, CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CTimeDlg)
	enum { IDD = IDD_TIMEDLG };
	CButtonEx		m_btOk;
	CButtonEx		m_btCancel;
	CBitmapButton	m_btUp;
	CBitmapButton	m_btDown;
	UINT			m_nHour;
	UINT			m_nMinute;
	UINT			m_nSecond;
	//}}AFX_DATA

// attribute
public:
	int				m_nFocus;
	BOOL			m_bHaveTime;
// operatore
public:
	CString			GetTimeString( );
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	afx_msg void OnSetfocusEditHour();
	afx_msg void OnSetfocusEditMinute();
	afx_msg void OnSetfocusEditSecond();
	afx_msg void OnKillfocusEditHour();
	afx_msg void OnKillfocusEditMinute();
	afx_msg void OnKillfocusEditSecond();
	afx_msg void OnDown();
	afx_msg void OnUp();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__02780114_6D5E_48C4_A527_38A1C93C1A49__INCLUDED_)
