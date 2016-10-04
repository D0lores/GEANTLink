﻿/*
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

#include "StdAfx.h"

using namespace std;
using namespace winstd;


//////////////////////////////////////////////////////////////////////
// eap::credentials_tls
//////////////////////////////////////////////////////////////////////

eap::credentials_tls::credentials_tls(_In_ module &mod) : credentials(mod)
{
}


eap::credentials_tls::credentials_tls(_In_ const credentials_tls &other) :
    m_cert(other.m_cert),
    credentials(other)
{
}


eap::credentials_tls::credentials_tls(_Inout_ credentials_tls &&other) :
    m_cert(std::move(other.m_cert)),
    credentials(std::move(other))
{
}


eap::credentials_tls& eap::credentials_tls::operator=(_In_ const credentials_tls &other)
{
    if (this != &other) {
        (credentials&)*this = other;
        m_cert              = other.m_cert;
    }

    return *this;
}


eap::credentials_tls& eap::credentials_tls::operator=(_Inout_ credentials_tls &&other)
{
    if (this != &other) {
        (credentials&)*this = std::move(other);
        m_cert              = std::move(other.m_cert);
    }

    return *this;
}


eap::config* eap::credentials_tls::clone() const
{
    return new credentials_tls(*this);
}


void eap::credentials_tls::clear()
{
    credentials::clear();
    m_cert.free();
}


bool eap::credentials_tls::empty() const
{
    return !m_cert;
}


void eap::credentials_tls::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot) const
{
    assert(pDoc);
    assert(pConfigRoot);

    credentials::save(pDoc, pConfigRoot);

    HRESULT hr;

    // <ClientCertificate>
    com_obj<IXMLDOMElement> pXmlElClientCertificate;
    if (FAILED(hr = eapxml::create_element(pDoc, pConfigRoot, bstr(L"eap-metadata:ClientCertificate"), bstr(L"ClientCertificate"), namespace_eapmetadata, pXmlElClientCertificate)))
        throw com_runtime_error(hr, __FUNCTION__ " Error creating <ClientCertificate> element.");

    if (m_cert) {
        // <ClientCertificate>/<format>
        if (FAILED(hr = eapxml::put_element_value(pDoc, pXmlElClientCertificate, bstr(L"format"), namespace_eapmetadata, bstr(L"PEM"))))
            throw com_runtime_error(hr, __FUNCTION__ " Error creating <format> element.");

        // <ClientCertificate>/<cert-data>
        if (FAILED(hr = eapxml::put_element_base64(pDoc, pXmlElClientCertificate, bstr(L"cert-data"), namespace_eapmetadata, m_cert->pbCertEncoded, m_cert->cbCertEncoded)))
            throw com_runtime_error(hr, __FUNCTION__ " Error creating <cert-data> element.");
    }
}


void eap::credentials_tls::load(_In_ IXMLDOMNode *pConfigRoot)
{
    assert(pConfigRoot);
    HRESULT hr;

    credentials::load(pConfigRoot);

    std::wstring xpath(eapxml::get_xpath(pConfigRoot));

    m_cert.free();

    // <ClientCertificate>
    com_obj<IXMLDOMElement> pXmlElClientCertificate;
    if (FAILED(hr = eapxml::select_element(pConfigRoot, bstr(L"eap-metadata:ClientCertificate"), pXmlElClientCertificate)))
        throw com_runtime_error(hr, __FUNCTION__ " Error reading <ClientCertificate> element.");

    // <ClientCertificate>/<format>
    bstr bstrFormat;
    if (SUCCEEDED(eapxml::get_element_value(pXmlElClientCertificate, bstr(L"eap-metadata:format"), bstrFormat))) {
        if (CompareStringEx(LOCALE_NAME_INVARIANT, NORM_IGNORECASE, bstrFormat, bstrFormat.length(), L"PEM", -1, NULL, NULL, 0) == CSTR_EQUAL) {
            // <ClientCertificate>/<cert-data>
            vector<unsigned char> aData;
            if (SUCCEEDED(eapxml::get_element_base64(pXmlElClientCertificate, bstr(L"eap-metadata:cert-data"), aData)))
                m_cert.create(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, aData.data(), (DWORD)aData.size());
        }
    }
    m_module.log_config((xpath + L"/ClientCertificate").c_str(), get_name().c_str());
}


void eap::credentials_tls::operator<<(_Inout_ cursor_out &cursor) const
{
    credentials::operator<<(cursor);
    cursor << m_cert;
}


size_t eap::credentials_tls::get_pk_size() const
{
    return
        credentials::get_pk_size() +
        pksizeof(m_cert);
}


void eap::credentials_tls::operator>>(_Inout_ cursor_in &cursor)
{
    credentials::operator>>(cursor);
    cursor >> m_cert;
}


void eap::credentials_tls::store(_In_z_ LPCTSTR pszTargetName, _In_ unsigned int level) const
{
    assert(pszTargetName);

    data_blob cred_enc;
    if (m_cert) {
        // Encrypt the certificate using user's key.
        DATA_BLOB cred_blob    = { m_cert->cbCertEncoded, m_cert->pbCertEncoded         };
        DATA_BLOB entropy_blob = { sizeof(s_entropy)    , const_cast<LPBYTE>(s_entropy) };
        if (!CryptProtectData(&cred_blob, NULL, &entropy_blob, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &cred_enc))
            throw win_runtime_error(__FUNCTION__ " CryptProtectData failed.");
    }

    tstring target(target_name(pszTargetName, level));

    // Write credentials.
    assert(cred_enc.cbData     < CRED_MAX_CREDENTIAL_BLOB_SIZE);
    assert(m_identity.length() < CRED_MAX_USERNAME_LENGTH     );
    CREDENTIAL cred = {
        0,                                     // Flags
        CRED_TYPE_GENERIC,                     // Type
        const_cast<LPTSTR>(target.c_str()),    // TargetName
        _T(""),                                // Comment
        { 0, 0 },                              // LastWritten
        cred_enc.cbData,                       // CredentialBlobSize
        cred_enc.pbData,                       // CredentialBlob
        CRED_PERSIST_ENTERPRISE,               // Persist
        0,                                     // AttributeCount
        NULL,                                  // Attributes
        NULL,                                  // TargetAlias
        const_cast<LPTSTR>(m_identity.c_str()) // UserName
    };
    if (!CredWrite(&cred, 0))
        throw win_runtime_error(__FUNCTION__ " CredWrite failed.");
}


void eap::credentials_tls::retrieve(_In_z_ LPCTSTR pszTargetName, _In_ unsigned int level)
{
    assert(pszTargetName);

    // Read credentials.
    unique_ptr<CREDENTIAL, CredFree_delete<CREDENTIAL> > cred;
    if (!CredRead(target_name(pszTargetName, level).c_str(), CRED_TYPE_GENERIC, 0, (PCREDENTIAL*)&cred))
        throw win_runtime_error(__FUNCTION__ " CredRead failed.");

    if (cred->CredentialBlobSize) {
        // Decrypt the certificate using user's key.
        DATA_BLOB cred_enc     = { cred->CredentialBlobSize, cred->CredentialBlob          };
        DATA_BLOB entropy_blob = { sizeof(s_entropy)       , const_cast<LPBYTE>(s_entropy) };
        data_blob cred_int;
        if (!CryptUnprotectData(&cred_enc, NULL, &entropy_blob, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN | CRYPTPROTECT_VERIFY_PROTECTION, &cred_int))
            throw win_runtime_error(__FUNCTION__ " CryptUnprotectData failed.");

        bool bResult = m_cert.create(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, cred_int.pbData, cred_int.cbData);
        SecureZeroMemory(cred_int.pbData, cred_int.cbData);
        if (!bResult)
            throw win_runtime_error(__FUNCTION__ " Error loading certificate.");
    } else
        m_cert.free();

    if (cred->UserName)
        m_identity = cred->UserName;
    else
        m_identity.clear();

    wstring xpath(pszTargetName);
    m_module.log_config((xpath + L"/Identity").c_str(), m_identity.c_str());
    m_module.log_config((xpath + L"/Certificate").c_str(), get_name().c_str());
}


LPCTSTR eap::credentials_tls::target_suffix() const
{
    return _T("Cert");
}


std::wstring eap::credentials_tls::get_identity() const
{
    if (!m_identity.empty()) {
        return m_identity;
    } else if (m_cert) {
        for (DWORD idx_ext = 0; idx_ext < m_cert->pCertInfo->cExtension; idx_ext++) {
            unique_ptr<CERT_ALT_NAME_INFO, LocalFree_delete<CERT_ALT_NAME_INFO> > san_info;
            if (strcmp(m_cert->pCertInfo->rgExtension[idx_ext].pszObjId, szOID_SUBJECT_ALT_NAME2) == 0) {
                unsigned char *output = NULL;
                DWORD size_output;
                if (!CryptDecodeObjectEx(
                        X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                        szOID_SUBJECT_ALT_NAME2,
                        m_cert->pCertInfo->rgExtension[idx_ext].Value.pbData, m_cert->pCertInfo->rgExtension[idx_ext].Value.cbData,
                        CRYPT_DECODE_ALLOC_FLAG | CRYPT_DECODE_ENABLE_PUNYCODE_FLAG,
                        NULL,
                        &output, &size_output))
                    throw win_runtime_error(__FUNCTION__ " Error decoding subjectAltName2 certificate extension.");
                san_info.reset((CERT_ALT_NAME_INFO*)output);
            } else if (strcmp(m_cert->pCertInfo->rgExtension[idx_ext].pszObjId, szOID_SUBJECT_ALT_NAME) == 0) {
                unsigned char *output = NULL;
                DWORD size_output;
                if (!CryptDecodeObjectEx(
                        X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                        szOID_SUBJECT_ALT_NAME,
                        m_cert->pCertInfo->rgExtension[idx_ext].Value.pbData, m_cert->pCertInfo->rgExtension[idx_ext].Value.cbData,
                        CRYPT_DECODE_ALLOC_FLAG | CRYPT_DECODE_ENABLE_PUNYCODE_FLAG,
                        NULL,
                        &output, &size_output))
                    throw win_runtime_error(__FUNCTION__ " Error decoding subjectAltName certificate extension.");
                san_info.reset((CERT_ALT_NAME_INFO*)output);
            } else {
                // Skip this extension.
                continue;
            }

            for (DWORD idx_entry = 0; idx_entry < san_info->cAltEntry; idx_entry++) {
                if (san_info->rgAltEntry[idx_entry].dwAltNameChoice == CERT_ALT_NAME_RFC822_NAME)
                    return san_info->rgAltEntry[idx_entry].pwszRfc822Name;
            }
        }
    }

    return L"";
}


eap::credentials::source_t eap::credentials_tls::combine(
    _In_opt_   const credentials   *cred_cached,
    _In_       const config_method &cfg,
    _In_opt_z_       LPCTSTR       pszTargetName)
{
    if (cred_cached) {
        // Using EAP service cached credentials.
        *this = *dynamic_cast<const credentials_tls*>(cred_cached);
        m_module.log_event(&EAPMETHOD_TRACE_EVT_CRED_CACHED2, event_data((unsigned int)eap_type_tls), event_data(credentials_tls::get_name()), event_data(pszTargetName), event_data::blank);
        return source_cache;
    }

    auto const *cfg_with_cred = dynamic_cast<const config_method_with_cred*>(&cfg);
    if (cfg_with_cred->m_use_cred) {
        // Using configured credentials.
        *this = *dynamic_cast<const credentials_tls*>(cfg_with_cred->m_cred.get());
        m_module.log_event(&EAPMETHOD_TRACE_EVT_CRED_CONFIG2, event_data((unsigned int)eap_type_tls), event_data(credentials_tls::get_name()), event_data(pszTargetName), event_data::blank);
        return source_config;
    }

    if (pszTargetName) {
        try {
            credentials_tls cred_loaded(m_module);
            cred_loaded.retrieve(pszTargetName, cfg.m_level);

            // Using stored credentials.
            *this = std::move(cred_loaded);
            m_module.log_event(&EAPMETHOD_TRACE_EVT_CRED_STORED2, event_data((unsigned int)eap_type_tls), event_data(credentials_tls::get_name()), event_data(pszTargetName), event_data::blank);
            return source_storage;
        } catch (...) {
            // Not actually an error.
        }
    }

    return source_unknown;
}


const unsigned char eap::credentials_tls::s_entropy[1024] = {
    0xb9, 0xd1, 0x62, 0xd4, 0x1c, 0xe6, 0x8c, 0x25, 0x98, 0x9b, 0x1d, 0xbc, 0x40, 0x46, 0x9e, 0x6d,
    0x63, 0xba, 0xda, 0x78, 0x65, 0x56, 0x97, 0x4f, 0xa0, 0x89, 0xf4, 0xc5, 0x1b, 0xf5, 0x8d, 0x69,
    0xa1, 0x8c, 0xf3, 0xf9, 0x91, 0x86, 0x7f, 0xf3, 0x47, 0x2e, 0x23, 0x61, 0xde, 0x4f, 0x61, 0x94,
    0xba, 0xba, 0x27, 0x63, 0x0b, 0xf0, 0x4e, 0xa0, 0x24, 0xab, 0x17, 0x62, 0x3f, 0xc4, 0xd8, 0xad,
    0xd6, 0x03, 0x1f, 0x3b, 0xdd, 0x88, 0xf7, 0x9a, 0x56, 0xf4, 0x0d, 0xce, 0x9b, 0x18, 0x33, 0x54,
    0x5a, 0x1a, 0x3b, 0x91, 0x70, 0xf5, 0x95, 0x1c, 0x39, 0xe8, 0x42, 0x6c, 0x6e, 0xe6, 0x4d, 0xb8,
    0x1c, 0xa6, 0xce, 0xad, 0xcd, 0x9e, 0x55, 0x88, 0x90, 0xff, 0x5e, 0x81, 0xdf, 0x08, 0x68, 0x54,
    0xa1, 0x60, 0xfb, 0x41, 0x8a, 0xc1, 0xf2, 0xf0, 0xc4, 0x0e, 0xb9, 0xd1, 0x61, 0xa5, 0xc4, 0x02,
    0xd9, 0x43, 0xbb, 0x16, 0x9f, 0x9a, 0xc3, 0xe0, 0x61, 0xf8, 0x57, 0x16, 0xb1, 0x7f, 0x00, 0x53,
    0xf6, 0x8b, 0x97, 0x8f, 0xec, 0x3f, 0x72, 0x32, 0x0c, 0x0a, 0x80, 0x00, 0x4f, 0x87, 0x36, 0x2e,
    0x24, 0x1d, 0xb4, 0xe5, 0x6c, 0x41, 0x34, 0xe9, 0x75, 0x4c, 0xf2, 0xdb, 0x16, 0xb5, 0x9a, 0x54,
    0x40, 0xe9, 0x1f, 0xc0, 0xf1, 0xc5, 0x0d, 0x5d, 0xa7, 0xb5, 0x51, 0x15, 0x05, 0x95, 0xe2, 0x46,
    0x9d, 0xc7, 0x74, 0xd7, 0xab, 0x93, 0xce, 0x7d, 0xf9, 0x61, 0x9d, 0x2b, 0xe7, 0x45, 0x61, 0x0b,
    0xcc, 0x18, 0xf1, 0xf4, 0x00, 0xb9, 0x78, 0x23, 0x45, 0x8a, 0xd6, 0x1d, 0x95, 0x6b, 0x99, 0xe0,
    0x21, 0x6b, 0x98, 0x91, 0xcb, 0x0e, 0x50, 0x9a, 0x2e, 0x64, 0xa2, 0xe9, 0x1b, 0x1f, 0x6e, 0x69,
    0x78, 0x1d, 0xd1, 0xa1, 0xe5, 0x95, 0x34, 0x78, 0xf2, 0x8b, 0xe6, 0x38, 0x74, 0xd6, 0x48, 0x69,
    0x62, 0xf6, 0xd3, 0x18, 0x1c, 0xb1, 0x0e, 0xc0, 0xdf, 0xff, 0x2e, 0xd3, 0xbc, 0x4e, 0xae, 0xd7,
    0xe0, 0xb8, 0x47, 0x15, 0xcc, 0x10, 0xc3, 0x3a, 0x3d, 0x67, 0x79, 0x33, 0x1d, 0xb1, 0x73, 0xdf,
    0xfb, 0xb2, 0x89, 0xbb, 0x04, 0x76, 0xec, 0x4a, 0x73, 0x73, 0xa8, 0x07, 0xb7, 0xb0, 0xbe, 0x15,
    0xac, 0xc3, 0x32, 0x1e, 0x70, 0xc2, 0x0e, 0x8c, 0x29, 0x2e, 0x2d, 0xfc, 0x36, 0x1f, 0x9d, 0x90,
    0x86, 0x1b, 0x12, 0xca, 0x82, 0x4d, 0xea, 0x9e, 0xb4, 0x5e, 0xb0, 0x33, 0xc4, 0x19, 0x25, 0x3f,
    0x27, 0x11, 0x5a, 0x79, 0x91, 0x44, 0x2c, 0x50, 0x56, 0xe0, 0xd2, 0xb3, 0x81, 0x17, 0x3f, 0x06,
    0x57, 0x39, 0x18, 0x2c, 0xd4, 0x1e, 0xf3, 0x90, 0x7e, 0xc3, 0x08, 0x50, 0x89, 0x7a, 0xf7, 0x7f,
    0xe9, 0xf1, 0x2d, 0x73, 0x95, 0xd9, 0x2e, 0x83, 0xc8, 0x93, 0x33, 0xd9, 0x00, 0xc3, 0xa0, 0x43,
    0x32, 0x57, 0x7b, 0xa9, 0xbf, 0x55, 0xfc, 0x35, 0xfb, 0x85, 0x08, 0x1c, 0x84, 0xa7, 0xce, 0xb0,
    0x8b, 0xab, 0x56, 0xfa, 0x70, 0x9c, 0xd5, 0x8f, 0x21, 0xf6, 0x8f, 0x5e, 0xd5, 0x1b, 0x81, 0x17,
    0xf7, 0x82, 0xb2, 0x28, 0xde, 0xc5, 0xc1, 0xba, 0xe7, 0xfa, 0x21, 0x06, 0xff, 0xf3, 0x27, 0xf8,
    0x3a, 0x7d, 0xbc, 0x96, 0x5e, 0xdf, 0xf4, 0x89, 0x9f, 0x1c, 0x40, 0x03, 0x1a, 0xd2, 0x53, 0xb9,
    0xe4, 0xeb, 0x16, 0xbf, 0xaa, 0xe3, 0xdf, 0x5d, 0x2a, 0xef, 0x16, 0x6f, 0x5d, 0x2b, 0x75, 0x4c,
    0x0e, 0xe0, 0xda, 0xc4, 0xd7, 0x05, 0x52, 0x28, 0x25, 0xc4, 0x3f, 0xe0, 0x55, 0x07, 0x93, 0x21,
    0x80, 0x2b, 0x49, 0x0c, 0x00, 0xd7, 0x13, 0xb3, 0xe0, 0x29, 0x93, 0x66, 0x0a, 0x4b, 0x88, 0x63,
    0xac, 0x14, 0x5f, 0x9b, 0x1c, 0xf4, 0xe3, 0xe7, 0xeb, 0xac, 0x2d, 0xe3, 0x08, 0x7d, 0xcf, 0xce,
    0x12, 0xf0, 0xcd, 0x68, 0x6e, 0xe2, 0x06, 0x16, 0x38, 0x17, 0x93, 0xbc, 0xf9, 0xfe, 0x8e, 0xb2,
    0x14, 0x99, 0x76, 0x82, 0xf7, 0xc2, 0x93, 0x46, 0x95, 0xd7, 0x81, 0x03, 0x16, 0xae, 0xfc, 0x39,
    0xb0, 0x26, 0xd1, 0x74, 0x73, 0x82, 0x21, 0xdb, 0x74, 0x48, 0xd7, 0xc2, 0xae, 0x73, 0x2d, 0x81,
    0x84, 0x61, 0x6d, 0x1d, 0x8a, 0xb4, 0x9d, 0xb3, 0x2a, 0xa7, 0x9b, 0x08, 0x89, 0x2a, 0x96, 0x98,
    0xc1, 0x64, 0xf2, 0x10, 0x8b, 0x8d, 0xaa, 0xbe, 0x0d, 0x37, 0xaa, 0x42, 0x94, 0x9f, 0xae, 0x18,
    0x64, 0xcd, 0x77, 0x24, 0x41, 0xc8, 0x6a, 0xbc, 0x80, 0x7f, 0xd8, 0x1f, 0x94, 0x29, 0xe7, 0x38,
    0xb8, 0x7f, 0x90, 0x54, 0xe4, 0xb6, 0xb8, 0x30, 0x7f, 0x40, 0xeb, 0x60, 0x6c, 0x6a, 0x07, 0x36,
    0x5b, 0xfc, 0x09, 0x72, 0xff, 0x02, 0x96, 0xce, 0xd6, 0xdc, 0x07, 0x80, 0x25, 0x70, 0x6f, 0x9e,
    0x63, 0xac, 0x97, 0x1d, 0x3d, 0x3a, 0x26, 0x83, 0xc8, 0xe3, 0x99, 0xa8, 0x10, 0xf4, 0x68, 0xf4,
    0xf3, 0x8c, 0x38, 0x8d, 0xd2, 0x13, 0xd5, 0x95, 0xce, 0x80, 0x1e, 0xcf, 0x14, 0xb8, 0x16, 0x64,
    0x28, 0xf1, 0x40, 0xd9, 0xa0, 0x24, 0x13, 0x84, 0x3b, 0x8b, 0x92, 0x73, 0x67, 0x77, 0x93, 0xfe,
    0x07, 0x67, 0x7d, 0xcf, 0x7f, 0x9e, 0x7b, 0x74, 0x6a, 0x07, 0xb8, 0x1f, 0xdc, 0xa6, 0xdd, 0xbb,
    0x63, 0xc8, 0x5d, 0xde, 0x48, 0x93, 0x34, 0xf3, 0x3b, 0xa6, 0x4d, 0x08, 0xdf, 0xd4, 0x40, 0x55,
    0x0c, 0x85, 0x6c, 0xda, 0x41, 0xc2, 0xd5, 0x4f, 0x08, 0xfc, 0x87, 0x43, 0x22, 0x42, 0x59, 0x53,
    0xbe, 0x21, 0xe4, 0x09, 0xcc, 0x6a, 0xa2, 0x50, 0x6e, 0x2d, 0x9a, 0x61, 0xdc, 0x36, 0xd0, 0x51,
    0xab, 0xdb, 0x24, 0xad, 0x37, 0xe5, 0x47, 0x93, 0xcd, 0x74, 0x94, 0x17, 0x71, 0x8f, 0xc1, 0xca,
    0x3f, 0xfa, 0x4f, 0xd8, 0xb5, 0xbb, 0xb6, 0xf3, 0xab, 0x7d, 0xa6, 0x65, 0x24, 0x42, 0x2a, 0x4b,
    0x3a, 0xbb, 0x7c, 0xcf, 0x1e, 0x32, 0x12, 0xf4, 0xe1, 0x90, 0xb3, 0x50, 0xb1, 0xfc, 0x7c, 0x6b,
    0x91, 0x06, 0x18, 0x02, 0x33, 0x83, 0x4b, 0x20, 0x75, 0xf5, 0xad, 0x37, 0x5d, 0xb8, 0xc2, 0xb5,
    0x23, 0x28, 0x32, 0x50, 0x36, 0xd8, 0x6d, 0x65, 0x98, 0xca, 0x58, 0x51, 0x91, 0x72, 0x3b, 0x42,
    0xd5, 0xcd, 0x09, 0x1e, 0xcf, 0x8c, 0x88, 0x4c, 0xf4, 0x4d, 0x31, 0x0b, 0xd3, 0x81, 0xe8, 0x28,
    0x2b, 0xf6, 0x6d, 0x70, 0x34, 0x0f, 0x7e, 0x8d, 0xfc, 0x03, 0xc4, 0x8c, 0xf2, 0xc5, 0x6c, 0xbd,
    0xf8, 0x14, 0xec, 0x2b, 0x0a, 0xb7, 0x7e, 0x8b, 0xcf, 0xb5, 0x58, 0xa5, 0x4d, 0x34, 0x61, 0x58,
    0xa3, 0xfd, 0x72, 0x4e, 0x20, 0xbe, 0x96, 0xc4, 0x6c, 0xec, 0x1f, 0xb6, 0x0c, 0x15, 0xbc, 0x71,
    0x30, 0xa1, 0x57, 0x13, 0x85, 0x5c, 0xf3, 0x36, 0x42, 0x8b, 0x22, 0x26, 0x5b, 0xfb, 0x76, 0x01,
    0xf3, 0xf3, 0xff, 0xe1, 0x6b, 0xf3, 0x8c, 0x25, 0xe3, 0x60, 0xee, 0xc8, 0x8f, 0xe3, 0xdb, 0xa8,
    0x6e, 0xed, 0x1e, 0x5a, 0xd4, 0xd2, 0xff, 0x28, 0xea, 0x63, 0x56, 0xc1, 0xc3, 0xee, 0x37, 0x57,
    0xd7, 0x6d, 0x92, 0xf8, 0x2b, 0x9a, 0x55, 0x62, 0x7b, 0x08, 0x27, 0xde, 0x13, 0x27, 0x35, 0x30,
    0x20, 0xb3, 0x43, 0x31, 0xeb, 0xf6, 0x28, 0xb4, 0x6e, 0x92, 0x82, 0x48, 0x1e, 0xbf, 0xe6, 0x3d,
    0x84, 0x0d, 0x9f, 0x5f, 0x55, 0x97, 0x96, 0x26, 0x65, 0x59, 0xfa, 0x6a, 0x72, 0xc6, 0x49, 0xa5,
    0x0d, 0xd0, 0x84, 0x17, 0x97, 0x56, 0x2e, 0xff, 0x82, 0x76, 0x61, 0x75, 0x9f, 0x15, 0xd2, 0x08,
    0xbb, 0x24, 0xb5, 0xba, 0xaa, 0x5e, 0x20, 0xdd, 0x03, 0x4c, 0x3c, 0x54, 0xd8, 0x8f, 0x87, 0x49,
};
