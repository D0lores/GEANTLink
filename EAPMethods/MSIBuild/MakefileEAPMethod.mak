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
!IF "$(PLAT)" == "Win32"
clEAPMethod$(EAPMETHOD_TYPE).dll.Win32	{326E5E$(EAPMETHOD_GUID)-B6B6-4E75-BA21-5BEE2A40590E}	1
clEAPMethod$(EAPMETHOD_TYPE)_UI.dll.Win32	{8E0766$(EAPMETHOD_GUID)-3201-45E9-BBCB-5D9A527012AB}	1
!ENDIF
!IF "$(PLAT)" == "x64"
clEAPMethod$(EAPMETHOD_TYPE).dll.x64	{1E5401$(EAPMETHOD_GUID)-813D-4DAA-B5A8-FFC7B9DB0B80}	1
clEAPMethod$(EAPMETHOD_TYPE)_UI.dll.x64	{6DA063$(EAPMETHOD_GUID)-FFF0-42F1-88ED-367EB94E7E8E}	1
!ENDIF
!IF "$(PLAT)" == "ARM64"
clEAPMethod$(EAPMETHOD_TYPE).dll.ARM64	{70A98A$(EAPMETHOD_GUID)-9E97-4960-BBA7-86F1838B47C8}	1
clEAPMethod$(EAPMETHOD_TYPE)_UI.dll.ARM64	{7291C4$(EAPMETHOD_GUID)-9045-47DC-9D68-86318078F350}	1
!ENDIF
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
!IF "$(PLAT)" == "Win32"
compEAPMethod$(EAPMETHOD_TYPE).dll.Win32	{326E5E$(EAPMETHOD_GUID)-B6B6-4E75-BA21-5BEE2A40590E}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	0		fileEAPMethod$(EAPMETHOD_TYPE).dll.Win32
compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.Win32	{8E0766$(EAPMETHOD_GUID)-3201-45E9-BBCB-5D9A527012AB}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	0		fileEAPMethod$(EAPMETHOD_TYPE)_UI.dll.Win32
!ENDIF
!IF "$(PLAT)" == "x64"
compEAPMethod$(EAPMETHOD_TYPE).dll.x64	{1E5401$(EAPMETHOD_GUID)-813D-4DAA-B5A8-FFC7B9DB0B80}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	256		fileEAPMethod$(EAPMETHOD_TYPE).dll.x64
compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.x64	{6DA063$(EAPMETHOD_GUID)-FFF0-42F1-88ED-367EB94E7E8E}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	256		fileEAPMethod$(EAPMETHOD_TYPE)_UI.dll.x64
!ENDIF
!IF "$(PLAT)" == "ARM64"
compEAPMethod$(EAPMETHOD_TYPE).dll.ARM64	{70A98A$(EAPMETHOD_GUID)-9E97-4960-BBA7-86F1838B47C8}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	256		fileEAPMethod$(EAPMETHOD_TYPE).dll.ARM64
compEAPMethod$(EAPMETHOD_TYPE)_UI.dll.ARM64	{7291C4$(EAPMETHOD_GUID)-9045-47DC-9D68-86318078F350}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	256		fileEAPMethod$(EAPMETHOD_TYPE)_UI.dll.ARM64
!ENDIF
compEAPMethod$(EAPMETHOD_TYPE)PeerDllPath	{A932B1$(EAPMETHOD_GUID)-3B65-4317-8201-03078C72A998}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerDllPath
compEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath	{D640C9$(EAPMETHOD_GUID)-45C0-4550-A323-86E8EE0FE9E9}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerConfigUIPath
compEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath	{F06B12$(EAPMETHOD_GUID)-DEF8-441E-87FD-FBFFEF4BD4F7}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerIdentityPath
compEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath	{44B2DE$(EAPMETHOD_GUID)-C667-482C-A5E7-630F7295A43E}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInteractiveUIPath
compEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName	{7D4ABF$(EAPMETHOD_GUID)-D166-4BD2-953E-0B43C8E2C286}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerFriendlyName
compEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog	{C2D911$(EAPMETHOD_GUID)-13EB-4B75-BBFF-BA557CB55A3C}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInvokePasswordDialog
compEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog	{59194C$(EAPMETHOD_GUID)-C234-4CE8-B65E-116FE15A7FC8}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)PeerInvokeUsernameDialog
compEAPMethod$(EAPMETHOD_TYPE)Properties	{75835E$(EAPMETHOD_GUID)-CAFE-4EAE-AD60-B158403035BF}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEAPMethod$(EAPMETHOD_TYPE)Properties
!IF "$(LANG)" == "bg_BG"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.bg_BG	{FEEA3A$(EAPMETHOD_GUID)-28BB-40BF-86E3-78181B816C06}	$(MSIBUILD_PRODUCT_NAME_UC)LOCBGBGDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.bg_BG
!ENDIF
!IF "$(LANG)" == "ca_ES"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ca_ES	{4324EF$(EAPMETHOD_GUID)-ADDB-40DC-86EE-8E4B8803EFC2}	$(MSIBUILD_PRODUCT_NAME_UC)LOCCAESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ca_ES
!ENDIF
!IF "$(LANG)" == "cs_CZ"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.cs_CZ	{FD14DD$(EAPMETHOD_GUID)-54CF-4998-8195-50B4AC80DB84}	$(MSIBUILD_PRODUCT_NAME_UC)LOCCSCZDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.cs_CZ
!ENDIF
!IF "$(LANG)" == "cy_UK"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.cy_UK	{150A4F$(EAPMETHOD_GUID)-78B6-4E1B-A5F4-846A623DEB9F}	$(MSIBUILD_PRODUCT_NAME_UC)LOCCYUKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.cy_UK
!ENDIF
!IF "$(LANG)" == "de_DE"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.de_DE	{F6553A$(EAPMETHOD_GUID)-9B1C-4548-92C5-0E112EC9BE72}	$(MSIBUILD_PRODUCT_NAME_UC)LOCDEDEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.de_DE
!ENDIF
!IF "$(LANG)" == "el_GR"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.el_GR	{F473E5$(EAPMETHOD_GUID)-3CF4-4B23-81BF-235BE66C4802}	$(MSIBUILD_PRODUCT_NAME_UC)LOCELGRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.el_GR
!ENDIF
!IF "$(LANG)" == "es_ES"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.es_ES	{2D2F53$(EAPMETHOD_GUID)-D685-4DB3-BB6C-86CD8DE75D1E}	$(MSIBUILD_PRODUCT_NAME_UC)LOCESESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.es_ES
!ENDIF
!IF "$(LANG)" == "et_EE"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.et_EE	{BCC51E$(EAPMETHOD_GUID)-3CD0-4AA0-9B58-DCF00D0D9E34}	$(MSIBUILD_PRODUCT_NAME_UC)LOCETEEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.et_EE
!ENDIF
!IF "$(LANG)" == "eu_ES"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.eu_ES	{D8C518$(EAPMETHOD_GUID)-9ADD-45A2-B7C9-53B0B5E9E497}	$(MSIBUILD_PRODUCT_NAME_UC)LOCEUESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.eu_ES
!ENDIF
!IF "$(LANG)" == "fi_FI"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fi_FI	{297F57$(EAPMETHOD_GUID)-B0B4-4CF3-A2A1-715642BA2F3E}	$(MSIBUILD_PRODUCT_NAME_UC)LOCFIFIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fi_FI
!ENDIF
!IF "$(LANG)" == "fr_CA"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fr_CA	{76B5D2$(EAPMETHOD_GUID)-D0A2-4835-A524-57A007ED1299}	$(MSIBUILD_PRODUCT_NAME_UC)LOCFRCADIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fr_CA
!ENDIF
!IF "$(LANG)" == "fr_FR"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fr_FR	{8628A5$(EAPMETHOD_GUID)-6E9A-4A2B-994D-49B4C3554C60}	$(MSIBUILD_PRODUCT_NAME_UC)LOCFRFRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.fr_FR
!ENDIF
!IF "$(LANG)" == "gl_ES"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.gl_ES	{F38FBB$(EAPMETHOD_GUID)-77E8-457E-95CC-D23622C1F841}	$(MSIBUILD_PRODUCT_NAME_UC)LOCGLESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.gl_ES
!ENDIF
!IF "$(LANG)" == "hr_HR"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.hr_HR	{61B512$(EAPMETHOD_GUID)-E5B1-4AC2-B3A5-AEA5452AC97A}	$(MSIBUILD_PRODUCT_NAME_UC)LOCHRHRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.hr_HR
!ENDIF
!IF "$(LANG)" == "hu_HU"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.hu_HU	{4C97F6$(EAPMETHOD_GUID)-4473-4299-9E79-7EFB1D142998}	$(MSIBUILD_PRODUCT_NAME_UC)LOCHUHUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.hu_HU
!ENDIF
!IF "$(LANG)" == "is_IS"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.is_IS	{2FF50F$(EAPMETHOD_GUID)-1643-4E21-BA88-F423A566B3EB}	$(MSIBUILD_PRODUCT_NAME_UC)LOCISISDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.is_IS
!ENDIF
!IF "$(LANG)" == "it_IT"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.it_IT	{A05A05$(EAPMETHOD_GUID)-821F-4DD6-BE78-518B4C304C95}	$(MSIBUILD_PRODUCT_NAME_UC)LOCITITDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.it_IT
!ENDIF
!IF "$(LANG)" == "ko_KR"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ko_KR	{98B218$(EAPMETHOD_GUID)-5823-447B-A804-B38D3C4E75E0}	$(MSIBUILD_PRODUCT_NAME_UC)LOCKOKRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ko_KR
!ENDIF
!IF "$(LANG)" == "lt_LT"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.lt_LT	{BE7AF9$(EAPMETHOD_GUID)-CB33-4BA7-8615-CE2AD93DB086}	$(MSIBUILD_PRODUCT_NAME_UC)LOCLTLTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.lt_LT
!ENDIF
!IF "$(LANG)" == "nb_NO"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.nb_NO	{56CFDD$(EAPMETHOD_GUID)-D711-4964-8ED8-8C34F97B80AB}	$(MSIBUILD_PRODUCT_NAME_UC)LOCNBNODIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.nb_NO
!ENDIF
!IF "$(LANG)" == "nl_NL"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.nl_NL	{B2D874$(EAPMETHOD_GUID)-D46D-45F6-9414-12F2EA0B2A1C}	$(MSIBUILD_PRODUCT_NAME_UC)LOCNLNLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.nl_NL
!ENDIF
!IF "$(LANG)" == "pl_PL"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.pl_PL	{2178BE$(EAPMETHOD_GUID)-9B19-45D7-A55A-27FDEFCBCC6E}	$(MSIBUILD_PRODUCT_NAME_UC)LOCPLPLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.pl_PL
!ENDIF
!IF "$(LANG)" == "pt_PT"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.pt_PT	{23C725$(EAPMETHOD_GUID)-9143-45A1-A3C7-80E7BE1F21F5}	$(MSIBUILD_PRODUCT_NAME_UC)LOCPTPTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.pt_PT
!ENDIF
!IF "$(LANG)" == "ru_RU"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ru_RU	{5E6C6E$(EAPMETHOD_GUID)-7DFE-4510-B653-36C0DDDB0C38}	$(MSIBUILD_PRODUCT_NAME_UC)LOCRURUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.ru_RU
!ENDIF
!IF "$(LANG)" == "sk_SK"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sk_SK	{F1CC8D$(EAPMETHOD_GUID)-273F-485D-B094-F093EAA35B9E}	$(MSIBUILD_PRODUCT_NAME_UC)LOCSKSKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sk_SK
!ENDIF
!IF "$(LANG)" == "sl_SI"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sl_SI	{F6FCBE$(EAPMETHOD_GUID)-1C93-4F83-BA7C-8D3BAE0FF26E}	$(MSIBUILD_PRODUCT_NAME_UC)LOCSLSIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sl_SI
!ENDIF
!IF "$(LANG)" == "sr_RS"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sr_RS	{1C8BCB$(EAPMETHOD_GUID)-3A6F-4682-81FD-533868BFB886}	$(MSIBUILD_PRODUCT_NAME_UC)LOCSRRSDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sr_RS
!ENDIF
!IF "$(LANG)" == "sv_SE"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sv_SE	{2958C0$(EAPMETHOD_GUID)-FE75-454F-AFC2-05CFE0344EA8}	$(MSIBUILD_PRODUCT_NAME_UC)LOCSVSEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.sv_SE
!ENDIF
!IF "$(LANG)" == "tr_TR"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.tr_TR	{5A49E7$(EAPMETHOD_GUID)-BF08-4D19-A81D-E528C254AADF}	$(MSIBUILD_PRODUCT_NAME_UC)LOCTRTRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.tr_TR
!ENDIF
!IF "$(LANG)" == "vi_VN"
compEAPMethod$(EAPMETHOD_TYPE)_UI.mo.vi_VN	{F4F94B$(EAPMETHOD_GUID)-ABB8-4622-866F-0F454FE72373}	$(MSIBUILD_PRODUCT_NAME_UC)LOCVIVNDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		fileEAPMethod$(EAPMETHOD_TYPE)_UI.mo.vi_VN
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
