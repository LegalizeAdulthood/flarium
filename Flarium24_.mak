# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Flarium24 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Flarium24 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Flarium24 - Win32 Release" && "$(CFG)" !=\
 "Flarium24 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Flarium24.mak" CFG="Flarium24 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Flarium24 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Flarium24 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Flarium24 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Flarium24 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Flarium24.exe"

CLEAN : 
	-@erase "$(INTDIR)\Affine.obj"
	-@erase "$(INTDIR)\BGColor.obj"
	-@erase "$(INTDIR)\Clouds.obj"
	-@erase "$(INTDIR)\Cmplx.obj"
	-@erase "$(INTDIR)\Dibapi.obj"
	-@erase "$(INTDIR)\Equation.obj"
	-@erase "$(INTDIR)\Filters.obj"
	-@erase "$(INTDIR)\Flarium24.obj"
	-@erase "$(INTDIR)\Flarium24.pch"
	-@erase "$(INTDIR)\Flarium24.res"
	-@erase "$(INTDIR)\Flarium24Doc.obj"
	-@erase "$(INTDIR)\Flarium24View.obj"
	-@erase "$(INTDIR)\formulae.obj"
	-@erase "$(INTDIR)\Formulae2.obj"
	-@erase "$(INTDIR)\Formulae3.obj"
	-@erase "$(INTDIR)\Fparams.obj"
	-@erase "$(INTDIR)\Gradient.obj"
	-@erase "$(INTDIR)\Lattoof.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Myfile.obj"
	-@erase "$(INTDIR)\Nthorder.obj"
	-@erase "$(INTDIR)\OneNum.obj"
	-@erase "$(INTDIR)\Orient.obj"
	-@erase "$(INTDIR)\Pattern.obj"
	-@erase "$(INTDIR)\PrtScale.obj"
	-@erase "$(INTDIR)\Qparams.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Two_num.obj"
	-@erase "$(INTDIR)\Unique.obj"
	-@erase "$(INTDIR)\Xysize.obj"
	-@erase "$(OUTDIR)\Flarium24.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Flarium24.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Flarium24.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Flarium24.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Flarium24.pdb" /machine:I386 /out:"$(OUTDIR)/Flarium24.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Affine.obj" \
	"$(INTDIR)\BGColor.obj" \
	"$(INTDIR)\Clouds.obj" \
	"$(INTDIR)\Cmplx.obj" \
	"$(INTDIR)\Dibapi.obj" \
	"$(INTDIR)\Equation.obj" \
	"$(INTDIR)\Filters.obj" \
	"$(INTDIR)\Flarium24.obj" \
	"$(INTDIR)\Flarium24.res" \
	"$(INTDIR)\Flarium24Doc.obj" \
	"$(INTDIR)\Flarium24View.obj" \
	"$(INTDIR)\formulae.obj" \
	"$(INTDIR)\Formulae2.obj" \
	"$(INTDIR)\Formulae3.obj" \
	"$(INTDIR)\Fparams.obj" \
	"$(INTDIR)\Gradient.obj" \
	"$(INTDIR)\Lattoof.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Myfile.obj" \
	"$(INTDIR)\Nthorder.obj" \
	"$(INTDIR)\OneNum.obj" \
	"$(INTDIR)\Orient.obj" \
	"$(INTDIR)\Pattern.obj" \
	"$(INTDIR)\PrtScale.obj" \
	"$(INTDIR)\Qparams.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Two_num.obj" \
	"$(INTDIR)\Unique.obj" \
	"$(INTDIR)\Xysize.obj"

"$(OUTDIR)\Flarium24.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Flarium24 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Flarium24.exe"

