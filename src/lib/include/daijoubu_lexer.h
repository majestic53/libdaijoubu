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

#ifndef DAIJOUBU_LEXER_H_
#define DAIJOUBU_LEXER_H_

#include <map>
#include <vector>

namespace DAIJOUBU {

	namespace LANGUAGE {

		typedef enum {
			DAIJOUBU_CHAR_ALPHA = 0,
			DAIJOUBU_CHAR_DIGIT,
			DAIJOUBU_CHAR_END,
			DAIJOUBU_CHAR_SPACE,
			DAIJOUBU_CHAR_SYMBOL,
		} daijoubu_char_t;

		#define DAIJOUBU_CHAR_MAX DAIJOUBU_CHAR_SYMBOL

		typedef class _daijoubu_lexer_base {

			public:

				_daijoubu_lexer_base(
					__in_opt const std::wstring &input = std::wstring()
					);

				_daijoubu_lexer_base(
					__in const _daijoubu_lexer_base &other
					);

				virtual ~_daijoubu_lexer_base(void);

				_daijoubu_lexer_base &operator=(
					__in const _daijoubu_lexer_base &other
					);

				wchar_t character(void);

				std::wstring &character_buffer(void);

				size_t character_column(void);

				std::wstring character_exception(
					__in size_t tab,
					__in_opt bool verbose = false
					);

				std::wstring character_line(void);

				size_t character_position(void);

				size_t character_row(void);

				static daijoubu_char_t character_to_type(
					__in wchar_t input
					);

				daijoubu_char_t character_type(void);

				static std::wstring character_as_string(
					__in daijoubu_char_t type
					);

				virtual void clear(void);

				bool has_next_character(void);

				bool has_previous_character(void);

				wchar_t move_next_character(void);

				wchar_t move_previous_character(void);

				virtual void reset(void);

				virtual void set(
					__in const std::wstring &input
					);

				virtual size_t size(void);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

			protected:

				std::map<size_t, std::pair<size_t, std::wstring>>::iterator find(
					__in size_t row
					);

				std::wstring m_ch_buffer;

				size_t m_ch_column;

				std::map<size_t, std::pair<size_t, std::wstring>> m_ch_line_map;

				size_t m_ch_position;

				size_t m_ch_row;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_lexer_base, *daijoubu_lexer_base_ptr;

		typedef class _daijoubu_lexer :
				protected daijoubu_lexer_base {

			public:

				_daijoubu_lexer(
					__in_opt const std::wstring &input = std::wstring()
					);

				_daijoubu_lexer(
					__in const _daijoubu_lexer &other
					);

				virtual ~_daijoubu_lexer(void);

				_daijoubu_lexer &operator=(
					__in const _daijoubu_lexer &other
					);

				virtual void clear(void);

				bool has_next_token(void);

				bool has_previous_token(void);

				daijoubu_token &move_next_token(void);

				daijoubu_token &move_previous_token(void);

				virtual void reset(void);

				virtual void set(
					__in const std::wstring &input
					);

				virtual size_t size(void);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

				daijoubu_token &token(void);

				static std::wstring token_as_string(
					__in daijoubu_token &token,
					__in_opt bool verbose = false
					);

				std::wstring token_exception(
					__in size_t tab,
					__in_opt bool verbose = false
					);

				size_t token_position(void);

			protected:

				daijoubu_uid token_add(
					__in_opt daijoubu_token_t type = INVALID_TOKEN_TYPE,
					__in_opt uint16_t subtype = INVALID_TOKEN_SUBTYPE,
					__in_opt const std::wstring &text = std::wstring(),
					__in_opt const std::wstring &line = std::wstring(),
					__in_opt size_t offset = 0,
					__in_opt size_t position = 0,
					__in_opt size_t column = 0,
					__in_opt size_t row = 0
					);

				daijoubu_token &token_at(
					__in size_t position
					);

				void token_remove(
					__in size_t position
					);

				std::vector<daijoubu_uid> m_tok_list;
	
				size_t m_tok_position;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_lexer, *daijoubu_lexer_ptr;
	}
}

#endif // DAIJOUBU_LEXER_H_
