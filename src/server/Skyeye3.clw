; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSysinfoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Skyeye3.h"

ClassCount=10
Class1=CSkyeye3App
Class2=CSkyeye3Dlg

ResourceCount=8
Resource2=IDD_ADDDIALOG
Resource1=IDR_MAINFRAME
Class3=CloginDlg
Resource3=IDD_HELLOWORLDDIALOG
Class4=ChelloDlg
Class5=CChatSocket
Class6=CSeverSocket
Resource4=IDD_BLACKDATEDIALOG
Class7=CBlackDateDlg
Resource5=IDD_SKYEYE3_DIALOG
Class8=CAddblackDlg
Resource6=IDD_SYSINFODIALOG
Resource7=IDD_DLOGINDIALOG
Class9=CAboutUsDlg
Class10=CSysinfoDlg
Resource8=IDD_ABOUTUSDIALOG

[CLS:CSkyeye3App]
Type=0
HeaderFile=Skyeye3.h
ImplementationFile=Skyeye3.cpp
Filter=N

[CLS:CSkyeye3Dlg]
Type=0
HeaderFile=Skyeye3Dlg.h
ImplementationFile=Skyeye3Dlg.cpp
Filter=D
LastObject=CSkyeye3Dlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SKYEYE3_DIALOG]
Type=1
Class=CSkyeye3Dlg
ControlCount=20
Control1=IDC_TITLE,button,1342242944
Control2=IDC_INFO,button,1342242944
Control3=IDC_SYSDATE,button,1342242944
Control4=IDC_ABOUT_US,button,1342242944
Control5=IDC_CLOSE,button,1342242944
Control6=IDC_MINI,button,1342242944
Control7=IDC_INFOTREE,SysTreeView32,1350631424
Control8=IDC_PROCLIST,SysListView32,1350631425
Control9=IDC_IPNAME,static,1342308352
Control10=IDC_IP,edit,1350633600
Control11=IDC_USERNAME,static,1342308352
Control12=IDC_USER,edit,1350633600
Control13=IDC_CPUINFO,static,1342308352
Control14=IDC_CPU,edit,1350633604
Control15=IDC_SYSINFO,static,1342308352
Control16=IDC_SYS,edit,1350633604
Control17=IDC_DELETE,button,1342242944
Control18=IDC_BLACKDATE,button,1342242944
Control19=IDC_NETWORK,edit,1352730756
Control20=IDC_NET,static,1342308352

[DLG:IDD_DLOGINDIALOG]
Type=1
Class=CloginDlg
ControlCount=4
Control1=IDC_PASSPORT,edit,1350631584
Control2=IDC_IDNAME,edit,1350631552
Control3=IDC_LOGIN,button,1342242944
Control4=IDC_QUIT,button,1342242944

[CLS:CloginDlg]
Type=0
HeaderFile=loginDlg.h
ImplementationFile=loginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LOGIN
VirtualFilter=dWC

[DLG:IDD_HELLOWORLDDIALOG]
Type=1
Class=ChelloDlg
ControlCount=0

[CLS:ChelloDlg]
Type=0
HeaderFile=helloDlg.h
ImplementationFile=helloDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ChelloDlg
VirtualFilter=dWC

[CLS:CChatSocket]
Type=0
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[CLS:CSeverSocket]
Type=0
HeaderFile=SeverSocket.h
ImplementationFile=SeverSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[DLG:IDD_BLACKDATEDIALOG]
Type=1
Class=CBlackDateDlg
ControlCount=4
Control1=IDC_BLACKLIST,SysListView32,1350631425
Control2=IDC_ADDBUTTON,button,1342242944
Control3=IDC_DELETEBUTTON,button,1342242944
Control4=IDC_OKBUTTON,button,1342242944

[CLS:CBlackDateDlg]
Type=0
HeaderFile=BlackDateDlg.h
ImplementationFile=BlackDateDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBlackDateDlg
VirtualFilter=dWC

[CLS:CAddblackDlg]
Type=0
HeaderFile=AddblackDlg.h
ImplementationFile=AddblackDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_OKBUTTON
VirtualFilter=dWC

[DLG:IDD_ADDDIALOG]
Type=1
Class=CAddblackDlg
ControlCount=3
Control1=IDC_NEWBLACK,edit,1350631552
Control2=IDC_OKBUTTON,button,1342242816
Control3=IDC_CANCELBUTTON,button,1342242816

[DLG:IDD_SYSINFODIALOG]
Type=1
Class=CSysinfoDlg
ControlCount=3
Control1=IDC_SYSINFOLIST,SysListView32,1350631425
Control2=IDC_CURTAIN,button,1342242944
Control3=IDC_DELETEALL,button,1342242944

[CLS:CAboutUsDlg]
Type=0
HeaderFile=AboutUsDlg.h
ImplementationFile=AboutUsDlg.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_ABOUTUSDIALOG]
Type=1
Class=CAboutUsDlg
ControlCount=0

[CLS:CSysinfoDlg]
Type=0
HeaderFile=SysinfoDlg.h
ImplementationFile=SysinfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CURTAIN
VirtualFilter=dWC

