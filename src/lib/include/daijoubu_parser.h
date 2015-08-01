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

#ifndef DAIJOUBU_PARSER_H_
#define DAIJOUBU_PARSER_H_

#include <vector>

namespace DAIJOUBU {

	namespace LANGUAGE {

		typedef std::vector<daijoubu_uid> daijoubu_statement;

		typedef class _daijoubu_parser :
				protected daijoubu_lexer {

			public:

				_daijoubu_parser(
					__in_opt const std::wstring &input = std::wstring(),
					__in_opt bool simple = false
					);

				_daijoubu_parser(
					__in const _daijoubu_parser &other
					);

				virtual ~_daijoubu_parser(void);

				_daijoubu_parser &operator=(
					__in const _daijoubu_parser &other
					);

				virtual void clear(void);

				virtual void discover(void);

				bool has_next_statement(void);

				bool has_previous_statement(void);

				daijoubu_statement &move_next_statement(void);

				daijoubu_statement &move_previous_statement(void);

				virtual void reset(void);

				virtual void set(
					__in const std::wstring &input,
					__in_opt bool simple = false
					);

				virtual size_t size(void);

				daijoubu_statement &statement(void);

				size_t statement_position(void);

				static std::wstring statement_as_string(
					__in const daijoubu_statement &statement,
					__in_opt bool verbose = false
					);

				std::wstring statement_exception(
					__in size_t tab,
					__in_opt bool verbose = false
					);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

			protected:

				size_t enumerate_control_case(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_elif(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_else(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_final(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_for(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_for_initial(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_for_iterator(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_if(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_control_switch(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_expression(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_assignment(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_call_function(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_call_native(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_control(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_list(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				size_t enumerate_statement_unary(
					__inout daijoubu_statement &statement,
					__in size_t parent_position
					);

				static daijoubu_node &node_at_uid(
					__in daijoubu_uid uid
					);

				static daijoubu_node_factory_ptr node_factory(void);

				daijoubu_statement statement_add(void);

				daijoubu_statement &statement_add(
					__in daijoubu_uid root_uid
					);

				static size_t statement_add_child(
					__in daijoubu_statement &statement,
					__in daijoubu_uid child_uid,
					__in size_t parent_position
					);

				static void statement_as_string_nested(
					__out std::wstringstream &stream,
					__in const daijoubu_statement &statement,
					__in size_t position,
					__in size_t tab,
					__in_opt bool verbose = false
					);

				daijoubu_statement &statement_at(
					__in size_t position
					);

				daijoubu_statement &statement_begin(void);

				daijoubu_statement &statement_end(void);

				void statement_insert(
					__in const daijoubu_statement &statement
					);

				void statement_remove(
					__in size_t position
					);

				static daijoubu_token &token_at_uid(
					__in daijoubu_uid uid
					);

				std::vector<daijoubu_statement> m_stmt_list;

				size_t m_stmt_position;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_parser, *daijoubu_parser_ptr;
	}
}

#endif // DAIJOUBU_PARSER_H_
