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

#ifndef DAIJOUBU_LANGUAGE_TYPE_H_
#define DAIJOUBU_LANGUAGE_TYPE_H_

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define DAIJOUBU_LANGUAGE_HEADER L"(LANGUAGE)"

		#ifndef NDEBUG
		#define DAIJOUBU_LANGUAGE_EXCEPTION_HEADER DAIJOUBU_LANGUAGE_HEADER
		#else
		#define DAIJOUBU_LANGUAGE_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_CHARACTER = 0,
			DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_RADIX,
		};

		#define DAIJOUBU_LANGUAGE_EXCEPTION_MAX DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_RADIX

		static const std::wstring DAIJOUBU_LANGUAGE_EXCEPTION_STR[] = {
			DAIJOUBU_LANGUAGE_EXCEPTION_HEADER L" Invalid character",
			DAIJOUBU_LANGUAGE_EXCEPTION_HEADER L" Invalid radix",
			};

		#define DAIJOUBU_LANGUAGE_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_LANGUAGE_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			CHECK_STRING(DAIJOUBU_LANGUAGE_EXCEPTION_STR[_TYPE_]))

		#define THROW_DAIJOUBU_LANGUAGE_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(_EXCEPT_, DAIJOUBU_REGION_LANGUAGE, \
			DAIJOUBU_LANGUAGE_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(_EXCEPT_, DAIJOUBU_REGION_LANGUAGE, \
			DAIJOUBU_LANGUAGE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)
	}
}

#endif // DAIJOUBU_LANGUAGE_TYPE_H_
