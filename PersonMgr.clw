; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "personmgr.h"
LastPage=0
CDK=Y

ClassCount=23
Class1=CAlarmDlg
Class2=CButtonEx
Class3=CListCtrlEx
Class4=CTreeCtrlEx
Class5=CDateDlg
Class6=CDialogEx
Class7=CEditDlg
Class8=CEditEx
Class9=CLoginDlg
Class10=CMainFrame
Class11=CNMUserDlg
Class12=CPersonMgrApp
Class13=CAboutDlg
Class14=CPersonMgrDoc
Class15=CPersonMgrListView
Class16=CPersonMgrQueryView
Class17=CPersonMgrTitleView
Class18=CPersonMgrTreeView
Class19=CRegDlg
Class20=CSDSetupDlg
Class21=CSuperLink
Class22=CTimeDlg
Class23=CToolBarEx

ResourceCount=12
Resource1=IDD_REGDLG
Resource2=IDD_EDITDLG
Resource3=IDD_SDSETUPDLG
Resource4=IDR_USERMENU
Resource5=IDD_NMUSERDLG
Resource6=IDD_ALARMDLG
Resource7=IDD_DATEDLG
Resource8=IDD_QUERYDLG
Resource9=IDD_TIMEDLG
Resource10=IDD_ABOUTBOX (English (U.S.))
Resource11=IDD_LOGINDLG
Resource12=IDR_MAINFRAME (English (U.S.))

[CLS:CAlarmDlg]
Type=0
BaseClass=CDialogEx
HeaderFile=AlarmDlg.h
ImplementationFile=AlarmDlg.cpp

[CLS:CButtonEx]
Type=0
BaseClass=CButton
HeaderFile=ButtonEx.h
ImplementationFile=ButtonEx.cpp

[CLS:CListCtrlEx]
Type=0
BaseClass=CListCtrl
HeaderFile=CtrlExt.h
ImplementationFile=CtrlExt.cpp

[CLS:CTreeCtrlEx]
Type=0
BaseClass=CTreeCtrl
HeaderFile=CtrlExt.h
ImplementationFile=CtrlExt.cpp

[CLS:CDateDlg]
Type=0
BaseClass=CDialogEx
HeaderFile=DateDlg.h
ImplementationFile=DateDlg.cpp

[CLS:CDialogEx]
Type=0
BaseClass=CDialog
HeaderFile=DialogEx.h
ImplementationFile=DialogEx.cpp

[CLS:CEditDlg]
Type=0
BaseClass=CDialogEx
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
LastObject=CEditDlg

[CLS:CEditEx]
Type=0
BaseClass=CEdit
HeaderFile=EditEx.h
ImplementationFile=EditEx.cpp
LastObject=IDC_REGISTER

[CLS:CLoginDlg]
Type=0
BaseClass=CDialog
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
LastObject=CLoginDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame
Filter=W
VirtualFilter=fWC

[CLS:CNMUserDlg]
Type=0
BaseClass=CDialog
HeaderFile=NMUserDlg.h
ImplementationFile=NMUserDlg.cpp

[CLS:CPersonMgrApp]
Type=0
BaseClass=CWinApp
HeaderFile=PersonMgr.h
ImplementationFile=PersonMgr.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=PersonMgr.cpp
ImplementationFile=PersonMgr.cpp
LastObject=IDC_EMAIL

[CLS:CPersonMgrDoc]
Type=0
BaseClass=CDocument
HeaderFile=PersonMgrDoc.h
ImplementationFile=PersonMgrDoc.cpp

[CLS:CPersonMgrListView]
Type=0
BaseClass=CListView
HeaderFile=PersonMgrListView.h
ImplementationFile=PersonMgrListView.cpp
LastObject=CPersonMgrListView

[CLS:CPersonMgrQueryView]
Type=0
BaseClass=CFormView
HeaderFile=PersonMgrQueryView.h
ImplementationFile=PersonMgrQueryView.cpp
Filter=D
VirtualFilter=VWC
LastObject=IDC_CHINESE

[CLS:CPersonMgrTitleView]
Type=0
BaseClass=CView
HeaderFile=PersonMgrTitleView.h
ImplementationFile=PersonMgrTitleView.cpp

[CLS:CPersonMgrTreeView]
Type=0
BaseClass=CTreeView
HeaderFile=PersonMgrTreeView.h
ImplementationFile=PersonMgrTreeView.cpp

[CLS:CRegDlg]
Type=0
BaseClass=CDialogEx
HeaderFile=RegDlg.h
ImplementationFile=RegDlg.cpp
LastObject=CRegDlg

[CLS:CSDSetupDlg]
Type=0
BaseClass=CDialog
HeaderFile=SDSetupDlg.h
ImplementationFile=SDSetupDlg.cpp

[CLS:CSuperLink]
Type=0
BaseClass=CStatic
HeaderFile=SuperLink.h
ImplementationFile=SuperLink.cpp

[CLS:CTimeDlg]
Type=0
BaseClass=CDialog
HeaderFile=TimeDlg.h
ImplementationFile=TimeDlg.cpp

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=ToolBarEx.h
ImplementationFile=ToolBarEx.cpp

