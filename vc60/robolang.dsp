# Microsoft Developer Studio Project File - Name="robolang" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=robolang - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "robolang.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "robolang.mak" CFG="robolang - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "robolang - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "robolang - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "robolang - Win32 Release"

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
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "robolang - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "robolang - Win32 Release"
# Name "robolang - Win32 Debug"
# Begin Group "vc60"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\newrobota.ico
# End Source File
# Begin Source File

SOURCE=.\res\old_tool.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\robolang.ico
# End Source File
# Begin Source File

SOURCE=.\robolang.rc
# End Source File
# Begin Source File

SOURCE=.\res\robolang.rc2
# End Source File
# Begin Source File

SOURCE=.\res\robolangDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgNew.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNew.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewCondition.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\robolang.cpp
# End Source File
# Begin Source File

SOURCE=.\robolang.h
# End Source File
# Begin Source File

SOURCE=.\robolangDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\robolangDoc.h
# End Source File
# Begin Source File

SOURCE=.\RobolangEditWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\RobolangEditWindow.h
# End Source File
# Begin Source File

SOURCE=.\RobolangMapWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\robolangmapwindow.h
# End Source File
# Begin Source File

SOURCE=.\RobolangSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\RobolangSplitter.h
# End Source File
# Begin Source File

SOURCE=.\robolangView.cpp
# End Source File
# Begin Source File

SOURCE=.\robolangView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "control"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\control\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\control\Control.h
# End Source File
# End Group
# Begin Group "interpreter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\interpreter\Interpreter.cpp
# End Source File
# Begin Source File

SOURCE=..\interpreter\Interpreter.h
# End Source File
# End Group
# Begin Group "program"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\program\Command.cpp
# End Source File
# Begin Source File

SOURCE=..\program\Procedure.cpp
# End Source File
# Begin Source File

SOURCE=..\program\Program.cpp
# End Source File
# Begin Source File

SOURCE=..\program\Program.h
# End Source File
# End Group
# Begin Group "map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\map\RoboMap.cpp
# End Source File
# Begin Source File

SOURCE=..\map\RoboMap.h
# End Source File
# End Group
# Begin Group "programui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\programui\ProgramUI.cpp
# End Source File
# Begin Source File

SOURCE=..\programui\ProgramUI.h
# End Source File
# End Group
# Begin Group "mapui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\mapui\RoboMapUI.cpp
# End Source File
# Begin Source File

SOURCE=..\mapui\RoboMapUI.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
