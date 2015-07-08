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
#include "../include/daijoubu_uid_type.h"

namespace DAIJOUBU {

	namespace COMPONENT {

		#define UID_REFERENCE_INIT 1

		daijoubu_uid_ptr daijoubu_uid::m_instance = NULL;

		_daijoubu_uid::_daijoubu_uid(void) :
			m_initialized(false)
		{
			std::atexit(daijoubu_uid::_delete);
		}

		_daijoubu_uid::~_daijoubu_uid(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_daijoubu_uid::_delete(void)
		{

			if(daijoubu_uid::m_instance) {
				delete daijoubu_uid::m_instance;
				daijoubu_uid::m_instance = NULL;
			}
		}

		daijoubu_uid_ptr 
		_daijoubu_uid::acquire(void)
		{

			if(!daijoubu_uid::m_instance) {

				daijoubu_uid::m_instance = new daijoubu_uid;
				if(!daijoubu_uid::m_instance) {
					THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_ALLOCATION);
				}
			}

			return daijoubu_uid::m_instance;
		}

		void 
		_daijoubu_uid::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			m_uid_map.clear();
			m_uid_next = 0;
			m_uid_surplus.clear();
		}

		bool 
		_daijoubu_uid::contains(
			__in daijoubu_uid_t uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return (m_uid_map.find(uid) != m_uid_map.end());
		}

		size_t 
		_daijoubu_uid::decrement_reference(
			__in daijoubu_uid_t uid
			)
		{
			size_t result;
			std::map<daijoubu_uid_t, size_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			iter = find(uid);

			result = --(iter->second);
			if(!result) {
				m_uid_surplus.insert(iter->first);
				m_uid_map.erase(iter);
			}

			return result;
		}

		std::map<daijoubu_uid_t, size_t>::iterator 
		_daijoubu_uid::find(
			__in daijoubu_uid_t uid
			)
		{
			std::map<daijoubu_uid_t, size_t>::iterator result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			result = m_uid_map.find(uid);
			if(result == m_uid_map.end()) {
				THROW_DAIJOUBU_UID_EXCEPTION_MESSAGE(DAIJOUBU_UID_EXCEPTION_NOT_FOUND,
					L"0x%x", uid);
			}

			return result;
		}

		daijoubu_uid_t 
		_daijoubu_uid::generate(void)
		{
			daijoubu_uid_t result;
			std::set<daijoubu_uid_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			if(m_uid_next < INVALID_UID) {
				result = m_uid_next++;
			} else if(!m_uid_surplus.empty()) {
				iter = m_uid_surplus.begin();
				result = *iter;
				m_uid_surplus.erase(iter);
			} else {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_RESOURCES);
			}

			m_uid_map.insert(std::pair<daijoubu_uid_t, size_t>(result, UID_REFERENCE_INIT));

			return result;
		}

		size_t 
		_daijoubu_uid::increment_reference(
			__in daijoubu_uid_t uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return ++find(uid)->second;
		}

		void 
		_daijoubu_uid::initialize(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_INITIALIZED);
			}

			m_uid_map.clear();
			m_uid_next = 0;
			m_uid_surplus.clear();
			m_initialized = true;
		}

		bool 
		_daijoubu_uid::is_allocated(void)
		{
			return (daijoubu_uid::m_instance != NULL);
		}

		bool 
		_daijoubu_uid::is_initialized(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_initialized;
		}

		size_t 
		_daijoubu_uid::reference_count(
			__in daijoubu_uid_t uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return find(uid)->second;
		}

		size_t 
		_daijoubu_uid::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return m_uid_map.size();
		}

		std::wstring 
		_daijoubu_uid::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::map<daijoubu_uid_t, size_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			result << DAIJOUBU_UID_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
				<< L"] (" << VALUE_AS_HEX(uintptr_t, this) << L"), COUNT: " << m_uid_map.size();

			if(verbose) {

				for(iter = m_uid_map.begin(); iter != m_uid_map.end(); ++iter) {
					result << std::endl << L"{" << VALUE_AS_HEX(daijoubu_uid_t, iter->first) 
						<< L"}, REFERENCES: " << iter->second;
				}	
			}

			return CHECK_STRING(result.str());
		}

		void 
		_daijoubu_uid::uninitialize(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			clear();
			m_initialized = false;
		}
	}
}