[DLG:IDD_ALARMDLG]
Type=1
Class=CAlarmDlg
ControlCount=6
Control1=IDCANCEL,button,1342242827
Control2=IDC_ALARMTYPE,static,1342308865
Control3=IDC_NOTE,edit,1342242948
Control4=IDC_S_ALARMTIME,static,1342308352
Control5=IDC_TIME,static,1342308352
Control6=IDC_S_NOTE,static,1342308352

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=IDC_ADDUSER
Command2=IDC_CHGPSD
Command3=IDC_DELETEUSER
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=IDC_REGISTER
Command8=ID_APP_EXIT
Command9=IDC_REFRESH
Command10=IDC_INSERT
Command11=IDC_MODIFY
Command12=IDC_DELETE
Command13=IDC_EMAIL
Command14=IDC_BROWSE
Command15=IDC_CALCULATOR
Command16=IDC_SHUTDOWN
Command17=IDC_CHINESE
Command18=IDC_ENGLISH
Command19=IDC_SETUP_AUTOSD
Command20=IDC_DYNAMIC
Command21=ID_VIEW_TOOLBAR
Command22=ID_VIEW_STATUS_BAR
Command23=IDC_HELPINFO
Command24=ID_APP_ABOUT
CommandCount=24

[MNU:IDR_USERMENU]
Type=1
Class=?
Command1=IDC_COPYEMAIL
Command2=IDC_COPYWEB
Command3=IDC_REQUERY
CommandCount=3

[DLG:IDD_SDSETUPDLG]
Type=1
Class=?
ControlCount=7
Control1=IDC_COMBO_ONOFF,combobox,1342251011
Control2=IDC_EDITTIME,edit,1350631552
Control3=IDC_SETTIME,button,1342242827
Control4=IDOK,button,1342242827
Control5=IDCANCEL,button,1342242827
Control6=IDC_S_AUTOONOFF,static,1342308352
Control7=IDC_S_AUTOTIME,static,1342308352

[DLG:IDD_REGDLG]
Type=1
Class=?
ControlCount=13
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_MACHINECODE,edit,1350633600
Control8=IDC_REGISTERCODE,edit,1350631552
Control9=IDC_STATIC,static,1342177292
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EMAIL,static,1342308352
Control13=IDC_WEBSITE,static,1342308352

[DLG:IDD_QUERYDLG]
Type=1
Class=?
ControlCount=7
Control1=IDC_COLUMN1,static,1342308354
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_COLUMN2,static,1342308354
Control4=IDC_COMBO2,combobox,1344340226
Control5=IDC_COLUMN3,static,1342308354
Control6=IDC_COMBO3,combobox,1344340226
Control7=IDC_EXCUTE,button,1342246667

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373899
Control5=IDC_WEBSITE,static,1342308352
Control6=IDC_EMAIL,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DATEDLG]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_CALENDAR1,{8E27C92B-1264-101C-8A2F-040224009C02},1342242816
Control4=IDC_SETTIME,button,1342242827
Control5=IDC_TIME,static,1342308353
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_EDITDLG]
Type=1
Class=?
ControlCount=14
Control1=IDC_COLUMNLIST,listbox,1344340225
Control2=IDC_VALUELIST,listbox,1344340225
Control3=IDC_EDIT,edit,1345388676
Control4=IDC_MORE,button,1342242827
Control5=IDCANCEL,button,1342242827
Control6=IDOK,button,1342242827
Control7=IDC_HELPINFO,static,1342177280
Control8=IDC_S_HELPINFO,static,1342308352
Control9=IDC_S_COLUMN,static,1342308352
Control10=IDC_S_VALUE,static,1342308352
Control11=IDC_COLUMNNAME,static,1342308352
Control12=IDC_PLAY,button,1342242955
Control13=IDC_PAUSE,button,1342242955
Control14=IDC_STOP,button,1342242955

[DLG:IDD_LOGINDLG]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_S_USER,static,1342308352
Control4=IDC_USERCOMBO,combobox,1344340226
Control5=IDC_S_PASSWORD,static,1342308352
Control6=IDC_PSDEDIT,edit,1342242976
Control7=IDC_LOGINBMP,static,1342177792
Control8=IDC_HELPINFO,button,1342242827
Control9=IDC_S_DEFAULTPASSWORD,static,1342308352

[DLG:IDD_NMUSERDLG]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_USERNAME,static,1342308354
Control4=IDC_OLDPSDNAME,static,1342308354
Control5=IDC_NEWPSDNAME,static,1342308354
Control6=IDC_CFMPSDNAME,static,1342308354
Control7=IDC_USERVALUE,combobox,1344340226
Control8=IDC_OLDPSDVALUE,edit,1342242976
Control9=IDC_NEWPSDVALUE,edit,1342242976
Control10=IDC_CFMPSDVALUE,edit,1342242976

[DLG:IDD_TIMEDLG]
Type=1
Class=?
ControlCount=13
Control1=IDC_EDITHOUR,edit,1342251136
Control2=IDC_EDITMINUTE,edit,1342251136
Control3=IDC_EDITSECOND,edit,1342251136
Control4=IDC_UP,button,1342279563
Control5=IDC_DOWN,button,1342279563
Control6=IDOK,button,1342275595
Control7=IDCANCEL,button,1342275595
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,static,1342308353
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=IDC_REFRESH
Command5=IDC_INSERT
Command6=IDC_MODIFY
Command7=IDC_DELETE
Command8=IDC_EMAIL
Command9=IDC_BROWSE
Command10=IDC_CALCULATOR
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=IDC_COPYWEB
Command2=ID_EDIT_COPY
Command3=IDC_DELETE
Command4=IDC_COPYEMAIL
Command5=IDC_INSERT
Command6=IDC_MODIFY
Command7=ID_FILE_NEW
Command8=ID_FILE_OPEN
Command9=ID_FILE_PRINT
Command10=ID_FILE_SAVE
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=IDC_REFRESH
Command15=ID_NEXT_PANE
Command16=ID_PREV_PANE
Command17=ID_EDIT_COPY
Command18=ID_EDIT_PASTE
Command19=ID_EDIT_CUT
Command20=ID_EDIT_UNDO
CommandCount=20

