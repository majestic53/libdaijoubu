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

#include <fstream>
#include "../include/daijoubu.h"
#include "../include/daijoubu_unicode_type.h"

namespace DAIJOUBU {

	namespace COMPONENT {

		#define UNICODE_SEPERATOR ';'

		static const std::wstring DAIJOUBU_UNICODE_CLASS_STR[] {
			L"Cc", L"Cf", L"Cn", L"Co", L"Cs", L"Lc", L"Ll", L"Lm",
			L"Lo", L"Lt", L"Lu", L"Mc", L"Me", L"Mn", L"Nd", L"Nl",
			L"No", L"Pc", L"Pd", L"Pe", L"Pf", L"Pl", L"Po", L"Ps",
			L"Sc", L"Sk", L"Sm", L"So", L"Zl", L"Zp", L"Zs",
		};

		daijoubu_unicode_ptr daijoubu_unicode::m_instance = NULL;

		_daijoubu_unicode::_daijoubu_unicode(void) :
			m_initialized(false)
		{
			std::atexit(daijoubu_unicode::_delete);
		}

		_daijoubu_unicode::~_daijoubu_unicode(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_daijoubu_unicode::_delete(void)
		{

			if(daijoubu_unicode::m_instance) {
				delete daijoubu_unicode::m_instance;
				daijoubu_unicode::m_instance = NULL;
			}
		}

		daijoubu_unicode_ptr 
		_daijoubu_unicode::acquire(void)
		{

			if(!daijoubu_unicode::m_instance) {

				daijoubu_unicode::m_instance = new daijoubu_unicode;
				if(!daijoubu_unicode::m_instance) {
					THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_ALLOCATION);
				}
			}

			return daijoubu_unicode::m_instance;
		}

		bool 
		_daijoubu_unicode::contains(
			__in wchar_t character
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED);
			}

			return (m_type_map.find(character) != m_type_map.end());
		}

		std::map<wchar_t, daijoubu_unicode_t>::iterator 
		_daijoubu_unicode::find(
			__in wchar_t character
			)
		{
			std::map<wchar_t, daijoubu_unicode_t>::iterator result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED);
			}

			result = m_type_map.find(character);
			if(result == m_type_map.end()) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION_MESSAGE(DAIJOUBU_UNICODE_EXCEPTION_UNKNOWN,
					L"%lc", character);
			}

			return result;
		}

		void 
		_daijoubu_unicode::initialize(
			__in const std::string &input
			)
		{
			std::string line;
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_INITIALIZED);
			}

			m_initialized = true;
			m_type_map.clear();

			std::ifstream file(input.c_str(), std::ios::in);
			if(!file) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION_MESSAGE(DAIJOUBU_UNICODE_EXCEPTION_NOT_FOUND,
					L"%s", input.c_str());
			}

			while(std::getline(file, line)) {
				// TODO: read from 0 - first UNICODE_SEPERATOR (wchar_t)
				// TODO: read from second UNICODE_SEPERATOR + 1 - third UNICODE_SEPERATOR (type)
				line.clear();
			}

			file.close();
		}

		bool 
		_daijoubu_unicode::is_allocated(void)
		{
			return (daijoubu_unicode::m_instance != NULL);
		}

		bool 
		_daijoubu_unicode::is_initialized(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_initialized;
		}

		std::wstring 
		_daijoubu_unicode::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::map<daijoubu_uid, size_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);
			UNREFERENCE_PARAMETER(verbose);

			result << DAIJOUBU_UNICODE_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
				<< L"]";;

			return CHECK_STRING(result.str());
		}

		daijoubu_unicode_t 
		_daijoubu_unicode::type(
			__in wchar_t character
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED);
			}

			return find(character)->second;
		}

		void 
		_daijoubu_unicode::uninitialize(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED);
			}

			m_type_map.clear();
			m_initialized = false;
		}
	}
}
