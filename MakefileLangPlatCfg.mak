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

CleanSetup ::
	cd "MSI\Base"
	$(MAKE) /f "Makefile" /$(MAKEFLAGS) Clean LANG=$(LANG) PLAT=$(PLAT) CFG=$(CFG)
	cd "$(MAKEDIR)"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"
	-if exist "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" del /f /q "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).mst"

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" :: Localization

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" ::
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Build /p:Configuration=$(CFG) /p:Platform=$(PLAT)

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" ::
	cd "MSI\Base"
	$(MAKE) /f "Makefile" /$(MAKEFLAGS) LANG=$(LANG) PLAT=$(PLAT) CFG=$(CFG)
	cd "$(MAKEDIR)"

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" : \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf" \
	"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).sign"
	-if exist $@ del /f /q $@
	copy /y "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).2.msi" "$(@:"=).tmp" > NUL
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:SetCAB //Nologo "$(@:"=).tmp" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).inf"
	msiinfo.exe "$(@:"=).tmp" /nologo /U 4
!IFDEF MANIFESTCERTIFICATETHUMBPRINT
	signtool.exe sign /sha1 "$(MANIFESTCERTIFICATETHUMBPRINT)" /fd sha256 /tr "$(MANIFESTTIMESTAMPRFC3161URL)" /td sha256 /d "$(MSIBUILD_PRODUCT_NAME)" /q "$(@:"=).tmp"
!ENDIF
	attrib.exe +r "$(@:"=).tmp"
	move /y "$(@:"=).tmp" $@ > NUL

"$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).mst" : "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-en_US$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:MakeMST //Nologo "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-en_US$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" "$(OUTPUT_DIR)\$(MSIBUILD_PRODUCT_NAME_ID)-$(LANG)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" $@
