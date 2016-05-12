# Microsoft Developer Studio Project File - Name="his3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=his3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "his3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "his3.mak" CFG="his3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "his3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "his3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "his3 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "his3 - Win32 Debug"

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

# Name "his3 - Win32 Release"
# Name "his3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AffinityQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ComBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ComFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\CostBudget.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClass2Add.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClass2Modify.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClassA.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClassAadd.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClassAb.cpp
# End Source File
# Begin Source File

SOURCE=.\CostClassAmodify.cpp
# End Source File
# Begin Source File

SOURCE=.\CostConsumeAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\DechargeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DepartSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAccountQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogHjSf.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSickGetMed.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogUseAllQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogWait.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFlat.cpp
# End Source File
# Begin Source File

SOURCE=.\EmpQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\excel9.cpp
# End Source File
# Begin Source File

SOURCE=.\ExesList.cpp
# End Source File
# Begin Source File

SOURCE=.\FormGhList.cpp
# End Source File
# Begin Source File

SOURCE=.\FormGhList_del.cpp
# End Source File
# Begin Source File

SOURCE=.\GhQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\GhQuery_del.cpp
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\his3.cpp
# End Source File
# Begin Source File

SOURCE=.\his3.rc
# End Source File
# Begin Source File

SOURCE=.\his3Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\his3View.cpp
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Lock.cpp
# End Source File
# Begin Source File

SOURCE=.\Logon.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Mdiclient.cpp
# End Source File
# Begin Source File

SOURCE=.\Medcode.cpp
# End Source File
# Begin Source File

SOURCE=.\MedcodeAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\MedcodeModify.cpp
# End Source File
# Begin Source File

SOURCE=.\MedConsumeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\MedQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\MedStockList.cpp
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatorSel.cpp
# End Source File
# Begin Source File

SOURCE=.\PeculiarAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQueryHayb.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQueryJMTC.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQueryOtherSick.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQueryQpyb.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonQueryRelate.cpp
# End Source File
# Begin Source File

SOURCE=.\PlanAsWhole.cpp
# End Source File
# Begin Source File

SOURCE=.\PrivilegeQuota.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressIndicate.cpp
# End Source File
# Begin Source File

SOURCE=.\QiuXpButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterGh.cpp
# End Source File
# Begin Source File

SOURCE=.\RelateQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportDechargeList.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEmpCount.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEmpJSB.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportMedConsume.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAll.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAll1.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAllQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\SickGetMedView.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\UserQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewUserComuse.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AffinityQuery.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ComBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\ComFunc.h
# End Source File
# Begin Source File

SOURCE=.\CostBudget.h
# End Source File
# Begin Source File

SOURCE=.\CostClass2Add.h
# End Source File
# Begin Source File

SOURCE=.\CostClass2Modify.h
# End Source File
# Begin Source File

SOURCE=.\CostClassA.h
# End Source File
# Begin Source File

SOURCE=.\CostClassAadd.h
# End Source File
# Begin Source File

SOURCE=.\CostClassAb.h
# End Source File
# Begin Source File

SOURCE=.\CostClassAmodify.h
# End Source File
# Begin Source File

SOURCE=.\CostConsumeAdd.h
# End Source File
# Begin Source File

SOURCE=.\DechargeQuery.h
# End Source File
# Begin Source File

SOURCE=.\DepartSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogAccountQuery.h
# End Source File
# Begin Source File

SOURCE=.\DialogHjSf.h
# End Source File
# Begin Source File

SOURCE=.\DialogReportView.h
# End Source File
# Begin Source File

SOURCE=.\DialogSickGetMed.h
# End Source File
# Begin Source File

SOURCE=.\DialogUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DialogUseAllQuery.h
# End Source File
# Begin Source File

SOURCE=.\DialogWait.h
# End Source File
# Begin Source File

SOURCE=.\EditFlat.h
# End Source File
# Begin Source File

