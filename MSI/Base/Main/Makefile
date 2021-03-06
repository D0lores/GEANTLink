#
#    Copyright 1991-2020 Amebis
#    Copyright 2016 GÉANT
#
#    This file is part of GÉANTLink.
#
#    GÉANTLink is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    GÉANTLink is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with GÉANTLink. If not, see <http://www.gnu.org/licenses/>.
#

!INCLUDE "..\..\..\include\MSIBuildCfg.mak"

!IFNDEF MSIBUILD_PRODUCT_NAME
!ERROR Parameter MSIBUILD_PRODUCT_NAME is undefined.
!ENDIF

!IFNDEF MSIBUILD_PRODUCT_NAME_ID
!ERROR Parameter MSIBUILD_PRODUCT_NAME_ID is undefined.
!ENDIF

!IFNDEF MSIBUILD_PRODUCT_NAME_UC
!ERROR Parameter MSIBUILD_PRODUCT_NAME_UC is undefined.
!ENDIF

!IFNDEF MSIBUILD_PRODUCT_NAME_8_3
!ERROR Parameter MSIBUILD_PRODUCT_NAME_8_3 is undefined.
!ENDIF

!IFNDEF MSIBUILD_LANG_GUID
!ERROR Parameter MSIBUILD_LANG_GUID is undefined.
!ENDIF

MSIBUILD_IS_LOCALIZEABLE=1


######################################################################
# AppSearch

All :: "$(LANG).$(PLAT).$(CFG).AppSearch-1.idt"

"$(LANG).$(PLAT).$(CFG).AppSearch-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Signature_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
AppSearch	Property	Signature_
LANGREG	rlLanguage.Win32
!IF "$(PLAT)" == "x64" || "$(PLAT)" == "ARM64"
LANGREG	rlLanguage.$(PLAT)
!ENDIF
<<NOKEEP


######################################################################
# Component

All :: "$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
compLocalizationRepositoryPath	{6551BCAB-3558-4A73-A8F2-D5A17E85481B}	$(MSIBUILD_PRODUCT_NAME_UC)LOCDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regLocalizationRepositoryPath
compLanguage	{187A7FE1-A380-4281-9FB6-456B161CDF36}	$(MSIBUILD_PRODUCT_NAME_UC)LOCDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regLanguage
!IF "$(LANG)" != "en_US"
compwxstd.mo.$(LANG)	{5BFC819A-8A84-42D8-$(MSIBUILD_LANG_GUID)-3733450235E4}	$(MSIBUILD_PRODUCT_NAME_UC)LOC$(MSIBUILD_LANG_GUID)DIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxstd.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# CustomAction

All :: "$(LANG).$(PLAT).$(CFG).CustomAction-1.idt"

"$(LANG).$(PLAT).$(CFG).CustomAction-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Action	Type	Source	Target
s$(MSIBUILD_LENGTH_ID)	i2	S$(MSIBUILD_LENGTH_ID)	S255
CustomAction	Action
caSet$(MSIBUILD_PRODUCT_NAME_UC)DIR1	35	$(MSIBUILD_PRODUCT_NAME_UC)DIR	[OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR]
caSet$(MSIBUILD_PRODUCT_NAME_UC)DIR2	35	$(MSIBUILD_PRODUCT_NAME_UC)DIR	[INSTALLDIR]
caSetLANGUAGE1	307	LANGUAGE	[LANGREG]
caSetLANGUAGE2	307	LANGUAGE	[LANG]
<<NOKEEP


######################################################################
# Directory

All :: "$(LANG).$(PLAT).$(CFG).Directory-1.idt"

