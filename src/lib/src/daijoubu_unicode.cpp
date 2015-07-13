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

		daijoubu_unicode_t 
		_daijoubu_unicode::character_class(
			__in wchar_t character
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_UNICODE_EXCEPTION(DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED);
			}

			return find(character)->second;
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
			uint32_t value;
			std::string line;
			size_t iter, position;
			std::stringstream stream;

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
				stream.str(std::string());
				stream.clear();
				position = line.find_first_of(UNICODE_SEPERATOR);
				stream << line.substr(0, position);
				value = string_as_value(stream.str(), DAIJOUBU_RADIX_HEXIDECIMAL);
				position = line.find_first_of(UNICODE_SEPERATOR, position + 1);
				stream.str(std::string());
				stream.clear();	
				stream << line.substr(position + 1, line.find_first_of(UNICODE_SEPERATOR, position + 1) 
					- (position + 1));

				for(iter = DAIJOUBU_UNICODE_CLASS_CC; iter <= DAIJOUBU_UNICODE_CLASS_ZS; ++iter) {

					if(stream.str() == DAIJOUBU_UNICODE_CLASS_STRING(iter)) {
						break;
					}
				}

				if(iter > DAIJOUBU_UNICODE_CLASS_ZS) {
					THROW_DAIJOUBU_UNICODE_EXCEPTION_MESSAGE(DAIJOUBU_UNICODE_EXCEPTION_INVALID_CLASS,
						L"%s", stream.str().c_str());
				}

				m_type_map.insert(std::pair<wchar_t, daijoubu_unicode_t>((wchar_t) value, 
					(daijoubu_unicode_t) iter));
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

		bool 
		_daijoubu_unicode::is_whitespace(
			__in daijoubu_unicode_t type
			)
		{
			bool result;

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_CC:
				case DAIJOUBU_UNICODE_CLASS_ZL:
				case DAIJOUBU_UNICODE_CLASS_ZP:
				case DAIJOUBU_UNICODE_CLASS_ZS:
					result = true;
					break;
				default:
					result = false;
					break;
			}

			return result;
		}

		std::wstring 
		_daijoubu_unicode::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::map<wchar_t, daijoubu_unicode_t>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			result << DAIJOUBU_UNICODE_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
				<< L"]";;

			for(iter = m_type_map.begin(); iter != m_type_map.end(); ++iter) {
				result << std::endl << L"--- " << VALUE_AS_HEX(wchar_t, iter->first) << L" (\'" 
					<< (std::iswprint(iter->first) ? iter->first : L' ') << L"\', " 
					<< DAIJOUBU_UNICODE_CLASS_STRING(iter->second).c_str();
			}

			return CHECK_STRING(result.str());
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
