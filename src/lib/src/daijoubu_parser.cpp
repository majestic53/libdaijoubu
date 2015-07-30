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
			SERIALIZE_CALL_RECUR(m_lock);

			if(!has_next_statement()) {
				THROW_DAIJOUBU_PARSER_EXCEPTION_MESSAGE(DAIJOUBU_PARSER_EXCEPTION_NO_NEXT_STATEMENT,
					L"Statement position: %llu", m_stmt_position);
			}

			// TODO

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

		daijoubu_uid 
		_daijoubu_parser::node_add(
			__in daijoubu_uid root_uid
			)
		{
			daijoubu_uid result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO
			result = 0;
			// ---

			return result;
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
			node_add(token_begin());
			node_add(token_end());
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

		std::wstring 
		_daijoubu_parser::statement_as_string(
			__in const daijoubu_statement &statement,
			__in_opt bool verbose
			)
		{
			std::wstringstream result;

			// TODO

			return CHECK_STRING(result.str());
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
			std::wstringstream result;

			SERIALIZE_CALL_RECUR(m_lock);

			// TODO

			return CHECK_STRING(result.str());
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
					<< L")";
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
