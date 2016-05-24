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

using namespace std;
using namespace winstd;


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
// eap::config
//////////////////////////////////////////////////////////////////////

eap::config::config(_In_ module &mod) :
    m_module(mod)
{
}


eap::config::~config()
{
}


DWORD eap::config::save(_In_ IXMLDOMDocument2 *pDoc, _Inout_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    UNREFERENCED_PARAMETER(pDoc);
    UNREFERENCED_PARAMETER(pConfigRoot);
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD eap::config::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pConfigRoot);
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


//////////////////////////////////////////////////////////////////////
// eap::config_pass
//////////////////////////////////////////////////////////////////////

eap::config_pass::config_pass(_In_ module &mod) : config(mod)
{
}


DWORD eap::config_pass::save(_In_ IXMLDOMDocument2 *pDoc, _Inout_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    const variant varNodeTypeEl(NODE_ELEMENT);
    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    DWORD dwResult;
    HRESULT hr;

    // <Realm>
    if (!m_realm.empty())
        if ((dwResult = eapxml::put_element_value(pDoc, pConfigRoot, bstr(L"Realm"), bstrNamespace, bstr(m_realm.c_str()))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <Realm> element."), NULL);
            return dwResult;
        }

    // <ProviderInfo>
    com_obj<IXMLDOMNode> pXmlElProviderInfo;
    if (FAILED(hr = pDoc->createNode(varNodeTypeEl, bstr(L"ProviderInfo"), bstrNamespace, &pXmlElProviderInfo))) {
        *ppEapError = m_module.make_error(dwResult = HRESULT_CODE(hr), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <ProviderInfo> element."), NULL);
        return dwResult;
    }

    // <ProviderInfo>/<CredentialPrompt>
    if (!m_lbl_alt_credential.empty())
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElProviderInfo, bstr(L"CredentialPrompt"), bstrNamespace, bstr(m_lbl_alt_credential.c_str()))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <CredentialPrompt> element."), NULL);
            return dwResult;
        }

    // <ProviderInfo>/<UserNameLabel>
    if (!m_lbl_alt_identity.empty())
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElProviderInfo, bstr(L"UserNameLabel"), bstrNamespace, bstr(m_lbl_alt_identity.c_str()))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <UserNameLabel> element."), NULL);
            return dwResult;
        }

    // <ProviderInfo>/<PasswordLabel>
    if (!m_lbl_alt_password.empty())
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElProviderInfo, bstr(L"PasswordLabel"), bstrNamespace, bstr(m_lbl_alt_password.c_str()))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <PasswordLabel> element."), NULL);
            return dwResult;
        }

    if (FAILED(hr = pConfigRoot->appendChild(pXmlElProviderInfo, NULL))) {
        *ppEapError = m_module.make_error(dwResult = HRESULT_CODE(hr), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error appending <ProviderInfo> element."), NULL);
        return dwResult;
    }

    return config::save(pDoc, pConfigRoot, ppEapError);
}


DWORD eap::config_pass::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    wstring lang;
    LoadString(g_hResource, 2, lang);

    // <Realm>
    if (eapxml::get_element_value(pConfigRoot, bstr(L"eap-metadata:Realm"), m_realm) != ERROR_SUCCESS)
        m_realm.clear();

    m_lbl_alt_credential.clear();
    m_lbl_alt_identity.clear();
    m_lbl_alt_password.clear();

    // <ProviderInfo>
    com_obj<IXMLDOMElement> pXmlElProviderInfo;
    if (eapxml::select_element(pConfigRoot, bstr(L"eap-metadata:ProviderInfo"), &pXmlElProviderInfo) == ERROR_SUCCESS) {
        // <CredentialPrompt>
        eapxml::get_element_localized(pXmlElProviderInfo, bstr(L"eap-metadata:CredentialPrompt"), lang.c_str(), m_lbl_alt_credential);

        // <UserNameLabel>
        eapxml::get_element_localized(pXmlElProviderInfo, bstr(L"eap-metadata:UserNameLabel"), lang.c_str(), m_lbl_alt_identity);

        // <PasswordLabel>
        eapxml::get_element_localized(pXmlElProviderInfo, bstr(L"eap-metadata:PasswordLabel"), lang.c_str(), m_lbl_alt_password);
    }

    return config::load(pConfigRoot, ppEapError);
}


//////////////////////////////////////////////////////////////////////
// eap::config_tls
//////////////////////////////////////////////////////////////////////

eap::config_tls::config_tls(_In_ module &mod) : config(mod)
{
}


