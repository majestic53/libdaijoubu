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
#include "../include/daijoubu_lexer_type.h"

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define LEXER_BASE_SENTINEL_COUNT 1
		#define LEXER_SENTINEL_COUNT 2

		_daijoubu_lexer_base::_daijoubu_lexer_base(
			__in_opt const std::wstring &input,
			__in_opt bool simple
			) :
				m_ch_column(0),
				m_ch_position(0),
				m_ch_row(0),
				m_simple(false)
		{
			daijoubu_lexer_base::set(input, simple);
		}

		_daijoubu_lexer_base::_daijoubu_lexer_base(
			__in const _daijoubu_lexer_base &other
			) :
				m_ch_buffer(other.m_ch_buffer),
				m_ch_column(other.m_ch_column),
				m_ch_line_map(other.m_ch_line_map),
				m_ch_position(other.m_ch_position),
				m_ch_row(other.m_ch_row),
				m_simple(other.m_simple)
		{
			return;
		}

		_daijoubu_lexer_base::~_daijoubu_lexer_base(void)
		{
			daijoubu_lexer_base::clear();
		}

		_daijoubu_lexer_base &
		_daijoubu_lexer_base::operator=(
			__in const _daijoubu_lexer_base &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				m_ch_buffer = other.m_ch_buffer;
				m_ch_column = other.m_ch_column;
				m_ch_line_map = other.m_ch_line_map;
				m_ch_position = other.m_ch_position;
				m_ch_row = other.m_ch_row;
				m_simple = other.m_simple;
			}

			return *this;
		}

		wchar_t 
		_daijoubu_lexer_base::character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_ch_position >= m_ch_buffer.size()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
					L"Character position: %llu", m_ch_position);
			}

			return m_ch_buffer.at(m_ch_position);
		}

		std::wstring &
		_daijoubu_lexer_base::character_buffer(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_ch_buffer;
		}

		daijoubu_unicode_t 
		_daijoubu_lexer_base::character_class(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return character_to_class(character());
		}

		size_t 
		_daijoubu_lexer_base::character_column(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_ch_column;
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

			ln = character_line();
			if(!ln.empty()) {
				result << ln.substr(0, ln.size() - 1);

				if(verbose) {
					result << L" (" << m_ch_row << L":" << m_ch_column << L")";
				}

				result << std::endl;

				for(iter = 0; iter < tab; ++iter) {
					result << DAIJOUBU_CHARACTER_TAB;
				}

				position = m_ch_position - m_ch_column;

				for(iter = 0; iter < m_ch_column; ++iter, ++position) {

					if(position >= m_ch_buffer.size()) {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
							L"Character position: %llu", m_ch_position);
					}

					ch = m_ch_buffer.at(position);
					if(ch == DAIJOUBU_CHARACTER_TAB) {
						result << DAIJOUBU_CHARACTER_TAB;
					} else {
						result << L' ';
					}
				}

				result << L'^';
			}

			return CHECK_STRING(result.str());
		}

		std::wstring 
		_daijoubu_lexer_base::character_line(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return find(m_ch_row)->second.second;
		}

		size_t 
		_daijoubu_lexer_base::character_position(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_ch_position;
		}

		size_t 
		_daijoubu_lexer_base::character_row(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_ch_row;
		}

		daijoubu_unicode_t 
		_daijoubu_lexer_base::character_to_class(
			__in wchar_t input
			)
		{
			return daijoubu::acquire()->unicode()->character_class(input);
		}

		void 
		_daijoubu_lexer_base::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			m_ch_buffer.clear();
			m_ch_column = 0;
			m_ch_line_map.clear();
			m_ch_position = 0;
			m_ch_row = 0;
		}

		std::map<size_t, std::pair<size_t, std::wstring>>::iterator 
		_daijoubu_lexer_base::find(
			__in size_t row
			)
		{
			std::map<size_t, std::pair<size_t, std::wstring>>::iterator result;

			SERIALIZE_CALL_RECUR(m_lock);

			result = m_ch_line_map.find(row);
			if(result == m_ch_line_map.end()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_ROW_NOT_FOUND,
					L"Character row: %llu", row);
			}

			return result;
		}

		bool 
		_daijoubu_lexer_base::has_next_character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return ((m_ch_position < m_ch_buffer.size())
					&& (character() != DAIJOUBU_CHARACTER_END));
		}

		bool 
		_daijoubu_lexer_base::has_previous_character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_ch_position > 0);
		}

		daijoubu_newline_t 
		_daijoubu_lexer_base::is_newline_delimiter(void)
		{
			wchar_t ch;
			daijoubu_newline_t result = DAIJOUBU_NEWLINE_TYPE_NONE;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();
			switch(ch) {
				case DAIJOUBU_CHARACTER_CARRAGE_RETURN:

					if(has_next_character()) {

						ch = m_ch_buffer.at(m_ch_position + 1);
						if(ch == DAIJOUBU_CHARACTER_NEWLINE) {
							result = DAIJOUBU_NEWLINE_TYPE_WINDOWS;
						}
					}
					break;
				case DAIJOUBU_CHARACTER_NEWLINE:
					result = DAIJOUBU_NEWLINE_TYPE_UNIX;
					break;
			}

			return result;
		}

		bool 
		_daijoubu_lexer_base::is_simple(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_simple;
		}

		wchar_t 
		_daijoubu_lexer_base::move_next_character(void)
		{
			size_t position;
			std::wstring line;
			wchar_t ch, result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_next_character()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_NEXT_CHARACTER,
					L"Character position: %llu {%llu, %llu}", m_ch_position, m_ch_row, m_ch_column);
			}

			result = character();
			if(m_simple && (result > UINT8_MAX)) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_DIALECT,
					L"\'%lc\' (0x%x)", (std::iswprint(result) ? result : L' '), result);
			}

			if(result == DAIJOUBU_CHARACTER_NEWLINE) {
				++m_ch_row;

				if(m_ch_line_map.find(m_ch_row) == m_ch_line_map.end()) {
					position = m_ch_position + 1;

					do {
						ch = m_ch_buffer.at(position);
						line += ch;
						++position;

						if(ch == DAIJOUBU_CHARACTER_NEWLINE) {
							break;
						}
					} while(ch != DAIJOUBU_CHARACTER_END);

					m_ch_line_map.insert(std::pair<size_t, std::pair<size_t, std::wstring>>(m_ch_row, 
						std::pair<size_t, std::wstring>(m_ch_column, line)));
				}

				m_ch_column = 0;
			} else {
				++m_ch_column;
			}

			++m_ch_position;

			return result;
		}

		wchar_t 
		_daijoubu_lexer_base::move_previous_character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_previous_character()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_PREVIOUS_CHARACTER,
					L"Character position: %llu {%llu, %llu}", m_ch_position, m_ch_row, m_ch_column);
			}

			if(!m_ch_column) {
				m_ch_column = find(--m_ch_row)->second.first;
			} else {
				--m_ch_column;
			}

			--m_ch_position;

			return character();
		}

		void 
		_daijoubu_lexer_base::reset(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			m_ch_column = 0;
			m_ch_position = 0;
			m_ch_row = 0;
		}

		void 
		_daijoubu_lexer_base::set(
			__in const std::wstring &input,
			__in_opt bool simple
			)
		{
			wchar_t ch;
			std::wstring line;
			size_t column = 0, position = 0;

			SERIALIZE_CALL_RECUR(m_lock);

			m_simple = simple;
			daijoubu_lexer_base::clear();
			m_ch_buffer = input + DAIJOUBU_CHARACTER_END;

			do {
				ch = m_ch_buffer.at(position);
				line += ch;
				++column;
				++position;

				if(ch == DAIJOUBU_CHARACTER_NEWLINE) {
					break;
				}
			} while(ch != DAIJOUBU_CHARACTER_END);

			m_ch_line_map.insert(std::pair<size_t, std::pair<size_t, std::wstring>>(m_ch_row, 
				std::pair<size_t, std::wstring>(column, line)));

			reset();
		}

		size_t 
		_daijoubu_lexer_base::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_ch_buffer.size() - LEXER_BASE_SENTINEL_COUNT);
		}

		std::wstring 
		_daijoubu_lexer_base::to_string(
			__in_opt bool verbose
			)
		{
			wchar_t ch;
			std::wstring ln;
			std::wstringstream result;
			std::wstring::iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << L"(" << m_ch_position << L"/" << (m_ch_buffer.size() - 1)
					<< L") ";
			}
			
			ch = character();
			result << L"[" << DAIJOUBU_UNICODE_CLASS_STRING(character_class()).c_str() << L"] \'" 
				<< (std::iswprint(ch) ? ch : L' ') << L"\' (" 
				<< VALUE_AS_HEX(wchar_t, ch) << L")";

			if(verbose) {
				result << L":";

				ln = character_line();
				ln = ln.substr(0, ln.size() - 1);
				if(!ln.empty()) {
					result << L" \"";

					for(iter = ln.begin(); iter != ln.end(); ++iter) {
						result << (std::iswprint(*iter) ? *iter : L' ');
					}

					result << L"\"";
				}

				result << L" (" << m_ch_position <<  L", {" << m_ch_row << L", " 
					<< m_ch_column << L"})";
			}

			return CHECK_STRING(result.str());
		}

		_daijoubu_lexer::_daijoubu_lexer(
			__in_opt const std::wstring &input,
			__in_opt bool simple
			) :
				m_tok_position(0)
		{
			daijoubu_lexer::set(input, simple);
		}

		_daijoubu_lexer::_daijoubu_lexer(
			__in const _daijoubu_lexer &other
			) :
				daijoubu_lexer_base(other),
				m_tok_list(other.m_tok_list),
				m_tok_position(other.m_tok_position)
		{
			return;
		}

		_daijoubu_lexer::~_daijoubu_lexer(void)
		{
			daijoubu_lexer::clear();
		}

		_daijoubu_lexer &
		_daijoubu_lexer::operator=(
			__in const _daijoubu_lexer &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				daijoubu_lexer_base::operator=(other);
				m_tok_list = other.m_tok_list;
				m_tok_position = other.m_tok_position;
			}

			return *this;
		}

		void 
		_daijoubu_lexer::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			daijoubu_lexer_base::reset();
			m_tok_list.clear();
			m_tok_position = 0;
		}

		void 
		_daijoubu_lexer::discover(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			while(has_next_token()) {
				move_next_token();
			}

			daijoubu_lexer::reset();
		}

		void 
		_daijoubu_lexer::enumerate_class_control(
			__in daijoubu_unicode_t type
			)
		{
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_CC:
				case DAIJOUBU_UNICODE_CLASS_CF:
				case DAIJOUBU_UNICODE_CLASS_CN:
				case DAIJOUBU_UNICODE_CLASS_CO:
				case DAIJOUBU_UNICODE_CLASS_CS:

					// TODO
					supported = false;
					// ---

					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_CONTROL,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_class_letter(
			__in daijoubu_unicode_t type
			)
		{
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_LC:

					// TODO
					supported = false;
					// ---

					break;
				case DAIJOUBU_UNICODE_CLASS_LL:
				case DAIJOUBU_UNICODE_CLASS_LM:
				case DAIJOUBU_UNICODE_CLASS_LO:
				case DAIJOUBU_UNICODE_CLASS_LT:
				case DAIJOUBU_UNICODE_CLASS_LU:
					enumerate_keyword();
					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_LETTER,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_class_mark(
			__in daijoubu_unicode_t type
			)
		{
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_MC:
				case DAIJOUBU_UNICODE_CLASS_ME:
				case DAIJOUBU_UNICODE_CLASS_MN:

					// TODO
					supported = false;
					// ---

					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_MARK,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_class_number(
			__in daijoubu_unicode_t type
			)
		{
			wchar_t ch;
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_ND:

					// TODO
					supported = false;
					// ---

					break;
				case DAIJOUBU_UNICODE_CLASS_NL:
					enumerate_keyword();
					break;
				case DAIJOUBU_UNICODE_CLASS_NO:

					if(is_subscript_character()) {
						enumerate_subscript();
					} else if(is_superscript_character()) {
						enumerate_superscript();
					} else {
						supported = false;
					}
					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_NUMBER,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_class_punctuation(
			__in daijoubu_unicode_t type
			)
		{
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_PF:

					// TODO
					supported = false;
					// ---

					std::wcout << DAIJOUBU_UNICODE_CLASS_STRING(type).c_str() << std::endl;

					break;
				case DAIJOUBU_UNICODE_CLASS_PC:

					if(character() == DAIJOUBU_IDENTIFIER_LOW_LINE) {
						enumerate_keyword();
					} else {

						// TODO
						supported = false;
						// ---

					}
					break;
				case DAIJOUBU_UNICODE_CLASS_PD:
				case DAIJOUBU_UNICODE_CLASS_PE:
				case DAIJOUBU_UNICODE_CLASS_PO:
				case DAIJOUBU_UNICODE_CLASS_PS:
					enumerate_symbol();
					break;
				case DAIJOUBU_UNICODE_CLASS_PI:

					if(is_string_delimiter() == DAIJOUBU_STRING_OPEN_TYPE) {
						enumerate_string();
					} else {

						// TODO
						supported = false;
						// ---

					}
					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_PUNCTUATION,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_class_symbol(
			__in daijoubu_unicode_t type
			)
		{
			bool supported = true;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(type) {
				case DAIJOUBU_UNICODE_CLASS_SC:
				case DAIJOUBU_UNICODE_CLASS_SK:
				case DAIJOUBU_UNICODE_CLASS_SO:
					enumerate_symbol();
					break;
				case DAIJOUBU_UNICODE_CLASS_SM:

					if(is_string_delimiter() == DAIJOUBU_STRING_OPEN_SIMPLE_TYPE) {
						enumerate_string();
					} else if(is_modifier_character()) {
						enumerate_modifier();
					} else {
						enumerate_symbol();
					}
					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_CLASS_SYMBOL,
						L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
			}

			if(!supported) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}
		}

		void 
		_daijoubu_lexer::enumerate_keyword(void)
		{			
			std::wstring text;
			bool terminated = false, lm_ch = false;
			uint16_t subtype = INVALID_TOKEN_SUBTYPE;
			daijoubu_token_t type = DAIJOUBU_TOKEN_IDENTIFIER;

			SERIALIZE_CALL_RECUR(m_lock);

			switch(character_class()) {
				case DAIJOUBU_UNICODE_CLASS_LM:
					lm_ch = true;
				case DAIJOUBU_UNICODE_CLASS_LL:
				case DAIJOUBU_UNICODE_CLASS_LO:
				case DAIJOUBU_UNICODE_CLASS_LT:
				case DAIJOUBU_UNICODE_CLASS_LU:
				case DAIJOUBU_UNICODE_CLASS_NL:
					text += character();
					break;
				case DAIJOUBU_UNICODE_CLASS_PC:

					if(character() == DAIJOUBU_IDENTIFIER_LOW_LINE) {
						text += character();
					} else {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
							DAIJOUBU_LEXER_EXCEPTION_EXPECTING_KEYWORD,
							L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
					}

					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_KEYWORD,
						L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}

			while(!terminated) {

				if(!has_next_character()) {
					terminated = true;
					continue;
				}

				move_next_character();

				switch(character_class()) {
					case DAIJOUBU_UNICODE_CLASS_LL:
					case DAIJOUBU_UNICODE_CLASS_LM:
					case DAIJOUBU_UNICODE_CLASS_LO:
					case DAIJOUBU_UNICODE_CLASS_LT:
					case DAIJOUBU_UNICODE_CLASS_LU:
					case DAIJOUBU_UNICODE_CLASS_MC:
					case DAIJOUBU_UNICODE_CLASS_MN:
					case DAIJOUBU_UNICODE_CLASS_ND:
					case DAIJOUBU_UNICODE_CLASS_NL:
						text += character();
						break;
					case DAIJOUBU_UNICODE_CLASS_PC:

						if(character() == DAIJOUBU_IDENTIFIER_LOW_LINE) {
							text += character();
						} else {
							terminated = true;
							continue;
						}

						break;
					default:
						terminated = true;
						continue;
				}
			}

			if(IS_DAIJOUBU_CONSTANT_TYPE(text)) {
				type = DAIJOUBU_TOKEN_CONSTANT;
				subtype = determine_token_subtype(text, type);
			} else if(IS_DAIJOUBU_CONTROL_TYPE(text)) {
				type = DAIJOUBU_TOKEN_CONTROL;
				subtype = determine_token_subtype(text, type);
			} else if(IS_DAIJOUBU_LITERAL_BOOLEAN_TYPE(text)) {
				type = DAIJOUBU_TOKEN_LITERAL_BOOLEAN;
				subtype = determine_token_subtype(text, type);
			} else if(IS_DAIJOUBU_MODIFIER_TYPE(text)) {
				type = DAIJOUBU_TOKEN_MODIFIER;
				subtype = determine_token_subtype(text, type);
			} else if(IS_DAIJOUBU_OPERATOR_TYPE(text)) {
				type = DAIJOUBU_TOKEN_OPERATOR;
				subtype = determine_token_subtype(text, type);
			} else if(IS_DAIJOUBU_TYPE_TYPE(text)) {
				type = DAIJOUBU_TOKEN_TYPE;
				subtype = determine_token_subtype(text, type);
			} else if(lm_ch && (text.size() == 1)) {
				type = DAIJOUBU_TOKEN_MODIFIER;
			}

			token_insert(token_add(type));
			daijoubu_token &tok = token_at(m_tok_position + 1);
			tok.subtype() = subtype;
			tok.text() = text;
		}

		void 
		_daijoubu_lexer::enumerate_modifier(void)
		{
			std::wstring text;

			SERIALIZE_CALL_RECUR(m_lock);

			text += character();
			move_next_character();

			if(!IS_DAIJOUBU_MODIFIER_TYPE(text)) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_EXPECTING_MODIFIER,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}

			token_insert(token_add(DAIJOUBU_TOKEN_MODIFIER));
			daijoubu_token &tok = token_at(m_tok_position + 1);
			tok.subtype() = determine_token_subtype(text, DAIJOUBU_TOKEN_MODIFIER);			
			tok.text() = text;
			
		}

		void 
		_daijoubu_lexer::enumerate_number(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
		}

		void 
		_daijoubu_lexer::enumerate_string(void)
		{
			std::wstring text;
			bool terminated = false;
			daijoubu_string_t open_type;

			SERIALIZE_CALL_RECUR(m_lock);

			open_type = is_string_delimiter();
			switch(open_type) {
				case DAIJOUBU_STRING_OPEN_SIMPLE_TYPE:
					move_next_character();
					move_next_character();
					break;
				case DAIJOUBU_STRING_OPEN_TYPE:
					move_next_character();
					break;
				default:
					THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
						DAIJOUBU_LEXER_EXCEPTION_EXPECTING_LITERAL_STRING,
						L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
					break;
			}

			while(has_next_character() && !terminated) {
				text += character();
				move_next_character();

				switch(is_string_delimiter()) {
					case DAIJOUBU_STRING_OPEN_SIMPLE_TYPE:
					case DAIJOUBU_STRING_OPEN_TYPE:
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
							DAIJOUBU_LEXER_EXCEPTION_INVALID_NESTED_LITERAL_STRING,
							L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
						break;
					case DAIJOUBU_STRING_CLOSE_SIMPLE_TYPE:

						if(open_type != DAIJOUBU_STRING_OPEN_SIMPLE_TYPE) {
							THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
								DAIJOUBU_LEXER_EXCEPTION_MISMATCHED_LITERAL_STRING_DELIMITER,
								L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
						}

						terminated = true;
						move_next_character();
						move_next_character();
						break;
					case DAIJOUBU_STRING_CLOSE_TYPE:

						if(open_type != DAIJOUBU_STRING_OPEN_TYPE) {
							THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
								DAIJOUBU_LEXER_EXCEPTION_MISMATCHED_LITERAL_STRING_DELIMITER,
								L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
						}

						terminated = true;
						move_next_character();
						break;
					default:
						continue;
				}
			}

			if(!terminated) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNTERMINATED_LITERAL_STRING,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}

			token_insert(token_add(DAIJOUBU_TOKEN_LITERAL_STRING));
			token_at(m_tok_position + 1).text() = text;
		}

		void 
		_daijoubu_lexer::enumerate_subscript(void)
		{
			std::wstring text;

			SERIALIZE_CALL_RECUR(m_lock);

			do {
				text += character();

				if(!has_next_character()) {
					break;
				}

				move_next_character();
			} while(is_subscript_character());

			token_insert(token_add(DAIJOUBU_TOKEN_SUBSCRIPT));
			daijoubu_token &tok = token_at(m_tok_position + 1);
			tok.text() = text;
			tok.value() = unicode_string_as_value(convert_subscript_to_string(text), 
				DAIJOUBU_RADIX_DECIMAL);
		}

		void 
		_daijoubu_lexer::enumerate_superscript(void)
		{
			std::wstring text;

			SERIALIZE_CALL_RECUR(m_lock);

			do {
				text += character();

				if(!has_next_character()) {
					break;
				}

				move_next_character();
			} while(is_superscript_character());

			token_insert(token_add(DAIJOUBU_TOKEN_SUPERSCRIPT));
			daijoubu_token &tok = token_at(m_tok_position + 1);
			tok.text() = text;
			tok.value() = unicode_string_as_value(convert_superscript_to_string(text), 
				DAIJOUBU_RADIX_DECIMAL);
		}

		void 
		_daijoubu_lexer::enumerate_symbol(void)
		{
			std::wstring text;
			daijoubu_token_t type = DAIJOUBU_TOKEN_SYMBOL;

			SERIALIZE_CALL_RECUR(m_lock);

			do {
				text += character();

				if(!has_next_character()) {
					break;
				}

				move_next_character();
			} while(IS_DAIJOUBU_OPERATOR_TYPE(text + character())
					|| IS_DAIJOUBU_SYMBOL_TYPE(text + character()));

			if(IS_DAIJOUBU_OPERATOR_TYPE(text)) {
				type = DAIJOUBU_TOKEN_OPERATOR;
			} else if(!IS_DAIJOUBU_SYMBOL_TYPE(text)) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
					DAIJOUBU_LEXER_EXCEPTION_UNKNOWN_SYMBOL,
					L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
			}

			token_insert(token_add(type));
			daijoubu_token &tok = token_at(m_tok_position + 1);
			tok.subtype() = determine_token_subtype(text, type);
			tok.text() = text;
		}

		bool 
		_daijoubu_lexer::has_next_token(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (token_at(m_tok_position).type() != DAIJOUBU_TOKEN_END);
		}

		bool 
		_daijoubu_lexer::has_previous_token(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_tok_position > 0);
		}

		daijoubu_comment_t 
		_daijoubu_lexer::is_comment_delimiter(void)
		{
			wchar_t ch;
			daijoubu_comment_t result = DAIJOUBU_COMMENT_TYPE_NONE;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();
			switch(ch) {
				case DAIJOUBU_COMMENT_BLOCK_CLOSE:
					result = DAIJOUBU_COMMENT_BLOCK_CLOSE_TYPE;
					break;
				case DAIJOUBU_COMMENT_BLOCK_OPEN:
					result = DAIJOUBU_COMMENT_BLOCK_OPEN_TYPE;
					break;
				case DAIJOUBU_COMMENT_LINE:
					result = DAIJOUBU_COMMENT_LINE_TYPE;
					break;
				case DAIJOUBU_COMMENT_LINE_SIMPLE:

					if(has_next_character()) {

						ch = m_ch_buffer.at(m_ch_position + 1);
						if(ch == DAIJOUBU_COMMENT_BLOCK_CLOSE_SIMPLE) {
							result = DAIJOUBU_COMMENT_BLOCK_CLOSE_SIMPLE_TYPE;
						} else if(ch == DAIJOUBU_COMMENT_LINE_SIMPLE) {
							result = DAIJOUBU_COMMENT_LINE_SIMPLE_TYPE;
						}
					}
					break;
				case DAIJOUBU_COMMENT_BLOCK_OPEN_SIMPLE:

					if(has_next_character()) {

						ch = m_ch_buffer.at(m_ch_position + 1);
						if(ch == DAIJOUBU_COMMENT_LINE_SIMPLE) {
							result = DAIJOUBU_COMMENT_BLOCK_OPEN_SIMPLE_TYPE;
						}
					}
					break;
			}

			return result;
		}

		bool 
		_daijoubu_lexer::is_modifier_character(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return IS_DAIJOUBU_MODIFIER_TYPE(std::wstring(1, character()));
		}

		daijoubu_string_t 
		_daijoubu_lexer::is_string_delimiter(void)
		{
			wchar_t ch;
			daijoubu_string_t result = DAIJOUBU_STRING_TYPE_NONE;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();
			switch(ch) {
				case DAIJOUBU_LITERAL_STRING_CLOSE:
					result = DAIJOUBU_STRING_CLOSE_TYPE;
					break;
				case DAIJOUBU_LITERAL_STRING_OPEN:
					result = DAIJOUBU_STRING_OPEN_TYPE;
					break;
				case DAIJOUBU_LITERAL_STRING_CLOSE_SIMPLE:

					if(has_next_character()) {

						ch = m_ch_buffer.at(m_ch_position + 1);
						if(ch == DAIJOUBU_LITERAL_STRING_CLOSE_SIMPLE) {
							result = DAIJOUBU_STRING_CLOSE_SIMPLE_TYPE;
						}
					}
					break;
				case DAIJOUBU_LITERAL_STRING_OPEN_SIMPLE:

					if(has_next_character()) {

						ch = m_ch_buffer.at(m_ch_position + 1);
						if(ch == DAIJOUBU_LITERAL_STRING_OPEN_SIMPLE) {
							result = DAIJOUBU_STRING_OPEN_SIMPLE_TYPE;
						}
					}
					break;
			}

			return result;
		}

		bool 
		_daijoubu_lexer::is_subscript_character(void)
		{
			wchar_t ch;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();

			return ((ch >= DAIJOUBU_SUBSCRIPT_LOW) 
				&& (ch <= DAIJOUBU_SUBSCRIPT_HIGH));
		}

		bool 
		_daijoubu_lexer::is_superscript_character(void)
		{
			wchar_t ch;

			SERIALIZE_CALL_RECUR(m_lock);

			ch = character();

			return (((ch >= DAIJOUBU_SUPERSCRIPT_FIRST_LOW) 
				&& (ch <= DAIJOUBU_SUPERSCRIPT_FIRST_HIGH))
				|| ((ch >= DAIJOUBU_SUPERSCRIPT_SECOND_LOW) 
				&& (ch <= DAIJOUBU_SUPERSCRIPT_SECOND_HIGH)));
		}

		daijoubu_token &
		_daijoubu_lexer::move_next_token(void)
		{
			daijoubu_unicode_t type;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_next_token()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_NEXT_TOKEN,
					L"Token position: %llu", m_tok_position);
			}

			skip_whitespace();

			if(has_next_character()
					&& (m_tok_position == daijoubu_lexer::size())) {

				type = character_class();
				switch(type) {
					case DAIJOUBU_UNICODE_CLASS_CC:
					case DAIJOUBU_UNICODE_CLASS_CF:
					case DAIJOUBU_UNICODE_CLASS_CN:
					case DAIJOUBU_UNICODE_CLASS_CO:
					case DAIJOUBU_UNICODE_CLASS_CS:
						enumerate_class_control(type);
						break;
					case DAIJOUBU_UNICODE_CLASS_LC:
					case DAIJOUBU_UNICODE_CLASS_LL:
					case DAIJOUBU_UNICODE_CLASS_LM:
					case DAIJOUBU_UNICODE_CLASS_LO:
					case DAIJOUBU_UNICODE_CLASS_LT:
					case DAIJOUBU_UNICODE_CLASS_LU:
						enumerate_class_letter(type);
						break;
					case DAIJOUBU_UNICODE_CLASS_MC:
					case DAIJOUBU_UNICODE_CLASS_ME:
					case DAIJOUBU_UNICODE_CLASS_MN:
						enumerate_class_mark(type);
						break;
					case DAIJOUBU_UNICODE_CLASS_ND:
					case DAIJOUBU_UNICODE_CLASS_NL:
					case DAIJOUBU_UNICODE_CLASS_NO:
						enumerate_class_number(type);
						break;
					case DAIJOUBU_UNICODE_CLASS_PC:
					case DAIJOUBU_UNICODE_CLASS_PD:
					case DAIJOUBU_UNICODE_CLASS_PE:
					case DAIJOUBU_UNICODE_CLASS_PF:
					case DAIJOUBU_UNICODE_CLASS_PI:
					case DAIJOUBU_UNICODE_CLASS_PO:
					case DAIJOUBU_UNICODE_CLASS_PS:
						enumerate_class_punctuation(type);
						break;
					case DAIJOUBU_UNICODE_CLASS_SC:
					case DAIJOUBU_UNICODE_CLASS_SK:
					case DAIJOUBU_UNICODE_CLASS_SM:
					case DAIJOUBU_UNICODE_CLASS_SO:
						enumerate_class_symbol(type);
						break;
					default:
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
							DAIJOUBU_LEXER_EXCEPTION_UNSUPPORTED_CHARACTER_CLASS,
							L"0x%x\n\t%ls", type, CHECK_STRING(character_exception(1, true)));
				}
			}

			++m_tok_position;

			return token_at(m_tok_position);
		}

		daijoubu_token &
		_daijoubu_lexer::move_previous_token(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_previous_token()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_NO_PREVIOUS_TOKEN,
					L"Token position: %llu", m_tok_position);
			}

			return token_at(--m_tok_position);
		}

		void 
		_daijoubu_lexer::reset(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			m_tok_position = 0;
		}

		void 
		_daijoubu_lexer::set(
			__in const std::wstring &input,
			__in_opt bool simple
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			daijoubu_lexer::clear();
			daijoubu_lexer_base::set(input, simple);
			m_tok_list.push_back(token_add(DAIJOUBU_TOKEN_BEGIN));
			m_tok_list.push_back(token_add(DAIJOUBU_TOKEN_END));
		}

		void 
		_daijoubu_lexer::skip_comment_block(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(is_comment_delimiter() == DAIJOUBU_COMMENT_BLOCK_OPEN_TYPE) {

				do {

					if(!has_next_character()) {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
							DAIJOUBU_LEXER_EXCEPTION_UNTERMINATED_COMMENT,
							L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
					}

					move_next_character();

					while(is_comment_delimiter() == DAIJOUBU_COMMENT_BLOCK_OPEN_TYPE) {
						skip_comment_block();
					}
				} while(is_comment_delimiter() != DAIJOUBU_COMMENT_BLOCK_CLOSE_TYPE);

				move_next_character();
			}
		}

		void 
		_daijoubu_lexer::skip_comment_block_simple(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(is_comment_delimiter() == DAIJOUBU_COMMENT_BLOCK_OPEN_SIMPLE_TYPE) {
				move_next_character();

				do {

					if(!has_next_character()) {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(
							DAIJOUBU_LEXER_EXCEPTION_UNTERMINATED_COMMENT,
							L"\n\t%ls", CHECK_STRING(character_exception(1, true)));
					}

					move_next_character();

					while(is_comment_delimiter() == DAIJOUBU_COMMENT_BLOCK_OPEN_SIMPLE_TYPE) {
						skip_comment_block_simple();
					}
				} while(is_comment_delimiter() != DAIJOUBU_COMMENT_BLOCK_CLOSE_SIMPLE_TYPE);

				move_next_character();
				move_next_character();
			}
		}

		void 
		_daijoubu_lexer::skip_comment_line(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(is_comment_delimiter() == DAIJOUBU_COMMENT_LINE_TYPE) {

				do {

					if(!has_next_character()) {
						break;
					}

					move_next_character();
				} while(character() != DAIJOUBU_CHARACTER_NEWLINE);

				if(has_next_character()) {
					move_next_character();
				}
			}
		}

		void 
		_daijoubu_lexer::skip_comment_line_simple(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(is_comment_delimiter() == DAIJOUBU_COMMENT_LINE_SIMPLE_TYPE) {
				move_next_character();

				do {

					if(!has_next_character()) {
						break;
					}

					move_next_character();
				} while(character() != DAIJOUBU_CHARACTER_NEWLINE);

				if(has_next_character()) {
					move_next_character();
				}
			}
		}

		void 
		_daijoubu_lexer::skip_whitespace(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			while(has_next_character() 
					&& daijoubu_unicode::is_whitespace(character_class())) {
				move_next_character();
			}

			if(has_next_character()) {
				skip_comment_block_simple();
				skip_comment_block();
				skip_comment_line_simple();
				skip_comment_line();			

				if((daijoubu_unicode::is_whitespace(character_class()) 
						&& (character() != DAIJOUBU_CHARACTER_END))
						|| (is_comment_delimiter() != DAIJOUBU_COMMENT_TYPE_NONE)) {
					skip_whitespace();
				}
			}
		}

		size_t 
		_daijoubu_lexer::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_tok_list.size() - LEXER_SENTINEL_COUNT);
		}

		std::wstring 
		_daijoubu_lexer::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << L"(" << m_tok_position << L"/" << (m_tok_list.size() - 1)
					<< L") ";
			}

			result << token().to_string(verbose);

			return CHECK_STRING(result.str());
		}

		daijoubu_token &
		_daijoubu_lexer::token(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return token_at(m_tok_position);
		}

		daijoubu_uid 
		_daijoubu_lexer::token_add(
			__in daijoubu_token_t type,
			__in_opt uint16_t subtype
			)
		{
			return token_add(type, subtype, std::wstring(), 0.0, character_line(), 
				character_column(), character_position(), character_column(),
				character_row());
		}

		daijoubu_uid 
		_daijoubu_lexer::token_add(
			__in daijoubu_token_t type,
			__in uint16_t subtype,
			__in_opt const std::wstring &text,
			__in_opt long double value,
			__in_opt const std::wstring &line,
			__in_opt size_t offset,
			__in_opt size_t position,
			__in_opt size_t column,
			__in_opt size_t row
			)
		{
			daijoubu_uid result;
			daijoubu_token_factory_ptr fact = NULL;

			SERIALIZE_CALL_RECUR(m_lock);

			fact = daijoubu::acquire()->acquire_token_factory();
			result = fact->generate(type, subtype);
			daijoubu_token &tok = fact->at(result);
			tok.text() = text;
			tok.value() = value;
			tok.line() = line;
			tok.offset() = offset;
			tok.position() = position;
			tok.column() = column;
			tok.row() = row;

			return result;
		}

		std::wstring 
		_daijoubu_lexer::token_as_string(
			__in daijoubu_token &token,
			__in_opt bool verbose
			)
		{
			return daijoubu_token::token_as_string(token, verbose);
		}

		daijoubu_token &
		_daijoubu_lexer::token_at(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(position >= m_tok_list.size()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
					L"Token position: %llu", position);
			}

			return daijoubu::acquire()->acquire_token_factory()->at(
				m_tok_list.at(position));
		}

		void 
		_daijoubu_lexer::token_insert(
			__in daijoubu_uid uid
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			m_tok_list.insert(m_tok_list.begin() + m_tok_position + 1, uid);
		}

		std::wstring 
		_daijoubu_lexer::token_exception(
			__in size_t tab,
			__in_opt bool verbose
			)
		{
			wchar_t ch;
			std::wstring ln;
			size_t iter, position;
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			daijoubu_token &tok = token();

			ln = tok.line();
			if(!ln.empty()) {
				result << ln;

				if(verbose) {
					result << L" (" << tok.row() << L":" << tok.column() << L")";
				}

				result << std::endl;

				for(iter = 0; iter < tab; ++iter) {
					result << DAIJOUBU_CHARACTER_TAB;
				}

				position = tok.offset();
				for(iter = 0; iter < position; ++iter) {

					if(position >= ln.size()) {
						THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
							L"Character position: %llu", position);
					}

					ch = ln.at(position);
					if(ch == DAIJOUBU_CHARACTER_TAB) {
						result << DAIJOUBU_CHARACTER_TAB;
					} else {
						result << L' ';
					}
				}

				result << L'^';
			}

			return CHECK_STRING(result.str());
		}

		size_t 
		_daijoubu_lexer::token_position(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_tok_position;
		}

		void 
		_daijoubu_lexer::token_remove(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(position >= m_tok_list.size()) {
				THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
					L"Token position: %llu", position);
			}

			daijoubu::acquire()->acquire_token_factory()->decrement_reference(
				m_tok_list.at(position));
			m_tok_list.erase(m_tok_list.begin() + position);

			if(m_tok_position >= position) {
				--m_tok_position;
			}
		}
	}
}
