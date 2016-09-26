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

#pragma comment(lib, "Crypt32.lib")


//////////////////////////////////////////////////////////////////////
// wxCertificateClientData
//////////////////////////////////////////////////////////////////////

wxCertificateClientData::wxCertificateClientData(PCCERT_CONTEXT cert) : m_cert(cert)
{
}


wxCertificateClientData::~wxCertificateClientData()
{
    if (m_cert)
        CertFreeCertificateContext(m_cert);
}


//////////////////////////////////////////////////////////////////////
// wxHostNameValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxHostNameValidator, wxValidator);


wxHostNameValidator::wxHostNameValidator(std::wstring *val) :
    m_val(val),
    wxValidator()
{
}


wxHostNameValidator::wxHostNameValidator(const wxHostNameValidator &other) :
    m_val(other.m_val),
    wxValidator(other)
{
}


wxObject* wxHostNameValidator::Clone() const
{
    return new wxHostNameValidator(*this);
}


bool wxHostNameValidator::Validate(wxWindow *parent)
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxHostNameValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val)
        ((wxTextCtrl*)GetWindow())->SetValue(*m_val);

    return true;
}


bool wxHostNameValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxHostNameValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::wstring *val_out)
{
    const wxStringCharType *buf = val_in;

    size_t i = i_start;
    for (;;) {
        if (i >= i_end) {
            // End of host name found.
            if (val_out) val_out->assign(val_in.c_str() + i_start, i - i_start);
            return true;
        } else if (buf[i] == _T('-') || buf[i] == _T('_') || buf[i] == _T('*') || _istalnum(buf[i])) {
            // Valid character found.
            i++;
        } else {
            // Invalid character found.
            ctrl->SetFocus();
            ctrl->SetSelection(i, i + 1);
            wxMessageBox(wxString::Format(_("Invalid character in host name found: %c"), buf[i]), _("Validation conflict"), wxOK | wxICON_EXCLAMATION, parent);
            return false;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// wxFQDNValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxFQDNValidator, wxValidator);


wxFQDNValidator::wxFQDNValidator(std::wstring *val) :
    m_val(val),
    wxValidator()
{
}


wxFQDNValidator::wxFQDNValidator(const wxFQDNValidator &other) :
    m_val(other.m_val),
    wxValidator(other)
{
}


wxObject* wxFQDNValidator::Clone() const
{
    return new wxFQDNValidator(*this);
}


bool wxFQDNValidator::Validate(wxWindow *parent)
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxFQDNValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val)
        ((wxTextCtrl*)GetWindow())->SetValue(*m_val);

    return true;
}


bool wxFQDNValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxFQDNValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::wstring *val_out)
{
    const wxStringCharType *buf = val_in;

    size_t i = i_start;
    for (;;) {
        const wxStringCharType *buf_next;
        if ((buf_next = wmemchr(buf + i, L'.', i_end - i)) != NULL) {
            // FQDN separator found.
            if (!wxHostNameValidator::Parse(val_in, i, buf_next - buf, ctrl, parent))
                return false;
            i = buf_next - buf + 1;
        } else if (wxHostNameValidator::Parse(val_in, i, i_end, ctrl, parent)) {
            // The rest of the FQDN parsed succesfully.
            if (val_out) val_out->assign(val_in.c_str() + i_start, i_end - i_start);
            return true;
        } else
            return false;
    }
}


//////////////////////////////////////////////////////////////////////
// wxFQDNListValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxFQDNListValidator, wxValidator);


wxFQDNListValidator::wxFQDNListValidator(std::list<std::wstring> *val) :
    m_val(val),
    wxValidator()
{
}


wxFQDNListValidator::wxFQDNListValidator(const wxFQDNListValidator &other) :
    m_val(other.m_val),
    wxValidator(other)
{
}


wxObject* wxFQDNListValidator::Clone() const
{
    return new wxFQDNListValidator(*this);
}


bool wxFQDNListValidator::Validate(wxWindow *parent)
{
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxFQDNListValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val) {
        wxString str;
        for (std::list<std::wstring>::const_iterator name = m_val->cbegin(), name_end = m_val->cend(); name != name_end; ++name) {
            if (!str.IsEmpty()) str += wxT("; ");
            str += *name;
        }
        ((wxTextCtrl*)GetWindow())->SetValue(str);
    }

    return true;
}


