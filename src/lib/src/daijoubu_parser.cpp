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
#include "../include/daijoubu_parser_type.h"

namespace DAIJOUBU {

	namespace LANGUAGE {

		#define PARSER_SENTINEL_COUNT 2

		_daijoubu_parser::_daijoubu_parser(
			__in_opt const std::wstring &input,
			__in_opt bool simple
			) :
				m_stmt_position(0)
		{
			daijoubu_parser::set(input, simple);
		}

		_daijoubu_parser::_daijoubu_parser(
			__in const _daijoubu_parser &other
			) :
				daijoubu_lexer(other),
				m_stmt_list(other.m_stmt_list),
				m_stmt_position(other.m_stmt_position)
		{
			return;
		}

		_daijoubu_parser::~_daijoubu_parser(void)
		{
			daijoubu_parser::clear();
		}

		_daijoubu_parser &
		_daijoubu_parser::operator=(
			__in const _daijoubu_parser &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				daijoubu_lexer::operator=(other);
				m_stmt_list = other.m_stmt_list;
				m_stmt_position = other.m_stmt_position;
			}

			return *this;
		}

		void 
		_daijoubu_parser::clear(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			daijoubu_lexer::reset();
			m_stmt_list.clear();
			m_stmt_position = 0;
		}

		void 
		_daijoubu_parser::discover(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			while(has_next_statement()) {
				move_next_statement();
			}

			daijoubu_parser::reset();
		}

