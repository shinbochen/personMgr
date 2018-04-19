// Tray.h: interface for the CTray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAY_H__9FD1C079_A73F_4E6D_95DE_1501112340AD__INCLUDED_)
#define AFX_TRAY_H__9FD1C079_A73F_4E6D_95DE_1501112340AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTray : public CObject  
{
public:
	CTray();
	virtual ~CTray();
// operator
public:
	BOOL Creat(CWnd *pWnd, UINT nCallBackMessage, LPCSTR strToolTip, HICON hIcon, UINT uID);

// attribute
public:
	NOTIFYICONDATA	m_nid;
	CFrameWnd		*m_pWnd;
	UINT			m_uID;
	HICON			m_hIcon;
	BOOL			m_bEnabled;
};

#endif // !defined(AFX_TRAY_H__9FD1C079_A73F_4E6D_95DE_1501112340AD__INCLUDED_)
