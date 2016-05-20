/*
    Copyright 2015-2016 Amebis
    Copyright 2016 GÉANT

    This file is part of GÉANTLink.

    GÉANTLink is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GÉANTLink is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GÉANTLink. If not, see <http://www.gnu.org/licenses/>.
*/

#include <StdAfx.h>


//////////////////////////////////////////////////////////////////////
// eap::session
//////////////////////////////////////////////////////////////////////

eap::session::session()
{
}


eap::session::~session()
{
}


DWORD eap::session::begin(
    _In_                                   DWORD         dwFlags,
    _In_                             const EapAttributes *pAttributeArray,
    _In_                                   HANDLE        hTokenImpersonateUser,
    _In_                                   DWORD         dwConnectionDataSize,
    _In_count_(dwConnectionDataSize) const BYTE          *pConnectionData,
    _In_                                   DWORD         dwUserDataSize,
    _In_count_(dwUserDataSize)       const BYTE          *pUserData,
    _In_                                   DWORD         dwMaxSendPacketSize,
    _Out_                                  EAP_ERROR     **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(pAttributeArray);
    UNREFERENCED_PARAMETER(hTokenImpersonateUser);
    UNREFERENCED_PARAMETER(dwConnectionDataSize);
    UNREFERENCED_PARAMETER(pConnectionData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(dwMaxSendPacketSize);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_SUCCESS;
}


DWORD eap::session::end(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_SUCCESS;
}


DWORD eap::session::process_request_packet(
    _In_                                       DWORD               dwReceivedPacketSize,
    _In_bytecount_(dwReceivedPacketSize) const EapPacket           *pReceivedPacket,
    _Out_                                      EapPeerMethodOutput *pEapOutput,
    _Out_                                      EAP_ERROR           **ppEapError)
{
    UNREFERENCED_PARAMETER(dwReceivedPacketSize);
    UNREFERENCED_PARAMETER(pReceivedPacket);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_response_packet(
    _Inout_                            DWORD              *pdwSendPacketSize,
    _Inout_bytecap_(*dwSendPacketSize) EapPacket          *pSendPacket,
    _Out_                              EAP_ERROR          **ppEapError)
{
    UNREFERENCED_PARAMETER(pdwSendPacketSize);
    UNREFERENCED_PARAMETER(pSendPacket);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_result(_In_ EapPeerMethodResultReason reason, _Out_ EapPeerMethodResult *ppResult, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(ppResult);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_ui_context(
    _Out_ DWORD     *pdwUIContextDataSize,
    _Out_ BYTE      **ppUIContextData,
    _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pdwUIContextDataSize);
    UNREFERENCED_PARAMETER(ppUIContextData);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::set_ui_context(
    _In_                                  DWORD               dwUIContextDataSize,
    _In_count_(dwUIContextDataSize) const BYTE                *pUIContextData,
    _In_                            const EapPeerMethodOutput *pEapOutput,
    _Out_                                 EAP_ERROR           **ppEapError)
{
    UNREFERENCED_PARAMETER(dwUIContextDataSize);
    UNREFERENCED_PARAMETER(pUIContextData);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_response_attributes(_Out_ EapAttributes *pAttribs, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pAttribs);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::set_response_attributes(const _In_ EapAttributes *pAttribs, _Out_ EapPeerMethodOutput *pEapOutput, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pAttribs);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


//////////////////////////////////////////////////////////////////////
// eap::module
//////////////////////////////////////////////////////////////////////

eap::module::module()
{
    m_ep.create(&EAPMETHOD_TRACE_EVENT_PROVIDER);
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_LOAD, winstd::event_data((BYTE)EAPMETHOD_TYPE), winstd::event_data::blank);

    m_heap.create(0, 0, 0);
}


eap::module::~module()
{
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_UNLOAD, winstd::event_data((BYTE)EAPMETHOD_TYPE), winstd::event_data::blank);
}


EAP_ERROR* eap::module::make_error(_In_ DWORD dwErrorCode, _In_ DWORD dwReasonCode, _In_ LPCGUID pRootCauseGuid, _In_ LPCGUID pRepairGuid, _In_ LPCGUID pHelpLinkGuid, _In_z_ LPCWSTR pszRootCauseString, _In_z_ LPCWSTR pszRepairString) const
{
    // Calculate memory size requirement.
    SIZE_T
        nRootCauseSize    = pszRootCauseString != NULL && pszRootCauseString[0] ? (wcslen(pszRootCauseString) + 1)*sizeof(WCHAR) : 0,
        nRepairStringSize = pszRepairString    != NULL && pszRepairString   [0] ? (wcslen(pszRepairString   ) + 1)*sizeof(WCHAR) : 0,
        nEapErrorSize = sizeof(EAP_ERROR) + nRootCauseSize + nRepairStringSize;

    EAP_ERROR *pError = (EAP_ERROR*)HeapAlloc(m_heap, 0, nEapErrorSize);
    if (!pError)
        return NULL;
    BYTE *p = (BYTE*)(pError + 1);

    // Fill the error descriptor.
    pError->dwWinError                = dwErrorCode;
    pError->type.eapType.type         = EAPMETHOD_TYPE;
    pError->type.eapType.dwVendorId   = 0;
    pError->type.eapType.dwVendorType = 0;
    pError->type.dwAuthorId           = 67532;
    pError->dwReasonCode              = dwReasonCode;
    pError->rootCauseGuid             = pRootCauseGuid != NULL ? *pRootCauseGuid : GUID_NULL;
    pError->repairGuid                = pRepairGuid    != NULL ? *pRepairGuid    : GUID_NULL;
    pError->helpLinkGuid              = pHelpLinkGuid  != NULL ? *pHelpLinkGuid  : GUID_NULL;
    if (nRootCauseSize) {
        pError->pRootCauseString = (LPWSTR)p;
        memcpy(pError->pRootCauseString, pszRootCauseString, nRootCauseSize);
        p += nRootCauseSize;
    } else
        pError->pRootCauseString = NULL;
    if (nRepairStringSize) {
        pError->pRepairString = (LPWSTR)p;
        memcpy(pError->pRepairString, pszRepairString, nRepairStringSize);
        p += nRepairStringSize;
    } else
        pError->pRepairString = NULL;

    // Write trace event.
    std::vector<EVENT_DATA_DESCRIPTOR> evt_desc;
    evt_desc.reserve(8);
    evt_desc.push_back(winstd::event_data(pError->dwWinError));
    evt_desc.push_back(winstd::event_data(pError->type.eapType.type));
    evt_desc.push_back(winstd::event_data(pError->dwReasonCode));
    evt_desc.push_back(winstd::event_data(&(pError->rootCauseGuid), sizeof(GUID)));
    evt_desc.push_back(winstd::event_data(&(pError->repairGuid), sizeof(GUID)));
    evt_desc.push_back(winstd::event_data(&(pError->helpLinkGuid), sizeof(GUID)));
    evt_desc.push_back(winstd::event_data(pError->pRootCauseString));
    evt_desc.push_back(winstd::event_data(pError->pRepairString));
    m_ep.write(&EAPMETHOD_TRACE_EAP_ERROR, (ULONG)evt_desc.size(), evt_desc.data());

    return pError;
}


void eap::module::free_memory(_In_ void *ptr)
{
    ETW_FN_VOID;

    // Since we do security here and some of the BLOBs contain credentials, sanitize every memory block before freeing.
    SecureZeroMemory(ptr, HeapSize(m_heap, 0, ptr));
    HeapFree(m_heap, 0, ptr);
}


void eap::module::free_error_memory(_In_ EAP_ERROR *err)
{
    ETW_FN_VOID;

    // pRootCauseString and pRepairString always trail the ppEapError to reduce number of (de)allocations.
    HeapFree(m_heap, 0, err);
}


//////////////////////////////////////////////////////////////////////
// eap::peer
//////////////////////////////////////////////////////////////////////

eap::peer::peer() : module()
{
}


DWORD APIENTRY eap::peer::initialize(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD APIENTRY eap::peer::shutdown(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD APIENTRY eap::peer::get_identity(
    _In_                                   DWORD     dwFlags,
    _In_                                   DWORD     dwConnectionDataSize,
    _In_count_(dwConnectionDataSize) const BYTE      *pConnectionData,
    _In_                                   DWORD     dwUserDataSize,
    _In_count_(dwUserDataSize)       const BYTE      *pUserData,
    _In_                                   HANDLE    hTokenImpersonateUser,
    _Out_                                  BOOL      *pfInvokeUI,
    _Out_                                  DWORD     *pdwUserDataOutSize,
    _Out_                                  BYTE      **ppUserDataOut,
    _Out_                                  WCHAR     **ppwszIdentity,
    _Out_                                  EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwConnectionDataSize);
    UNREFERENCED_PARAMETER(pConnectionData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(hTokenImpersonateUser);
    UNREFERENCED_PARAMETER(pfInvokeUI);
    UNREFERENCED_PARAMETER(pdwUserDataOutSize);
    UNREFERENCED_PARAMETER(ppUserDataOut);
    UNREFERENCED_PARAMETER(ppwszIdentity);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::config_xml_to_blob(
    _In_  DWORD            dwFlags,
    _In_  IXMLDOMDocument2 *pConfigDoc,
    _Out_ BYTE             **ppConfigOut,
    _Out_ DWORD            *pdwConfigOutSize,
    _Out_ EAP_ERROR        **ppEapError) const
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(pConfigDoc);
    UNREFERENCED_PARAMETER(ppConfigOut);
    UNREFERENCED_PARAMETER(pdwConfigOutSize);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::config_blob_to_xml(
    _In_                             DWORD            dwFlags,
    _In_count_(dwConfigInSize) const BYTE             *pConfigIn,
    _In_                             DWORD            dwConfigInSize,
    _Out_                            IXMLDOMDocument2 **ppConfigDoc,
    _Out_                            EAP_ERROR        **ppEapError) const
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(pConfigIn);
    UNREFERENCED_PARAMETER(dwConfigInSize);
    UNREFERENCED_PARAMETER(ppConfigDoc);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::get_method_properties(
    _In_                                DWORD                     dwVersion,
    _In_                                DWORD                     dwFlags,
    _In_                                HANDLE                    hUserImpersonationToken,
    _In_                                DWORD                     dwEapConnDataSize,
    _In_count_(dwEapConnDataSize) const BYTE                      *pEapConnData,
    _In_                                DWORD                     dwUserDataSize,
    _In_count_(dwUserDataSize)    const BYTE                      *pUserData,
    _Out_                               EAP_METHOD_PROPERTY_ARRAY *pMethodPropertyArray,
    _Out_                               EAP_ERROR                 **ppEapError) const
{
    UNREFERENCED_PARAMETER(dwVersion);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(hUserImpersonationToken);
    UNREFERENCED_PARAMETER(dwEapConnDataSize);
    UNREFERENCED_PARAMETER(pEapConnData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(pMethodPropertyArray);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::credentials_xml_to_blob(
    _In_                             DWORD            dwFlags,
    _In_                             IXMLDOMDocument2 *pCredentialsDoc,
    _In_count_(dwConfigInSize) const BYTE             *pConfigIn,
    _In_                             DWORD            dwConfigInSize,
    _Out_                            BYTE             **ppCredentialsOut,
    _Out_                            DWORD            *pdwCredentialsOutSize,
    _Out_                            EAP_ERROR        **ppEapError) const
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(pCredentialsDoc);
    UNREFERENCED_PARAMETER(pConfigIn);
    UNREFERENCED_PARAMETER(dwConfigInSize);
    UNREFERENCED_PARAMETER(ppCredentialsOut);
    UNREFERENCED_PARAMETER(pdwCredentialsOutSize);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::query_credential_input_fields(
    _In_                                HANDLE                       hUserImpersonationToken,
    _In_                                DWORD                        dwFlags,
    _In_                                DWORD                        dwEapConnDataSize,
    _In_count_(dwEapConnDataSize) const BYTE                         *pEapConnData,
    _Out_                               EAP_CONFIG_INPUT_FIELD_ARRAY *pEapConfigInputFieldsArray,
    _Out_                               EAP_ERROR                    **ppEapError) const
{
    UNREFERENCED_PARAMETER(hUserImpersonationToken);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwEapConnDataSize);
    UNREFERENCED_PARAMETER(pEapConnData);
    UNREFERENCED_PARAMETER(pEapConfigInputFieldsArray);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer::query_user_blob_from_credential_input_fields(
    _In_                                HANDLE                       hUserImpersonationToken,
    _In_                                DWORD                        dwFlags,
    _In_                                DWORD                        dwEapConnDataSize,
    _In_count_(dwEapConnDataSize) const BYTE                         *pEapConnData,
    _In_                          const EAP_CONFIG_INPUT_FIELD_ARRAY *pEapConfigInputFieldArray,
    _Inout_                             DWORD                        *pdwUsersBlobSize,
    _Inout_                             BYTE                         **ppUserBlob,
    _Out_                               EAP_ERROR                    **ppEapError) const
{
    UNREFERENCED_PARAMETER(hUserImpersonationToken);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwEapConnDataSize);
    UNREFERENCED_PARAMETER(pEapConnData);
    UNREFERENCED_PARAMETER(pEapConfigInputFieldArray);
    UNREFERENCED_PARAMETER(pdwUsersBlobSize);
    UNREFERENCED_PARAMETER(ppUserBlob);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


///
/// Defines the implementation of an EAP method API that provides the input fields for interactive UI components to be raised on the supplicant.
///
/// \sa [EapPeerQueryInteractiveUIInputFields function](https://msdn.microsoft.com/en-us/library/windows/desktop/bb204695.aspx)
///
DWORD eap::peer::query_interactive_ui_input_fields(
    _In_                                  DWORD                   dwVersion,
    _In_                                  DWORD                   dwFlags,
    _In_                                  DWORD                   dwUIContextDataSize,
    _In_count_(dwUIContextDataSize) const BYTE                    *pUIContextData,
    _Out_                                 EAP_INTERACTIVE_UI_DATA *pEapInteractiveUIData,
    _Out_                                 EAP_ERROR               **ppEapError,
    _Inout_                               LPVOID                  *pvReserved) const
{
    UNREFERENCED_PARAMETER(dwVersion);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwUIContextDataSize);
    UNREFERENCED_PARAMETER(pUIContextData);
    UNREFERENCED_PARAMETER(pEapInteractiveUIData);
    UNREFERENCED_PARAMETER(ppEapError);
    UNREFERENCED_PARAMETER(pvReserved);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


///
/// Converts user information into a user BLOB that can be consumed by EAPHost run-time functions.
///
/// \sa [EapPeerQueryUIBlobFromInteractiveUIInputFields function](https://msdn.microsoft.com/en-us/library/windows/desktop/bb204696.aspx)
///
DWORD eap::peer::query_ui_blob_from_interactive_ui_input_fields(
    _In_                                  DWORD                   dwVersion,
    _In_                                  DWORD                   dwFlags,
    _In_                                  DWORD                   dwUIContextDataSize,
    _In_count_(dwUIContextDataSize) const BYTE                    *pUIContextData,
    _In_                            const EAP_INTERACTIVE_UI_DATA *pEapInteractiveUIData,
    _Out_                                 DWORD                   *pdwDataFromInteractiveUISize,
    _Out_                                 BYTE                    **ppDataFromInteractiveUI,
    _Out_                                 EAP_ERROR               **ppEapError,
    _Inout_                               LPVOID                  *ppvReserved) const
{
    UNREFERENCED_PARAMETER(dwVersion);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwUIContextDataSize);
    UNREFERENCED_PARAMETER(pUIContextData);
    UNREFERENCED_PARAMETER(pEapInteractiveUIData);
    UNREFERENCED_PARAMETER(pdwDataFromInteractiveUISize);
    UNREFERENCED_PARAMETER(ppDataFromInteractiveUI);
    UNREFERENCED_PARAMETER(ppEapError);
    UNREFERENCED_PARAMETER(ppvReserved);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


//////////////////////////////////////////////////////////////////////
// eap::peer_ui
//////////////////////////////////////////////////////////////////////

eap::peer_ui::peer_ui() : module()
{
}
