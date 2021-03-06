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

!IF "$(EAPMETHOD_TYPE)" == "21"
EAPMETHOD_GUID=15
EAPMETHOD_NAME=EAP-TTLS
!ELSE
!ERROR Unknown EAP Method type.
!ENDIF

MSIBUILD_IS_LOCALIZEABLE=1


######################################################################
# AppSearch

All :: "$(LANG).$(PLAT).$(CFG).AppSearch-1.idt"

"$(LANG).$(PLAT).$(CFG).AppSearch-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Signature_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
AppSearch	Property	Signature_
OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR	clEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)
OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR	clEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)
<<NOKEEP


######################################################################
# CompLocator

All :: "$(LANG).$(PLAT).$(CFG).CompLocator-1.idt"

"$(LANG).$(PLAT).$(CFG).CompLocator-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Signature_	ComponentId	Type
s$(MSIBUILD_LENGTH_ID)	s38	I2
CompLocator	Signature_
clEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)	{326E5E$(EAPMETHOD_GUID)-B6B6-4E75-BA2$(MSIBUILD_PLAT_GUID)-5BEE2A40590E}	1
clEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)	{8E0766$(EAPMETHOD_GUID)-3201-45E9-BBC$(MSIBUILD_PLAT_GUID)-5D9A527012AB}	1
<<NOKEEP


######################################################################
# Component

All :: "$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
compEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)	{326E5E$(EAPMETHOD_GUID)-B6B6-4E75-BA2$(MSIBUILD_PLAT_GUID)-5BEE2A40590E}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)
compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)	{8E0766$(EAPMETHOD_GUID)-3201-45E9-BBC$(MSIBUILD_PLAT_GUID)-5D9A527012AB}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)
compEAPMethod$(EAPMETHOD_TYPE)PeerDllPath	{A932B1$(EAPMETHOD_GUID)-3B65-4317-8201-03078C72A998}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerDllPath
compEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath	{D640C9$(EAPMETHOD_GUID)-45C0-4550-A323-86E8EE0FE9E9}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath
compEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath	{F06B12$(EAPMETHOD_GUID)-DEF8-441E-87FD-FBFFEF4BD4F7}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath
compEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath	{44B2DE$(EAPMETHOD_GUID)-C667-482C-A5E7-630F7295A43E}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath
compEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName	{7D4ABF$(EAPMETHOD_GUID)-D166-4BD2-953E-0B43C8E2C286}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName
compEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog	{C2D911$(EAPMETHOD_GUID)-13EB-4B75-BBFF-BA557CB55A3C}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog
compEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog	{59194C$(EAPMETHOD_GUID)-C234-4CE8-B65E-116FE15A7FC8}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog
compEAPMethod$(EAPMETHOD_TYPE)Properties	{75835E$(EAPMETHOD_GUID)-CAFE-4EAE-AD60-B158403035BF}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)Properties
!IF "$(LANG)" != "en_US"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.$(LANG)	{FEEA3A$(EAPMETHOD_GUID)-28BB-40BF-$(MSIBUILD_LANG_GUID)-78181B816C06}	$(MSIBUILD_PRODUCT_NAME_UC)LOC$(MSIBUILD_LANG_GUID)DIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# Feature

All :: "$(LANG).$(PLAT).$(CFG).Feature-2.idt"

"en_US.$(PLAT).$(CFG).Feature-2.idtx" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Feature	Feature_Parent	Title	Description	Display	Level	Directory_	Attributes
s$(MSIBUILD_LENGTH_ID)	S$(MSIBUILD_LENGTH_ID)	L64	L255	I2	i2	S$(MSIBUILD_LENGTH_ID)	i2
1252	Feature	Feature
featEAPMethod$(EAPMETHOD_TYPE)	featEAPMethods	$(EAPMETHOD_NAME)	$(EAPMETHOD_NAME) Method	1	3	$(MSIBUILD_PRODUCT_NAME_UC)DIR	8
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

"$(LANG).$(PLAT).$(CFG).FeatureComponents-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Feature_	Component_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
FeatureComponents	Feature_	Component_
featEAPMethod$(EAPMETHOD_TYPE)	compEvents.dll.$(PLAT)
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisher1
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisher2
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisher3
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisher4
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChannels
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChOperational1
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChOperational2
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChOperational3
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChAnalytic1
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChAnalytic2
featEAPMethod$(EAPMETHOD_TYPE)	compEventsPublisherChAnalytic3
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational1
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational2
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational3
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational4
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational5
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational6
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational7
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational8
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelOperational9
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic1
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic2
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic3
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic4
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic5
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic6
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic7
featEAPMethod$(EAPMETHOD_TYPE)	compEventsChannelAnalytic8
featEAPMethod$(EAPMETHOD_TYPE)	compEAPHostAuthor
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerDllPath
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)Properties
featEAPMethod$(EAPMETHOD_TYPE)	compLocalizationRepositoryPath
featEAPMethod$(EAPMETHOD_TYPE)	compLanguage
!IF "$(LANG)" != "en_US"
featEAPMethod$(EAPMETHOD_TYPE)	compwxstd.mo.$(LANG)
featEAPMethod$(EAPMETHOD_TYPE)	compwxExtend.mo.$(LANG)
featEAPMethod$(EAPMETHOD_TYPE)	compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# File

All :: "$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
fileEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)	compEAPMethod$(EAPMETHOD_TYPE).dll.$(PLAT)	EAPME~$(EAPMETHOD_GUID).DLL|$(EAPMETHOD_NAME).dll	0		0	1536	1
fileEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)	compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.$(PLAT)	EAPMU~$(EAPMETHOD_GUID).DLL|$(EAPMETHOD_NAME)_UI.dll	0		0	1536	1
!IF "$(LANG)" != "en_US"
fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.$(LANG)	compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.$(LANG)	EAPMU~$(EAPMETHOD_GUID).MO|$(EAPMETHOD_NAME)_UI.mo	0		$(MSIBUILD_LANGID)	0	1
!ENDIF
<<NOKEEP


######################################################################
# Registry

All :: "$(LANG).$(PLAT).$(CFG).Registry-1.idt"

"$(LANG).$(PLAT).$(CFG).Registry-1.idt" : "Makefile" "..\MSIBuild\MakefileEAPMethod.mak" "..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Registry	Root	Key	Name	Value	Component_
s$(MSIBUILD_LENGTH_ID)	i2	l255	L255	L0	s$(MSIBUILD_LENGTH_ID)
Registry	Registry
regEAPMethod$(EAPMETHOD_TYPE)PeerDllPath	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerDllPath	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]$(EAPMETHOD_NAME).dll	compEAPMethod$(EAPMETHOD_TYPE)PeerDllPath
regEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerConfigUIPath	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]$(EAPMETHOD_NAME)_UI.dll	compEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath
regEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerIdentityPath	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]$(EAPMETHOD_NAME)_UI.dll	compEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath
regEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerInteractiveUIPath	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]$(EAPMETHOD_NAME)_UI.dll	compEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath
regEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerFriendlyName	@[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]$(EAPMETHOD_NAME).dll,-1	compEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName
regEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerInvokePasswordDialog	#0	compEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog
regEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	PeerInvokeUsernameDialog	#0	compEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog
regEAPMethod$(EAPMETHOD_TYPE)Properties	2	SYSTEM\CurrentControlSet\services\EapHost\Methods\$(EAPMETHOD_AUTHOR_ID)\$(EAPMETHOD_TYPE)	Properties	#389871807	compEAPMethod$(EAPMETHOD_TYPE)Properties
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\MSI\MSIBuild\MSM.mak"
