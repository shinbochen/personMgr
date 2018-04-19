/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
#include  "buttonex.h"
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
#if !defined(AFX_NMUSERDLG_H__37659E4D_235E_4A96_BB37_921A97586A85__INCLUDED_)
#define AFX_NMUSERDLG_H__37659E4D_235E_4A96_BB37_921A97586A85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Enum declare
enum{
	NONETYPE = 0,
	NEWUSER,
	CHGPSD,
	DELETEUSER};

/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog

class CNMUserDlg : public CDialog
{
// Construction
public:
	CNMUserDlg( CWnd* pParent = NULL );   // standard constructor
	CNMUserDlg( CMapStringToString* pMap, 
				int nType = NONETYPE,
				CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNMUserDlg)
	enum { IDD = IDD_NMUSERDLG };
	CButtonEx	m_btOK;
	CButtonEx	m_btCancel;
	CComboBox	m_ctrCombo;
	CString	m_strNewPSD;
	CString	m_strCfmPSD;
	CString	m_strOldPSD;
	CString	m_strUser;
	//}}AFX_DATA

// attribute
public:

	COLORREF			m_bkCr;
	CBrush				m_bBrush;

	CString				m_strTitle;
	int					m_nType;
	CMapStringToString*	m_pMapUserPSD;
// operator
public:
	BOOL				IsNewUser( CString strUser );
	BOOL				ChkDataValid( );
	void				SetUser( CString strUser ){ m_strUser = strUser; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNMUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNMUserDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NMUSERDLG_H__37659E4D_235E_4A96_BB37_921A97586A85__INCLUDED_)
