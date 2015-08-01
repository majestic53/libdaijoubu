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

	static const char RADIX_CHAR[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z',
		};

	static const wchar_t RADIX_WCHAR[] = {
		L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7',
		L'8', L'9', L'a', L'b', L'c', L'd', L'e', L'f',
		L'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n', 
		L'o', L'p', L'q', L'r', L's', L't', L'u', L'v',
		L'w', L'x', L'y', L'z',
		};

	static const uint32_t RADIX_SCALE[] = {
		36, 2, 10, 16, 8,
		};

	std::wstring 
	convert_subscript_to_string(
		__in const std::wstring &input
		)
	{
		std::wstring result;
		std::wstring::const_iterator iter;

		for(iter = input.begin(); iter != input.end(); ++iter) {
			result += ((*iter - DAIJOUBU_SUBSCRIPT_LOW) + L'0');
		}

		return result;
	}

	std::wstring 
	convert_superscript_to_string(
		__in const std::wstring &input
		)
	{
		std::wstring result;
		std::wstring::const_iterator iter;

		for(iter = input.begin(); iter != input.end(); ++iter) {

			switch(*iter) {
				case L'⁰':
					result += L'0';
					break;
				case L'¹':
					result += L'1';
					break;
				case L'²':
					result += L'2';
					break;
				case L'³':
					result += L'3';
					break;
				default:
					result += ((*iter - L'⁴') + L'4');
					break;
			}
		}

		return result;
	}

	uint16_t 
	determine_token_subtype(
		__in const std::wstring &input,
		__in daijoubu_token_t type
		)
	{
		size_t iter = 0, len;
		const std::wstring *str = NULL;
		uint16_t result = INVALID_TOKEN_SUBTYPE;

		if(!input.empty()) {

			if(type <= DAIJOUBU_TOKEN_MAX) {

				len = DAIJOUBU_TOKEN_SUBTYPE_LENGTH(type);
				if(len) {

					str = DAIJOUBU_TOKEN_SUBTYPE_STRINGS(type);
					if(str) {

						for(; iter < len; ++iter) {

							if(input == str[iter]) {
								result = iter;
								break;
							}
						}
					}
				}
			}
		}

		return result;
	}

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

	long double 
	unicode_string_as_value(
		__in const std::wstring &input,
		__in daijoubu_radix_t radix,
		__in_opt bool simple
		)
	{
		wchar_t ch;		
		long double result = 0.0;
		size_t count = 1, iter = 0, radix_iter;
		bool fraction = false, negative = false;

		if(!input.empty()) {

			switch(radix) {
				case DAIJOUBU_RADIX_DECIMAL:

					if((input.at(iter) == DAIJOUBU_LITERAL_NUMERIC_UNARY_NEGATION)
							|| (simple
							&& (input.at(iter) == DAIJOUBU_LITERAL_NUMERIC_UNARY_NEGATION_SIMPLE))) {
						negative = true;
						++iter;
					}

				case DAIJOUBU_RADIX_36:
				case DAIJOUBU_RADIX_BINARY:
				case DAIJOUBU_RADIX_HEXIDECIMAL:
				case DAIJOUBU_RADIX_OCTAL:

					for(; iter < input.size(); ++iter) {
						ch = std::towlower(input.at(iter));

						if(input.at(iter) == DAIJOUBU_LITERAL_NUMERIC_DECIMAL) {

							if(fraction) {
								THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
									DAIJOUBU_LANGUAGE_EXCEPTION_MALFORMED_FLOAT,
									L"\'%lc\' (radix: %lu)", ch, RADIX_SCALE[radix]);
							} else if(radix != DAIJOUBU_RADIX_DECIMAL) {
								THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
									DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_FLOAT,
									L"\'%lc\' (radix: %lu)", ch, RADIX_SCALE[radix]);
							}

							fraction = true;
							result /= std::pow(RADIX_SCALE[radix], input.size() - iter);
							continue;
						}

						for(radix_iter = 0; radix_iter < RADIX_SCALE[radix]; 
								++radix_iter) {

							if(ch == RADIX_WCHAR[radix_iter]) {
								break;
							}
						}

						if(radix_iter >= RADIX_SCALE[radix]) {
							THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
								DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_CHARACTER,
								L"\'%lc\' (radix: %lu)", ch, RADIX_SCALE[radix]);
						}

						if(fraction) {
							result += (radix_iter * (1.0 / std::pow(RADIX_SCALE[radix], 
								count++)));
						} else {
							result += (radix_iter * std::pow(RADIX_SCALE[radix], 
								(input.size() - iter - 1)));
						}
					}
					break;
				default:
					THROW_DAIJOUBU_LANGUAGE_EXCEPTION_MESSAGE(
						DAIJOUBU_LANGUAGE_EXCEPTION_INVALID_RADIX,
						L"%lu", radix);
			}

			if(negative) {
				result *= -1.0;
			}
		}

		return result;
	}

	std::wstring 
	token_subtype_as_unicode_string(
		__in daijoubu_token_t type,
		__in uint16_t subtype
		)
	{
		std::wstring result = INVALID;
		const std::wstring *str = NULL;

		if(type <= DAIJOUBU_TOKEN_MAX) {

			if(subtype < DAIJOUBU_TOKEN_SUBTYPE_LENGTH(type)) {

				str = DAIJOUBU_TOKEN_SUBTYPE_STRINGS(type);
				if(str) {
					result = str[subtype];
				}
			}
		}

		return result;
	}
}
