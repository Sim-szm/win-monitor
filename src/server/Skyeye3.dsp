# Microsoft Developer Studio Project File - Name="Skyeye3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Skyeye3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Skyeye3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Skyeye3.mak" CFG="Skyeye3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Skyeye3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Skyeye3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Skyeye3 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Skyeye3 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Skyeye3 - Win32 Release"
# Name "Skyeye3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutUsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddblackDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BlackDateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\helloDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\loginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SeverSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Skyeye3.cpp
# End Source File
# Begin Source File

SOURCE=.\Skyeye3.rc
# End Source File
# Begin Source File

SOURCE=.\Skyeye3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysinfoDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutUsDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddblackDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlackDateDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChatSocket.h
# End Source File
# Begin Source File

SOURCE=.\helloDlg.h
# End Source File
# Begin Source File

SOURCE=.\loginDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SeverSocket.h
# End Source File
# Begin Source File

SOURCE=.\Skyeye3.h
# End Source File
# Begin Source File

SOURCE=.\Skyeye3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysinfoDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\123.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Skyeye3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Skyeye3.rc2
# End Source File
# Begin Source File

SOURCE=".\res\弹窗.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登录按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\底板1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\关闭按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\黑名单底板.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\清空按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\确定按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\删除按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\首页.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\添加按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\退出按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面 底板.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\最小化按钮.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
