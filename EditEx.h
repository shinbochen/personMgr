/////////////////////////////////////////////////////////////////////////////
// CEditEx window ( can edit more type: such BOOL, number etc.)
// by shinbo on 2003/11/12
// edit type can be as following: bool, byte, short etc

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_EDITEX_H__F39788A9_237D_400B_AB8E_88B3403329C8__INCLUDED_)
#define AFX_EDITEX_H__F39788A9_237D_400B_AB8E_88B3403329C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		WM_UPKEY			WM_USER+200
#define		WM_DOWNKEY			WM_USER+201
#define		WM_ENTERKEY			WM_USER+202
#define		WM_CTRLENTER		WM_USER+203
#define		WM_SHIFTENTER		WM_USER+204


enum {
	SHIFT_FLAG = 0x01,
	CTRL_FLAG = 0x02
};

enum {
	ALL_TYPE = 0,
	BOOL_TYPE,
	BYTE_TYPE,
	INTEGER_TYPE,
	LONG_TYPE,
	DECIMAL_TYPE,
	DATETIME_TYPE,
	SIMPLETIME_TYPE};
/////////////////////////////////////////////////////////////////////////////
// CEditEx window

class CEditEx : public CEdit
{
// Construction
public:
	CEditEx();

// Attributes
public:
	CString			m_strWaring;
	int				m_nEditType;
	int				m_nKeyStatus;
	COLORREF		m_bkCr;
	COLORREF		m_textCr;
	CBrush			m_bkBrush;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL		CheckTimeValid( CString strText, CString& strWarning );
	BOOL		CheckDateValid( CString strDate, CString& strWaring);
	BOOL		CheckValue( CString& strNotify );
	BOOL		GetValue( CString& strValue );
	int			SetEditType( CString strEditType );
	virtual		~CEditEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditEx)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEX_H__F39788A9_237D_400B_AB8E_88B3403329C8__INCLUDED_)
