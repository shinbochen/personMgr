// Tray.cpp: implementation of the CTray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonMgr.h"
#include "Tray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTray::CTray(){
	memset(&m_nid,0,sizeof(&m_nid));
	m_bEnabled=FALSE;
}

CTray::~CTray(){
	Shell_NotifyIcon(NIM_DELETE,&m_nid);
}
//////////////////////////////////////////////////////////////////////
// ½¨Á¢ÍÐpan
BOOL CTray::Creat(CWnd *pWnd, UINT nCallBackMessage, 
				  LPCSTR strToolTip, HICON hIcon, UINT uID){
	//only allow windows 98 or higher
	VERIFY( m_bEnabled = (LOBYTE(LOWORD(GetVersion()))>=4) );
	if(!m_bEnabled){
		return FALSE;
	}
	//make sure the notifation window is valid
	VERIFY( m_bEnabled = ( pWnd && ::IsWindow( pWnd->GetSafeHwnd() ) ) );
	if(!m_bEnabled){
		return FALSE;
	}
	//make sure the nCallBackMessage is user define
	ASSERT( nCallBackMessage >= WM_USER+100);
	//make sure the tooltip length lessthan 64
	ASSERT( strlen(strToolTip) <= 64);
	//load up the NotifyIcondata;
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hIcon = hIcon;
	m_nid.hWnd = pWnd->GetSafeHwnd();
	strncpy( m_nid.szTip, strToolTip, 64);
	*(m_nid.szTip+64) = 0;
	m_nid.uCallbackMessage = nCallBackMessage;
	m_nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_nid.uID = uID;
	//backup some thing to this class
	m_pWnd = (CFrameWnd *)pWnd;

	VERIFY( Shell_NotifyIcon(NIM_ADD,&m_nid) );
	return m_bEnabled;
}
