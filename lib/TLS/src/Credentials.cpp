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
    return credentials::empty() && !m_cert;
}


bool eap::credentials_tls::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    DWORD dwResult;
    HRESULT hr;

    // Don't save m_identity. We rebuild it on every load.
    //if (!credentials::save(pDoc, pConfigRoot, ppEapError))
    //    return false;

    // <ClientCertificate>
    com_obj<IXMLDOMElement> pXmlElClientCertificate;
    if ((dwResult = eapxml::create_element(pDoc, bstr(L"ClientCertificate"), bstrNamespace, &pXmlElClientCertificate))) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <ClientCertificate> element."), NULL);
        return false;
    }

    if (m_cert) {
        // <ClientCertificate>/<format>
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElClientCertificate, bstr(L"format"), bstrNamespace, bstr(L"PEM"))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <format> element."), NULL);
            return false;
        }

        // <ClientCertificate>/<cert-data>
        if ((dwResult = eapxml::put_element_base64(pDoc, pXmlElClientCertificate, bstr(L"cert-data"), bstrNamespace, m_cert->pbCertEncoded, m_cert->cbCertEncoded)) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <cert-data> element."), NULL);
            return false;
        }
    }

    if (FAILED(hr = pConfigRoot->appendChild(pXmlElClientCertificate, NULL))) {
        *ppEapError = m_module.make_error(HRESULT_CODE(hr), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error appending <ClientCertificate> element."), NULL);
        return false;
    }

    return true;
}


bool eap::credentials_tls::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    assert(pConfigRoot);
    DWORD dwResult;

    // Don't load m_identity. We rebuild it on load.
    //if (!credentials::load(pConfigRoot, ppEapError))
    //    return false;

    m_identity.clear();
    m_cert.free();

    // <ClientCertificate>
    com_obj<IXMLDOMElement> pXmlElClientCertificate;
    if ((dwResult = eapxml::select_element(pConfigRoot, bstr(L"eap-metadata:ClientCertificate"), &pXmlElClientCertificate)) != ERROR_SUCCESS) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error reading <ClientCertificate> element."), NULL);
        return false;
    }

    // <ClientCertificate>/<format>
    bstr bstrFormat;
    if ((dwResult = eapxml::get_element_value(pXmlElClientCertificate, bstr(L"eap-metadata:format"), &bstrFormat)) == ERROR_SUCCESS) {
        if (CompareStringEx(LOCALE_NAME_INVARIANT, NORM_IGNORECASE, bstrFormat, bstrFormat.length(), L"PEM", -1, NULL, NULL, 0) == CSTR_EQUAL) {
            // <ClientCertificate>/<cert-data>
            vector<unsigned char> aData;
            if ((dwResult = eapxml::get_element_base64(pXmlElClientCertificate, bstr(L"eap-metadata:cert-data"), aData)) == ERROR_SUCCESS) {
                if (m_cert.create(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, aData.data(), (DWORD)aData.size())) {
                    // Generate identity. TODO: Find which CERT_NAME_... constant returns valid identity (username@domain or DOMAIN\Username).
                    CertGetNameString(m_cert, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, m_identity);
                }
            }
        }
    }

    return true;
}


bool eap::credentials_tls::store(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError) const
{
    assert(pszTargetName);
    assert(ppEapError);
    string cert_enc;

    // Prepare cryptographics provider.
    crypt_prov cp;
    if (!cp.create(NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptAcquireContext failed."), NULL);
        return false;
    }

    // Encrypt certificate.
    vector<unsigned char> cert;
    if (!m_module.encrypt_md5(cp, m_cert->pbCertEncoded, m_cert->cbCertEncoded, cert, ppEapError))
        return false;

    // Convert encrypted certificate to Base64, since CredProtectA() fail for binary strings.
    string cert_base64;
    base64_enc enc;
    enc.encode(cert_base64, cert.data(), cert.size());

    // Encrypt the certificate using user's key.
    CRED_PROTECTION_TYPE cpt;
    if (!CredProtectA(TRUE, cert_base64.c_str(), (DWORD)cert_base64.length(), cert_enc, &cpt)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredProtect failed."), NULL);
        return false;
    }

    tstring target(target_name(pszTargetName));

    // Write credentials.
    assert(cert_enc.size()     < CRED_MAX_CREDENTIAL_BLOB_SIZE);
    assert(m_identity.length() < CRED_MAX_USERNAME_LENGTH     );
    CREDENTIAL cred = {
        0,                          // Flags
        CRED_TYPE_GENERIC,          // Type
        (LPTSTR)target.c_str(),     // TargetName
        _T(""),                     // Comment
        { 0, 0 },                   // LastWritten
        (DWORD)cert_enc.size(),     // CredentialBlobSize
        (LPBYTE)cert_enc.data(),    // CredentialBlob
        CRED_PERSIST_ENTERPRISE,    // Persist
        0,                          // AttributeCount
        NULL,                       // Attributes
        NULL,                       // TargetAlias
        (LPTSTR)m_identity.c_str()  // UserName
    };
    if (!CredWrite(&cred, 0)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredWrite failed."), NULL);
        return false;
    }

    return true;
}


bool eap::credentials_tls::retrieve(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError)
{
    assert(pszTargetName);

    // Read credentials.
    unique_ptr<CREDENTIAL, CredFree_delete<CREDENTIAL> > cred;
    if (!CredRead(target_name(pszTargetName).c_str(), CRED_TYPE_GENERIC, 0, (PCREDENTIAL*)&cred)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredRead failed."), NULL);
        return false;
    }

    // Decrypt the certificate using user's key.
    string cert_base64;
    if (!CredUnprotectA(TRUE, (LPCSTR)(cred->CredentialBlob), cred->CredentialBlobSize, cert_base64)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredUnprotect failed."), NULL);
        return false;
    }

    // Convert Base64 to binary encrypted certificate, since CredProtectA() fail for binary strings.
    vector<unsigned char> cert;
    base64_dec dec;
    bool is_last;
    dec.decode(cert, is_last, cert_base64.c_str(), cert_base64.length());

    // Prepare cryptographics provider.
    crypt_prov cp;
    if (!cp.create(NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptAcquireContext failed."), NULL);
        return false;
    }

    // Decrypt certificate.
    vector<unsigned char, sanitizing_allocator<unsigned char> > _cert;
    if (!m_module.decrypt_md5(cp, cert.data(), cert.size(), _cert, ppEapError))
        return false;

    if (!m_cert.create(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, _cert.data(), (DWORD)_cert.size())) {
        *ppEapError = m_module.make_error(GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error loading certificate."), NULL);
        return false;
    }

    // Generate identity. TODO: Find which CERT_NAME_... constant returns valid identity (username@domain or DOMAIN\Username).
    CertGetNameString(m_cert, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, m_identity);

    return true;
}