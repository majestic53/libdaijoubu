/**
 * libdaijoubu
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libdaijoubu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libdaijoubu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/daijoubu.h"
#include "../include/daijoubu_type.h"

namespace DAIJOUBU {

	#define UNICODE_RESOURCE_PATH "./res/unicode.txt"

	daijoubu_ptr daijoubu::m_instance = NULL;

	_daijoubu::_daijoubu(void) :
		m_factory_token(daijoubu_token_factory::acquire()),
		m_factory_uid(daijoubu_uid_factory::acquire()),
		m_unicode(daijoubu_unicode::acquire()),
		m_initialized(false)
	{
		std::atexit(daijoubu::_delete);
	}

	_daijoubu::~_daijoubu(void)
	{

		if(m_initialized) {
			uninitialize();
		}
	}

	void 
	_daijoubu::_delete(void)
	{

		if(daijoubu::m_instance) {
			delete daijoubu::m_instance;
			daijoubu::m_instance = NULL;
		}
	}

	daijoubu_ptr 
	_daijoubu::acquire(void)
	{

		if(!daijoubu::m_instance) {

			daijoubu::m_instance = new daijoubu;
			if(!daijoubu::m_instance) {
				THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_ALLOCATION);
			}
		}

		return daijoubu::m_instance;
	}

	daijoubu_token_factory_ptr 
	_daijoubu::acquire_token_factory(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_UNINITIALIZED);
		}

		return m_factory_token;
	}

	daijoubu_uid_factory_ptr 
	_daijoubu::acquire_uid_factory(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_UNINITIALIZED);
		}

		return m_factory_uid;
	}

	uint32_t 
	_daijoubu::exception_information(
		__out daijoubu_region_t &region,
		__out std::wstring &message
		)
	{		
		uint32_t result = 0;

		_last_exception(result, region, message);

		return result;
	}

	void 
	_daijoubu::initialize(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);

		if(m_initialized) {
			THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_INITIALIZED);
		}

		m_initialized = true;
		m_unicode->initialize(UNICODE_RESOURCE_PATH);
		m_factory_uid->initialize();
		m_factory_token->initialize();

		// TODO

	}

	bool 
	_daijoubu::is_allocated(void)
	{
		return (daijoubu::m_instance != NULL);
	}

	bool 
	_daijoubu::is_initialized(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);
		return m_initialized;
	}

	std::wstring 
	_daijoubu::to_string(
		__in_opt bool verbose
		)
	{
		std::wstringstream result;

		SERIALIZE_CALL_RECUR(m_lock);

		result << DAIJOUBU_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
			<< L"] (" << VALUE_AS_HEX(uintptr_t, this) << L")" 
			<< std::endl << m_unicode->to_string(verbose) 
			<< std::endl << m_factory_uid->to_string(verbose)
			<< std::endl << m_factory_token->to_string(verbose);

		return CHECK_STRING(result.str());
	}

	daijoubu_unicode_ptr 
	_daijoubu::unicode(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_UNINITIALIZED);
		}

		return m_unicode;
	}

	void 
	_daijoubu::uninitialize(void)
	{
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_DAIJOUBU_EXCEPTION(DAIJOUBU_EXCEPTION_UNINITIALIZED);
		}

		// TODO

		m_factory_token->uninitialize();
		m_factory_uid->uninitialize();
		m_unicode->uninitialize();
		m_initialized = false;
	}

	std::wstring 
	_daijoubu::version(void)
	{
		return VERSION_STRING;
	}
}
