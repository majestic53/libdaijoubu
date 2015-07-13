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

#include <cmath>
#include "../include/daijoubu.h"
#include "../include/daijoubu_language_type.h"

namespace DAIJOUBU {

	namespace LANGUAGE {

		static const char RADIX_CHAR[] = {
			'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z',
			};

		static const uint32_t RADIX_SCALE[] = {
			36, 2, 10, 16, 8,
			};

		uint32_t 
		string_as_value(
			__in const std::string &input,
			__in daijoubu_radix_t radix
			)
		{
			char ch;
			uint32_t result = 0;
			size_t iter = 0, radix_iter;

			if(!input.empty()) {

				switch(radix) {
					case DAIJOUBU_RADIX_36:
					case DAIJOUBU_RADIX_BINARY:
					case DAIJOUBU_RADIX_DECIMAL:
					case DAIJOUBU_RADIX_HEXIDECIMAL:
					case DAIJOUBU_RADIX_OCTAL:

						for(; iter < input.size(); ++iter) {
							ch = std::tolower(input.at(iter));

							for(radix_iter = 0; radix_iter < RADIX_SCALE[radix]; 
									++radix_iter) {

								if(ch == RADIX_CHAR[radix_iter]) {
									break;
								}
							}

							if(radix_iter >= RADIX_SCALE[radix]) {
								THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
									DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_CHARACTER,
									L"\'%c\' (radix: %lu)", ch, RADIX_SCALE[radix]);
							}

							result += radix_iter * std::pow(RADIX_SCALE[radix], 
								(input.size() - iter - 1));
						}
						break;
					default:
						THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
							DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_RADIX,
							L"%lu", radix);
				}
			}

			return result;
		}
	}
}