bool wxFQDNListValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxFQDNListValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::list<std::wstring> *val_out)
{
    const wxStringCharType *buf = val_in;
    std::wstring _fqdn, *fqdn = val_out ? &_fqdn : NULL;
    std::list<std::wstring> _val_out;

    size_t i = i_start;
    for (;;) {
        // Skip initial white-space.
        for (; i < i_end && _istspace(buf[i]); i++);

        const wxStringCharType *buf_next;
        if ((buf_next = wmemchr(buf + i, L';', i_end - i)) != NULL) {
            // FQDN list separator found.

            // Skip trailing white-space.
            size_t i_next = buf_next - buf;
            for (; i < i_next && _istspace(buf[i_next - 1]); i_next--);

            if (!wxFQDNValidator::Parse(val_in, i, i_next, ctrl, parent, fqdn))
                return false;
            if (fqdn && !fqdn->empty()) _val_out.push_back(std::move(*fqdn));

            i = buf_next - buf + 1;
        } else {
            // Skip trailing white-space.
            for (; i < i_end && _istspace(buf[i_end - 1]); i_end--);

            if (wxFQDNValidator::Parse(val_in, i, i_end, ctrl, parent, fqdn)) {
                // The rest of the FQDN list parsed succesfully.
                if (fqdn && !fqdn->empty()) _val_out.push_back(std::move(*fqdn));
                if (val_out) *val_out = std::move(_val_out);
                return true;
            } else
                return false;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// wxTLSCredentialsPanel
//////////////////////////////////////////////////////////////////////

wxTLSCredentialsPanel::wxTLSCredentialsPanel(const eap::config_provider &prov, const eap::config_method_with_cred &cfg, eap::credentials_tls &cred, wxWindow* parent, bool is_config) :
    wxEAPCredentialsPanel<eap::credentials_tls, wxTLSCredentialsPanelBase>(prov, cfg, cred, parent, is_config)
{
    // Load and set icon.
    winstd::library lib_shell32;
    if (lib_shell32.load(_T("certmgr.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE))
        m_credentials_icon->SetIcon(wxLoadIconFromResource(lib_shell32, MAKEINTRESOURCE(6170)));
}


bool wxTLSCredentialsPanel::TransferDataToWindow()
{
    // Populate certificate list.
    m_certificate->Append(_("<empty>"), (wxCertificateClientData*)NULL);
    bool is_found = false;
    winstd::cert_store store;
    if (store.create(CERT_STORE_PROV_SYSTEM, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, (HCRYPTPROV)NULL, CERT_SYSTEM_STORE_CURRENT_USER, _T("My"))) {
        for (PCCERT_CONTEXT cert = NULL; (cert = CertEnumCertificatesInStore(store, cert)) != NULL;) {
            DWORD dwKeySpec = 0, dwSize = sizeof(dwKeySpec);
            if (!CertGetCertificateContextProperty(cert, CERT_KEY_SPEC_PROP_ID, &dwKeySpec, &dwSize) || !dwKeySpec) {
                // Skip certificates without private key.
                continue;
            }

            // Prepare certificate information.
            std::unique_ptr<wxCertificateClientData> data(new wxCertificateClientData(CertDuplicateCertificateContext(cert)));

            // Add to list.
            bool is_selected =
                m_cred.m_cert &&
                m_cred.m_cert->cbCertEncoded == data->m_cert->cbCertEncoded &&
                memcmp(m_cred.m_cert->pbCertEncoded, data->m_cert->pbCertEncoded, m_cred.m_cert->cbCertEncoded) == 0;
            winstd::tstring name(std::move(eap::get_cert_title(cert)));
            int i = m_certificate->Append(name, data.release());
            if (is_selected) {
                m_certificate->SetSelection(i);
                is_found = true;
            }
        }
    }

    if (!is_found)
        m_certificate->SetSelection(0);

    m_identity->SetValue(m_cred.m_identity);

    return wxEAPCredentialsPanel<eap::credentials_tls, wxTLSCredentialsPanelBase>::TransferDataToWindow();
}


bool wxTLSCredentialsPanel::TransferDataFromWindow()
{
    // Check if m_certificate control has selected item, and has client object data (at least one user certificate on the list). Then try to get the data from selected item.
    int sel = m_certificate->GetSelection();
    const wxCertificateClientData *data =
        sel != wxNOT_FOUND && m_certificate->HasClientObjectData() ?
            dynamic_cast<const wxCertificateClientData*>(m_certificate->GetClientObject(sel)) :
            NULL;
    if (data)
        m_cred.m_cert.attach_duplicated(data->m_cert);
    else
        m_cred.m_cert.free();

    m_cred.m_identity = m_identity->GetValue();

    // Inherited TransferDataFromWindow() calls m_cred.store().
    // Therefore, call it only now, that m_cred is set.
    return wxEAPCredentialsPanel<eap::credentials_tls, wxTLSCredentialsPanelBase>::TransferDataFromWindow();
}


void wxTLSCredentialsPanel::OnUpdateUI(wxUpdateUIEvent& /*event*/)
{
    if (!m_is_config && m_cfg.m_use_cred) {
        // Credential prompt mode & Using configured credentials
        m_certificate->Enable(false);
        m_identity   ->Enable(false);
    } else {
        // Configuration mode or using stored credentials. Enable controls.
        m_certificate->Enable(true);
        m_identity   ->Enable(true);
    }
}


//////////////////////////////////////////////////////////////////////
// wxTLSServerTrustPanel
//////////////////////////////////////////////////////////////////////

wxTLSServerTrustPanel::wxTLSServerTrustPanel(const eap::config_provider &prov, eap::config_method_tls &cfg, wxWindow* parent) :
    m_prov(prov),
    m_cfg(cfg),
    wxTLSServerTrustPanelBase(parent)
{
    // Load and set icon.
    winstd::library lib_certmgr;
    if (lib_certmgr.load(_T("certmgr.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE))
        m_server_trust_icon->SetIcon(wxLoadIconFromResource(lib_certmgr, MAKEINTRESOURCE(379)));

    // Do not use cfg.m_server_names directly, so we can decide not to store the value in case of provider-locked configuration.
    // Never rely on control disabled state alone, as they can be enabled using external tool like Spy++.
    m_server_names->SetValidator(wxFQDNListValidator(&m_server_names_val));
}


bool wxTLSServerTrustPanel::TransferDataToWindow()
{
    // Populate trusted CA list.
    for (std::list<winstd::cert_context>::const_iterator cert = m_cfg.m_trusted_root_ca.cbegin(), cert_end = m_cfg.m_trusted_root_ca.cend(); cert != cert_end; ++cert)
        m_root_ca->Append(wxString(eap::get_cert_title(*cert)), new wxCertificateClientData(cert->duplicate()));

    // Set server acceptable names. The edit control will get populated by validator.
    m_server_names_val = m_cfg.m_server_names;

    return wxTLSServerTrustPanelBase::TransferDataToWindow();
}


bool wxTLSServerTrustPanel::TransferDataFromWindow()
{
    wxCHECK(wxTLSServerTrustPanelBase::TransferDataFromWindow(), false);

    if (!m_prov.m_read_only) {
        // This is not a provider-locked configuration. Save the data.

        // Parse trusted CA list.
        m_cfg.m_trusted_root_ca.clear();
        for (unsigned int i = 0, i_end = m_root_ca->GetCount(); i < i_end; i++) {
            wxCertificateClientData *cert = dynamic_cast<wxCertificateClientData*>(m_root_ca->GetClientObject(i));
            if (cert)
                m_cfg.add_trusted_ca(cert->m_cert->dwCertEncodingType, cert->m_cert->pbCertEncoded, cert->m_cert->cbCertEncoded);
        }

        // Save acceptable server names.
        m_cfg.m_server_names = m_server_names_val;
    }

    return true;
}


void wxTLSServerTrustPanel::OnUpdateUI(wxUpdateUIEvent& /*event*/)
{
    if (m_prov.m_read_only) {
        // This is provider-locked configuration. Disable controls.
        m_root_ca_add_store->Enable(false);
        m_root_ca_add_file ->Enable(false);
        m_root_ca_remove   ->Enable(false);
        m_server_names     ->Enable(false);
    } else {
        // This is not a provider-locked configuration. Selectively enable/disable controls.
        m_root_ca_add_store->Enable(true);
        m_root_ca_add_file ->Enable(true);
        m_root_ca_remove   ->Enable(ListBox_GetSelCount(m_root_ca->GetHWND()) ? true : false); // *
        m_server_names     ->Enable(true);

        // * ListBox_GetSelCount() is not cross-platform, but this is Windows EAP Supplicant,
        //   and this is the fastest way to find out if there is a selection in the list box,
        //   observing wxWidgets 3.0.2 has nothing faster to offer.
    }
}


void wxTLSServerTrustPanel::OnRootCADClick(wxCommandEvent& event)
{
    wxCertificateClientData *cert = dynamic_cast<wxCertificateClientData*>(event.GetClientObject());
    if (cert)
        CryptUIDlgViewContext(CERT_STORE_CERTIFICATE_CONTEXT, cert->m_cert, this->GetHWND(), NULL, 0, NULL);
}


void wxTLSServerTrustPanel::OnRootCAAddStore(wxCommandEvent& /*event*/)
{
    winstd::cert_store store;
    if (store.create(NULL, _T("ROOT"))) {
        winstd::cert_context cert;
        cert.attach(CryptUIDlgSelectCertificateFromStore(store, this->GetHWND(), NULL, NULL, 0, 0, NULL));
        if (cert)
            AddRootCA(cert);
    }
}


void wxTLSServerTrustPanel::OnRootCAAddFile(wxCommandEvent& event)
{
    const wxString separator(wxT("|"));
    wxFileDialog open_dialog(this, _("Add Certificate"), wxEmptyString, wxEmptyString,
        _("Certificate Files (*.cer;*.crt;*.der;*.p7b;*.pem)") + separator + wxT("*.cer;*.crt;*.der;*.p7b;*.pem") + separator +
        _("X.509 Certificate Files (*.cer;*.crt;*.der;*.pem)") + separator + wxT("*.cer;*.crt;*.der;*.pem") + separator +
        _("PKCS #7 Certificate Files (*.p7b)") + separator + wxT("*.p7b") + separator +
        _("All Files (*.*)") + separator + wxT("*.*"),
        wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
    if (open_dialog.ShowModal() == wxID_CANCEL) {
        event.Skip();
        return;
    }

    wxArrayString paths;
    open_dialog.GetPaths(paths);
    for (size_t i = 0, i_end = paths.GetCount(); i < i_end; i++) {
        // Load certificate(s) from file.
        winstd::cert_store cs;
        if (cs.create(CERT_STORE_PROV_FILENAME, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, (LPCTSTR)(paths[i]))) {
            for (PCCERT_CONTEXT cert = NULL; (cert = CertEnumCertificatesInStore(cs, cert)) != NULL;)
                AddRootCA(cert);
        } else
            wxMessageBox(wxString::Format(_("Invalid or unsupported certificate file %s"), paths[i]), _("Error"), wxOK | wxICON_EXCLAMATION, this);
    }
}


void wxTLSServerTrustPanel::OnRootCARemove(wxCommandEvent& /*event*/)
{
    wxArrayInt selections;
    for (int i = m_root_ca->GetSelections(selections); i--; )
        m_root_ca->Delete(selections[i]);
}


bool wxTLSServerTrustPanel::AddRootCA(PCCERT_CONTEXT cert)
{
    for (unsigned int i = 0, i_end = m_root_ca->GetCount(); i < i_end; i++) {
        wxCertificateClientData *c = dynamic_cast<wxCertificateClientData*>(m_root_ca->GetClientObject(i));
        if (c && c->m_cert &&
            c->m_cert->cbCertEncoded == cert->cbCertEncoded &&
            memcmp(c->m_cert->pbCertEncoded, cert->pbCertEncoded, cert->cbCertEncoded) == 0)
        {
            // This certificate is already on the list.
            m_root_ca->SetSelection(i);
            return false;
        }
    }

    // Add certificate to the list.
    int i = m_root_ca->Append(wxString(eap::get_cert_title(cert)), new wxCertificateClientData(CertDuplicateCertificateContext(cert)));
    if (0 <= i)
        m_root_ca->SetSelection(i);

    return true;
}


//////////////////////////////////////////////////////////////////////
// wxTLSConfigPanel
//////////////////////////////////////////////////////////////////////

wxTLSConfigPanel::wxTLSConfigPanel(const eap::config_provider &prov, eap::config_method_tls &cfg, wxWindow* parent) :
    m_prov(prov),
    m_cfg(cfg),
    wxPanel(parent)
{
    wxBoxSizer* sb_content;
    sb_content = new wxBoxSizer( wxVERTICAL );

    m_server_trust = new wxTLSServerTrustPanel(prov, cfg, this);
    sb_content->Add(m_server_trust, 0, wxDOWN|wxEXPAND, 5);

    m_credentials = new wxTLSCredentialsConfigPanel(prov, cfg, this, _("User Certificate"));
    sb_content->Add(m_credentials, 0, wxUP|wxEXPAND, 5);

    this->SetSizer(sb_content);
    this->Layout();

    // Connect Events
    this->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(wxTLSConfigPanel::OnInitDialog));
}


wxTLSConfigPanel::~wxTLSConfigPanel()
{
    // Disconnect Events
    this->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(wxTLSConfigPanel::OnInitDialog));
}


void wxTLSConfigPanel::OnInitDialog(wxInitDialogEvent& event)
{
    // Forward the event to child panels.
    m_server_trust->GetEventHandler()->ProcessEvent(event);
    if (m_credentials)
        m_credentials->GetEventHandler()->ProcessEvent(event);
}


#if EAP_TLS < EAP_TLS_SCHANNEL

bool wxTLSConfigPanel::TransferDataFromWindow()
{
    wxCHECK(wxPanel::TransferDataFromWindow(), false);

    if (!m_prov.m_read_only) {
        // This is not a provider-locked configuration. The data will get saved.

        // Reset session ID and master secret to force clean connect next time.
        m_cfg.m_session_id.clear();
        m_cfg.m_master_secret.clear();
    }

    return true;
}

#endif
