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
#include "../include/daijoubu_token_type.h"

namespace DAIJOUBU {

	namespace COMPONENT {

		_daijoubu_token::_daijoubu_token(
			__in_opt daijoubu_token_t type,
			__in_opt uint16_t subtype
			) :
				m_column(0),
				m_offset(0),
				m_position(0),
				m_row(0),
				m_subtype(subtype),
				m_type(type),
				m_value(0.0)
		{
			return;
		}

		_daijoubu_token::_daijoubu_token(
			__in const _daijoubu_token &other
			) :
				daijoubu_uid_class(other),
				m_column(other.m_column),
				m_line(other.m_line),
				m_offset(other.m_offset),
				m_position(other.m_position),
				m_row(other.m_row),
				m_subtype(other.m_subtype),
				m_text(other.m_text),
				m_type(other.m_type),
				m_value(other.m_value)
		{
			return;
		}

		_daijoubu_token::~_daijoubu_token(void)
		{
			return;
		}

		_daijoubu_token &
		_daijoubu_token::operator=(
			__in const _daijoubu_token &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				daijoubu_uid_class::operator=(other);
				m_column = other.m_column;
				m_line = other.m_line;
				m_offset = other.m_offset;
				m_position = other.m_position;
				m_row = other.m_row;
				m_subtype = other.m_subtype;
				m_text = other.m_text;
				m_type = other.m_type;
				m_value = other.m_value;
			}

			return *this;
		}

		bool 
		_daijoubu_token::operator==(
			__in const _daijoubu_token &other
			)
		{
			bool result;

			SERIALIZE_CALL_RECUR(m_lock);

			result = (this == &other);
			if(!result) {
				result = (daijoubu_uid_class::operator==(other)
					&& (m_column == other.m_column)
					&& (m_line == other.m_line)
					&& (m_position == other.m_position)
					&& (m_offset == other.m_offset)
					&& (m_row == other.m_row)
					&& (m_subtype == other.m_subtype)
					&& (m_text == other.m_text)
					&& (m_type == other.m_type)
					&& (m_value == other.m_value));
			}

			return result;
		}

		bool 
		_daijoubu_token::operator!=(
			__in const _daijoubu_token &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return !(*this == other);
		}

		size_t &
		_daijoubu_token::column(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_column;
		}

		std::wstring &
		_daijoubu_token::line(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_line;
		}

		size_t &
		_daijoubu_token::offset(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_offset;
		}

		size_t &
		_daijoubu_token::position(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_position;
		}

		size_t &
		_daijoubu_token::row(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_row;
		}

		uint16_t &
		_daijoubu_token::subtype(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_subtype;
		}

		std::wstring &
		_daijoubu_token::text(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_text;
		}

		std::wstring 
		_daijoubu_token::to_string(
			__in_opt bool verbose
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return token_as_string(*this, verbose);
		}

		std::wstring 
		_daijoubu_token::token_as_string(
			__in const _daijoubu_token &token,
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::wstring::const_iterator iter;

			if(verbose) {
				result << L"(" << VALUE_AS_HEX(daijoubu_uid, token.m_uid) << L") ";
			}

			result << L"[" << DAIJOUBU_TOKEN_STRING(token.m_type);

			if(token.m_subtype != INVALID_TOKEN_SUBTYPE) {
				result << L", " << token_subtype_as_unicode_string(token.m_type, token.m_subtype);
			}

			result << L"]";

			if(!token.m_text.empty()) {
				result << L" \'";

				for(iter = token.m_text.begin(); iter != token.m_text.end(); 
						++iter) {
					result << (std::iswprint(*iter) ? *iter : L' ');
				}

				result << L"\'";
			}

			switch(token.m_type) {
				case DAIJOUBU_TOKEN_BEGIN:
				case DAIJOUBU_TOKEN_END:
					break;
				case DAIJOUBU_TOKEN_LITERAL_NUMERIC:
				case DAIJOUBU_TOKEN_SUBSCRIPT:
				case DAIJOUBU_TOKEN_SUPERSCRIPT:
					result << L" " << token.m_value;
					break;
				default:
					break;
			}

			switch(token.m_type) {
				case DAIJOUBU_TOKEN_BEGIN:
				case DAIJOUBU_TOKEN_END:
					break;
				default:

					if(verbose) {
						result << L":";

						if(!token.m_line.empty()) {
							result << L" \"";

							for(iter = token.m_line.begin(); iter != token.m_line.end(); 
									++iter) {
								result << (std::iswprint(*iter) ? *iter : L' ');
							}

							result << L"\"[" << token.m_offset << L"]";
						}

						result << L" (" << token.m_position << L", {"
							<< token.m_row << L", " << token.m_column << L"})";
					}

					break;
			}

			return CHECK_STRING(result.str());
		}

