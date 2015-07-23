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

#ifndef DAIJOUBU_NODE_H_
#define DAIJOUBU_NODE_H_

#include <vector>

namespace DAIJOUBU {

	namespace COMPONENT {

		#define INVALID_NODE_PARENT INVALID_TYPE(size_t)

		typedef class _daijoubu_node :
				public daijoubu_uid_class {

			public:

				_daijoubu_node(
					__in daijoubu_uid tok_uid,
					__in_opt size_t parent = INVALID_NODE_PARENT
					);

				_daijoubu_node(
					__in const _daijoubu_node &other
					);

				virtual ~_daijoubu_node(void);

				_daijoubu_node &operator=(
					__in const _daijoubu_node &other
					);

				bool operator==(
					__in const _daijoubu_node &other
					);

				bool operator!=(
					__in const _daijoubu_node &other
					);

				size_t &child(
					__in size_t position
					);

				size_t child_insert(
					__in size_t index
					);

				size_t child_insert(
					__in size_t position,
					__in size_t index
					);

				void child_remove(
					__in size_t position
					);

				bool is_leaf(void);

				bool is_root(void);

				static std::wstring node_as_string(
					__in const _daijoubu_node &node,
					__in_opt bool verbose = false
					);

				size_t &parent(void);

				size_t size(void);

				daijoubu_uid &token(void);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

			protected:

				std::vector<size_t>::iterator find(
					__in size_t position
					);

				std::vector<size_t> m_children;

				size_t m_parent;

				daijoubu_uid m_token;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_node, *daijoubu_node_ptr;

		// TODO: implement node factory
	}
}

#endif // DAIJOUBU_NODE_H_
