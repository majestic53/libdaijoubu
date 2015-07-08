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

#ifndef DAIJOUBU_TYPE_H_
#define DAIJOUBU_TYPE_H_

using namespace DAIJOUBU;

namespace DAIJOUBU {

	#define DAIJOUBU_HEADER L"(LIB)"

	enum {
		DAIJOUBU_EXCEPTION_ALLOCATION = 0,
		DAIJOUBU_EXCEPTION_INITIALIZED,
		DAIJOUBU_EXCEPTION_UNINITIALIZED,
	};

	#define DAIJOUBU_EXCEPTION_MAX DAIJOUBU_EXCEPTION_UNINITIALIZED

	static const std::wstring DAIJOUBU_EXCEPTION_STR[] = {
		DAIJOUBU_HEADER L" Failed to allocate library",
		DAIJOUBU_HEADER L" Library is initialized",
		DAIJOUBU_HEADER L" Library is uninitialized",
		};

	#define DAIJOUBU_EXCEPTION_STRING(_TYPE_) \
		((_TYPE_) > DAIJOUBU_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
		CHECK_STRING(DAIJOUBU_EXCEPTION_STR[_TYPE_]))

	#define THROW_DAIJOUBU_EXCEPTION(_EXCEPT_) \
		THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_LIBRARY, \
		DAIJOUBU_EXCEPTION_STRING(_EXCEPT_))
	#define THROW_DAIJOUBU_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_LIBRARY, \
		DAIJOUBU_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	class _daijoubu;
	typedef _daijoubu daijoubu, *daijoubu_ptr;
}

#endif // DAIJOUBU_TYPE_H_
