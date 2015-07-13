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

#ifndef DAIJOUBU_UNICODE_H_
#define DAIJOUBU_UNICODE_H_

#include <map>

namespace DAIJOUBU {

	namespace COMPONENT {

		typedef enum {
			DAIJOUBU_UNICODE_CLASS_CC = 0,
			DAIJOUBU_UNICODE_CLASS_CF,
			DAIJOUBU_UNICODE_CLASS_CN,
			DAIJOUBU_UNICODE_CLASS_CO,
			DAIJOUBU_UNICODE_CLASS_CS,
			DAIJOUBU_UNICODE_CLASS_LC,
			DAIJOUBU_UNICODE_CLASS_LL,
			DAIJOUBU_UNICODE_CLASS_LM,
			DAIJOUBU_UNICODE_CLASS_LO,
			DAIJOUBU_UNICODE_CLASS_LT,
			DAIJOUBU_UNICODE_CLASS_LU,
			DAIJOUBU_UNICODE_CLASS_MC,
			DAIJOUBU_UNICODE_CLASS_ME,
			DAIJOUBU_UNICODE_CLASS_MN,
			DAIJOUBU_UNICODE_CLASS_ND,
			DAIJOUBU_UNICODE_CLASS_NL,
			DAIJOUBU_UNICODE_CLASS_NO,
			DAIJOUBU_UNICODE_CLASS_PC,
			DAIJOUBU_UNICODE_CLASS_PD,
			DAIJOUBU_UNICODE_CLASS_PE,
			DAIJOUBU_UNICODE_CLASS_PF,
			DAIJOUBU_UNICODE_CLASS_PI,
			DAIJOUBU_UNICODE_CLASS_PO,
			DAIJOUBU_UNICODE_CLASS_PS,
			DAIJOUBU_UNICODE_CLASS_SC,
			DAIJOUBU_UNICODE_CLASS_SK,
			DAIJOUBU_UNICODE_CLASS_SM,
			DAIJOUBU_UNICODE_CLASS_SO,
			DAIJOUBU_UNICODE_CLASS_ZL,
			DAIJOUBU_UNICODE_CLASS_ZP,
			DAIJOUBU_UNICODE_CLASS_ZS,
		} daijoubu_unicode_t;

		#define DAIJOUBU_UNICODE_CLASS_MAX DAIJOUBU_UNICODE_CLASS_ZS

		static const std::string DAIJOUBU_UNICODE_CLASS_STR[] {
			"Cc", "Cf", "Cn", "Co", "Cs", "Lc", "Ll", "Lm",
			"Lo", "Lt", "Lu", "Mc", "Me", "Mn", "Nd", "Nl",
			"No", "Pc", "Pd", "Pe", "Pf", "Pi", "Po", "Ps", 
			"Sc", "Sk", "Sm", "So", "Zl", "Zp", "Zs",
		};

		#define DAIJOUBU_UNICODE_CLASS_STRING(_TYPE_) \
			((_TYPE_) > DAIJOUBU_UNICODE_CLASS_MAX ? std::string() : \
			DAIJOUBU_UNICODE_CLASS_STR[_TYPE_].c_str())

		typedef class _daijoubu_unicode {

			public:

				~_daijoubu_unicode(void);

				static _daijoubu_unicode *acquire(void);

				daijoubu_unicode_t character_class(
					__in wchar_t character
					);

				bool contains(
					__in wchar_t character
					);

				void initialize(
					__in const std::string &input
					);

				static bool is_allocated(void);

				bool is_initialized(void);

				static bool is_whitespace(
					__in daijoubu_unicode_t type
					);

				std::wstring to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

			protected:

				_daijoubu_unicode(void);

				_daijoubu_unicode(
					__in const _daijoubu_unicode &other
					);

				_daijoubu_unicode &operator=(
					__in const _daijoubu_unicode &other
					);

				static void _delete(void);

				std::map<wchar_t, daijoubu_unicode_t>::iterator find(
					__in wchar_t character
					);

				bool m_initialized;

				static _daijoubu_unicode *m_instance;

				std::map<wchar_t, daijoubu_unicode_t> m_type_map;

			private:

				std::recursive_mutex m_lock;

		} daijoubu_unicode, *daijoubu_unicode_ptr;
	}
}

#endif // DAIJOUBU_UNICODE_H_
