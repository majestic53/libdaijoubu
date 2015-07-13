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

#ifndef DAIJOUBU_LANGUAGE_H_
#define DAIJOUBU_LANGUAGE_H_

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define DAIJOUBU_CHARACTER(_CH_) ((wchar_t) _CH_)
		#define DAIJOUBU_COMMENT_LINE DAIJOUBU_CHARACTER(L'※')
		#define DAIJOUBU_COMMENT_BLOCK_CLOSE DAIJOUBU_CHARACTER(L'】')
		#define DAIJOUBU_COMMENT_BLOCK_OPEN DAIJOUBU_CHARACTER(L'【')

		typedef enum {
			DAIJOUBU_RADIX_36 = 0,
			DAIJOUBU_RADIX_BINARY,
			DAIJOUBU_RADIX_DECIMAL,
			DAIJOUBU_RADIX_HEXIDECIMAL,
			DAIJOUBU_RADIX_OCTAL,
		} daijoubu_radix_t;

		#define DAIJOUBU_RADIX_MAX DAIJOUBU_RADIX_OCTAL

		extern uint32_t string_as_value(
			__in const std::string &input,
			__in daijoubu_radix_t radix
			);
	}
}

#endif // DAIJOUBU_LANGUAGE_H_
