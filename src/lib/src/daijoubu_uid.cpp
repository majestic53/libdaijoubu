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

		_daijoubu_uid_class::_daijoubu_uid_class(void) :
			m_uid(daijoubu::acquire()->acquire_uid_factory()->generate())
		{
			return;
		}

		_daijoubu_uid_class::_daijoubu_uid_class(
			__in const _daijoubu_uid_class &other
			) :
				m_uid(other.m_uid)
		{
			daijoubu_uid_factory_ptr fact = daijoubu::acquire()->acquire_uid_factory();

			if(fact->contains(m_uid)) {
				fact->increment_reference(m_uid);
			}
		}

		_daijoubu_uid_class::~_daijoubu_uid_class(void)
		{
			daijoubu_uid_factory_ptr fact = daijoubu::acquire()->acquire_uid_factory();

			if(fact->contains(m_uid)) {
				fact->decrement_reference(m_uid);
			}

			m_uid = INVALID_UID;
		}

		_daijoubu_uid_class &
		_daijoubu_uid_class::operator=(
			__in const _daijoubu_uid_class &other
			)
		{
			daijoubu_uid_factory_ptr fact = NULL;

			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				fact = daijoubu::acquire()->acquire_uid_factory();

				if(fact->contains(m_uid)) {
					fact->decrement_reference(m_uid);
				}

				m_uid = other.m_uid;

				if(fact->contains(m_uid)) {
					fact->increment_reference(m_uid);
				}
			}

			return *this;
		}

		bool 
		_daijoubu_uid_class::operator==(
			__in const _daijoubu_uid_class &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_uid == other.m_uid);
		}

		bool 
		_daijoubu_uid_class::operator!=(
			__in const _daijoubu_uid_class &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return !(*this == other);
		}

		std::wstring 
		_daijoubu_uid_class::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);
			UNREFERENCE_PARAMETER(verbose);

			result << L"(" << VALUE_AS_HEX(daijoubu_uid, m_uid) << L")";

			return CHECK_STRING(result.str());
		}

		daijoubu_uid 
		_daijoubu_uid_class::uid(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_uid;
		}

		daijoubu_uid_factory_ptr daijoubu_uid_factory::m_instance = NULL;

		_daijoubu_uid_factory::_daijoubu_uid_factory(void) :
			m_initialized(false)
		{
			std::atexit(daijoubu_uid_factory::_delete);
		}

		_daijoubu_uid_factory::~_daijoubu_uid_factory(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_daijoubu_uid_factory::_delete(void)
		{

			if(daijoubu_uid_factory::m_instance) {
				delete daijoubu_uid_factory::m_instance;
				daijoubu_uid_factory::m_instance = NULL;
			}
		}

		daijoubu_uid_factory_ptr 
		_daijoubu_uid_factory::acquire(void)
		{

			if(!daijoubu_uid_factory::m_instance) {

				daijoubu_uid_factory::m_instance = new daijoubu_uid_factory;
				if(!daijoubu_uid_factory::m_instance) {
					THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_ALLOCATION);
				}
			}

			return daijoubu_uid_factory::m_instance;
		}

		void 
		_daijoubu_uid_factory::clear(void)
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
		_daijoubu_uid_factory::contains(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return (m_uid_map.find(uid) != m_uid_map.end());
		}

		size_t 
		_daijoubu_uid_factory::decrement_reference(
			__in daijoubu_uid uid
			)
		{
			size_t result;
			std::map<daijoubu_uid, size_t>::iterator iter;

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

		std::map<daijoubu_uid, size_t>::iterator 
		_daijoubu_uid_factory::find(
			__in daijoubu_uid uid
			)
		{
			std::map<daijoubu_uid, size_t>::iterator result;

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

		daijoubu_uid 
		_daijoubu_uid_factory::generate(void)
		{
			daijoubu_uid result;
			std::set<daijoubu_uid>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			if(!m_uid_surplus.empty()) {
				iter = m_uid_surplus.begin();
				result = *iter;
				m_uid_surplus.erase(iter);
			} else if(m_uid_next < INVALID_UID) {
				result = m_uid_next++;
			} else {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_RESOURCES);
			}

			m_uid_map.insert(std::pair<daijoubu_uid, size_t>(result, REFERENCE_INIT));

			return result;
		}

		size_t 
		_daijoubu_uid_factory::increment_reference(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return ++find(uid)->second;
		}

		void 
		_daijoubu_uid_factory::initialize(void)
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
		_daijoubu_uid_factory::is_allocated(void)
		{
			return (daijoubu_uid_factory::m_instance != NULL);
		}

		bool 
		_daijoubu_uid_factory::is_initialized(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_initialized;
		}

		size_t 
		_daijoubu_uid_factory::reference_count(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return find(uid)->second;
		}

		size_t 
		_daijoubu_uid_factory::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UID_EXCEPTION(DAIJOUBU_UID_EXCEPTION_UNINITIALIZED);
			}

			return m_uid_map.size();
		}

		std::wstring 
		_daijoubu_uid_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::map<daijoubu_uid, size_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			result << DAIJOUBU_UID_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
				<< L"] (" << VALUE_AS_HEX(uintptr_t, this) << L"), COUNT: " << m_uid_map.size();

			if(verbose) {

				for(iter = m_uid_map.begin(); iter != m_uid_map.end(); ++iter) {
					result << std::endl << L"{" << VALUE_AS_HEX(daijoubu_uid, iter->first) 
						<< L"}, REFERENCES: " << iter->second;
				}	
			}

			return CHECK_STRING(result.str());
		}

		void 
		_daijoubu_uid_factory::uninitialize(void)
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
