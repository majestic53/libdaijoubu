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

#ifndef DAIJOUBU_UNICODE_TYPE_H_
#define DAIJOUBU_UNICODE_TYPE_H_

namespace DAIJOUBU {

	namespace COMPONENT {

		#define DAIJOUBU_UNICODE_HEADER L"(UNICODE)"

		#ifndef NDEBUG
		#define DAIJOUBU_UNICODE_EXCEPTION_HEADER DAIJOUBU_UNICODE_HEADER
		#else
		#define DAIJOUBU_UNICODE_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			DAIJOUBU_UNICODE_EXCEPTION_ALLOCATION = 0,
			DAIJOUBU_UNICODE_EXCEPTION_INITIALIZED,
			DAIJOUBU_UNICODE_EXCEPTION_NOT_FOUND,
			DAIJOUBU_UNICODE_EXCEPTION_UNINITIALIZED,
			DAIJOUBU_UNICODE_EXCEPTION_UNKNOWN,
		};

		#define DAIJOUBU_UNICODE_EXCEPTION_MAX DAIJOUBU_UNICODE_EXCEPTION_UNKNOWN

		static const std::wstring DAIJOUBU_UNICODE_EXCEPTION_STR[] = {
			DAIJOUBU_UNICODE_EXCEPTION_HEADER L" Failed to allocate component",
			DAIJOUBU_UNICODE_EXCEPTION_HEADER L" Component is initialized",
			DAIJOUBU_UNICODE_EXCEPTION_HEADER L" File does not exist", 
			DAIJOUBU_UNICODE_EXCEPTION_HEADER L" Component in uninitialized",
			DAIJOUBU_UNICODE_EXCEPTION_HEADER L" Unknown unicode character",
			};

		#define DAIJOUBU_UNICODE_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_UNICODE_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			CHECK_STRING(DAIJOUBU_UNICODE_EXCEPTION_STR[_TYPE_]))

		#define THROW_DAIJOUBU_UNICODE_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_UNICODE, \
			DAIJOUBU_UNICODE_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_DAIJOUBU_UNICODE_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_UNICODE, \
			DAIJOUBU_UNICODE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _daijoubu_unicode;
		typedef _daijoubu_unicode daijoubu_unicode, *daijoubu_unicode_ptr;			
	}
}

#endif // DAIJOUBU_UNICODE_TYPE_H_
