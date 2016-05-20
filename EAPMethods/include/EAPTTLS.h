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

#include "EAPMethods.h"

namespace eap
{
    class session_ttls;
    class peer_ttls;
    class peer_ttls_ui;
}

#pragma once


namespace eap
{
    class session_ttls : public session
    {
    public:
        ///
        /// Constructor
        ///
        session_ttls();
    };


    class peer_ttls : public peer
    {
    };


    class peer_ttls_ui : public peer_ui
    {
    public:
        ///
        /// Constructor
        ///
        peer_ttls_ui();

        ///
        /// Raises the EAP method's specific connection configuration user interface dialog on the client.
        ///
        /// \sa [EapPeerInvokeConfigUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363614.aspx)
        ///
        virtual DWORD invoke_config_ui(
            _In_                                     HWND            hwndParent,
            _In_                                     DWORD           dwFlags,
            _In_                                     DWORD           dwConnectionDataInSize,
            _In_count_(dwConnectionDataInSize) const BYTE            *pConnectionDataIn,
            _Out_                                    DWORD           *pdwConnectionDataOutSize,
            _Out_                                    BYTE            **ppConnectionDataOut,
            _Out_                                    EAP_ERROR       **ppEapError);

        ///
        /// Raises a custom interactive user interface dialog to obtain user identity information for the EAP method on the client.
        ///
        /// \sa [EapPeerInvokeIdentityUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363615.aspx)
        ///
        virtual DWORD invoke_identity_ui(
            _In_                                   DWORD           dwFlags,
            _In_                                   HWND            hwndParent,
            _In_                                   DWORD           dwConnectionDataSize,
            _In_count_(dwConnectionDataSize) const BYTE            *pConnectionData,
            _In_                                   DWORD           dwUserDataSize,
            _In_count_(dwUserDataSize)       const BYTE            *pUserData,
            _Out_                                  DWORD           *pdwUserDataOutSize,
            _Out_                                  BYTE            **ppUserDataOut,
            _Out_                                  LPWSTR          *ppwszIdentity,
            _Out_                                  EAP_ERROR       **ppEapError);

        ///
        /// Raises a custom interactive user interface dialog for the EAP method on the client.
        ///
        /// \sa [EapPeerInvokeInteractiveUI function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363616.aspx)
        ///
        virtual DWORD invoke_interactive_ui(
            _In_                                  HWND            hwndParent,
            _In_                                  DWORD           dwUIContextDataSize,
            _In_count_(dwUIContextDataSize) const BYTE            *pUIContextData,
            _Out_                                 DWORD           *pdwDataFromInteractiveUISize,
            _Out_                                 BYTE            **ppDataFromInteractiveUI,
            _Out_                                 EAP_ERROR       **ppEapError);
    };
}
