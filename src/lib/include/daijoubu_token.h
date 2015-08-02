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

#ifndef DAIJOUBU_TOKEN_H_
#define DAIJOUBU_TOKEN_H_

#include <map>

namespace DAIJOUBU {

	namespace COMPONENT {

		typedef enum {
			DAIJOUBU_TOKEN_SPECIAL_NONE = 0,
			DAIJOUBU_TOKEN_SPECIAL_FOLLOW,
			DAIJOUBU_TOKEN_SPECIAL_POINTER,
		} daijoubu_token_special_t;

		#define DAIJOUBU_TOKEN_SPECIAL_MAX DAIJOUBU_TOKEN_SPECIAL_POINTER

		typedef class _daijoubu_token :
				public daijoubu_uid_class {

			public:

				_daijoubu_token(
					__in_opt daijoubu_token_t type = INVALID_TOKEN_TYPE,
					__in_opt uint16_t subtype = INVALID_TOKEN_SUBTYPE
					);

				_daijoubu_token(
					__in const _daijoubu_token &other
					);

				virtual ~_daijoubu_token(void);

				_daijoubu_token &operator=(
					__in const _daijoubu_token &other
					);

				bool operator==(
					__in const _daijoubu_token &other
					);

				bool operator!=(
					__in const _daijoubu_token &other
					);

				size_t &column(void);

				std::wstring &line(void);

				size_t &offset(void);

				uint8_t &order(void);

				size_t &position(void);

				size_t &row(void);

				daijoubu_token_special_t &special(void);

				uint16_t &subtype(void);

				std::wstring &text(void);

				virtual std::wstring to_string(
					__in_opt bool verbose = false
					);

				static std::wstring token_as_string(
					__in const _daijoubu_token &token,
					__in_opt bool verbose = false
					);

				daijoubu_token_t &type(void);

				long double &value(void);

			protected:

				size_t m_column;

				std::wstring m_line;

				size_t m_offset;

				uint8_t m_order;

				size_t m_position;

				size_t m_row;

				daijoubu_token_special_t m_special;

				uint16_t m_subtype;

				std::wstring m_text;

				daijoubu_token_t m_type;

				long double m_value;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_token, *daijoubu_token_ptr;

		typedef class _daijoubu_token_factory {

			public:

				~_daijoubu_token_factory(void);

				static _daijoubu_token_factory *acquire(void);

				daijoubu_token &at(
					__in daijoubu_uid uid
					);

				bool contains(
					__in daijoubu_uid uid
					);

				size_t decrement_reference(
					__in daijoubu_uid uid
					);

				daijoubu_uid generate(
					__in_opt daijoubu_token_t type = INVALID_TOKEN_TYPE,
					__in_opt uint16_t subtype = INVALID_TOKEN_SUBTYPE
					);

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

				_daijoubu_token_factory(void);

				_daijoubu_token_factory(
					__in const _daijoubu_token_factory &other
					);

				_daijoubu_token_factory &operator=(
					__in const _daijoubu_token_factory &other
					);

				static void _delete(void);

				void clear(void);

				std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>>::iterator find(
					__in daijoubu_uid uid
					);

				bool m_initialized;

				static _daijoubu_token_factory *m_instance;

				std::map<daijoubu_uid, std::pair<daijoubu_token, size_t>> m_token_map;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_token_factory, *daijoubu_token_factory_ptr;
	}
}

#endif // DAIJOUBU_TOKEN_H_
