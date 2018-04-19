// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "splitterWndEx.h"
#include "StatusBarEx.h"
#include "toolbarEx.h"
#include "MenuEx.h"
#include "tray.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_MAINFRM_H__F5F90339_1EEF_4352_A00B_710CFECE1B37__INCLUDED_)
#define AFX_MAINFRM_H__F5F90339_1EEF_4352_A00B_710CFECE1B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWndEx		m_parSplitWnd;
	CSplitterWndEx		m_subSplitWnd;
	CStatusBarEx		m_wndStatusBar;
	CToolBarEx			m_wndToolBar; 
	CTray				m_oTray;	  

	// 菜单
	CMenuEx				m_nMenu;
	// 记录短语的中英文对照
	CMapStringToString	m_mapPhrase;
	int					m_nLangID;
	BOOL				m_bDynamic;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// inline
public:
	void			SetDynamicDlg( BOOL bDynamic ){ m_bDynamic = bDynamic;}
	BOOL			IsDynamicDlg( ){ return m_bDynamic;}
	void			SetLangID( int nLangID ){ m_nLangID = nLangID; }
	int				GetLangID( ){ return m_nLangID;}
public:
	// 重新设置所有
	void			Reset( );
	void			Refresh();
	CString			LoadStringA( int nID );
	// 得到反转的字符
	CString			GetReversePhrase( CString strReverse );
	// 根据语言状态得到相应显示的数据
	CString			GetDispPhrase( CString strEn );
	// 初始化中英文对照的短语
	// 成功返回TRUE
	BOOL			InitPhrase( );
	void			Register( );
	void			AutoShutDown( );
	void			GetShutDownPrivilege( );
// attribute
public:
	void			DrawMenu( CWindowDC*	pDC );
	void			GetMenuRect( CRect& rect );
	void			DrawBottom( CWindowDC*	pDC );
	void			GetBottomRect( CRect& rect );
	void			DrawRightBoard( CWindowDC*	pDC );
	void			GetRightBoardRect( CRect&  rect );
	void			DrawLeftBoard( CWindowDC*	pDC );
	void			GetLeftBoardRect( CRect& rect );
	void			DrawSystemButton( CWindowDC*	pDC );
	void			DrawCaption( CWindowDC*	pDC );
	void			GetButtonRect( CRect& rect );
	void			GetCaptionRect( CRect&  rect );
	void			PopulateTreeView( );


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRefresh();
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModify(CCmdUI* pCmdUI);
	afx_msg void OnDelete();
	afx_msg void OnInsert();
	afx_msg void OnModify();
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnAdduser();
	afx_msg void OnChgpsd();
	afx_msg void OnCalculator();
	afx_msg void OnShutdown();
	afx_msg void OnDeleteuser();
	afx_msg void OnSetupAutosd();
	afx_msg void OnRegister();
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam );		
	afx_msg int	 OnTray(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnNcPaint( );
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	afx_msg void OnUpdateChinese(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnglish(CCmdUI* pCmdUI);
	afx_msg void OnEnglish();
	afx_msg void OnChinese();
	afx_msg void OnDynamic();
	afx_msg void OnUpdateDynamic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRegister(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F5F90339_1EEF_4352_A00B_710CFECE1B37__INCLUDED_)