"$(LANG).$(PLAT).$(CFG).Directory-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Directory	Directory_Parent	DefaultDir
s$(MSIBUILD_LENGTH_ID)	S$(MSIBUILD_LENGTH_ID)	l255
Directory	Directory
TARGETDIR		SourceDir
ProgramFilesFolder	TARGETDIR	.
!IF "$(PLAT)" == "x64" || "$(PLAT)" == "ARM64"
ProgramFiles64Folder	TARGETDIR	.
PROGRAMFILESDIR	ProgramFiles64Folder	.
!ELSE
PROGRAMFILESDIR	ProgramFilesFolder	.
!ENDIF
ProgramMenuFolder	TARGETDIR	.
$(MSIBUILD_PRODUCT_NAME_ID)ShortcutDir	ProgramMenuFolder	$(MSIBUILD_PRODUCT_NAME_8_3)|$(MSIBUILD_PRODUCT_NAME):.
$(MSIBUILD_PRODUCT_NAME_UC)DIR	PROGRAMFILESDIR	$(MSIBUILD_PRODUCT_NAME_8_3)|$(MSIBUILD_PRODUCT_NAME):.
!IF     "$(PLAT)" == "Win32" && "$(CFG)" == "Debug"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:WIN32~1.DEB|Win32.Debug
!ELSEIF "$(PLAT)" == "Win32" && "$(CFG)" == "Release"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:WIN32~1.REL|Win32.Release
!ELSEIF "$(PLAT)" == "x64"   && "$(CFG)" == "Debug"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:X64~1.DEB|x64.Debug
!ELSEIF "$(PLAT)" == "x64"   && "$(CFG)" == "Release"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:X64~1.REL|x64.Release
!ELSEIF "$(PLAT)" == "ARM64"   && "$(CFG)" == "Debug"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:ARM64~1.DEB|ARM64.Debug
!ELSEIF "$(PLAT)" == "ARM64"   && "$(CFG)" == "Release"
$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	.:ARM64~1.REL|ARM64.Release
!ENDIF
$(MSIBUILD_PRODUCT_NAME_UC)LOCDIR	$(MSIBUILD_PRODUCT_NAME_UC)DIR	locale
!IF "$(LANG)" != "en_US"
$(MSIBUILD_PRODUCT_NAME_UC)LOC$(MSIBUILD_LANG_GUID)DIR	$(MSIBUILD_PRODUCT_NAME_UC)LOCDIR	$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# File

All :: "$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
!IF "$(LANG)" != "en_US"
filewxstd.mo.$(LANG)	compwxstd.mo.$(LANG)	wxstd.mo	0		$(MSIBUILD_LANGID)	0	1
!ENDIF
<<NOKEEP


######################################################################
# Icon

All :: \
	"$(LANG).$(PLAT).$(CFG).Icon-1.idt" \
	"$(LANG).$(PLAT).$(CFG).Icon-1\product.ico"

"$(LANG).$(PLAT).$(CFG).Icon-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak" "$(LANG).$(PLAT).$(CFG).Icon-1"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Name	Data
s$(MSIBUILD_LENGTH_ID)	v0
Icon	Name
iconproduct.ico	product.ico
<<NOKEEP

"$(LANG).$(PLAT).$(CFG).Icon-1\product.ico" : "..\..\..\include\icon_full.ico"
	copy /y $** $@ > NUL


######################################################################
# InstallExecuteSequence

All :: "$(LANG).$(PLAT).$(CFG).InstallExecuteSequence-1.idt"

"$(LANG).$(PLAT).$(CFG).InstallExecuteSequence-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Action	Condition	Sequence
s$(MSIBUILD_LENGTH_ID)	S255	I2
InstallExecuteSequence	Action
caSetLANGUAGE1	LANGREG	653
caSetLANGUAGE2	LANG	654
caSet$(MSIBUILD_PRODUCT_NAME_UC)DIR1	OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR AND UILevel < 4	1001
caSet$(MSIBUILD_PRODUCT_NAME_UC)DIR2	INSTALLDIR AND UILevel < 4	1002
<<NOKEEP


######################################################################
# LaunchCondition

All :: "$(LANG).$(PLAT).$(CFG).LaunchCondition-2.idt"

"en_US.$(PLAT).$(CFG).LaunchCondition-2.idtx" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Condition	Description
s255	l255
LaunchCondition	Condition
VersionNT >= "600"	[ProductName] requires Windows Vista or later version of Windows.
<<NOKEEP

!IF "$(LANG)" == "en_US"
"en_US.$(PLAT).$(CFG).LaunchCondition-2.idt" : "en_US.$(PLAT).$(CFG).LaunchCondition-2.idtx"
	copy /y $** $@ > NUL
