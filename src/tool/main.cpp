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

#include <locale>
#include "../lib/include/daijoubu.h"

int 
main(void) 
{
	uint32_t id;
	int result = 0;
	std::wstring message;
	daijoubu_region_t region;
	daijoubu_ptr inst = NULL;

	std::setlocale(LC_CTYPE,"");

	try {

		std::wcout << L"libdaijoubu " << daijoubu::version() << std::endl
			<< L"Copyright (C) 2015 David Jolly" << std::endl;

		inst = daijoubu::acquire();
		inst->initialize();
		//std::wcout << inst->to_string(true) << std::endl;

		// TODO

		daijoubu_lexer lex(L"だいじょうぶ。\nabc\n01\n;.\n");

		std::wcout << L"Size: " << lex.size() << std::endl;

		while(lex.has_next_token()) {
			std::wcout << lex.to_string(true) << std::endl;
			lex.move_next_token();
		}

		std::wcout << lex.to_string(true) << std::endl;

		while(lex.has_previous_token()) {
			lex.move_previous_token();
			std::wcout << lex.to_string(true) << std::endl;
		}

		inst->uninitialize();
		//std::wcout << inst->to_string(true) << std::endl;
	} catch(std::runtime_error &exc) {
		id = daijoubu::exception_information(region, message);
		std::wcerr << L"[" << VALUE_AS_HEX(uint32_t, id) << "]" << message << std::endl;
		result = -1;
	}

	return result;
}
