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

#include "TLS.h"
#include "../res/wxTLS_UI.h"

class wxEAPTLSConfigPanel;
class wxCERTCONTEXTClientData;

#pragma once

#include <wx/icon.h>
#include <wx/validate.h>


///
/// EAPTLS configuration panel
///
class wxEAPTLSConfigPanel : public wxEAPTLSConfigPanelBase
{
public:
    ///
    /// Constructs a configuration panel
    ///
    wxEAPTLSConfigPanel(eap::config_tls &cfg, wxWindow* parent);

protected:
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();
    virtual void OnRootCA(wxCommandEvent& event);
    virtual void OnRootCADClick(wxCommandEvent& event);
    virtual void OnRootCAAddStore(wxCommandEvent& event);
    virtual void OnRootCAAddFile(wxCommandEvent& event);
    virtual void OnRootCARemove(wxCommandEvent& event);

    bool AddRootCA(PCCERT_CONTEXT cert);

protected:
    eap::config_tls &m_cfg;     ///< TLS configuration
    winstd::library m_certmgr;  ///< certmgr.dll resource library reference
    wxIcon m_icon;              ///< Panel icon
};


///
/// Helper class for auto-destroyable certificates used in wxWidget's item containers
///
class wxCertificateClientData : public wxClientData
{
public:
    ///
    /// Constructs client data object with existing handle
    ///
    wxCertificateClientData(PCCERT_CONTEXT m_cert);

    ///
    /// Releases certificate handle and destructs the object
    ///
    virtual ~wxCertificateClientData();

public:
    PCCERT_CONTEXT m_cert;  ///< Certificate
};


///
/// Validator for host name
///
class wxHostNameValidator : public wxValidator
{
    wxDECLARE_DYNAMIC_CLASS(wxHostNameValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxHostNameValidator);

public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxHostNameValidator(std::string *val = NULL);

    ///
    /// Copy constructor
    ///
    wxHostNameValidator(const wxHostNameValidator &other);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::string *val_out = NULL);

protected:
    std::string *m_val;
};


///
/// Validator for FQDN
///
class wxFQDNValidator : public wxValidator
{
    wxDECLARE_DYNAMIC_CLASS(wxFQDNValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxFQDNValidator);

public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxFQDNValidator(std::string *val = NULL);

    ///
    /// Copy constructor
    ///
    wxFQDNValidator(const wxFQDNValidator &other);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::string *val_out = NULL);

protected:
    std::string *m_val;
};


///
/// Validator for FQDN lists
///
class wxFQDNListValidator : public wxValidator
{
    wxDECLARE_DYNAMIC_CLASS(wxFQDNListValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxFQDNListValidator);

public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxFQDNListValidator(std::list<std::string> *val = NULL);

    ///
    /// Copy constructor
    ///
    wxFQDNListValidator(const wxFQDNListValidator &other);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN list value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, std::list<std::string> *val_out = NULL);

protected:
    std::list<std::string> *m_val;
};