!ELSE
"$(LANG).$(PLAT).$(CFG).LaunchCondition-2.idt" : "en_US.$(PLAT).$(CFG).LaunchCondition-2.idtx" "..\locale\$(LANG).po"
	cscript.exe "..\..\MSIBuild\MSI.wsf" //Job:IDTTranslate //Nologo $@ $** /CP:$(MSIBUILD_CODEPAGE)
!ENDIF


######################################################################
# Media

All :: "$(LANG).$(PLAT).$(CFG).Media-1.idt"

"$(LANG).$(PLAT).$(CFG).Media-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
DiskId	LastSequence	DiskPrompt	Cabinet	VolumeLabel	Source
i2	i2	L64	S255	S32	S$(MSIBUILD_LENGTH_ID)
Media	DiskId
1	1	[ProductName]		$(MSIBUILD_PRODUCT_NAME_UC)	
<<NOKEEP


######################################################################
# Property

All :: \
	"$(LANG).$(PLAT).$(CFG).Property-1.idt" \
	"$(LANG).$(PLAT).$(CFG).Property-2.idt"

"$(LANG).$(PLAT).$(CFG).Property-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Value
s$(MSIBUILD_LENGTH_ID)	l0
Property	Property
ARPPRODUCTICON	iconproduct.ico
ALLUSERS	1
DISABLEADVTSHORTCUTS	1
INSTALLLEVEL	3
InstallMode	Typical
SecureCustomProperties	OLDPRODUCTFOUND;NEWPRODUCTFOUND;LANG
LANGUAGE	$(LANG)
<<NOKEEP

"en_US.$(PLAT).$(CFG).Property-2.idtx" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Value
s$(MSIBUILD_LENGTH_ID)	l0
1252	Property	Property
ARPURLINFOABOUT	http://www.geant.org/
ARPHELPLINK	http://www.geant.org/
ARPURLUPDATEINFO	https://github.com/Amebis/GEANTLink/releases
<<NOKEEP

!IF "$(LANG)" == "en_US"
"en_US.$(PLAT).$(CFG).Property-2.idt" : "en_US.$(PLAT).$(CFG).Property-2.idtx"
	copy /y $** $@ > NUL
!ELSE
"$(LANG).$(PLAT).$(CFG).Property-2.idt" : "en_US.$(PLAT).$(CFG).Property-2.idtx" "..\locale\$(LANG).po"
	cscript.exe "..\..\MSIBuild\MSI.wsf" //Job:IDTTranslate //Nologo $@ $** /CP:$(MSIBUILD_CODEPAGE)
!ENDIF


######################################################################
# Registry

All :: "$(LANG).$(PLAT).$(CFG).Registry-1.idt"

"$(LANG).$(PLAT).$(CFG).Registry-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Registry	Root	Key	Name	Value	Component_
s$(MSIBUILD_LENGTH_ID)	i2	l255	L255	L0	s$(MSIBUILD_LENGTH_ID)
Registry	Registry
regLocalizationRepositoryPath	2	SOFTWARE\$(MSIBUILD_VENDOR_NAME)\$(MSIBUILD_PRODUCT_NAME)	LocalizationRepositoryPath	[$(MSIBUILD_PRODUCT_NAME_UC)LOCDIR]	compLocalizationRepositoryPath
regLanguage	2	SOFTWARE\$(MSIBUILD_VENDOR_NAME)\$(MSIBUILD_PRODUCT_NAME)	Language	[LANGUAGE]	compLanguage
<<NOKEEP


######################################################################
# RegLocator

All :: "$(LANG).$(PLAT).$(CFG).RegLocator-1.idt"

"$(LANG).$(PLAT).$(CFG).RegLocator-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Signature_	Root	Key	Name	Type
s$(MSIBUILD_LENGTH_ID)	i2	s255	S255	I2
RegLocator	Signature_
rlLanguage.Win32	2	SOFTWARE\$(MSIBUILD_VENDOR_NAME)\$(MSIBUILD_PRODUCT_NAME)	Language	2
!IF "$(PLAT)" == "x64" || "$(PLAT)" == "ARM64"
rlLanguage.$(PLAT)	2	SOFTWARE\$(MSIBUILD_VENDOR_NAME)\$(MSIBUILD_PRODUCT_NAME)	Language	18
!ENDIF
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\MSIBuild\MSM.mak"
