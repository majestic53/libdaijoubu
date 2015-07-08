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

#include <cstdarg>
#include <stdexcept>
#include "../include/daijoubu.h"

namespace DAIJOUBU {

	#define EXCEPTION_MAX_LENGTH 0x200

	enum {
		EXCEPTION_ERROR_ALLOCATION = 0,
		EXCEPTION_ERROR_MALFORMED,
	};

	#define EXCEPTION_ERROR_MAX EXCEPTION_ERROR_MALFORMED

	static const wchar_t *EXCEPTION_ERROR_STR[] = {
		L"Failed to allocate exception buffer",
		L"Exception format is malformed",
		};

	#define EXCEPTION_ERROR_STRING(_TYPE_) \
		((_TYPE_) > EXCEPTION_ERROR_MAX ? UNKNOWN_EXCEPTION : \
		EXCEPTION_ERROR_STR[_TYPE_])

	static uint32_t m_id = 0;

	static wchar_t m_message[EXCEPTION_MAX_LENGTH] = { 0 };

	static daijoubu_region_t m_region = DAIJOUBU_REGION_NONE;

	void 
	_last_exception(
		__out uint32_t &id,
		__out daijoubu_region_t &region,
		__out std::wstring &message
		)
	{
		id = m_id;
		region = m_region;
		message = m_message;
	}

	void 
	_throw_exception(
		__in uint32_t id,
		__in daijoubu_region_t region,
		__in const std::wstring &except,
		__in const std::string &file,
		__in size_t line,
		__in const wchar_t *format,
		...
		)
	{
		int len;
		va_list args;
		std::wstring buf;
		std::wstringstream result;
		const wchar_t *buf_err = NULL;

		result << except;

		if(format) {
			va_start(args, format);
			len = vswprintf(m_message, EXCEPTION_MAX_LENGTH, format, args);
			std::wmemset(m_message, 0, EXCEPTION_MAX_LENGTH);

			if(len > 0) {
				va_end(args);
				va_start(args, format);
				buf.resize(len + 1);

				len = vswprintf((wchar_t *) &buf[0], len + 1, format, args);
				if(len < 0) {
					buf_err = EXCEPTION_ERROR_STRING(
						EXCEPTION_ERROR_MALFORMED);
				}
			} else {
				buf_err = EXCEPTION_ERROR_STRING(
					EXCEPTION_ERROR_MALFORMED);
			}

			va_end(args);
		}

		if(buf_err) {
			result << L": " << buf_err;
			buf_err = NULL;
		} else if(!buf.empty()) {
			result << L": " << buf;
		}

#ifndef NDEBUG
		result << L" (" << file.c_str() << L":" << line << L")";
#endif // NDEBUG
		m_id = id;
		m_region = region;
		std::wmemcpy(m_message, result.str().c_str(), result.str().size());
		throw std::runtime_error("");
	}
}
