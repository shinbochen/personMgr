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
	CString		m_linktext;		// shell ���õ����Ӳ���
	BOOL		m_bClicked;		// ����Ƿ񵥻�������
	HCURSOR		m_hCursor;		// ����ƶ�����������ʱ�������״

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
	BOOL		m_bcaptured;		//��׽����ƶ�
	COLORREF	m_crClicked;		//���������Ӻ��ı�����ɫ
	COLORREF	m_crMoveOn;			//����ƶ���������ʱ���ı�����ɫ
	COLORREF	m_crOrdinary;		//δ�������ʱ�ı�����ɫ
	LOGFONT		m_lf;          
	CFont		m_font;				//�������ϵ��ı�������
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERLINK_H__BCD26D29_AB04_4FD7_9700_2335C4E77CA4__INCLUDED_)
