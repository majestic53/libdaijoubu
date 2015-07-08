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
					__in_opt const std::wstring &input = std::wstring(),
					__in_opt bool is_file = false
					);

				_daijoubu_lexer_base(
					__in const _daijoubu_lexer_base &other
					);

				virtual ~_daijoubu_lexer_base(void);

				_daijoubu_lexer_base &operator=(
					__in const _daijoubu_lexer_base &other
					);

				std::wstring &buffer(void);

				wchar_t character(void);

				static daijoubu_char_t character_type(
					__in wchar_t input
					);

				void clear(void);

				size_t column(void);

				bool has_next(void);

				bool has_previous(void);

				std::wstring line(void);

				wchar_t move_next(void);

				wchar_t move_previous(void);

				size_t position(void);

				void reset(void);

				size_t row(void);

				void set(
					__in const std::wstring &input,
					__in_opt bool is_file = false
					);

				size_t size(void);

				daijoubu_char_t type(void);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

			protected:

				std::map<size_t, std::pair<size_t, std::wstring>>::iterator find(
					__in size_t row
					);

				std::wstring m_buffer;

				size_t m_column;

				std::map<size_t, std::pair<size_t, std::wstring>> m_line_map;

				size_t m_position;

				size_t m_row;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_lexer_base, *daijoubu_lexer_base_ptr;
	}
}

#endif // DAIJOUBU_LEXER_H_