DWORD eap::config_tls::save(_In_ IXMLDOMDocument2 *pDoc, _Inout_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    const variant varNodeTypeEl(NODE_ELEMENT);
    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    DWORD dwResult;
    HRESULT hr;

    for (list<cert_context>::const_iterator i = m_trusted_root_ca.begin(), i_end = m_trusted_root_ca.end(); i != i_end; ++i) {
        // <CA>
        com_obj<IXMLDOMNode> pXmlElCA;
        if (FAILED(hr = pDoc->createNode(varNodeTypeEl, bstr(L"CA"), bstrNamespace, &pXmlElCA))) {
            *ppEapError = m_module.make_error(dwResult = HRESULT_CODE(hr), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <CA> element."), NULL);
            return dwResult;
        }

        // <CA>/<format>
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElCA, bstr(L"format"), bstrNamespace, bstr(L"PEM"))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <format> element."), NULL);
            return dwResult;
        }

        // <CA>/<cert-data>
        const cert_context &cc = *i;
        if ((dwResult = eapxml::put_element_base64(pDoc, pXmlElCA, bstr(L"cert-data"), bstrNamespace, cc->pbCertEncoded, cc->cbCertEncoded)) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <cert-data> element."), NULL);
            return dwResult;
        }

        if (FAILED(hr = pConfigRoot->appendChild(pXmlElCA, NULL))) {
            *ppEapError = m_module.make_error(dwResult = HRESULT_CODE(hr), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error appending <CA> element."), NULL);
            return dwResult;
        }
    }

    // <ServerName>
    for (list<string>::const_iterator i = m_server_names.begin(), i_end = m_server_names.end(); i != i_end; ++i) {
        wstring str;
        MultiByteToWideChar(CP_UTF8, 0, i->c_str(), (int)i->length(), str);
        if ((dwResult = eapxml::put_element_value(pDoc, pConfigRoot, bstr(L"ServerName"), bstrNamespace, bstr(str.c_str()))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <ServerName> element."), NULL);
            return dwResult;
        }
    }

    return config::save(pDoc, pConfigRoot, ppEapError);
}


DWORD eap::config_tls::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    // Iterate and load trusted CAs (<CA>).
    m_trusted_root_ca.clear();
    com_obj<IXMLDOMNodeList> pXmlListCAs;
    long lCACount = 0;
    if (eapxml::select_nodes(pConfigRoot, bstr(L"eap-metadata:CA"), &pXmlListCAs) == ERROR_SUCCESS && SUCCEEDED(pXmlListCAs->get_length(&lCACount))) {
        for (long j = 0; j < lCACount; j++) {
            // Load CA certificate.
            com_obj<IXMLDOMNode> pXmlElCA;
            pXmlListCAs->get_item(j, &pXmlElCA);
            bstr bstrFormat;
            if (eapxml::get_element_value(pXmlElCA, bstr(L"eap-metadata:format"), &bstrFormat) == ERROR_SUCCESS) {
                if (CompareStringEx(LOCALE_NAME_INVARIANT, NORM_IGNORECASE, bstrFormat, bstrFormat.length(), L"PEM", -1, NULL, NULL, 0) == CSTR_EQUAL) {
                    vector<unsigned char> aData;
                    if (eapxml::get_element_base64(pXmlElCA, bstr(L"eap-metadata:cert-data"), aData) == ERROR_SUCCESS)
                        add_trusted_ca(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, aData.data(), (DWORD)aData.size());
                }
            }
        }
    }

    // Iterate and load acceptable server names (<ServerName>).
    m_server_names.clear();
    com_obj<IXMLDOMNodeList> pXmlListServerIDs;
    long lServerIDCount = 0;
    if (eapxml::select_nodes(pConfigRoot, bstr(L"eap-metadata:ServerName"), &pXmlListServerIDs) == ERROR_SUCCESS && SUCCEEDED(pXmlListServerIDs->get_length(&lServerIDCount))) {
        for (long j = 0; j < lServerIDCount; j++) {
            // Load server name (<ServerName>).
            com_obj<IXMLDOMNode> pXmlElServerID;
            pXmlListServerIDs->get_item(j, &pXmlElServerID);
            bstr bstrServerID;
            pXmlElServerID->get_text(&bstrServerID);

            // Server names (FQDNs) are always ASCII. Hopefully. Convert them to UTF-8 anyway for consistent comparison. CP_ANSI varies.
            string str;
            WideCharToMultiByte(CP_UTF8, 0, bstrServerID, bstrServerID.length(), str, NULL, NULL);

            m_server_names.push_back(str);
        }
    }

    return config::load(pConfigRoot, ppEapError);
}


bool eap::config_tls::add_trusted_ca(_In_  DWORD dwCertEncodingType, _In_  const BYTE *pbCertEncoded, _In_  DWORD cbCertEncoded)
{
    cert_context cert;
    if (!cert.create(dwCertEncodingType, pbCertEncoded, cbCertEncoded)) {
        // Invalid or unsupported certificate.
        return false;
    }

    for (list<cert_context>::const_iterator i = m_trusted_root_ca.cbegin(), i_end = m_trusted_root_ca.cend();; ++i) {
        if (i != i_end) {
            if (*i == cert) {
                // This certificate is already on the list.
                return false;
            }
        } else {
            // End of list reached. Append certificate.
            m_trusted_root_ca.push_back(cert);
            return true;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// eap::module
//////////////////////////////////////////////////////////////////////

eap::module::module()
{
    m_ep.create(&EAPMETHOD_TRACE_EVENT_PROVIDER);
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_LOAD, event_data((BYTE)EAPMETHOD_TYPE), event_data::blank);

    m_heap.create(0, 0, 0);
}


eap::module::~module()
{
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_UNLOAD, event_data((BYTE)EAPMETHOD_TYPE), event_data::blank);
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
    vector<EVENT_DATA_DESCRIPTOR> evt_desc;
    evt_desc.reserve(8);
    evt_desc.push_back(event_data(pError->dwWinError));
    evt_desc.push_back(event_data(pError->type.eapType.type));
    evt_desc.push_back(event_data(pError->dwReasonCode));
    evt_desc.push_back(event_data(&(pError->rootCauseGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(&(pError->repairGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(&(pError->helpLinkGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(pError->pRootCauseString));
    evt_desc.push_back(event_data(pError->pRepairString));
    m_ep.write(&EAPMETHOD_TRACE_EAP_ERROR, (ULONG)evt_desc.size(), evt_desc.data());

    return pError;
}


BYTE* eap::module::alloc_memory(_In_ size_t size)
{
    return (BYTE*)HeapAlloc(m_heap, 0, size);
}


void eap::module::free_memory(_In_ BYTE *ptr)
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


DWORD eap::peer::initialize(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD eap::peer::shutdown(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD eap::peer::get_identity(
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
