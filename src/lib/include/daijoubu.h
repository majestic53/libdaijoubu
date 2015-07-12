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

#ifndef DAIJOUBU_H_
#define DAIJOUBU_H_

//#define NDEBUG

#ifndef DAIJOUBU
#define DAIJOUBU __daijoubu
#endif // DAIJOUBU

#include "daijoubu_defines.h"
#include "daijoubu_exception.h"

using namespace DAIJOUBU;

#ifndef COMPONENT
#define COMPONENT comp
#endif // COMPONENT

#include "daijoubu_unicode.h"
#include "daijoubu_uid.h"
#include "daijoubu_token.h"

using namespace DAIJOUBU::COMPONENT;

#ifndef LANGUAGE
#define LANGUAGE lang
#endif // LANGUAGE

#include "daijoubu_language.h"
#include "daijoubu_lexer.h"

using namespace DAIJOUBU::LANGUAGE;

namespace DAIJOUBU {

	typedef class _daijoubu {

		public:

			~_daijoubu(void);

			static _daijoubu *acquire(void);

			daijoubu_token_factory_ptr acquire_token_factory(void);

			daijoubu_uid_factory_ptr acquire_uid_factory(void);

			static uint32_t exception_information(
				__out daijoubu_region_t &region,
				__out std::wstring &message
				);

			void initialize(void);

			static bool is_allocated(void);

			bool is_initialized(void);

			std::wstring to_string(
				__in_opt bool verbose = false
				);

			daijoubu_unicode_ptr unicode(void);

			void uninitialize(void);

			static std::wstring version(void);

		protected:

			_daijoubu(void);

			_daijoubu(
				__in const _daijoubu &other
				);

			_daijoubu &operator=(
				__in const _daijoubu &other
				);

			static void _delete(void);

			daijoubu_token_factory_ptr m_factory_token;

			daijoubu_uid_factory_ptr m_factory_uid;

			daijoubu_unicode_ptr m_unicode;

			bool m_initialized;

			static _daijoubu *m_instance;

		private:

			std::recursive_mutex m_lock;

	} daijoubu, *daijoubu_ptr;
}

#endif // DAIJOUBU_H_
