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

!INCLUDE "..\..\include\MSIBuildCfg.mak"

!IFNDEF MSIBUILD_PRODUCT_NAME
!ERROR Parameter MSIBUILD_PRODUCT_NAME is undefined.
!ENDIF

!IFNDEF MSIBUILD_PRODUCT_NAME_UC
!ERROR Parameter MSIBUILD_PRODUCT_NAME_UC is undefined.
!ENDIF

!IFNDEF MSIBUILD_PLAT_GUID
!ERROR Parameter MSIBUILD_PLAT_GUID is undefined.
!ENDIF

!IFNDEF MSIBUILD_LANG_GUID
!ERROR Parameter MSIBUILD_LANG_GUID is undefined.
!ENDIF

MSIBUILD_IS_LOCALIZEABLE=1


######################################################################
# AppSearch

All :: "$(LANG).$(PLAT).$(CFG).AppSearch-1.idt"

"$(LANG).$(PLAT).$(CFG).AppSearch-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Signature_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
AppSearch	Property	Signature_
OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR	clEventMonitor.exe.$(PLAT)
<<NOKEEP


######################################################################
# CompLocator

All :: "$(LANG).$(PLAT).$(CFG).CompLocator-1.idt"

"$(LANG).$(PLAT).$(CFG).CompLocator-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Signature_	ComponentId	Type
s$(MSIBUILD_LENGTH_ID)	s38	I2
CompLocator	Signature_
clEventMonitor.exe.$(PLAT)	{3E4DDA0E-F8B2-4210-8D8$(MSIBUILD_PLAT_GUID)-90C221670B81}	1
<<NOKEEP


######################################################################
# Component

All :: "$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
compEventMonitor.exe.$(PLAT)	{3E4DDA0E-F8B2-4210-8D8$(MSIBUILD_PLAT_GUID)-90C221670B81}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEventMonitor.exe.$(PLAT)
!IF "$(LANG)" != "en_US"
compEventMonitor.mo.$(LANG)	{289D4CED-93CB-41BC-$(MSIBUILD_LANG_GUID)-49AAF92A9D34}	$(MSIBUILD_PRODUCT_NAME_UC)LOC$(MSIBUILD_LANG_GUID)DIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEventMonitor.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# Feature

All :: "$(LANG).$(PLAT).$(CFG).Feature-2.idt"

"en_US.$(PLAT).$(CFG).Feature-2.idtx" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Feature	Feature_Parent	Title	Description	Display	Level	Directory_	Attributes
s$(MSIBUILD_LENGTH_ID)	S$(MSIBUILD_LENGTH_ID)	L64	L255	I2	i2	S$(MSIBUILD_LENGTH_ID)	i2
1252	Feature	Feature
featEventMonitor		Event Monitor	Real-time display of internal events	101	3	$(MSIBUILD_PRODUCT_NAME_UC)DIR	8
<<NOKEEP

!IF "$(LANG)" == "en_US"
"en_US.$(PLAT).$(CFG).Feature-2.idt" : "en_US.$(PLAT).$(CFG).Feature-2.idtx"
	copy /y $** $@ > NUL
!ELSE
"$(LANG).$(PLAT).$(CFG).Feature-2.idt" : "en_US.$(PLAT).$(CFG).Feature-2.idtx" "..\locale\$(LANG).po"
	cscript.exe "..\..\MSI\MSIBuild\MSI.wsf" //Job:IDTTranslate //Nologo $@ $** /CP:$(MSIBUILD_CODEPAGE)
!ENDIF


######################################################################
# FeatureComponents

All :: "$(LANG).$(PLAT).$(CFG).FeatureComponents-1.idt"

"$(LANG).$(PLAT).$(CFG).FeatureComponents-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Feature_	Component_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
FeatureComponents	Feature_	Component_
featEventMonitor	compEvents.dll.$(PLAT)
featEventMonitor	compEventsPublisher1
featEventMonitor	compEventsPublisher2
featEventMonitor	compEventsPublisher3
featEventMonitor	compEventMonitor.exe.$(PLAT)
featEventMonitor	compLocalizationRepositoryPath
featEventMonitor	compLanguage
!IF "$(LANG)" != "en_US"
featEventMonitor	compwxstd.mo.$(LANG)
featEventMonitor	compwxExtend.mo.$(LANG)
featEventMonitor	compEventMonitor.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# File

All :: "$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
fileEventMonitor.exe.$(PLAT)	compEventMonitor.exe.$(PLAT)	EVENTM~1.EXE|EventMonitor.exe	0		0	1536	1
!IF "$(LANG)" != "en_US"
fileEventMonitor.mo.$(LANG)	compEventMonitor.mo.$(LANG)	EVENTM~1.MO|EventMonitor.mo	0		$(MSIBUILD_LANGID)	0	1
!ENDIF
<<NOKEEP


######################################################################
# RemoveFile

All :: "$(LANG).$(PLAT).$(CFG).RemoveFile-1.idt"

"$(LANG).$(PLAT).$(CFG).RemoveFile-1.idt" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
FileKey	Component_	FileName	DirProperty	InstallMode
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	L255	s$(MSIBUILD_LENGTH_ID)	i2
RemoveFile	FileKey
rmfiEventMonitor	compEventMonitor.exe.$(PLAT)		$(MSIBUILD_PRODUCT_NAME_ID)ShortcutDir	2
<<NOKEEP


######################################################################
# Shortcut

All :: "$(LANG).$(PLAT).$(CFG).Shortcut-2.idt"

"en_US.$(PLAT).$(CFG).Shortcut-2.idtx" : "Makefile" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Shortcut	Directory_	Name	Component_	Target	Arguments	Description	Hotkey	Icon_	IconIndex	ShowCmd	WkDir
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l128	s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	S255	L255	I2	S$(MSIBUILD_LENGTH_ID)	I2	I2	S$(MSIBUILD_LENGTH_ID)
1252	Shortcut	Shortcut
shctEventMonitor	$(MSIBUILD_PRODUCT_NAME_ID)ShortcutDir	EVENTM~1|$(MSIBUILD_PRODUCT_NAME) Event Monitor	compEventMonitor.exe.$(PLAT)	featEventMonitor		Real-time display of internal events					$(MSIBUILD_PRODUCT_NAME_UC)BINDIR
<<NOKEEP

!IF "$(LANG)" == "en_US"
"en_US.$(PLAT).$(CFG).Shortcut-2.idt" : "en_US.$(PLAT).$(CFG).Shortcut-2.idtx"
	copy /y $** $@ > NUL
!ELSE
"$(LANG).$(PLAT).$(CFG).Shortcut-2.idt" : "en_US.$(PLAT).$(CFG).Shortcut-2.idtx" "..\locale\$(LANG).po"
	cscript.exe "..\..\MSI\MSIBuild\MSI.wsf" //Job:IDTTranslate //Nologo $@ $** /CP:$(MSIBUILD_CODEPAGE)
!ENDIF


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\MSI\MSIBuild\MSM.mak"
