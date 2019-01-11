# Microsoft Developer Studio Generated NMAKE File, Based on versionone.dsp
!IF "$(CFG)" == ""
CFG=versionone - Win32 Debug
!MESSAGE No configuration specified. Defaulting to versionone - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "versionone - Win32 Release" && "$(CFG)" != "versionone - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "versionone.mak" CFG="versionone - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "versionone - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "versionone - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "versionone - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\versionone.exe"


CLEAN :
	-@erase "$(INTDIR)\BoolMap.obj"
	-@erase "$(INTDIR)\FuzzyMap.obj"
	-@erase "$(INTDIR)\FzyRelation.obj"
	-@erase "$(INTDIR)\GrayMap.obj"
	-@erase "$(INTDIR)\InFer.obj"
	-@erase "$(INTDIR)\Laser.obj"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\MakeInferences.obj"
	-@erase "$(INTDIR)\MakeMapping.obj"
	-@erase "$(INTDIR)\MakeRelations.obj"
	-@erase "$(INTDIR)\MapController.obj"
	-@erase "$(INTDIR)\Matrix.obj"
	-@erase "$(INTDIR)\MembFunc.obj"
	-@erase "$(INTDIR)\Node.obj"
	-@erase "$(INTDIR)\NodeMap.obj"
	-@erase "$(INTDIR)\Robot.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\versionone.obj"
	-@erase "$(INTDIR)\versionone.pch"
	-@erase "$(INTDIR)\versionone.res"
	-@erase "$(OUTDIR)\versionone.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\versionone.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\versionone.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\versionone.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\versionone.pdb" /machine:I386 /out:"$(OUTDIR)\versionone.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BoolMap.obj" \
	"$(INTDIR)\FuzzyMap.obj" \
	"$(INTDIR)\FzyRelation.obj" \
	"$(INTDIR)\GrayMap.obj" \
	"$(INTDIR)\InFer.obj" \
	"$(INTDIR)\Laser.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\MakeInferences.obj" \
	"$(INTDIR)\MakeMapping.obj" \
	"$(INTDIR)\MakeRelations.obj" \
	"$(INTDIR)\MapController.obj" \
	"$(INTDIR)\Matrix.obj" \
	"$(INTDIR)\MembFunc.obj" \
	"$(INTDIR)\Node.obj" \
	"$(INTDIR)\NodeMap.obj" \
	"$(INTDIR)\Robot.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\versionone.obj" \
	"$(INTDIR)\versionone.res"

"$(OUTDIR)\versionone.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\versionone.exe" "$(OUTDIR)\versionone.bsc"


CLEAN :
	-@erase "$(INTDIR)\BoolMap.obj"
	-@erase "$(INTDIR)\BoolMap.sbr"
	-@erase "$(INTDIR)\FuzzyMap.obj"
	-@erase "$(INTDIR)\FuzzyMap.sbr"
	-@erase "$(INTDIR)\FzyRelation.obj"
	-@erase "$(INTDIR)\FzyRelation.sbr"
	-@erase "$(INTDIR)\GrayMap.obj"
	-@erase "$(INTDIR)\GrayMap.sbr"
	-@erase "$(INTDIR)\InFer.obj"
	-@erase "$(INTDIR)\InFer.sbr"
	-@erase "$(INTDIR)\Laser.obj"
	-@erase "$(INTDIR)\Laser.sbr"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\list.sbr"
	-@erase "$(INTDIR)\MakeInferences.obj"
	-@erase "$(INTDIR)\MakeInferences.sbr"
	-@erase "$(INTDIR)\MakeMapping.obj"
	-@erase "$(INTDIR)\MakeMapping.sbr"
	-@erase "$(INTDIR)\MakeRelations.obj"
	-@erase "$(INTDIR)\MakeRelations.sbr"
	-@erase "$(INTDIR)\MapController.obj"
	-@erase "$(INTDIR)\MapController.sbr"
	-@erase "$(INTDIR)\Matrix.obj"
	-@erase "$(INTDIR)\Matrix.sbr"
	-@erase "$(INTDIR)\MembFunc.obj"
	-@erase "$(INTDIR)\MembFunc.sbr"
	-@erase "$(INTDIR)\Node.obj"
	-@erase "$(INTDIR)\Node.sbr"
	-@erase "$(INTDIR)\NodeMap.obj"
	-@erase "$(INTDIR)\NodeMap.sbr"
	-@erase "$(INTDIR)\Robot.obj"
	-@erase "$(INTDIR)\Robot.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\versionone.obj"
	-@erase "$(INTDIR)\versionone.pch"
	-@erase "$(INTDIR)\versionone.res"
	-@erase "$(INTDIR)\versionone.sbr"
	-@erase "$(OUTDIR)\versionone.bsc"
	-@erase "$(OUTDIR)\versionone.exe"
	-@erase "$(OUTDIR)\versionone.ilk"
	-@erase "$(OUTDIR)\versionone.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\versionone.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\versionone.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\versionone.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BoolMap.sbr" \
	"$(INTDIR)\FuzzyMap.sbr" \
	"$(INTDIR)\FzyRelation.sbr" \
	"$(INTDIR)\GrayMap.sbr" \
	"$(INTDIR)\InFer.sbr" \
	"$(INTDIR)\Laser.sbr" \
	"$(INTDIR)\list.sbr" \
	"$(INTDIR)\MakeInferences.sbr" \
	"$(INTDIR)\MakeMapping.sbr" \
	"$(INTDIR)\MakeRelations.sbr" \
	"$(INTDIR)\MapController.sbr" \
	"$(INTDIR)\Matrix.sbr" \
	"$(INTDIR)\MembFunc.sbr" \
	"$(INTDIR)\Node.sbr" \
	"$(INTDIR)\NodeMap.sbr" \
	"$(INTDIR)\Robot.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\versionone.sbr"