		daijoubu_token_t &
		_daijoubu_token::type(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_type;
		}

		long double &
		_daijoubu_token::value(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_value;
		}

		daijoubu_token_factory_ptr daijoubu_token_factory::m_instance = NULL;

		_daijoubu_token_factory::_daijoubu_token_factory(void) :
			m_initialized(false)
		{
			std::atexit(daijoubu_token_factory::_delete);
		}

		_daijoubu_token_factory::~_daijoubu_token_factory(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_daijoubu_token_factory::_delete(void)
		{

			if(daijoubu_token_factory::m_instance) {
				delete daijoubu_token_factory::m_instance;
				daijoubu_token_factory::m_instance = NULL;
			}
		}

		daijoubu_token_factory_ptr 
		_daijoubu_token_factory::acquire(void)
		{

			if(!daijoubu_token_factory::m_instance) {

				daijoubu_token_factory::m_instance = new daijoubu_token_factory;
				if(!daijoubu_token_factory::m_instance) {
					THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_ALLOCATION);
				}
			}

			return daijoubu_token_factory::m_instance;
		}

		daijoubu_token &
		_daijoubu_token_factory::at(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			return find(uid)->second.first;
		}

		void 
		_daijoubu_token_factory::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			m_token_map.clear();
		}

		bool 
		_daijoubu_token_factory::contains(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			return (m_token_map.find(uid) != m_token_map.end());
		}

		size_t 
		_daijoubu_token_factory::decrement_reference(
			__in daijoubu_uid uid
			)
		{
			size_t result;
			std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			iter = find(uid);

			result = --iter->second.second;
			if(!result) {
				m_token_map.erase(iter);
			}

			return result;
		}

		std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>>::iterator 
		_daijoubu_token_factory::find(
			__in daijoubu_uid uid
			)
		{
			std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>>::iterator result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			result = m_token_map.find(uid);
			if(result == m_token_map.end()) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION_MESSAGE(DAIJOUBU_TOKEN_EXCEPTION_NOT_FOUND,
					L"0x%x", uid);
			}

			return result;
		}

		daijoubu_uid 
		_daijoubu_token_factory::generate(
			__in_opt daijoubu_token_t type,
			__in_opt uint16_t subtype
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			daijoubu_token tok(type, subtype);
			m_token_map.insert(std::pair<daijoubu_uid, std::pair<daijoubu_token, size_t>>(tok.uid(), 
				std::pair<daijoubu_token, size_t>(tok, REFERENCE_INIT)));

			return tok.uid();
		}

		size_t 
		_daijoubu_token_factory::increment_reference(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			return ++find(uid)->second.second;
		}

		void 
		_daijoubu_token_factory::initialize(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_INITIALIZED);
			}

			m_initialized =true;
			clear();
		}

		bool 
		_daijoubu_token_factory::is_allocated(void)
		{
			return (daijoubu_token_factory::m_instance != NULL);
		}

		bool 
		_daijoubu_token_factory::is_initialized(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_initialized;
		}

		size_t 
		_daijoubu_token_factory::reference_count(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			return find(uid)->second.second;
		}

		size_t 
		_daijoubu_token_factory::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			return m_token_map.size();
		}

		std::wstring 
		_daijoubu_token_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;
			std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>>::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			result << DAIJOUBU_TOKEN_HEADER << L" [" << (m_initialized ? L"INITIALIZED" : L"UNINITIALIZED")
				<< L"] (" << VALUE_AS_HEX(uintptr_t, this) << L"), COUNT: " << m_token_map.size();

			if(verbose) {

				for(iter = m_token_map.begin(); iter != m_token_map.end(); ++iter) {
					result << std::endl << L"{" << VALUE_AS_HEX(daijoubu_uid, iter->first) 
						<< L"}, REFERENCES: " << iter->second.second << L", "
						<< iter->second.first.to_string(true);
				}	
			}

			return CHECK_STRING(result.str());
		}

		void 
		_daijoubu_token_factory::uninitialize(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_DAIJOUBU_TOKEN_EXCEPTION(DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED);
			}

			clear();
			m_initialized = false;
		}
	}
}
