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
// eap::peer_ttls_ui
//////////////////////////////////////////////////////////////////////

eap::peer_ttls_ui::peer_ttls_ui() : peer_ui<eap::config_ttls, int, int, int>()
{
}


DWORD eap::peer_ttls_ui::invoke_config_ui(
    _In_    HWND        hwndParent,
    _In_    DWORD       dwFlags,
    _Inout_ config_type &cfg,
    _Out_   EAP_ERROR   **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(ppEapError);

    // Initialize application.
    auto *app = new wxApp();
    wxEntryStart(g_module);

    // Create wxWidget-approved parent window. On heap, the wxWidget framework will call delete on it in wxEntryCleanup().
    auto *parent = new wxWindow();
    parent->SetHWND(hwndParent);
    app->SetTopWindow(parent);

    // Create and launch configuration dialog. On heap, the wxWidget framework will call delete on it in wxEntryCleanup().
    auto *dlg = new wxEAPConfig<config_ttls, wxEAPTTLSConfig>(cfg, parent);
    int result = wxShowModal(dlg);

    // Clean-up and return.
    wxEntryCleanup();
    return result == wxID_OK ? ERROR_SUCCESS : ERROR_CANCELLED;
}


DWORD eap::peer_ttls_ui::invoke_identity_ui(
            _In_    HWND          hwndParent,
            _In_    DWORD         dwFlags,
            _Inout_ config_type   &cfg,
            _Inout_ identity_type &usr,
            _Out_   LPWSTR        *ppwszIdentity,
            _Out_   EAP_ERROR     **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(cfg);
    UNREFERENCED_PARAMETER(usr);
    UNREFERENCED_PARAMETER(ppwszIdentity);
    UNREFERENCED_PARAMETER(ppEapError);

    InitCommonControls();
    MessageBox(hwndParent, _T(PRODUCT_NAME_STR) _T(" credential prompt goes here!"), _T(PRODUCT_NAME_STR) _T(" Credentials"), MB_OK);

    return ERROR_SUCCESS;
}


DWORD eap::peer_ttls_ui::invoke_interactive_ui(
            _In_        HWND                      hwndParent,
            _In_  const interactive_request_type  &req,
            _Out_       interactive_response_type &res,
            _Out_       EAP_ERROR                 **ppEapError)
{
    UNREFERENCED_PARAMETER(req);
    UNREFERENCED_PARAMETER(res);
    UNREFERENCED_PARAMETER(ppEapError);

    InitCommonControls();
    MessageBox(hwndParent, _T(PRODUCT_NAME_STR) _T(" interactive UI goes here!"), _T(PRODUCT_NAME_STR) _T(" Prompt"), MB_OK);

    return ERROR_SUCCESS;
}


//////////////////////////////////////////////////////////////////////
// wxEAPTTLSConfig
//////////////////////////////////////////////////////////////////////

wxEAPTTLSConfig::wxEAPTTLSConfig(eap::config_ttls &cfg, wxWindow* parent) :
    m_cfg(cfg),
    wxEAPTTLSConfigBase(parent)
{
    // Load and set icon.
    if (m_shell32.load(_T("shell32.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE)) {
        HICON icon;
        if (SUCCEEDED(LoadIconWithScaleDown(m_shell32, MAKEINTRESOURCE(265), GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), &icon))) {
            m_icon.CreateFromHICON(icon);
            m_outer_identity_icon->SetIcon(m_icon);
            Layout();
        }
    }

    // Populate identity controls.
    if (m_cfg.m_anonymous_identity.empty())
        m_outer_identity_same->SetValue(true);
    else if (m_cfg.m_anonymous_identity == L"@")
        m_outer_identity_empty->SetValue(true);
    else {
        m_outer_identity_custom->SetValue(true);
        m_outer_identity_custom_val->SetValue(m_cfg.m_anonymous_identity);
    }
}
