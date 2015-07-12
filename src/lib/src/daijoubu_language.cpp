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

#include "../include/daijoubu.h"
#include "../include/daijoubu_language_type.h"

namespace DAIJOUBU {

	namespace LANGUAGE {

		static const char LANGUAGE_CHAR[] = {
			'0', '1', '2', '3', '4', '5', '6', '7', 
			'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
			};

		static const LANGUAGE_SCALE[] = {
			
			};

		wchar_t 
		string_as_wchar(
			__in const std::wstring &input,
			__in daijoubu_radix_t radix
			)
		{
			wchar_t result = 0;

			switch(radix) {
				case DAIJOUBU_RADIX_BINARY:
				case DAIJOUBU_RADIX_DECIMAL:
				case DAIJOUBU_RADIX_HEXIDECIMAL:
				case DAIJOUBU_RADIX_OCTAL:

					// TODO
					break;
				default:
					THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_RADIX,
						L"%lu", radix);
			}

			return result;
		}
	}
}
