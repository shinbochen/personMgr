#if !defined(AFX_TOOLBAREX_H__BF07FE2C_AA93_461E_8B82_BF3E4DD65A26__INCLUDED_)
#define AFX_TOOLBAREX_H__BF07FE2C_AA93_461E_8B82_BF3E4DD65A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx window

class CToolBarEx : public CToolBar
{
// Construction
public:
	CToolBarEx();

// Attributes
public:
	int			m_nX;
	int			m_nY;

	int			m_nX0;
	UINT		m_nTimer;
	CString		m_strUser;
	CString		m_strPrev;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	void		SetUser( CString strUser ){ m_strUser = strUser;}
	CString		GetString( );
	void		MoveText( );
	void		DrawSeparator(CDC* pDC, int nCnt );
	void		OnDrawSelect( CDC* pDC, int nCnt, int nIID );
	void		OnDrawNormal( CDC* pDC, int nCnt, int nIID );
	void		OnDrawNormalD( CDC* pDC, int nCnt, int nIID );
	int			GetItemWidth( );
	virtual		~CToolBarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAREX_H__BF07FE2C_AA93_461E_8B82_BF3E4DD65A26__INCLUDED_)