		size_t 
		_daijoubu_parser::enumerate_control_case(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_elif(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_else(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_final(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_for(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_for_initial(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_for_iterator(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_if(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_control_switch(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_expression(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = statement_add_child(statement, token().uid(), parent_position);
			move_next_token();
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_assignment(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_call_function(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_call_native(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_control(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_list(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		size_t 
		_daijoubu_parser::enumerate_statement_unary(
			__inout daijoubu_statement &statement,
			__in size_t parent_position
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
		}

		bool 
		_daijoubu_parser::has_next_statement(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (token_at_uid(statement().front()).type() != DAIJOUBU_TOKEN_END);
		}

		bool 
		_daijoubu_parser::has_previous_statement(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_stmt_position > 0);
		}

		daijoubu_statement &
		_daijoubu_parser::move_next_statement(void)
		{
			daijoubu_statement stmt;

			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_next_statement()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_NO_NEXT_STATEMENT,
					L"Statement position: %llu", m_stmt_position);
			}

			if(token().type() == DAIJOUBU_TOKEN_BEGIN) {
				move_next_token();
			}

			if(has_next_token()
					&& (m_stmt_position == daijoubu_parser::size())) {
				stmt = statement_add();
				enumerate_statement(stmt, 0);
				statement_insert(stmt);
			}

			++m_stmt_position;

			return statement();
		}

		daijoubu_statement &
		_daijoubu_parser::move_previous_statement(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_previous_statement()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT,
					L"Statement position: %llu", m_stmt_position);
			}

			return statement_at(--m_stmt_position);
		}

		daijoubu_node &
		_daijoubu_parser::node_at_uid(
			__in daijoubu_uid uid
			)
		{
			return node_factory()->at(uid);
		}

		daijoubu_node_factory_ptr 
		_daijoubu_parser::node_factory(void)
		{
			return daijoubu::acquire()->acquire_node_factory();
		}

		void 
		_daijoubu_parser::reset(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			m_stmt_position = 0;
		}

		void 
		_daijoubu_parser::set(
			__in const std::wstring &input,
			__in_opt bool simple
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			daijoubu_parser::clear();
			daijoubu_lexer::set(input, simple);
			statement_add(token_begin());
			statement_add(token_end());
		}

		size_t 
		_daijoubu_parser::size(void)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			result = m_stmt_list.size();
			if(result >= PARSER_SENTINEL_COUNT) {
				result -= PARSER_SENTINEL_COUNT;
			}

			return result;
		}

		daijoubu_statement &
		_daijoubu_parser::statement(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return statement_at(m_stmt_position);
		}

		daijoubu_statement 
		_daijoubu_parser::statement_add(void)
		{
			daijoubu_statement stmt;

			SERIALIZE_CALL_RECUR(m_lock);

			stmt.push_back(node_factory()->generate(
				token_factory()->generate(DAIJOUBU_TOKEN_STATEMENT)));

			return stmt;
		}

		daijoubu_statement & 
		_daijoubu_parser::statement_add(
			__in daijoubu_uid root_uid
			)
		{
			daijoubu_statement stmt;

			SERIALIZE_CALL_RECUR(m_lock);

			stmt.push_back(node_factory()->generate(root_uid));
			m_stmt_list.push_back(stmt);

			return m_stmt_list.back();
		}

		size_t 
		_daijoubu_parser::statement_add_child(
			__in daijoubu_statement &statement,
			__in daijoubu_uid child_uid,
			__in size_t parent_position
			)
		{
			size_t result;
			daijoubu_uid uid;

			if(parent_position >= statement.size()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_INVALID_POSITION,
					L"Parent statement position: %llu", parent_position);
			}

			result = statement.size();

			if(parent_position != INVALID_NODE_PARENT) {
				node_at_uid(statement.at(parent_position)).child_insert(result);
			}

			uid = node_factory()->generate(child_uid);
			node_at_uid(uid).parent() = parent_position;
			statement.push_back(uid);

			return result;
		}

		std::wstring 
		_daijoubu_parser::statement_as_string(
			__in const daijoubu_statement &statement,
			__in_opt bool verbose
			)
		{
			std::wstringstream result;

			statement_as_string_nested(result, statement, 0, 0, verbose);

			return CHECK_STRING(result.str());
		}

		void 
		_daijoubu_parser::statement_as_string_nested(
			__out std::wstringstream &stream,
			__in const daijoubu_statement &statement,
			__in size_t position,
			__in size_t tab,
			__in_opt bool verbose
			)
		{
			uint8_t flag = 0;
			size_t child_iter = 0, tab_iter = 0;

			if(position >= statement.size()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_INVALID_POSITION,
					L"Statement position: %llu", position);
			}

			if(verbose && tab) {
				stream << L"      ";

				for(; tab_iter < tab; ++tab_iter) {
					stream << L"---";
				}
			}

			daijoubu_node &node = node_at_uid(statement.at(position));
			daijoubu_token &tok = token_at_uid(node.uid());
			stream << tok.to_string(verbose);

			if(verbose
					&& (tok.type() != DAIJOUBU_TOKEN_BEGIN)
					&& (tok.type() != DAIJOUBU_TOKEN_END)) {
				stream << L" [" << node.size() << L"]";

				if(node.is_leaf()) {
					flag |= DAIJOUBU_LEAF_NODE;
				}

				if(node.is_root()) {
					flag |= DAIJOUBU_ROOT_NODE;
				}

				if(flag) {
					stream << L" (";

					if(flag & DAIJOUBU_ROOT_NODE) {
						stream << L"ROOT";

						if(flag & DAIJOUBU_LEAF_NODE) {
							stream << L", LEAF";
						}
					} else if(flag & DAIJOUBU_LEAF_NODE) {
						stream << L"LEAF";
					}

					stream << L")";
				}
			}

			for(; child_iter < node.size(); ++child_iter) {
				stream << std::endl;
				statement_as_string_nested(stream, statement, node.child_at(child_iter), 
					tab + 1, verbose);
			}
		}

		daijoubu_statement &
		_daijoubu_parser::statement_at(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(position >= m_stmt_list.size()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_INVALID_POSITION,
					L"Statement position: %llu", position);
			}

			return m_stmt_list.at(position);
		}

		daijoubu_statement &
		_daijoubu_parser::statement_begin(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_stmt_list.front();
		}

		daijoubu_statement &
		_daijoubu_parser::statement_end(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_stmt_list.back();
		}

		std::wstring 
		_daijoubu_parser::statement_exception(
			__in size_t tab,
			__in_opt bool verbose
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return token_exception(tab, verbose);
		}

		void 
		_daijoubu_parser::statement_insert(
			__in const daijoubu_statement &statement
			)
		{
			daijoubu_node_factory_ptr fact = NULL;
			daijoubu_statement::const_iterator iter;

			SERIALIZE_CALL_RECUR(m_lock);

			fact = node_factory();

			for(iter = statement.begin(); iter != statement.end(); 
					++iter) {

				if(fact->contains(*iter)) {
					fact->increment_reference(*iter);
				}
			}

			m_stmt_list.insert(m_stmt_list.begin() + m_stmt_position + 1, statement);
		}

		size_t 
		_daijoubu_parser::statement_position(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_stmt_position;
		}

		void 
		_daijoubu_parser::statement_remove(
			__in size_t position
			)
		{
			daijoubu_statement::iterator iter;
			daijoubu_node_factory_ptr fact = NULL;
			
			SERIALIZE_CALL_RECUR(m_lock);

			fact = node_factory();

			daijoubu_statement &statement = statement_at(position);
			for(iter = statement.begin(); iter != statement.end(); 
					++iter) {

				if(fact->contains(*iter)) {
					fact->decrement_reference(*iter);
				}
			}

			m_stmt_list.erase(m_stmt_list.begin() + position);

			if(m_stmt_position >= position) {
				--m_stmt_position;
			}
		}

		std::wstring 
		_daijoubu_parser::to_string(
			__in_opt bool verbose
			)
		{
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << L"(" << m_stmt_position << L"/" << (m_stmt_list.size() - 1) 
					<< L") ";
			}

			result << statement_as_string(statement(), verbose);

			return CHECK_STRING(result.str());
		}

		daijoubu_token &
		_daijoubu_parser::token_at_uid(
			__in daijoubu_uid uid
			)
		{
			return token_factory()->at(node_factory()->at(uid).token());
		}
	}
}
