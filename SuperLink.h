#if !defined(AFX_SUPERLINK_H__BCD26D29_AB04_4FD7_9700_2335C4E77CA4__INCLUDED_)
#define AFX_SUPERLINK_H__BCD26D29_AB04_4FD7_9700_2335C4E77CA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SuperLink.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CSuperLink window

class CSuperLink : public CStatic
{
// Construction
public:
	CSuperLink();
	CSuperLink(COLORREF crClicked, COLORREF crMoveOn, COLORREF crOordinary);

// Attributes
public:

	BOOL SetLinkAddress(CString strLink); 

	void MouseLeave(void);
	void MouseEnter(void);
	void SetLinkCursor(HCURSOR hCursor); 

	void SetSuperLink(BOOL setlink);
	
protected:
	COLORREF	m_crText;
	CString		m_linktext;		// shell 调用的联接参数
	BOOL		m_bClicked;		// 鼠标是否单击超联接
	HCURSOR		m_hCursor;		// 鼠标移动到超联接上时的鼠标形状

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperLink)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSuperLink();

	// Generated message map functions
protected:
public:
	//{{AFX_MSG(CSuperLink)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	BOOL		m_bcaptured;		//捕捉鼠标移动
	COLORREF	m_crClicked;		//单击超联接后文本的颜色
	COLORREF	m_crMoveOn;			//鼠标移动到超联接时的文本的颜色
	COLORREF	m_crOrdinary;		//未激活超联接时文本的颜色
	LOGFONT		m_lf;          
	CFont		m_font;				//超联接上的文本的字体
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERLINK_H__BCD26D29_AB04_4FD7_9700_2335C4E77CA4__INCLUDED_)
