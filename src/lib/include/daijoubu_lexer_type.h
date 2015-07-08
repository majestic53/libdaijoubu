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

#ifndef DAIJOUBU_LEXER_TYPE_H_
#define DAIJOUBU_LEXER_TYPE_H_

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define DAIJOUBU_LEXER_HEADER L"(LEX)"

		#ifndef NDEBUG
		#define DAIJOUBU_LEXER_EXCEPTION_HEADER DAIJOUBU_LEXER_HEADER
		#else
		#define DAIJOUBU_LEXER_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			DAIJOUBU_LEXER_EXCEPTION_FILE_NOT_FOUND = 0,
			DAIJOUBU_LEXER_EXCEPTION_INVALID_POSITION,
			DAIJOUBU_LEXER_EXCEPTION_NO_NEXT_CHARACTER,
			DAIJOUBU_LEXER_EXCEPTION_NO_PREVIOUS_CHARACTER,
			DAIJOUBU_LEXER_EXCEPTION_ROW_NOT_FOUND,
		};

		#define DAIJOUBU_LEXER_EXCEPTION_MAX DAIJOUBU_LEXER_EXCEPTION_ROW_NOT_FOUND

		static const std::wstring DAIJOUBU_LEXER_EXCEPTION_STR[] = {
			DAIJOUBU_LEXER_EXCEPTION_HEADER L" File does not exist",
			DAIJOUBU_LEXER_EXCEPTION_HEADER L" Invalid position",
			DAIJOUBU_LEXER_EXCEPTION_HEADER L" No next character exists",
			DAIJOUBU_LEXER_EXCEPTION_HEADER L" No previous character exists",
			DAIJOUBU_LEXER_EXCEPTION_HEADER L" Row does not exist",
			};

		#define DAIJOUBU_LEXER_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_LEXER_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			CHECK_STRING(DAIJOUBU_LEXER_EXCEPTION_STR[_TYPE_]))

		#define THROW_DAIJOUBU_LEXER_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_LEXER, \
			DAIJOUBU_LEXER_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_DAIJOUBU_LEXER_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_LEXER, \
			DAIJOUBU_LEXER_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _daijoubu_lexer_base;
		typedef _daijoubu_lexer_base daijoubu_lexer_base, *daijoubu_lexer_base_ptr;
	}
}

#endif // DAIJOUBU_LEXER_TYPE_H_
