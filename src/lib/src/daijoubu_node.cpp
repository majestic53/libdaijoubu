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
#include "../include/daijoubu_node_type.h"

namespace DAIJOUBU {

	namespace COMPONENT {

		enum {
			DAIJOUBU_LEAF_NODE = 1,
			DAIJOUBU_ROOT_NODE,
		};

		_daijoubu_node::_daijoubu_node(
			__in daijoubu_uid tok_uid,
			__in_opt size_t parent
			) :
				m_parent(parent),
				m_token(tok_uid)
		{
			return;
		}

		_daijoubu_node::_daijoubu_node(
			__in const _daijoubu_node &other
			) :
				daijoubu_uid_class(other),
				m_children(other.m_children),
				m_parent(other.m_parent),
				m_token(other.m_token)
		{
			return;
		}

		_daijoubu_node::~_daijoubu_node(void)
		{
			return;
		}

		_daijoubu_node &
		_daijoubu_node::operator=(
			__in const _daijoubu_node &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				daijoubu_uid_class::operator=(other);
				m_children = other.m_children;
				m_parent = other.m_parent;
				m_token = other.m_token;
			}

			return *this;
		}

		bool 
		_daijoubu_node::operator==(
			__in const _daijoubu_node &other
			)
		{
			bool result;
			size_t iter = 0;

			SERIALIZE_CALL_RECUR(m_lock);

			result = (daijoubu_uid_class::operator==(other)
				&& (m_children.size() == other.m_children.size())
				&& (m_parent == other.m_parent)
				&& (m_token == other.m_token));

			if(result) {

				for(; iter < m_children.size(); ++iter) {

					if(m_children.at(iter) != other.m_children.at(iter)) {
						result = false;
						break;
					}
				}
			}

			return result;
		}

		bool 
		_daijoubu_node::operator!=(
			__in const _daijoubu_node &other
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return !(*this == other);
		}

		size_t &
		_daijoubu_node::child(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return *find(position);
		}

		size_t 
		_daijoubu_node::child_insert(
			__in size_t index
			)
		{
			size_t result;

			SERIALIZE_CALL_RECUR(m_lock);

			result = m_children.size();
			m_children.push_back(index);

			return result;
		}

		size_t 
		_daijoubu_node::child_insert(
			__in size_t position,
			__in size_t index
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(position == m_children.size()) {
				m_children.push_back(index);
			} else if(position < m_children.size()) {
				m_children.insert(m_children.begin() + position, index);
			} else {
				THROW_DAIJOUBU_NODE_EXCEPTION_MESSAGE(DAIJOUBU_NODE_EXCEPTION_INVALID_POSITION, 
					L"%lu", position);
			}

			return position;
		}

		void 
		_daijoubu_node::child_remove(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			m_children.erase(find(position));
		}

		std::vector<size_t>::iterator 
		_daijoubu_node::find(
			__in size_t position
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);

			if(position >= m_children.size()) {
				THROW_DAIJOUBU_NODE_EXCEPTION_MESSAGE(DAIJOUBU_NODE_EXCEPTION_INVALID_POSITION, 
					L"%lu", position);
			}

			return m_children.begin() + position;
		}

		bool 
		_daijoubu_node::is_leaf(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_children.empty();
		}

		bool 
		_daijoubu_node::is_root(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return (m_parent == INVALID_NODE_PARENT);
		}

		std::wstring 
		_daijoubu_node::node_as_string(
			__in const _daijoubu_node &node,
			__in_opt bool verbose
			)
		{
			uint8_t flag = 0;
			std::wstringstream result;

			if(verbose) {
				result << L"(" << VALUE_AS_HEX(daijoubu_uid, node.m_uid) << L") ";
			}

			result << CHECK_STRING(daijoubu::acquire()->acquire_token_factory()->at(
				node.m_token).to_string(verbose)) << L" [" << node.m_children.size() << L"]";

			if(node.m_children.empty()) {
				flag |= DAIJOUBU_LEAF_NODE;
			}

			if(node.m_parent == INVALID_NODE_PARENT) {
				flag |= DAIJOUBU_ROOT_NODE;
			}

			if(verbose && flag) {
				result << L" (";

				if(flag & DAIJOUBU_ROOT_NODE) {
					result << L"ROOT";

					if(flag & DAIJOUBU_LEAF_NODE) {
						result << L", LEAF";
					}
				} else if(flag & DAIJOUBU_LEAF_NODE) {
					result << L"LEAF";
				}

				result << L")";
			}

			return CHECK_STRING(result.str());
		}

		size_t &
		_daijoubu_node::parent(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_parent;
		}

		size_t 
		_daijoubu_node::size(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_children.size();
		}

		daijoubu_uid &
		_daijoubu_node::token(void)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return m_token;
		}

		std::wstring 
		_daijoubu_node::to_string(
			__in_opt bool verbose
			)
		{
			SERIALIZE_CALL_RECUR(m_lock);
			return node_as_string(*this, verbose);
		}
	}
}
