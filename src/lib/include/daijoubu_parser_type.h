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

#ifndef DAIJOUBU_PARSER_TYPE_H_
#define DAIJOUBU_PARSER_TYPE_H_

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define DAIJOUBU_PARSER_HEADER L"(PAR)"

		#ifndef NDEBUG
		#define DAIJOUBU_PARSER_EXCEPTION_HEADER DAIJOUBU_PARSER_HEADER
		#else
		#define DAIJOUBU_PARSER_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			DAIJOUBU_PARSER_EXCEPTION_EXPECTING_ASSIGNMENT_OR_CALL = 0,
			DAIJOUBU_PARSER_EXCEPTION_EXPECTING_FUNCTION,
			DAIJOUBU_PARSER_EXCEPTION_EXPECTING_STATEMENT,
			DAIJOUBU_PARSER_EXCEPTION_EXPECTING_SYMBOL,
			DAIJOUBU_PARSER_EXCEPTION_EXPECTING_UNARY_OPERATOR,
			DAIJOUBU_PARSER_EXCEPTION_INVALID_CONTROL,
			DAIJOUBU_PARSER_EXCEPTION_INVALID_POSITION,
			DAIJOUBU_PARSER_EXCEPTION_NO_NEXT_STATEMENT,
			DAIJOUBU_PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT,
		};

		#define DAIJOUBU_PARSER_EXCEPTION_MAX DAIJOUBU_PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT

		static const std::wstring DAIJOUBU_PARSER_EXCEPTION_STR[] = {
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Expecting assignment or call",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Expecting function call or definition",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Expecting statement",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Expecting symbol",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Expecting unary operator",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Invalid control",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" Invalid position",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" No next statement exists",
			DAIJOUBU_PARSER_EXCEPTION_HEADER L" No previous statement exists",
			};

		#define DAIJOUBU_PARSER_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_PARSER_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			CHECK_STRING(DAIJOUBU_PARSER_EXCEPTION_STR[_TYPE_]))

		#define THROW_DAIJOUBU_PARSER_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_PARSER, \
			DAIJOUBU_PARSER_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_PARSER, \
			DAIJOUBU_PARSER_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _daijoubu_parser;
		typedef _daijoubu_parser daijoubu_parser, *daijoubu_parser_ptr;			
	}
}

#endif // DAIJOUBU_PARSER_TYPE_H_
