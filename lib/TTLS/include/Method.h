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

namespace eap
{
    ///
    /// EAP-TTLS method
    ///
    class method_ttls;
}

#pragma once

#include "Config.h"
#include "Credentials.h"

#include "../../TLS/include/Method.h"
#include "../../EAPBase/include/Method.h"


namespace eap
{
    class method_ttls : public method_tls
    {
    public:
        ///
        /// EAP-TTLS packet flags
        ///
        /// \sa [Extensible Authentication Protocol Tunneled Transport Layer Security Authenticated Protocol Version 0 (EAP-TTLSv0) (Chapter: 9.1 Packet Format)](https://tools.ietf.org/html/rfc5281#section-9.1)
        ///
        #pragma warning(suppress: 4480)
        enum flags_t : unsigned char {
            flags_length_incl = method_tls::flags_req_length_incl,  ///< Length included
            flags_more_frag   = method_tls::flags_req_more_frag,    ///< More fragments
            flags_start       = method_tls::flags_req_start,        ///< Start
            flags_ver_mask    = 0x07,                               ///< Version mask
        };

    public:
        ///
        /// Constructs an EAP method
        ///
        /// \param[in] mod   EAP module to use for global services
        /// \param[in] cfg   Connection configuration
        /// \param[in] cred  User credentials
        ///
        method_ttls(_In_ module &module, _In_ config_connection &cfg, _In_ credentials_ttls &cred);

        ///
        /// Moves an EAP method
        ///
        /// \param[in] other  EAP method to move from
        ///
        method_ttls(_Inout_ method_ttls &&other);

        ///
        /// Moves an EAP method
        ///
        /// \param[in] other  EAP method to move from
        ///
        /// \returns Reference to this object
        ///
        method_ttls& operator=(_Inout_ method_ttls &&other);

        /// \name Packet processing
        /// @{

        ///
        /// Processes a packet received by EapHost from a supplicant.
        ///
        /// \sa [EapPeerProcessRequestPacket function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363621.aspx)
        ///
        virtual void process_request_packet(
            _In_bytecount_(dwReceivedPacketSize) const EapPacket           *pReceivedPacket,
            _In_                                       DWORD               dwReceivedPacketSize,
            _Inout_                                    EapPeerMethodOutput *pEapOutput);

        ///
        /// Obtains a response packet from the EAP method.
        ///
        /// \sa [EapPeerGetResponsePacket function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363610.aspx)
        ///
        virtual void get_response_packet(
            _Inout_bytecap_(*dwSendPacketSize) EapPacket *pSendPacket,
            _Inout_                            DWORD     *pdwSendPacketSize);

        ///
        /// Obtains the result of an authentication session from the EAP method.
        ///
        /// \sa [EapPeerGetResult function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363611.aspx)
        ///
        virtual void get_result(
            _In_    EapPeerMethodResultReason reason,
            _Inout_ EapPeerMethodResult       *ppResult);

        /// @}

    protected:
#if EAP_TLS < EAP_TLS_SCHANNEL

        ///
        /// Generates master session key
        ///
        /// \sa [The EAP-TLS Authentication Protocol (Chapter 2.3. Key Hierarchy)](https://tools.ietf.org/html/rfc5216#section-2.3)
        ///
        virtual void derive_msk();

#else

        ///
        /// Processes an application message
        ///
        /// \param[in] msg       Application message data
        /// \param[in] size_msg  Application message data size
        ///
        virtual void process_application_data(_In_bytecount_(size_msg) const void *msg, _In_ size_t size_msg);

#endif

        ///
        /// Makes a PAP client message
        ///
        /// \sa [Extensible Authentication Protocol Tunneled Transport Layer Security Authenticated Protocol Version 0 (EAP-TTLSv0) (Chapter 11.2.5. PAP)](https://tools.ietf.org/html/rfc5281#section-11.2.5)
        ///
        /// \returns PAP client message
        ///
        sanitizing_blob make_pap_client() const;

    public:
        credentials_ttls &m_cred;           ///< TTLS credentials

        #pragma warning(suppress: 4480)
        enum version_t :unsigned char {
            version_0 = 0,                  ///< EAP-TTLS v0
        } m_version;                        ///< EAP-TTLS version
    };
}
