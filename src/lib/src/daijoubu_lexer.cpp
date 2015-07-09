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

#include <clocale>
#include <cwctype>
#include "../include/daijoubu.h"
#include "../include/daijoubu_lexer_type.h"

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define CHARACTER_END L'\0'
		#define CHARACTER_LOCALE "en_US.utf8"
		#define CHARACTER_NEWLINE L'\n'
		#define CHARACTER_TAB L'\t'
		#define LEXER_BASE_SENTINEL_COUNT 1

		static const std::wstring DAIJOUBU_CHAR_STR[] = {
			L"ALPHA", L"DIGIT", L"END", L"SPACE", L"SYMBOL",
			};

		#define DAIJOUBU_CHAR_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_CHAR_MAX ? UNKNOWN : \
			CHECK_STRING(DAIJOUBU_CHAR_STR[_TYPE_]))

		_daijoubu_lexer_base::_daijoubu_lexer_base(
			__in_opt const std::wstring &input
			) :
				m_column(0),
				m_position(0),
				m_row(0)
		{
			set(input);
		}

		_daijoubu_lexer_base::_daijoubu_lexer_base(
			__in const _daijoubu_lexer_base &other
			) :
				m_buffer(other.m_buffer),
				m_column(other.m_column),
				m_line_map(other.m_line_map),
				m_position(other.m_position),
				m_row(other.m_row)
		{
			return;
		}

		_daijoubu_lexer_base::~_daijoubu_lexer_base(void)
		{
			clear();
		}

		_daijoubu_lexer_base &
		_daijoubu_lexer_base::operator=(
			__in const _daijoubu_lexer_base &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				m_buffer = other.m_buffer;
				m_column = other.m_column;
				m_line_map = other.m_line_map;
				m_position = other.m_position;
				m_row = other.m_row;
			}

			return *this;
		}

		std::wstring &
		_daijoubu_lexer_base::buffer(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_buffer;
		}

		wchar_t 
		_daijoubu_lexer_base::character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_position >= m_buffer.size()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
					L"Character position: %llu", m_position);
			}

			return m_buffer.at(m_position);
		}

		std::wstring 
		_daijoubu_lexer_base::character_exception(
			__in size_t tab,
			__in_opt bool verbose
			)
		{
			wchar_t ch;
			std::wstring ln;
			size_t iter, position;
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			ln = line();
			if(!ln.empty()) {
				result << ln.substr(0, ln.size() - 1);

				if(verbose) {
					result << L" (" << m_row << L":" << m_column << L")";
				}

				result << std::endl;

				for(iter = 0; iter < tab; ++iter) {
					result << CHARACTER_TAB;
				}

				position = m_position - m_column;

				for(iter = 0; iter < m_column; ++iter, ++position) {

					if(position >= m_buffer.size()) {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
							L"Character position: %llu", m_position);
					}

					ch = m_buffer.at(position);
					if(ch == CHARACTER_TAB) {
						result << CHARACTER_TAB;
					} else {
						result << L' ';
					}
				}

				result << L'^';
			}

			return CHECK_STRING(result.str());
		}

		daijoubu_char_t 
		_daijoubu_lexer_base::character_type(
			__in wchar_t input
			)
		{
			daijoubu_char_t result = DAIJOUBU_CHAR_SYMBOL;

			std::setlocale(LC_ALL, CHARACTER_LOCALE);

			if(input == CHARACTER_END) {
				result = DAIJOUBU_CHAR_END;
			} else if(std::iswalpha(input)) {
				result = DAIJOUBU_CHAR_ALPHA;
			} else if(std::iswdigit(input)) {
				result = DAIJOUBU_CHAR_DIGIT;
			} else if(std::iswspace(input)) {
				result = DAIJOUBU_CHAR_SPACE;
			}

			return result;
		}

		void 
		_daijoubu_lexer_base::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			m_buffer.clear();
			m_column = 0;
			m_line_map.clear();
			m_position = 0;
			m_row = 0;
		}

		size_t 
		_daijoubu_lexer_base::column(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_column;
		}

		std::map<size_t, std::pair<size_t, std::wstring>>::iterator 
		_daijoubu_lexer_base::find(
			__in size_t row
			)
		{
			std::map<size_t, std::pair<size_t, std::wstring>>::iterator result;

			SERIALIZE_CALL_RECUR(m_lock);

			result = m_line_map.find(row);
			if(result == m_line_map.end()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_ROW_NOT_FOUND,
					L"Character row: %llu", row);
			}

			return result;
		}

		bool 
		_daijoubu_lexer_base::has_next(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return ((m_position < m_buffer.size())
					&& (type() != DAIJOUBU_CHAR_END));
		}

		bool 
		_daijoubu_lexer_base::has_previous(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_position > 0);
		}

		std::wstring 
		_daijoubu_lexer_base::line(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return find(m_row)->second.second;
		}

		wchar_t 
		_daijoubu_lexer_base::move_next(void)
		{
			size_t position;
			std::wstring line;
			wchar_t ch, result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_next()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_NEXT_CHARACTER,
					L"Character position: %llu {%llu, %llu}", m_position, m_row, m_column);
			}

			result = character();
			if(result == CHARACTER_NEWLINE) {
				++m_row;

				if(m_line_map.find(m_row) == m_line_map.end()) {
					position = m_position + 1;

					do {
						ch = m_buffer.at(position);
						line += ch;
						++position;

						if(ch == CHARACTER_NEWLINE) {
							break;
						}
					} while(ch != CHARACTER_END);

					m_line_map.insert(std::pair<size_t, std::pair<size_t, std::wstring>>(m_row, 
						std::pair<size_t, std::wstring>(m_column, line)));
				}

				m_column = 0;
			} else {
				++m_column;
			}

			++m_position;

			return result;
		}

		wchar_t 
		_daijoubu_lexer_base::move_previous(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_previous()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_PREVIOUS_CHARACTER,
					L"Character position: %llu {%llu, %llu}", m_position, m_row, m_column);
			}

			if(!m_column) {
				m_column = find(--m_row)->second.first;
			} else {
				--m_column;
			}

			--m_position;

			return character();
		}

		size_t 
		_daijoubu_lexer_base::position(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_position;
		}

		void 
		_daijoubu_lexer_base::reset(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			m_column = 0;
			m_position = 0;
			m_row = 0;
		}

		size_t 
		_daijoubu_lexer_base::row(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_row;
		}

		void 
		_daijoubu_lexer_base::set(
			__in const std::wstring &input
			)
		{
			wchar_t ch;
			std::wstring line;
			std::wstringstream contents;
			size_t column = 0, position = 0;

			SERIALIZE_CALL_RECUR(m_lock);

			m_buffer = input + CHARACTER_END;

			do {
				ch = m_buffer.at(position);
				line += ch;
				++column;
				++position;

				if(ch == CHARACTER_NEWLINE) {
					break;
				}
			} while(ch != CHARACTER_END);

			m_line_map.insert(std::pair<size_t, std::pair<size_t, std::wstring>>(m_row, 
				std::pair<size_t, std::wstring>(column, line)));

			reset();
		}

		size_t 
		_daijoubu_lexer_base::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_buffer.size() - LEXER_BASE_SENTINEL_COUNT);
		}

		daijoubu_char_t 
		_daijoubu_lexer_base::type(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return character_type(character());
		}

		std::wstring 
		_daijoubu_lexer_base::to_string(
			__in_opt bool verbose
			)
		{
			wchar_t ch;
			std::wstring ln;
			daijoubu_char_t ch_type;
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << L"(" << m_position << L"/" << (m_buffer.size() - 1)
					<< L") ";
			}

			ch_type = type();
			ch = character();
			result << L"[" << DAIJOUBU_CHAR_STRING(ch_type) << L"] \'";

			switch(ch_type) {
				case DAIJOUBU_CHAR_END:
				case DAIJOUBU_CHAR_SPACE:
					result << L' ';
					break;
				default:
					result << ch;
					break;
			}

			result << L"\' (" << VALUE_AS_HEX(wchar_t, ch) << L")";

			if(verbose) {
				result << L":";

				ln = line().substr(0, line().size() - 1);
				if(!ln.empty()) {
					result << L" \"" << ln << L"\"";
				}

				result << L" (" << m_position <<  L", {" << m_row << L", " << m_column << L"})";
			}

			return CHECK_STRING(result.str());
		}
	}
}
