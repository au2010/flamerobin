// Service class implementation

/* (C) Copyright 2000-2006 T.I.P. Group S.A. and the IBPP Team (www.ibpp.org)

    The contents of this file are subject to the IBPP License (the "License");
    you may not use this file except in compliance with the License.  You may
    obtain a copy of the License at http://www.ibpp.org or in the 'license.txt'
    file which must have been distributed along with this file.

    This software, distributed under the License, is distributed on an "AS IS"
    basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See the
    License for the specific language governing rights and limitations
    under the License.
*/


#ifdef _MSC_VER
#pragma warning(disable: 4786 4996)
#ifndef _DEBUG
#pragma warning(disable: 4702)
#endif
#endif

#include "_ibpp.h"

#ifdef HAS_HDRSTOP
#pragma hdrstop
#endif

using namespace ibpp_internals;

#ifdef IBPP_UNIX
#include <unistd.h>
#define Sleep(x) usleep(x)
#endif

#include <regex>

//	(((((((( OBJECT INTERFACE IMPLEMENTATION ))))))))

void ServiceImpl::Connect()
{
	if (mHandle	!= 0) return;	// Already connected

	// Attach to the Service Manager
	IBS status;
	SPB spb;
	std::string connect;

	// Build a SPB based on	the properties
	spb.Insert(isc_spb_version);
	spb.Insert(isc_spb_current_version);
	if (!mUserName.empty())
	{
		spb.InsertString(isc_spb_user_name, 1, mUserName.c_str());
		spb.InsertString(isc_spb_password, 1, mUserPassword.c_str());
	}
	else
		spb.InsertString(isc_spb_trusted_auth, 1, "");

	if (! mServerName.empty())
	{
		connect = mServerName;
		connect += ":";
	}

	connect += "service_mgr";

	(*getGDS().Call()->m_service_attach)(status.Self(), (short)connect.size(), (char*)connect.c_str(),
		&mHandle, spb.Size(), spb.Self());
	if (status.Errors())
	{
		mHandle	= 0;		// Should be, but better be sure...
		throw SQLExceptionImpl(status, "Service::Connect", _("isc_service_attach failed"));
	}


    std::string version;
    GetVersion(version);

    std::smatch m;

    if (std::regex_search(version, m, std::regex("\\d+.\\d+.\\d+.\\d+"))) {
        version = m[0];
        
        const std::regex re{ "((?:[^\\\\.]|\\\\.)+)(?:.|$)" };

        const std::vector<std::string> m_vecFields{ std::sregex_token_iterator(cbegin(version), 
            cend(version), re, 1), std::sregex_token_iterator() 
        };
        if (m_vecFields.size() == 4) {

            std::string str = m_vecFields[0];
            major_ver = atoi(str.c_str());

            str = m_vecFields[1];
            minor_ver = atoi(str.c_str());

            str = m_vecFields[2];
            rev_no = atoi(str.c_str());

            str = m_vecFields[3];
            build_no = atoi(str.c_str());
        }
    }


}

void ServiceImpl::Disconnect()
{
	if (mHandle	== 0) return; // Already disconnected
	
	IBS status;

	// Detach from the service manager
	(*getGDS().Call()->m_service_detach)(status.Self(), &mHandle);

	// Set mHandle to 0 now, just in case we need to throw, because Disconnect()
	// is called from Service destructor and we want to maintain a coherent state.
	mHandle	= 0;
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Disconnect", _("isc_service_detach failed"));
}

