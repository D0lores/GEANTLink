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

#include "EAP.h"
#include "../res/wxEAP_UI.h"

#include <wx/dialog.h>
#include <wx/icon.h>

namespace eap
{
    template <class _Tmeth, class _Tid, class _Tint, class _Tintres> class peer_ui;
}

template <class _Tcfg, class _wxT> class wxEAPConfig;
class wxEAPBannerPanel;
class wxCredentialsConfigPanel;
class wxPasswordCredentialsPanel;

inline int wxShowModal(wxDialog *dlg);

#pragma once


namespace eap
{
    ///
    /// EAP UI peer base abstract class template
    ///
    /// A group of methods all EAP UI peers must or should implement.
    ///
    template <class _Tcfg, class _Tid, class _Tint, class _Tintres>
    class peer_ui : public module
    {
    public:
        ///
        /// Configuration data type
        ///
        typedef config_providers<config_provider<_Tcfg> > config_type;

        ///
        /// Identity data type
        ///
        typedef _Tid identity_type;

        ///
        /// Interactive request data type
        ///
        typedef _Tint interactive_request_type;

        ///
        /// Interactive response data type
        ///
        typedef _Tintres interactive_response_type;

    public:
        ///
        /// Constructor
        ///
        peer_ui() : module() {}

        ///
        /// Raises the EAP method's specific connection configuration user interface dialog on the client.
        ///
        /// \sa [EapPeerInvokeConfigUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363614.aspx)
        ///
        /// \param[in]    hwndParent  Parent window
        /// \param[in]    dwFlags     Flags passed to `EapPeerInvokeConfigUI()` call
        /// \param[inout] cfg         Configuration to edit
        /// \param[out]   ppEapError  Pointer to error descriptor in case of failure. Free using `module::free_error_memory()`.
        ///
        /// \returns
        /// - \c ERROR_SUCCESS if succeeded
        /// - error code otherwise
        ///
        virtual DWORD invoke_config_ui(
            _In_    HWND        hwndParent,
            _In_    DWORD       dwFlags,
            _Inout_ config_type &cfg,
            _Out_   EAP_ERROR   **ppEapError) = 0;

        ///
        /// Raises a custom interactive user interface dialog to obtain user identity information for the EAP method on the client.
        ///
        /// \sa [EapPeerInvokeIdentityUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363615.aspx)
        ///
        /// \param[in]    hwndParent     Parent window
        /// \param[in]    dwFlags        Flags passed to `EapPeerInvokeIdentityUI()` call
        /// \param[inout] cfg            Configuration
        /// \param[inout] usr            User data to edit
        /// \param[out]   ppwszIdentity  Pointer to user identity. Free using `module::free_memory()`.
        /// \param[out]   ppEapError     Pointer to error descriptor in case of failure. Free using `module::free_error_memory()`.
        ///
        /// \returns
        /// - \c ERROR_SUCCESS if succeeded
        /// - error code otherwise
        ///
        virtual DWORD invoke_identity_ui(
            _In_    HWND          hwndParent,
            _In_    DWORD         dwFlags,
            _Inout_ config_type   &cfg,
            _Inout_ identity_type &usr,
            _Out_   LPWSTR        *ppwszIdentity,
            _Out_   EAP_ERROR     **ppEapError) = 0;

        ///
        /// Raises a custom interactive user interface dialog for the EAP method on the client.
        ///
        /// \sa [EapPeerInvokeInteractiveUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363616.aspx)
        ///
        /// \param[in]  hwndParent     Parent window
        /// \param[in]  req            Interactive request
        /// \param[out] res            Interactive response
        /// \param[out] ppEapError     Pointer to error descriptor in case of failure. Free using `module::free_error_memory()`.
        ///
        /// \returns
        /// - \c ERROR_SUCCESS if succeeded
        /// - error code otherwise
        ///
        virtual DWORD invoke_interactive_ui(
            _In_        HWND                      hwndParent,
            _In_  const interactive_request_type  &req,
            _Out_       interactive_response_type &res,
            _Out_       EAP_ERROR                 **ppEapError) = 0;
    };
}


