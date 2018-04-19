// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__29D3C94A_5077_4F5B_A91D_8ADD33235586__INCLUDED_)
#define AFX_STDAFX_H__29D3C94A_5077_4F5B_A91D_8ADD33235586__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/////////////////////////////////////////////////////////////////////////
// user define
#define BKRCOLOR			0xd4	//135
#define BKGCOLOR			0xd0	//171
#define	BKBCOLOR			0xc8	//168

//////////////////////////////////////////////////////////////////////////
// include file
// 多媒体支持
#include "mmsystem.h"
// html help 支持
//#include <htmlhelp.h>

///////////////////////////////////////////////////////////////////////////
// local function declare
CString GetModulePath( );
// BOOL	GetIDESeriala( CString&	strText );
// CString GetRegisterCodea( CString strSN );
CString	ChangeVariantToString( COleVariant& varValue, BOOL bFlag );
BOOL	GetDate( CString strValue, CTime& time );
BOOL	GetVariantFromString( COleVariant& varValue, short nDataType, 
						   CString strValue );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__29D3C94A_5077_4F5B_A91D_8ADD33235586__INCLUDED_)