CLEAN : 
	-@erase "$(INTDIR)\Affine.obj"
	-@erase "$(INTDIR)\BGColor.obj"
	-@erase "$(INTDIR)\Clouds.obj"
	-@erase "$(INTDIR)\Cmplx.obj"
	-@erase "$(INTDIR)\Dibapi.obj"
	-@erase "$(INTDIR)\Equation.obj"
	-@erase "$(INTDIR)\Filters.obj"
	-@erase "$(INTDIR)\Flarium24.obj"
	-@erase "$(INTDIR)\Flarium24.pch"
	-@erase "$(INTDIR)\Flarium24.res"
	-@erase "$(INTDIR)\Flarium24Doc.obj"
	-@erase "$(INTDIR)\Flarium24View.obj"
	-@erase "$(INTDIR)\formulae.obj"
	-@erase "$(INTDIR)\Formulae2.obj"
	-@erase "$(INTDIR)\Formulae3.obj"
	-@erase "$(INTDIR)\Fparams.obj"
	-@erase "$(INTDIR)\Gradient.obj"
	-@erase "$(INTDIR)\Lattoof.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Myfile.obj"
	-@erase "$(INTDIR)\Nthorder.obj"
	-@erase "$(INTDIR)\OneNum.obj"
	-@erase "$(INTDIR)\Orient.obj"
	-@erase "$(INTDIR)\Pattern.obj"
	-@erase "$(INTDIR)\PrtScale.obj"
	-@erase "$(INTDIR)\Qparams.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Two_num.obj"
	-@erase "$(INTDIR)\Unique.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Xysize.obj"
	-@erase "$(OUTDIR)\Flarium24.exe"
	-@erase "$(OUTDIR)\Flarium24.ilk"
	-@erase "$(OUTDIR)\Flarium24.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/Flarium24.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Flarium24.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Flarium24.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Flarium24.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Flarium24.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Affine.obj" \
	"$(INTDIR)\BGColor.obj" \
	"$(INTDIR)\Clouds.obj" \
	"$(INTDIR)\Cmplx.obj" \
	"$(INTDIR)\Dibapi.obj" \
	"$(INTDIR)\Equation.obj" \
	"$(INTDIR)\Filters.obj" \
	"$(INTDIR)\Flarium24.obj" \
	"$(INTDIR)\Flarium24.res" \
	"$(INTDIR)\Flarium24Doc.obj" \
	"$(INTDIR)\Flarium24View.obj" \
	"$(INTDIR)\formulae.obj" \
	"$(INTDIR)\Formulae2.obj" \
	"$(INTDIR)\Formulae3.obj" \
	"$(INTDIR)\Fparams.obj" \
	"$(INTDIR)\Gradient.obj" \
	"$(INTDIR)\Lattoof.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Myfile.obj" \
	"$(INTDIR)\Nthorder.obj" \
	"$(INTDIR)\OneNum.obj" \
	"$(INTDIR)\Orient.obj" \
	"$(INTDIR)\Pattern.obj" \
	"$(INTDIR)\PrtScale.obj" \
	"$(INTDIR)\Qparams.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Two_num.obj" \
	"$(INTDIR)\Unique.obj" \
	"$(INTDIR)\Xysize.obj"

"$(OUTDIR)\Flarium24.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Flarium24 - Win32 Release"
# Name "Flarium24 - Win32 Debug"

!IF  "$(CFG)" == "Flarium24 - Win32 Release"

!ELSEIF  "$(CFG)" == "Flarium24 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Flarium24.cpp
DEP_CPP_FLARI=\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Flarium24.obj" : $(SOURCE) $(DEP_CPP_FLARI) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Flarium24 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Flarium24.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Flarium24.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Flarium24 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/Flarium24.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Flarium24.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Flarium24.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Flarium24Doc.cpp
DEP_CPP_FLARIU=\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Flarium24Doc.obj" : $(SOURCE) $(DEP_CPP_FLARIU) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Flarium24View.cpp
DEP_CPP_FLARIUM=\
	".\Affine.h"\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\fparams.h"\
	".\gradient.h"\
	".\MainFrm.h"\
	".\orient.h"\
	".\PrtScale.h"\
	".\StdAfx.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Flarium24View.obj" : $(SOURCE) $(DEP_CPP_FLARIUM) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Flarium24.rc
DEP_RSC_FLARIUM2=\
	".\Flarium24.rc2"\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\mainfram.bmp"\
	

"$(INTDIR)\Flarium24.res" : $(SOURCE) $(DEP_RSC_FLARIUM2) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dibapi.cpp
DEP_CPP_DIBAP=\
	".\dibapi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dibapi.obj" : $(SOURCE) $(DEP_CPP_DIBAP) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Myfile.cpp
DEP_CPP_MYFIL=\
	".\dibapi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Myfile.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cmplx.cpp
DEP_CPP_CMPLX=\
	".\cmplx.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Cmplx.obj" : $(SOURCE) $(DEP_CPP_CMPLX) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Xysize.cpp
DEP_CPP_XYSIZ=\
	".\Flarium24.h"\
	".\StdAfx.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Xysize.obj" : $(SOURCE) $(DEP_CPP_XYSIZ) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pattern.cpp
DEP_CPP_PATTE=\
	".\Affine.h"\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\Lattoof.h"\
	".\MainFrm.h"\
	".\nthorder.h"\
	".\OneNum.h"\
	".\qparams.h"\
	".\StdAfx.h"\
	".\Two_Num.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Pattern.obj" : $(SOURCE) $(DEP_CPP_PATTE) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Filters.cpp
