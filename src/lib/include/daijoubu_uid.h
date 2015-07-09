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

		typedef uint64_t daijoubu_uid;

		#define INVALID_UID INVALID_TYPE(daijoubu_uid)

		typedef class _daijoubu_uid_class {

			public:

				_daijoubu_uid_class(void);

				_daijoubu_uid_class(
					__in const _daijoubu_uid_class &other
					);

				virtual ~_daijoubu_uid_class(void);

				_daijoubu_uid_class &operator=(
					__in const _daijoubu_uid_class &other
					);

				bool operator==(
					__in const _daijoubu_uid_class &other
					);

				bool operator!=(
					__in const _daijoubu_uid_class &other
					);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

				daijoubu_uid uid(void);

			protected:

				daijoubu_uid m_uid;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_uid_class, *daijoubu_uid_class_ptr;

		typedef class _daijoubu_uid_factory {

			public:

				~_daijoubu_uid_factory(void);

				static _daijoubu_uid_factory *acquire(void);

				bool contains(
					__in daijoubu_uid uid
					);

				size_t decrement_reference(
					__in daijoubu_uid uid
					);

				daijoubu_uid generate(void);

				size_t increment_reference(
					__in daijoubu_uid uid
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				size_t reference_count(
					__in daijoubu_uid uid
					);

				size_t size(void);

				std::wstring to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

			protected:

				_daijoubu_uid_factory(void);

				_daijoubu_uid_factory(
					__in const _daijoubu_uid_factory &other
					);

				_daijoubu_uid_factory &operator=(
					__in const _daijoubu_uid_factory &other
					);

				static void _delete(void);

				void clear(void);

				std::map<daijoubu_uid, size_t>::iterator find(
					__in daijoubu_uid uid
					);

				bool m_initialized;

				static _daijoubu_uid_factory *m_instance;

				std::map<daijoubu_uid, size_t> m_uid_map;

				daijoubu_uid m_uid_next;

				std::set<daijoubu_uid> m_uid_surplus;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_uid_factory, *daijoubu_uid_factory_ptr;
	}
}

#endif // DAIJOUBU_UID_H_