"$(OUTDIR)\versionone.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\versionone.pdb" /debug /machine:I386 /out:"$(OUTDIR)\versionone.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BoolMap.obj" \
	"$(INTDIR)\FuzzyMap.obj" \
	"$(INTDIR)\FzyRelation.obj" \
	"$(INTDIR)\GrayMap.obj" \
	"$(INTDIR)\InFer.obj" \
	"$(INTDIR)\Laser.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\MakeInferences.obj" \
	"$(INTDIR)\MakeMapping.obj" \
	"$(INTDIR)\MakeRelations.obj" \
	"$(INTDIR)\MapController.obj" \
	"$(INTDIR)\Matrix.obj" \
	"$(INTDIR)\MembFunc.obj" \
	"$(INTDIR)\Node.obj" \
	"$(INTDIR)\NodeMap.obj" \
	"$(INTDIR)\Robot.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\versionone.obj" \
	"$(INTDIR)\versionone.res"

"$(OUTDIR)\versionone.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("versionone.dep")
!INCLUDE "versionone.dep"
!ELSE 
!MESSAGE Warning: cannot find "versionone.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "versionone - Win32 Release" || "$(CFG)" == "versionone - Win32 Debug"
SOURCE=.\BoolMap.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\BoolMap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\BoolMap.obj"	"$(INTDIR)\BoolMap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\FuzzyMap.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\FuzzyMap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\FuzzyMap.obj"	"$(INTDIR)\FuzzyMap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\FzyRelation.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\FzyRelation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\FzyRelation.obj"	"$(INTDIR)\FzyRelation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\GrayMap.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\GrayMap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\GrayMap.obj"	"$(INTDIR)\GrayMap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\InFer.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\InFer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\InFer.obj"	"$(INTDIR)\InFer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\Laser.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\Laser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\Laser.obj"	"$(INTDIR)\Laser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\list.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\list.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\list.obj"	"$(INTDIR)\list.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\MakeInferences.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\MakeInferences.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\MakeInferences.obj"	"$(INTDIR)\MakeInferences.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\MakeMapping.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\MakeMapping.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\MakeMapping.obj"	"$(INTDIR)\MakeMapping.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\MakeRelations.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\MakeRelations.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\MakeRelations.obj"	"$(INTDIR)\MakeRelations.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\MapController.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\MapController.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\MapController.obj"	"$(INTDIR)\MapController.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\Matrix.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\Matrix.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\Matrix.obj"	"$(INTDIR)\Matrix.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\MembFunc.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\MembFunc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\MembFunc.obj"	"$(INTDIR)\MembFunc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\Node.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\Node.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\Node.obj"	"$(INTDIR)\Node.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\NodeMap.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\NodeMap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\NodeMap.obj"	"$(INTDIR)\NodeMap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\Robot.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\Robot.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\Robot.obj"	"$(INTDIR)\Robot.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\versionone.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\versionone.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\versionone.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\versionone.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\versionone.cpp

!IF  "$(CFG)" == "versionone - Win32 Release"


"$(INTDIR)\versionone.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ELSEIF  "$(CFG)" == "versionone - Win32 Debug"


"$(INTDIR)\versionone.obj"	"$(INTDIR)\versionone.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\versionone.pch"


!ENDIF 

SOURCE=.\versionone.rc

"$(INTDIR)\versionone.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

