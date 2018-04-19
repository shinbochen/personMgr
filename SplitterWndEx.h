// SplitterWndEx.h: interface for the CSplitterWndEx class.
//
//////////////////////////////////////////////////////////////////////
// include file declare
#include <afxExt.h>
//////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_SPLITTERWNDEX_H__3B27FAB3_BE28_4B9A_A794_10E8F9E67A55__INCLUDED_)
#define AFX_SPLITTERWNDEX_H__3B27FAB3_BE28_4B9A_A794_10E8F9E67A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplitterWndEx : public CSplitterWnd  
{
public:
	CSplitterWndEx();
	virtual ~CSplitterWndEx();

// Implementation
protected:
	virtual void OnDrawSplitter(
	   CDC* pDC,
	   ESplitType nType,
	   const CRect& rect 
	);

	// Generated message map functions
	//{{AFX_MSG(CSplitterWndEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SPLITTERWNDEX_H__3B27FAB3_BE28_4B9A_A794_10E8F9E67A55__INCLUDED_)
