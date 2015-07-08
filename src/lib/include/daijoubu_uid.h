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

#ifndef DAIJOUBU_UID_H_
#define DAIJOUBU_UID_H_

#include <map>
#include <set>

namespace DAIJOUBU {

	namespace COMPONENT {

		typedef uint64_t daijoubu_uid_t;

		#define INVALID_UID INVALID(daijoubu_uid_t)

		typedef class _daijoubu_uid {

			public:

				~_daijoubu_uid(void);

				static _daijoubu_uid *acquire(void);

				bool contains(
					__in daijoubu_uid_t uid
					);

				size_t decrement_reference(
					__in daijoubu_uid_t uid
					);

				daijoubu_uid_t generate(void);

				size_t increment_reference(
					__in daijoubu_uid_t uid
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				size_t reference_count(
					__in daijoubu_uid_t uid
					);

				size_t size(void);

				std::wstring to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

			protected:

				_daijoubu_uid(void);

				_daijoubu_uid(
					__in const _daijoubu_uid &other
					);

				_daijoubu_uid &operator=(
					__in const _daijoubu_uid &other
					);

				static void _delete(void);

				void clear(void);

				std::map<daijoubu_uid_t, size_t>::iterator find(
					__in daijoubu_uid_t uid
					);

				bool m_initialized;

				static _daijoubu_uid *m_instance;

				std::map<daijoubu_uid_t, size_t> m_uid_map;

				daijoubu_uid_t m_uid_next;

				std::set<daijoubu_uid_t> m_uid_surplus;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_uid, *daijoubu_uid_ptr;
	}
}

#endif // DAIJOUBU_UID_H_
