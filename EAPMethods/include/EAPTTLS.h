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
#include "EAPSerialize.h"
#include "EAPTLS.h"
#include "PAP.h"

#include <WinStd/Crypt.h>


namespace eap
{
    class config_ttls;
    class session_ttls;
    class peer_ttls;
}

namespace eapserial
{
    inline void pack(_Inout_ unsigned char *&cursor, _In_ const eap::config_ttls &val);
    inline size_t get_pk_size(const eap::config_ttls &val);
    inline void unpack(_Inout_ const unsigned char *&cursor, _Out_ eap::config_ttls &val);
}

#pragma once


namespace eap
{
    ///
    /// TTLS configuration
    ///
    class config_ttls : public config_tls
    {
    public:
        ///
        /// Constructs configuration
        ///
        /// \param[in] mod  Reference of the EAP module to use for global services
        ///
        config_ttls(_In_ module &mod);

        ///
        /// Moves configuration
        ///
        /// \param[in] other  Configuration to move from
        ///
        config_ttls(_Inout_ config_ttls &&other);

        ///
        /// Destructs configuration
        ///
        virtual ~config_ttls();

        ///
        /// Moves configuration
        ///
        /// \param[in] other  Configuration to move from
        ///
        /// \returns Reference to this object
        ///
        config_ttls& operator=(_Inout_ config_ttls &&other);

        /// \name XML configuration management
        /// @{

        ///
        /// Save configuration to XML document
        ///
        /// \param[in]  pDoc         XML document
        /// \param[in]  pConfigRoot  Suggested root element for saving configuration
        /// \param[out] ppEapError   Pointer to error descriptor in case of failure. Free using `module::free_error_memory()`.
        ///
        /// \returns
        /// - \c ERROR_SUCCESS if succeeded
        /// - error code otherwise
        ///
        virtual DWORD save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const;

        ///
        /// Load configuration from XML document
        ///
        /// \param[in]  pConfigRoot  Root element for loading configuration
        /// \param[out] ppEapError   Pointer to error descriptor in case of failure. Free using `module::free_error_memory()`.
        ///
        /// \returns
        /// - \c ERROR_SUCCESS if succeeded
        /// - error code otherwise
        ///
        virtual DWORD load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError);

        /// @}

        ///
        /// Returns EAP method type of this configuration
        ///
        /// \returns `eap::type_ttls`
        ///
        virtual eap::type_t get_method_id() { return eap::type_ttls; }

    protected:
        ///
        /// Copy constructor is private <= This class is non-copyable.
        ///
        config_ttls(_In_ const config_ttls &other);

        ///
        /// Copy operator is private <= This class is non-copyable.
        ///
        config_ttls& operator=(_In_ const config_ttls &other);

    public:
        config_method *m_inner;    ///< Inner authentication configuration
    };


    ///
    /// TTLS session
    ///
    class session_ttls : public session
    {
    public:
        ///
        /// Constructor
        ///
        session_ttls();
    };


    ///
    /// TTLS peer
    ///
    class peer_ttls : public peer
    {
    public:
        ///
        /// Constructor
        ///
        peer_ttls();

        ///
        /// Initializes an EAP peer method for EAPHost.
        ///
        /// \sa [EapPeerGetInfo function](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363613.aspx)
        ///
        virtual DWORD initialize(_Out_ EAP_ERROR **ppEapError);
    };
}


namespace eapserial
{
    ///
    /// Packs a TTLS based method configuration
    ///
    /// \param[inout] cursor  Memory cursor
    /// \param[in]    val     Configuration to pack
    ///
    inline void pack(_Inout_ unsigned char *&cursor, _In_ const eap::config_ttls &val)
    {
        pack(cursor, (const eap::config_tls&)val);
        if (val.m_inner) {
            if (dynamic_cast<eap::config_pap*>(val.m_inner)) {
                pack(cursor, (unsigned char)eap::type_pap);
                pack(cursor, (const eap::config_pap&)*val.m_inner);
            } else {
                assert(0); // Unsupported inner authentication method type.
                pack(cursor, (unsigned char)0);
            }
        } else
            pack(cursor, (unsigned char)0);
    }


    ///
    /// Returns packed size of a TTLS based method configuration
    ///
    /// \param[in] val  Configuration to pack
    ///
    /// \returns Size of data when packed (in bytes)
    ///
    inline size_t get_pk_size(const eap::config_ttls &val)
    {
        size_t size_inner = sizeof(unsigned char);
        if (val.m_inner) {
            if (dynamic_cast<eap::config_pap*>(val.m_inner))
                size_inner += get_pk_size((const eap::config_pap&)*val.m_inner);
            else
                assert(0); // Unsupported inner authentication method type.
        }

        return
            get_pk_size((const eap::config_tls&)val) +
            size_inner;
    }


    ///
    /// Unpacks a TTLS based method configuration
    ///
    /// \param[inout] cursor  Memory cursor
    /// \param[out]   val     Configuration to unpack to
    ///
    inline void unpack(_Inout_ const unsigned char *&cursor, _Out_ eap::config_ttls &val)
    {
        unpack(cursor, (eap::config_tls&)val);

        assert(!val.m_inner);
        unsigned char eap_type;
        unpack(cursor, eap_type);
        switch (eap_type) {
            case eap::type_pap:
                val.m_inner = new eap::config_pap(val.m_module);
                unpack(cursor, (eap::config_pap&)*val.m_inner);
                break;
            case 0           : break;
            default          : assert(0); // Unsupported inner authentication method type.
        }
    }
}
