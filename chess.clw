; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChessDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chess.h"
LastPage=0

ClassCount=3
Class1=CChessApp
Class2=CChessDlg
Class3=CNewGame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_CHESS_DIALOG
Resource3=IDD_NEWGAME

[CLS:CChessApp]
Type=0
BaseClass=CWinApp
HeaderFile=chess.h
ImplementationFile=chess.cpp

[CLS:CChessDlg]
Type=0
BaseClass=CDialog
HeaderFile=chessDlg.h
ImplementationFile=chessDlg.cpp
LastObject=IDC_THINKPRG
Filter=D
VirtualFilter=dWC

[CLS:CNewGame]
Type=0
BaseClass=CDialog
HeaderFile=NewGame.h
ImplementationFile=NewGame.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_WHITESTONE

[DLG:IDD_CHESS_DIALOG]
Type=1
Class=CChessDlg
ControlCount=3
Control1=IDC_NODECOUNT,static,1342308352
Control2=IDC_NEWGAME,button,1342242816
Control3=IDC_THINKPRG,msctls_progress32,1350565889

[DLG:IDD_NEWGAME]
Type=1
Class=CNewGame
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_PLY,msctls_updown32,1342177334
Control4=IDC_STATIC,static,1342308352
Control5=IDC_WHITESTONE,button,1342177289
Control6=IDC_BLACKSTONE,button,1342177289
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

