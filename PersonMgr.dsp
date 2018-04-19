# Microsoft Developer Studio Project File - Name="PersonMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PersonMgr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PersonMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PersonMgr.mak" CFG="PersonMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PersonMgr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PersonMgr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PersonMgr - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "c:\program files\html help workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /machine:I386 /libpath:"c:\program files\html help workshop\lib"

!ELSEIF  "$(CFG)" == "PersonMgr - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "c:\program files\html help workshop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"c:\program files\html help workshop\lib"

!ENDIF 

# Begin Target

# Name "PersonMgr - Win32 Release"
# Name "PersonMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonEx.cpp
# End Source File
# Begin Source File

SOURCE=.\calendar.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlExt.cpp
# End Source File
# Begin Source File

SOURCE=.\DateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuEx.cpp
# End Source File
# Begin Source File

SOURCE=.\NMUserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgr.rc
# End Source File
# Begin Source File

SOURCE=.\PersonMgrDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgrListView.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgrQueryView.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgrTitleView.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMgrTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SDSetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterWndEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SuperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Tray.cpp
# End Source File
# Begin Source File

SOURCE=.\GetIDESN.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlarmDlg.h
# End Source File
# Begin Source File

SOURCE=.\ButtonEx.h
# End Source File
# Begin Source File

SOURCE=.\calendar.h
# End Source File
# Begin Source File

SOURCE=.\CtrlExt.h
# End Source File
# Begin Source File

SOURCE=.\CtrlExt.inl
# End Source File
# Begin Source File

SOURCE=.\DateDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogEx.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuEx.h
# End Source File
# Begin Source File

SOURCE=.\NMUserDlg.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgr.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgrDoc.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgrListView.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgrQueryView.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgrTitleView.h
# End Source File
# Begin Source File

SOURCE=.\PersonMgrTreeView.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\RegDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SDSetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\SplitterWndEx.h
# End Source File
# Begin Source File

SOURCE=.\StatusBarEx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SuperLink.h
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarEx.h
# End Source File
# Begin Source File

SOURCE=.\Tray.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\down1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\LOGIN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.jpg
# End Source File
# Begin Source File

SOURCE=.\res\login1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PersonMgr.ico
# End Source File
# Begin Source File

SOURCE=.\res\PersonMgr.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PersonMgrDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TREEVIEW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.ico
# End Source File
# Begin Source File

SOURCE=.\res\up1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section PersonMgr : {8E27C92B-1264-101C-8A2F-040224009C02}
# 	2:21:DefaultSinkHeaderFile:calendar.h
# 	2:16:DefaultSinkClass:CCalendar
# End Section
# Section PersonMgr : {8E27C92C-1264-101C-8A2F-040224009C02}
# 	2:5:Class:CCalendar
# 	2:10:HeaderFile:calendar.h
# 	2:8:ImplFile:calendar.cpp
# End Section
# Section PersonMgr : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
