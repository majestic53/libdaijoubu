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

#ifndef DAIJOUBU_EXCEPTION_H_
#define DAIJOUBU_EXCEPTION_H_

namespace DAIJOUBU {

	#define EXCEPTION_HEADER L"(EXCEPTION)"
	#define UNKNOWN_EXCEPTION L"Unknown exception"

	typedef enum {
		DAIJOUBU_REGION_NONE = 0,
		DAIJOUBU_REGION_LEXER,
		DAIJOUBU_REGION_LIBRARY,
		DAIJOUBU_REGION_TOKEN,
		DAIJOUBU_REGION_UID,
	} daijoubu_region_t;

	#define DAIJOUBU_REGION_MAX DAIJOUBU_REGION_UID

	static const std::wstring DAIJOUBU_REGION_STR[] = {
		L"NONE", L"LEXER", L"LIBRARY", L"TOKEN", L"UID",
		};

	#define DAIJOUBU_REGION_STRING(_TYPE_) \
		((_TYPE_) > DAIJOUBU_REGION_MAX ? UNKNOWN : \
		CHECK_STRING(DAIJOUBU_REGION_STR[_TYPE_]))

	extern void _last_exception(
		__out uint32_t &id,
		__out daijoubu_region_t &region,
		__out std::wstring &message
		);

	extern void _throw_exception(
		__in uint32_t id,
		__in daijoubu_region_t region,
		__in const std::wstring &except,
		__in const std::string &file,
		__in size_t line,
		__in const wchar_t *format,
		...
		);

	#define THROW_EXCEPTION(_ID_,_REGION_, _EXCEPT_) \
		_throw_exception(_ID_, _REGION_, _EXCEPT_, __FILE__, __LINE__, \
		NULL)
	#define THROW_EXCEPTION_MESSAGE(_ID_, _REGION_, _EXCEPT_, _FORMAT_, ...) \
		_throw_exception(_ID_, _REGION_, _EXCEPT_, __FILE__, __LINE__, \
		_FORMAT_, __VA_ARGS__)
}

#endif // DAIJOUBU_EXCEPTION_H_