SOURCE=.\EmpQuery.h
# End Source File
# Begin Source File

SOURCE=.\excel9.h
# End Source File
# Begin Source File

SOURCE=.\ExesList.h
# End Source File
# Begin Source File

SOURCE=.\FormGhList.h
# End Source File
# Begin Source File

SOURCE=.\FormGhList_del.h
# End Source File
# Begin Source File

SOURCE=.\GhQuery.h
# End Source File
# Begin Source File

SOURCE=.\GhQuery_del.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCell.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\his3.h
# End Source File
# Begin Source File

SOURCE=.\his3Doc.h
# End Source File
# Begin Source File

SOURCE=.\his3View.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\Lock.h
# End Source File
# Begin Source File

SOURCE=.\Logon.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Mdiclient.h
# End Source File
# Begin Source File

SOURCE=.\Medcode.h
# End Source File
# Begin Source File

SOURCE=.\MedcodeAdd.h
# End Source File
# Begin Source File

SOURCE=.\MedcodeModify.h
# End Source File
# Begin Source File

SOURCE=.\MedConsumeQuery.h
# End Source File
# Begin Source File

SOURCE=.\MedQuery.h
# End Source File
# Begin Source File

SOURCE=.\MedStockList.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\OperatorSel.h
# End Source File
# Begin Source File

SOURCE=.\PeculiarAdd.h
# End Source File
# Begin Source File

SOURCE=.\PersonQuery.h
# End Source File
# Begin Source File

SOURCE=.\PersonQueryHayb.h
# End Source File
# Begin Source File

SOURCE=.\PersonQueryJMTC.h
# End Source File
# Begin Source File

SOURCE=.\PersonQueryOtherSick.h
# End Source File
# Begin Source File

SOURCE=.\PersonQueryQpyb.h
# End Source File
# Begin Source File

SOURCE=.\PersonQueryRelate.h
# End Source File
# Begin Source File

SOURCE=.\PlanAsWhole.h
# End Source File
# Begin Source File

SOURCE=.\PrivilegeQuota.h
# End Source File
# Begin Source File

SOURCE=.\ProgressEx.h
# End Source File
# Begin Source File

SOURCE=.\ProgressIndicate.h
# End Source File
# Begin Source File

SOURCE=.\QiuXpButton.h
# End Source File
# Begin Source File

SOURCE=.\RegisterGh.h
# End Source File
# Begin Source File

SOURCE=.\RelateQuery.h
# End Source File
# Begin Source File

SOURCE=.\ReportDechargeList.h
# End Source File
# Begin Source File

SOURCE=.\ReportEmpCount.h
# End Source File
# Begin Source File

SOURCE=.\ReportEmpJSB.h
# End Source File
# Begin Source File

SOURCE=.\ReportMedConsume.h
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAll.h
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAll1.h
# End Source File
# Begin Source File

SOURCE=.\ReportUsedAllQuery.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SickGetMedView.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\GridCtrl_src\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\UserQuery.h
# End Source File
# Begin Source File

SOURCE=.\ViewUserComuse.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\Application _ iCal.ico"
# End Source File
# Begin Source File

SOURCE=.\res\firstaid.ico
# End Source File
# Begin Source File

SOURCE=.\res\his3.ico
# End Source File
# Begin Source File

SOURCE=.\res\his3.rc2
# End Source File
# Begin Source File

SOURCE=.\res\his3Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sherlock.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section his3 : {0ECD9B62-23AA-11D0-B351-00A0C9055D8E}
# 	2:5:Class:CMSHFlexGrid
# 	2:10:HeaderFile:mshflexgrid.h
# 	2:8:ImplFile:mshflexgrid.cpp
# End Section
# Section his3 : {0ECD9B64-23AA-11D0-B351-00A0C9055D8E}
# 	2:21:DefaultSinkHeaderFile:mshflexgrid.h
# 	2:16:DefaultSinkClass:CMSHFlexGrid
# End Section
