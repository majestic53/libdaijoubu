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

#include <fstream>
#include <locale>
#include "../lib/include/daijoubu.h"

#define DAIJOUBU_TEST
#ifdef DAIJOUBU_TEST

enum {
	DAIJOUBU_TEST_ARG_CALL = 0,
	DAIJOUBU_TEST_ARG_PATH,
};

#define DAIJOUBU_TEST_ARG_MAX DAIJOUBU_TEST_ARG_PATH
#define DAIJOUBU_TEST_ARG_COUNT (DAIJOUBU_TEST_ARG_MAX + 1)
#define DAIJOUBU_TEST_LEXER_BASE
//#define DAIJOUBU_TEST_LEXER
//#define DAIJOUBU_TEST_PARSER
#endif // DAIJOUBU_TEST

int 
main(
	__in int count,
	__in const char **arguments
	) 
{
	uint32_t id;
	int result = 0;
	daijoubu_ptr inst = NULL;
	daijoubu_region_t region;
	std::wstring input, message;

	std::setlocale(LC_CTYPE, std::string().c_str());

	try {

		std::wcout << L"libdaijoubu " << daijoubu::version() << std::endl
			<< L"Copyright (C) 2015 David Jolly" << std::endl << std::endl;

		inst = daijoubu::acquire();
		inst->initialize();
		//std::wcout << inst->to_string(true) << std::endl;

#ifdef DAIJOUBU_TEST

		input = L"";

#ifdef DAIJOUBU_TEST_LEXER_BASE
		daijoubu_lexer_base comp(input);
		std::wcout << L"Size: " << comp.size() << std::endl;

		while(comp.has_next_character()) {
			std::wcout << comp.to_string(true) << std::endl;
			comp.move_next_character();
		}

		std::wcout << comp.to_string(true) << std::endl;

		while(comp.has_previous_character()) {
			comp.move_previous_character();
			std::wcout << comp.to_string(true) << std::endl;
		}
#endif // DAIJOUBU_TEST_LEXER_BASE

#ifdef DAIJOUBU_TEST_LEXER
		daijoubu_lexer comp(input);

		comp.discover();
		std::wcout << L"Size: " << comp.size() << std::endl;

		while(comp.has_next_token()) {
			std::wcout << comp.to_string(true) << std::endl;
			comp.move_next_token();
		}

		std::wcout << comp.to_string(true) << std::endl;

		while(comp.has_previous_token()) {
			comp.move_previous_token();
			std::wcout << comp.to_string(true) << std::endl;
		}
#endif // DAIJOUBU_TEST_LEXER

#ifdef DAIJOUBU_TEST_PARSER
		daijoubu_parser comp(input);

		comp.discover();
		std::wcout << L"Size: " << comp.size() << std::endl;

		while(comp.has_next_statement()) {
			std::wcout << comp.to_string(true) << std::endl;
			comp.move_next_statement();
		}

		std::wcout << comp.to_string(true) << std::endl;

		while(comp.has_previous_statement()) {
			comp.move_previous_statement();
			std::wcout << comp.to_string(true) << std::endl;
		}
#endif // DAIJOUBU_TEST_PARSER

#else

		// TODO

#endif // DAIJOUBU_TEST

		inst->uninitialize();
		//std::wcout << inst->to_string(true) << std::endl;
	} catch(std::runtime_error &) {
		id = daijoubu::exception_information(region, message);
		std::wcerr << L"[" << VALUE_AS_HEX(uint32_t, id) << "]" << message << std::endl;
		result = -1;
	}

	return result;
}