DEP_CPP_FILTE=\
	".\Clouds.h"\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\OneNum.h"\
	".\StdAfx.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Filters.obj" : $(SOURCE) $(DEP_CPP_FILTE) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gradient.cpp
DEP_CPP_GRADI=\
	".\Flarium24.h"\
	".\gradient.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Gradient.obj" : $(SOURCE) $(DEP_CPP_GRADI) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fparams.cpp
DEP_CPP_FPARA=\
	".\Flarium24.h"\
	".\fparams.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Fparams.obj" : $(SOURCE) $(DEP_CPP_FPARA) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Orient.cpp
DEP_CPP_ORIEN=\
	".\Flarium24.h"\
	".\orient.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Orient.obj" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Nthorder.cpp
DEP_CPP_NTHOR=\
	".\Flarium24.h"\
	".\nthorder.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Nthorder.obj" : $(SOURCE) $(DEP_CPP_NTHOR) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Two_num.cpp
DEP_CPP_TWO_N=\
	".\Flarium24.h"\
	".\StdAfx.h"\
	".\Two_Num.h"\
	

"$(INTDIR)\Two_num.obj" : $(SOURCE) $(DEP_CPP_TWO_N) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\formulae.cpp
DEP_CPP_FORMU=\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\nthorder.h"\
	".\StdAfx.h"\
	".\Two_Num.h"\
	".\Xysize.h"\
	

"$(INTDIR)\formulae.obj" : $(SOURCE) $(DEP_CPP_FORMU) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Equation.cpp
DEP_CPP_EQUAT=\
	".\BGColor.h"\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Equation.obj" : $(SOURCE) $(DEP_CPP_EQUAT) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OneNum.cpp
DEP_CPP_ONENU=\
	".\Flarium24.h"\
	".\OneNum.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\OneNum.obj" : $(SOURCE) $(DEP_CPP_ONENU) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Formulae2.cpp
DEP_CPP_FORMUL=\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\nthorder.h"\
	".\StdAfx.h"\
	".\Two_Num.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Formulae2.obj" : $(SOURCE) $(DEP_CPP_FORMUL) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PrtScale.cpp
DEP_CPP_PRTSC=\
	".\Flarium24.h"\
	".\PrtScale.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PrtScale.obj" : $(SOURCE) $(DEP_CPP_PRTSC) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Clouds.cpp
DEP_CPP_CLOUD=\
	".\Clouds.h"\
	".\Flarium24.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Clouds.obj" : $(SOURCE) $(DEP_CPP_CLOUD) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lattoof.cpp
DEP_CPP_LATTO=\
	".\Flarium24.h"\
	".\Lattoof.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Lattoof.obj" : $(SOURCE) $(DEP_CPP_LATTO) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Affine.cpp
DEP_CPP_AFFIN=\
	".\Affine.h"\
	".\Flarium24.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Affine.obj" : $(SOURCE) $(DEP_CPP_AFFIN) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BGColor.cpp
DEP_CPP_BGCOL=\
	".\BGColor.h"\
	".\Flarium24.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BGColor.obj" : $(SOURCE) $(DEP_CPP_BGCOL) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Formulae3.cpp
DEP_CPP_FORMULA=\
	".\cmplx.h"\
	".\dibapi.h"\
	".\external.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\MainFrm.h"\
	".\nthorder.h"\
	".\StdAfx.h"\
	".\Two_Num.h"\
	".\Xysize.h"\
	

"$(INTDIR)\Formulae3.obj" : $(SOURCE) $(DEP_CPP_FORMULA) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Qparams.cpp
DEP_CPP_QPARA=\
	".\Flarium24.h"\
	".\qparams.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Qparams.obj" : $(SOURCE) $(DEP_CPP_QPARA) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Unique.cpp
DEP_CPP_UNIQU=\
	".\cmplx.h"\
	".\dibapi.h"\
	".\Flarium24.h"\
	".\Flarium24Doc.h"\
	".\Flarium24View.h"\
	".\StdAfx.h"\
	".\unique.h"\
	

"$(INTDIR)\Unique.obj" : $(SOURCE) $(DEP_CPP_UNIQU) "$(INTDIR)"\
 "$(INTDIR)\Flarium24.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\Flarium24.hpj

!IF  "$(CFG)" == "Flarium24 - Win32 Release"

!ELSEIF  "$(CFG)" == "Flarium24 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