void ServiceImpl::GetVersion(std::string& version)
{
	// Based on a patch provided by Torsten Martinsen (SourceForge 'bullestock')

	if (mHandle == 0)
		throw LogicExceptionImpl("Service::GetVersion", _("Service is not connected."));

	IBS status;
	SPB spb;
	RB result(250);

	spb.Insert(isc_info_svc_server_version);

	(*getGDS().Call()->m_service_query)(status.Self(), &mHandle, 0, 0, 0, spb.Size(), spb.Self(),
		result.Size(), result.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::GetVersion", _("isc_service_query failed"));

	result.GetString(isc_info_svc_server_version, version);
}

bool ibpp_internals::ServiceImpl::versionIsHigherOrEqualTo(int versionMajor, int versionMinor)
{
    return major_ver > versionMajor
        || (major_ver == versionMajor && minor_ver >= versionMinor);
}

void ServiceImpl::AddUser(const IBPP::User& user)
{
	if (mHandle == 0)
		throw LogicExceptionImpl("Service::AddUser", _("Service is not connected."));
	if (user.username.empty())
		throw LogicExceptionImpl("Service::AddUser", _("Username required."));
	if (user.password.empty())
		throw LogicExceptionImpl("Service::AddUser", _("Password required."));

	IBS status;
	SPB spb;
	spb.Insert(isc_action_svc_add_user);
	spb.InsertString(isc_spb_sec_username, 2, user.username.c_str());
	spb.InsertString(isc_spb_sec_password, 2, user.password.c_str());
	if (! user.firstname.empty())
			spb.InsertString(isc_spb_sec_firstname, 2, user.firstname.c_str());
	if (! user.middlename.empty())
			spb.InsertString(isc_spb_sec_middlename, 2, user.middlename.c_str());
	if (! user.lastname.empty())
			spb.InsertString(isc_spb_sec_lastname, 2, user.lastname.c_str());
	if (user.userid != 0)
			spb.InsertQuad(isc_spb_sec_userid, (int32_t)user.userid);
	if (user.groupid != 0)
			spb.InsertQuad(isc_spb_sec_groupid, (int32_t)user.groupid);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::AddUser", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::ModifyUser(const IBPP::User& user)
{
	if (mHandle == 0)
		throw LogicExceptionImpl("Service::ModifyUser", _("Service is not connected."));
	if (user.username.empty())
		throw LogicExceptionImpl("Service::ModifyUser", _("Username required."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_modify_user);
	spb.InsertString(isc_spb_sec_username, 2, user.username.c_str());
	if (! user.password.empty())
			spb.InsertString(isc_spb_sec_password, 2, user.password.c_str());
	if (! user.firstname.empty())
			spb.InsertString(isc_spb_sec_firstname, 2, user.firstname.c_str());
	if (! user.middlename.empty())
			spb.InsertString(isc_spb_sec_middlename, 2, user.middlename.c_str());
	if (! user.lastname.empty())
			spb.InsertString(isc_spb_sec_lastname, 2, user.lastname.c_str());
	if (user.userid != 0)
			spb.InsertQuad(isc_spb_sec_userid, (int32_t)user.userid);
	if (user.groupid != 0)
			spb.InsertQuad(isc_spb_sec_groupid, (int32_t)user.groupid);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::ModifyUser", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::RemoveUser(const std::string& username)
{

	if (mHandle == 0)
		throw LogicExceptionImpl("Service::RemoveUser", _("Service is not connected."));
	if (username.empty())
		throw LogicExceptionImpl("Service::RemoveUser", _("Username required."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_delete_user);
	spb.InsertString(isc_spb_sec_username, 2, username.c_str());

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::RemoveUser", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::GetUser(IBPP::User& user)
{
	if (mHandle == 0)
		throw LogicExceptionImpl("Service::GetUser", _("Service is not connected."));
	if (user.username.empty())
		throw LogicExceptionImpl("Service::GetUser", _("Username required."));

	SPB spb;
	spb.Insert(isc_action_svc_display_user);
	spb.InsertString(isc_spb_sec_username, 2, user.username.c_str());

	IBS status;
	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::GetUser", _("isc_service_start failed"));

	RB result(8000);
	char request[] = {isc_info_svc_get_users};
	status.Reset();
	(*getGDS().Call()->m_service_query)(status.Self(), &mHandle, 0, 0, 0,
		sizeof(request), request, result.Size(), result.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::GetUser", _("isc_service_query failed"));

	char* p = result.Self();
	if (*p != isc_info_svc_get_users)
		throw SQLExceptionImpl(status, "Service::GetUser", _("isc_service_query returned unexpected answer"));

	p += 3;	// Skips the 'isc_info_svc_get_users' and its total length
	user.clear();
	while (*p != isc_info_end)
	{
		if (*p == isc_spb_sec_userid)
		{
			user.userid = (uint32_t)(*getGDS().Call()->m_vax_integer)(p+1, 4);
			p += 5;
		}
		else if (*p == isc_spb_sec_groupid)
		{
			user.groupid = (uint32_t)(*getGDS().Call()->m_vax_integer)(p+1, 4);
			p += 5;
		}
		else
		{
			unsigned short len = (unsigned short)(*getGDS().Call()->m_vax_integer)(p+1, 2);
			switch (*p)
			{
			case isc_spb_sec_username :
				// For each user, this is the first element returned
				if (len != 0) user.username.assign(p+3, len);
				break;
			case isc_spb_sec_password :
				if (len != 0) user.password.assign(p+3, len);
				break;
			case isc_spb_sec_firstname :
				if (len != 0) user.firstname.assign(p+3, len);
				break;
			case isc_spb_sec_middlename :
				if (len != 0) user.middlename.assign(p+3, len);
				break;
			case isc_spb_sec_lastname :
				if (len != 0) user.lastname.assign(p+3, len);
				break;
			}
			p += (3 + len);
		}
	}
}

void ServiceImpl::GetUsers(std::vector<IBPP::User>& users)
{
	if (mHandle == 0)
		throw LogicExceptionImpl("Service::GetUsers", _("Service is not connected."));

	SPB spb;
	spb.Insert(isc_action_svc_display_user);

	IBS status;
	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::GetUsers", _("isc_service_start failed"));

	RB result(0xFFFF);
	char request[] = {isc_info_svc_get_users};
	status.Reset();
	(*getGDS().Call()->m_service_query)(status.Self(), &mHandle, 0, 0, 0,
		sizeof(request), request, result.Size(), result.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::GetUsers", _("isc_service_query failed"));

	users.clear();
	char* p = result.Self();
	if (*p != isc_info_svc_get_users)
		throw SQLExceptionImpl(status, "Service::GetUsers", _("isc_service_query returned unexpected answer"));

	char* pEnd = p + (unsigned short)(*getGDS().Call()->m_vax_integer)(p+1, 2);
	p += 3;	// Skips the 'isc_info_svc_get_users' and its total length
	IBPP::User user;
	while (p < pEnd && *p != isc_info_end)
	{
		if (*p == isc_spb_sec_userid)
		{
			user.userid = (uint32_t)(*getGDS().Call()->m_vax_integer)(p+1, 4);
			p += 5;
		}
		else if (*p == isc_spb_sec_groupid)
		{
			user.groupid = (uint32_t)(*getGDS().Call()->m_vax_integer)(p+1, 4);
			p += 5;
		}
		else
		{
			unsigned short len = (unsigned short)(*getGDS().Call()->m_vax_integer)(p+1, 2);
			switch (*p)
			{
			case isc_spb_sec_username :
				// For each user, this is the first element returned
				if (! user.username.empty()) users.push_back(user);	// Flush previous user
				user.clear();
				if (len != 0) user.username.assign(p+3, len);
				break;
			case isc_spb_sec_password :
				if (len != 0) user.password.assign(p+3, len);
				break;
			case isc_spb_sec_firstname :
				if (len != 0) user.firstname.assign(p+3, len);
				break;
			case isc_spb_sec_middlename :
				if (len != 0) user.middlename.assign(p+3, len);
				break;
			case isc_spb_sec_lastname :
				if (len != 0) user.lastname.assign(p+3, len);
				break;
			}
			p += (3 + len);
		}
	}
	if (! user.username.empty()) users.push_back(user);	// Flush last user
}

void ServiceImpl::SetPageBuffers(const std::string& dbfile, int buffers)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::SetPageBuffers", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::SetPageBuffers", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	spb.InsertQuad(isc_spb_prp_page_buffers, buffers);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::SetPageBuffers", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::SetSweepInterval(const std::string& dbfile, int sweep)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::SetSweepInterval", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::SetSweepInterval", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	spb.InsertQuad(isc_spb_prp_sweep_interval, sweep);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::SetSweepInterval", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::SetSyncWrite(const std::string& dbfile, bool sync)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::SetSyncWrite", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::SetSyncWrite", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	if (sync) spb.InsertByte(isc_spb_prp_write_mode, (char)isc_spb_prp_wm_sync);
	else spb.InsertByte(isc_spb_prp_write_mode, (char)isc_spb_prp_wm_async);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::SetSyncWrite", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::SetReadOnly(const std::string& dbfile, bool readonly)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::SetReadOnly", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::SetReadOnly", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	if (readonly) spb.InsertByte(isc_spb_prp_access_mode, (char)isc_spb_prp_am_readonly);
	else spb.InsertByte(isc_spb_prp_access_mode, (char)isc_spb_prp_am_readwrite);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::SetReadOnly", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::SetReserveSpace(const std::string& dbfile, bool reserve)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::SetReserveSpace", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::SetReserveSpace", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	if (reserve) spb.InsertByte(isc_spb_prp_reserve_space, (char)isc_spb_prp_res);
	else spb.InsertByte(isc_spb_prp_reserve_space, (char)isc_spb_prp_res_use_full);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::SetReserveSpace", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::Shutdown(const std::string& dbfile, IBPP::DSM flags, int sectimeout)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Shutdown", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Shutdown", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
    
	
    // Shutdown mode
    //if (flags & IBPP::dsCache) spb.InsertQuad(isc_spb_prp, sectimeout)
    if (flags & IBPP::dsDenyTrans) 
        spb.InsertQuad(isc_spb_prp_deny_new_transactions, sectimeout);
    if (flags & IBPP::dsDenyAttach) 
        spb.InsertQuad(isc_spb_prp_deny_new_attachments, sectimeout);
    if (flags & IBPP::dsForce) 
        spb.InsertQuad(isc_spb_prp_force_shutdown, sectimeout);

    // Database Mode
    if (flags & IBPP::dsNormal) 
        spb.InsertByte(isc_spb_prp_shutdown_mode, isc_spb_prp_sm_normal);
    if (flags & IBPP::dsSingle) 
        spb.InsertByte(isc_spb_prp_shutdown_mode, isc_spb_prp_sm_single);
    if (flags & IBPP::dsMulti) 
        spb.InsertByte(isc_spb_prp_shutdown_mode, isc_spb_prp_sm_multi);
    if (flags & IBPP::dsFull) 
        spb.InsertByte(isc_spb_prp_shutdown_mode, isc_spb_prp_sm_full);


	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Shutdown", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::Restart(const std::string& dbfile, IBPP::DSM flags )
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Restart", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Restart", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_properties);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	spb.InsertQuad(isc_spb_options, isc_spb_prp_db_online);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Restart", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::Sweep(const std::string& dbfile)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Sweep", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Sweep", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_repair);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	spb.InsertQuad(isc_spb_options, isc_spb_rpr_sweep_db);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Sweep", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::Repair(const std::string& dbfile, IBPP::RPF flags)
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Repair", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Repair", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_repair);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());

	unsigned int mask;
	if (flags & IBPP::rpValidateFull) mask = (isc_spb_rpr_full | isc_spb_rpr_validate_db);
	else if (flags & IBPP::rpValidatePages) mask = isc_spb_rpr_validate_db;
	else if (flags & IBPP::rpMendRecords) mask = isc_spb_rpr_mend_db;
	else throw LogicExceptionImpl("Service::Repair",
		_("One of rpMendRecords, rpValidatePages, rpValidateFull is required."));

	if (flags & IBPP::rpReadOnly)			mask |= isc_spb_rpr_check_db;
	if (flags & IBPP::rpIgnoreChecksums)	mask |= isc_spb_rpr_ignore_checksum;
	if (flags & IBPP::rpKillShadows)		mask |= isc_spb_rpr_kill_shadows;
	
	spb.InsertQuad(isc_spb_options, mask);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Repair", _("isc_service_start failed"));

	Wait();
}

void ServiceImpl::StartBackup(
    const std::string& dbfile,	const std::string& bkfile, const std::string& outfile,
    const int factor, IBPP::BRF flags,
    const std::string& cryptName, const std::string& keyHolder, const std::string& keyName,
    const std::string& skipData, const std::string& includeData, const int verboseInteval,
    const int parallelWorkers
    )
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Backup", _("Service is not connected."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Backup", _("Main database file must be specified."));
	if (bkfile.empty())
		throw LogicExceptionImpl("Service::Backup", _("Backup file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_backup);
	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());
	spb.InsertString(isc_spb_bkp_file, 2, bkfile.c_str());

    if (versionIsHigherOrEqualTo(3, 0)) {
        if ((flags & IBPP::brVerbose) && (verboseInteval == 0)) 
            spb.Insert(isc_spb_verbose);
        if (verboseInteval > 0) 
            spb.InsertQuad(isc_spb_verbint, verboseInteval);
    }else
        if (flags & IBPP::brVerbose) 
            spb.Insert(isc_spb_verbose);

    if (factor > 0) 
        spb.InsertQuad(isc_spb_bkp_factor, factor);

    if (!skipData.empty() && versionIsHigherOrEqualTo(3, 0)) 
        spb.InsertString(isc_spb_bkp_skip_data, 2, skipData.c_str());
    if (!includeData.empty() && versionIsHigherOrEqualTo(4, 0)) 
        spb.InsertString(isc_spb_bkp_include_data, 2, includeData.c_str());

    if (parallelWorkers > 0 && versionIsHigherOrEqualTo(3, 0))
        spb.InsertQuad(isc_spb_bkp_parallel_workers, parallelWorkers);

    if (versionIsHigherOrEqualTo(4, 0)) {
        if (!cryptName.empty()) 
            spb.InsertString(isc_spb_bkp_crypt, 2, cryptName.c_str());
        if (!keyHolder.empty()) 
            spb.InsertString(isc_spb_bkp_keyholder, 2, keyHolder.c_str());
        if (!keyName.empty()) 
            spb.InsertString(isc_spb_bkp_keyname, 2, keyName.c_str());
    }

	unsigned int mask = 0;
    if (flags & IBPP::brConvertExtTables)	mask |= isc_spb_bkp_convert;
    if (flags & IBPP::brExpand)             mask |= isc_spb_bkp_expand;
    if (flags & IBPP::brNoGarbageCollect)	mask |= isc_spb_bkp_no_garbage_collect;
    if (flags & IBPP::brIgnoreChecksums)	mask |= isc_spb_bkp_ignore_checksums;
	if (flags & IBPP::brIgnoreLimbo)		mask |= isc_spb_bkp_ignore_limbo;
    if (flags & IBPP::brNonTransportable)	mask |= isc_spb_bkp_non_transportable;
    if (flags & IBPP::brOldDescriptions)	mask |= isc_spb_bkp_old_descriptions;

    if (versionIsHigherOrEqualTo(2, 5)) {
        if (flags & IBPP::brNoDBTriggers)   mask |= isc_spb_bkp_no_triggers;
        if (flags & IBPP::brMetadataOnly)   mask |= isc_spb_bkp_metadata_only;
    }

    if ((flags & IBPP::brZip) && versionIsHigherOrEqualTo(4, 0))    mask |= isc_spb_bkp_zip;

    if (versionIsHigherOrEqualTo(2, 5)) {
        std::string stFlags = "";

        if (flags & IBPP::brstatistics_time)        stFlags += "T";
        if (flags & IBPP::brstatistics_delta)       stFlags += "D";
        if (flags & IBPP::brstatistics_pagereads)   stFlags += "R";
        if (flags & IBPP::brstatistics_pagewrites)  stFlags += "W";

        if(!stFlags.empty())
            spb.InsertString(isc_spb_bkp_stat, 2, stFlags.c_str());
    }


	if (mask != 0) spb.InsertQuad(isc_spb_options, mask);


	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Backup", _("isc_service_start failed"));
}

void ServiceImpl::StartRestore(
    const std::string& bkfile, const std::string& dbfile, const std::string& outfile,
    int pagesize, int buffers, IBPP::BRF flags,
    const std::string& cryptName, const std::string& keyHolder, const std::string& keyName,
    const std::string& skipData, const std::string& includeData, const int verboseInteval,
    const int parallelWorkers
    )
{
	if (mHandle	== 0)
		throw LogicExceptionImpl("Service::Restore", _("Service is not connected."));
	if (bkfile.empty())
		throw LogicExceptionImpl("Service::Restore", _("Backup file must be specified."));
	if (dbfile.empty())
		throw LogicExceptionImpl("Service::Restore", _("Main database file must be specified."));

	IBS status;
	SPB spb;

	spb.Insert(isc_action_svc_restore);
	spb.InsertString(isc_spb_bkp_file, 2, bkfile.c_str());	spb.InsertString(isc_spb_dbname, 2, dbfile.c_str());

    if (versionIsHigherOrEqualTo(3, 0)) {
        if ((flags & IBPP::brVerbose) && (verboseInteval == 0)) 
            spb.Insert(isc_spb_verbose);
        if (verboseInteval > 0) 
            spb.InsertQuad(isc_spb_verbint, verboseInteval);
    }
    else
        if (flags & IBPP::brVerbose) 
            spb.Insert(isc_spb_verbose);

	if (pagesize >	0) 
        spb.InsertQuad(isc_spb_res_page_size, pagesize);
    if (buffers > 0) 
        spb.InsertQuad(isc_spb_res_buffers, buffers);

    if (parallelWorkers > 0 && versionIsHigherOrEqualTo(3, 0))
        spb.InsertQuad(isc_spb_bkp_parallel_workers, parallelWorkers);

    if (!skipData.empty() && versionIsHigherOrEqualTo(3, 0)) 
        spb.InsertString(isc_spb_res_skip_data, 2, skipData.c_str());
    if (!includeData.empty() && versionIsHigherOrEqualTo(4, 0)) 
        spb.InsertString(isc_spb_res_include_data, 2, includeData.c_str());

    if (versionIsHigherOrEqualTo(4, 0)) {
        if (!cryptName.empty()) 
            spb.InsertString(isc_spb_res_crypt, 2, cryptName.c_str());
        if (!keyHolder.empty()) 
            spb.InsertString(isc_spb_res_keyholder, 2, keyHolder.c_str());
        if (!keyName.empty()) 
            spb.InsertString(isc_spb_res_keyname, 2, keyName.c_str());
    }

    spb.InsertByte(isc_spb_res_access_mode, (flags & IBPP::brDatabase_readonly) ? isc_spb_res_am_readonly : isc_spb_res_am_readwrite);
    

    if (versionIsHigherOrEqualTo(4, 0)) {
        if (flags & IBPP::brReplicaMode_none)
            spb.InsertByte(isc_spb_res_replica_mode, isc_spb_res_rm_none);
        if (flags & IBPP::brReplicaMode_readonly)
            spb.InsertByte(isc_spb_res_replica_mode, isc_spb_res_rm_readonly);
        if (flags & IBPP::brReplicaMode_readwrite)
            spb.InsertByte(isc_spb_res_replica_mode, isc_spb_res_rm_readwrite);
    }

    unsigned int mask = (flags & IBPP::brReplace) ? isc_spb_res_replace : isc_spb_res_create;	// Safe default mode

    if (flags & IBPP::brDeactivateIdx)	    mask |= isc_spb_res_deactivate_idx;
	if (flags & IBPP::brNoShadow)		    mask |= isc_spb_res_no_shadow;
	if (flags & IBPP::brNoValidity)		    mask |= isc_spb_res_no_validity;
	if (flags & IBPP::brPerTableCommit)	    mask |= isc_spb_res_one_at_a_time;
	if (flags & IBPP::brUseAllSpace)	    mask |= isc_spb_res_use_all_space;

    if (versionIsHigherOrEqualTo(2, 5)) {
        if (flags & IBPP::brMetadataOnly)		
            mask |= isc_spb_res_metadata_only;
        if (flags & IBPP::brFix_Fss_Data)
            spb.InsertString(isc_spb_res_fix_fss_data, 2, mCharSet.c_str());
        if (flags & IBPP::brFix_Fss_Metadata)
            spb.InsertString(isc_spb_res_fix_fss_metadata, 2, mCharSet.c_str());

        std::string stFlags = "";

        if (flags & IBPP::brstatistics_time)        stFlags += "T";
        if (flags & IBPP::brstatistics_delta)       stFlags += "D";
        if (flags & IBPP::brstatistics_pagereads)   stFlags += "R";
        if (flags & IBPP::brstatistics_pagewrites)  stFlags += "W";

        if (!stFlags.empty())
            spb.InsertString(isc_spb_bkp_stat, 2, stFlags.c_str());

    }
    
    if (mask != 0) 
        spb.InsertQuad(isc_spb_options, mask);

	(*getGDS().Call()->m_service_start)(status.Self(), &mHandle, 0, spb.Size(), spb.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "Service::Restore", _("isc_service_start failed"));
}

const char* ServiceImpl::WaitMsg()
{
	IBS status;
	SPB req;
	RB result(1024);

	req.Insert(isc_info_svc_line);	// Request one line of textual output

	// _service_query will only block until a line of result is available
	// (or until the end of the task if it does not report information)
	(*getGDS().Call()->m_service_query)(status.Self(), &mHandle, 0, 0, 0,
		req.Size(),	req.Self(),	result.Size(), result.Self());
	if (status.Errors())
		throw SQLExceptionImpl(status, "ServiceImpl::Wait", _("isc_service_query failed"));

	// If message length is	zero bytes,	task is	finished
	if (result.GetString(isc_info_svc_line,	mWaitMessage) == 0) return 0;

	// Task	is not finished, but we	have something to report
	return mWaitMessage.c_str();
}

void ServiceImpl::Wait()
{
	IBS status;
	SPB spb;
	RB result(1024);
	std::string msg;

	spb.Insert(isc_info_svc_line);
	for (;;)
	{
		// Sleeps 1 millisecond upfront. This will release the remaining
		// timeslot of the thread. Doing so will give a good chance for small
		// services tasks to finish before we check if they are still running.
		// The deal is to limit (in that particular case) the number of loops
		// polling _service_query that will happen.

		Sleep(1);

		// _service_query will only block until a line of result is available
		// (or until the end of the task if it does not report information) 
		(*getGDS().Call()->m_service_query)(status.Self(), &mHandle, 0, 0,	0,
			spb.Size(),	spb.Self(),	result.Size(), result.Self());
		if (status.Errors())
			throw SQLExceptionImpl(status, "ServiceImpl::Wait", _("isc_service_query failed"));

		// If message length is	zero bytes,	task is	finished
		if (result.GetString(isc_info_svc_line,	msg) ==	0) return;

		status.Reset();
		result.Reset();
	}
}

IBPP::IService* ServiceImpl::AddRef()
{
	ASSERTION(mRefCount >= 0);
	++mRefCount;
	return this;
}

void ServiceImpl::Release()
{
	// Release cannot throw, except in DEBUG builds on assertion
	ASSERTION(mRefCount >= 0);
	--mRefCount;
	try { if (mRefCount <= 0) delete this; }
		catch (...) { }
}

//	(((((((( OBJECT INTERNAL METHODS ))))))))

void ServiceImpl::SetServerName(const char* newName)
{
	if (newName == 0) mServerName.erase();
	else mServerName = newName;
}

void ServiceImpl::SetUserName(const char* newName)
{
	if (newName == 0) mUserName.erase();
	else mUserName = newName;
}

void ServiceImpl::SetUserPassword(const char* newPassword)
{
	if (newPassword == 0) mUserPassword.erase();
	else mUserPassword = newPassword;
}

void ibpp_internals::ServiceImpl::SetCharSet(const char* newCharset)
{
    if (newCharset == 0) 
        mCharSet.erase();
    else 
        mCharSet = newCharset;
}

void ibpp_internals::ServiceImpl::SetRoleName(const char* newRoleName)
{
    if (newRoleName == 0)
        mRoleName.erase();
    else
        mRoleName = newRoleName;
}

ServiceImpl::ServiceImpl(const std::string& ServerName,
			const std::string& UserName, const std::string& UserPassword, 
            const std::string& RoleName, const std::string& CharSet)
	:	mRefCount(0), mHandle(0),
		mServerName(ServerName), mUserName(UserName), mUserPassword(UserPassword),
        mRoleName(RoleName), mCharSet(CharSet)
{
}

ServiceImpl::~ServiceImpl()
{
	try { if (Connected()) Disconnect(); }
		catch (...) { }
}