///
/// EAP configuration dialog
///
template <class _Tmeth, class _wxT>
class wxEAPConfig : public wxEAPConfigBase
{
public:
    ///
    /// Configuration provider data type
    ///
    typedef eap::config_provider<_Tmeth> _Tprov;

    ///
    /// Configuration data type
    ///
    typedef eap::config_providers<_Tprov> config_type;

    ///
    /// This data type
    ///
    typedef wxEAPConfig<_Tmeth, _wxT> _T;

public:
    ///
    /// Constructs a config panel
    ///
    wxEAPConfig(config_type &cfg, wxWindow* parent) :
        m_cfg(cfg),
        wxEAPConfigBase(parent)
    {
        for (std::list<_Tprov>::iterator provider = m_cfg.m_providers.begin(), provider_end = m_cfg.m_providers.end(); provider != provider_end; ++provider) {
            bool is_single = provider->m_methods.size() == 1;
            std::list<_Tmeth>::size_type count = 0;
            std::list<_Tmeth>::iterator method = provider->m_methods.begin(), method_end = provider->m_methods.end();
            for (; method != method_end; ++method, count++)
                m_providers->AddPage(new _wxT(provider->m_methods.front(), m_providers), is_single ? provider->m_id : winstd::tstring_printf(_T("%s (%u)"), provider->m_id.c_str(), count));
        }

        this->Layout();
        this->GetSizer()->Fit(this);

        m_buttonsOK->SetDefault();

        // Connect Events
        this->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(_T::OnInitDialog));
    }


    ///
    /// Destructs the config panel
    ///
    virtual ~wxEAPConfig()
    {
        // Disconnect Events
        this->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(_T::OnInitDialog));
    }


protected:
    ///
    /// Initializes the dialog controls and its children
    ///
    virtual void OnInitDialog(wxInitDialogEvent& event)
    {
        // Forward the event to child panels.
        for (wxWindowList::compatibility_iterator provider = m_providers->GetChildren().GetFirst(); provider; provider = provider->GetNext()) {
            _wxT *prov = wxDynamicCast(provider->GetData(), _wxT);
            if (prov)
                prov->GetEventHandler()->ProcessEvent(event);
        }
    }


protected:
    config_type &m_cfg;  ///< EAP providers configuration
};


///
/// EAP dialog banner
///
class wxEAPBannerPanel : public wxEAPBannerPanelBase
{
public:
    wxEAPBannerPanel(wxWindow* parent);
};


///
/// Credentials configuration panel
///
class wxCredentialsConfigPanel : public wxCredentialsConfigPanelBase
{
public:
    wxCredentialsConfigPanel(eap::config_method &cfg, wxWindow* parent);

protected:
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();
    virtual void OnAllowSave(wxCommandEvent& event);
    virtual void OnCredentialsSet(wxCommandEvent& event);
    virtual void OnCredentialsClear(wxCommandEvent& event);

protected:
    eap::config_method &m_cfg;  ///< EAP providers configuration
    winstd::library m_shell32;  ///< shell32.dll resource library reference
    wxIcon m_icon;              ///< Panel icon
};


///
/// Password credentials panel
///
class wxPasswordCredentialsPanel : public wxPasswordCredentialsPanelBase
{
public:
    wxPasswordCredentialsPanel(eap::config_pass &cfg, wxWindow* parent);

protected:
    virtual bool TransferDataToWindow();

protected:
    eap::config_pass &m_cfg;    ///< EAP providers configuration
    winstd::library m_shell32;  ///< shell32.dll resource library reference
    wxIcon m_icon;              ///< Panel icon
};


///
/// Helper function to launch modal dialogs with parent disabled
///
/// \param[in] dlg  Dialog to launch modal
///
/// \returns Dialog result code
///
inline int wxShowModal(wxDialog *dlg)
{
    // Temporary disable the parent for true native modal experience, then launch the dialog.
    wxWindow *parent = dlg->GetParent();
    parent->Enable(false);
    int result;
    __try {
        result = dlg->ShowModal();
    } __finally {
        parent->Enable(true);
    }

    return result;
}
