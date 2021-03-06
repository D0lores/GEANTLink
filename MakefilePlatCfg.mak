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

All ::

Clean ::
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Clean /p:Configuration=$(CFG) /p:Platform=$(PLAT)

CleanSetup ::
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).ddf"       del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).ddf"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab"       del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf"       del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).rpt"       del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).rpt"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).sign"      del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).sign"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"       del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"
	-if exist "$(OUTPUT_DIR)\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" del /f /q "$(OUTPUT_DIR)\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"


######################################################################
# Building
######################################################################

"$(OUTPUT_DIR)\$(PLAT).$(CFG)\CredWrite.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\MsiUseFeature.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\WLANManager.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\Events.dll" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\EAP-TTLS.dll" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\EAP-TTLS_UI.dll" :: Localization

"$(OUTPUT_DIR)\$(PLAT).$(CFG)\CredWrite.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\MsiUseFeature.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\WLANManager.exe" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\Events.dll" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\EAP-TTLS.dll" \
"$(OUTPUT_DIR)\$(PLAT).$(CFG)\EAP-TTLS_UI.dll" ::
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Build /p:Configuration=$(CFG) /p:Platform=$(PLAT)

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).ddf" : \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-bg_BG$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ca_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cs_CZ$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cy_UK$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-de_DE$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-el_GR$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-es_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-et_EE$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-eu_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fi_FI$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_FR$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_CA$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-gl_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hr_HR$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hu_HU$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-is_IS$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-it_IT$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ko_KR$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-lt_LT$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nb_NO$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nl_NL$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pl_PL$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pt_PT$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ru_RU$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sk_SK$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sl_SI$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sr_RS$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sv_SE$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-tr_TR$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-vi_VN$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-en_US$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi"
	-if exist $@ del /f /q $@
	-if exist "$(@:"=).tmp" del /f /q "$(@:"=).tmp"
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:MakeDDF //Nologo "$(@:"=).tmp" $** /O:"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX)" /C:LZX
	move /y "$(@:"=).tmp" $@ > NUL

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab" \
"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf" \
"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).rpt" : "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).ddf"
	makecab.exe /F $**

!IFDEF MANIFESTCERTIFICATETHUMBPRINT

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).sign" : "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab"

!ENDIF

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" : \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-bg_BG$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ca_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cs_CZ$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cy_UK$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-de_DE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-el_GR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-es_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-et_EE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-eu_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fi_FI$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_FR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_CA$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-gl_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hr_HR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hu_HU$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-is_IS$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-it_IT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ko_KR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-lt_LT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nb_NO$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nl_NL$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pl_PL$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pt_PT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ru_RU$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sk_SK$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sl_SI$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sr_RS$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sv_SE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-tr_TR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
#	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-vi_VN$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-en_US$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"
	-if exist $@ del /f /q $@
	-if exist "$(@:"=).tmp" del /f /q "$(@:"=).tmp"
	copy /y "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-en_US$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" "$(@:"=).tmp" > NUL
	attrib.exe -r "$(@:"=).tmp"
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-bg_BG$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1026 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ca_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1027 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cs_CZ$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1029 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-cy_UK$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1106 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-de_DE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1031 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-el_GR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1032 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-es_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1034 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-et_EE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1061 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-eu_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1069 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fi_FI$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1035 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_FR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 3084 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-fr_CA$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1036 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-gl_ES$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1110 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hr_HR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1050 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-hu_HU$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1038 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-is_IS$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1039 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-it_IT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1040 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ko_KR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1042 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-lt_LT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1063 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nb_NO$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1044 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-nl_NL$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1043 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pl_PL$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1045 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-pt_PT$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 2070 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-ru_RU$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1049 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sk_SK$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1051 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sl_SI$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1060 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sr_RS$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 2074 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-sv_SE$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1053 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-tr_TR$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1055 /L
#	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-vi_VN$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" 1066 /L
	move /y "$(@:"=).tmp" $@ > NUL

"$(OUTPUT_DIR)\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" : \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf"
	$(MAKE) /f "MSI\MSIBuild\CAB.mak" /$(MAKEFLAGS) MSIBUILD_ROOT="MSI\MSIBuild" MSIBUILD_TARGET_MSI=$@ MSIBUILD_SOURCE_MSI="$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" MSIBUILD_INF="$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf" MSIBUILD_CAB="$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).cab" MSIBUILD_PRODUCT_NAME="$(MSIBUILD_PRODUCT_NAME)"

