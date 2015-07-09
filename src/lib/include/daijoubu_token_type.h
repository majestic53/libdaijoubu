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

#ifndef DAIJOUBU_TOKEN_TYPE_H_
#define DAIJOUBU_TOKEN_TYPE_H_

namespace DAIJOUBU {

	namespace COMPONENT {

		#define DAIJOUBU_TOKEN_HEADER "(TOK)"

		#ifndef NDEBUG
		#define DAIJOUBU_TOKEN_EXCEPTION_HEADER DAIJOUBU_TOKEN_HEADER
		#else
		#define DAIJOUBU_TOKEN_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			DAIJOUBU_TOKEN_EXCEPTION_ALLOCATION = 0,
			DAIJOUBU_TOKEN_EXCEPTION_INITIALIZED,
			DAIJOUBU_TOKEN_EXCEPTION_NOT_FOUND,
			DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED,
		};

		#define DAIJOUBU_TOKEN_EXCEPTION_MAX DAIJOUBU_TOKEN_EXCEPTION_UNINITIALIZED

		static const std::wstring DAIJOUBU_TOKEN_EXCEPTION_STR[] = {
			DAIJOUBU_TOKEN_EXCEPTION_HEADER L" Failed to allocate component",
			DAIJOUBU_TOKEN_EXCEPTION_HEADER L" Component is initialized",
			DAIJOUBU_TOKEN_EXCEPTION_HEADER L" Entry does not exist",
			DAIJOUBU_TOKEN_EXCEPTION_HEADER L" Component is uninitialized",
			};

		#define DAIJOUBU_TOKEN_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_TOKEN_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			CHECK_STRING(DAIJOUBU_TOKEN_EXCEPTION_STR[_TYPE_]))

		#define THROW_DAIJOUBU_TOKEN_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_TOKEN, \
			DAIJOUBU_TOKEN_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_DAIJOUBU_TOKEN_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_TOKEN, \
			DAIJOUBU_TOKEN_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _daijoubu_token;
		typedef _daijoubu_token _daijoubu_token, *_daijoubu_token_ptr;

		class _daijoubu_token_factory;
		typedef _daijoubu_token_factory _daijoubu_token_factory, *_daijoubu_token_factory_ptr;
	}
}

#endif // DAIJOUBU_TOKEN_TYPE_H_
