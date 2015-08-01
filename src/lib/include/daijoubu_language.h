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

#ifndef DAIJOUBU_LANGUAGE_H_
#define DAIJOUBU_LANGUAGE_H_

#include <set>

namespace DAIJOUBU {

	#define DAIJOUBU_CHARACTER(_CH_) ((wchar_t) _CH_)
	#define DAIJOUBU_CHARACTER_CARRAGE_RETURN DAIJOUBU_CHARACTER(L'\r')
	#define DAIJOUBU_CHARACTER_END DAIJOUBU_CHARACTER(L'\0')
	#define DAIJOUBU_CHARACTER_NEWLINE DAIJOUBU_CHARACTER(L'\n')
	#define DAIJOUBU_CHARACTER_TAB DAIJOUBU_CHARACTER(L'\t')
	#define DAIJOUBU_COMMENT_BLOCK_CLOSE DAIJOUBU_CHARACTER(L'】')
	#define DAIJOUBU_COMMENT_BLOCK_CLOSE_SIMPLE DAIJOUBU_CHARACTER(L']')
	#define DAIJOUBU_COMMENT_BLOCK_OPEN DAIJOUBU_CHARACTER(L'【')
	#define DAIJOUBU_COMMENT_BLOCK_OPEN_SIMPLE DAIJOUBU_CHARACTER(L'[')
	#define DAIJOUBU_COMMENT_LINE DAIJOUBU_CHARACTER(L'※')
	#define DAIJOUBU_COMMENT_LINE_SIMPLE DAIJOUBU_CHARACTER(L'#')
	#define DAIJOUBU_IDENTIFIER_LOW_LINE DAIJOUBU_CHARACTER(L'_')
	#define DAIJOUBU_LITERAL_NUMERIC_BINARY_HIGH DAIJOUBU_CHARACTER(L'1')
	#define DAIJOUBU_LITERAL_NUMERIC_BINARY_LOW DAIJOUBU_CHARACTER(L'0')
	#define DAIJOUBU_LITERAL_NUMERIC_DECIMAL DAIJOUBU_CHARACTER(L'.')
	#define DAIJOUBU_LITERAL_NUMERIC_DECIMAL_HIGH DAIJOUBU_CHARACTER(L'9')
	#define DAIJOUBU_LITERAL_NUMERIC_DECIMAL_LOW DAIJOUBU_CHARACTER(L'0')
	#define DAIJOUBU_LITERAL_NUMERIC_DELIMITER_BINARY DAIJOUBU_CHARACTER(L'b')
	#define DAIJOUBU_LITERAL_NUMERIC_DELIMITER_HEXIDECIMAL DAIJOUBU_CHARACTER(L'h')
	#define DAIJOUBU_LITERAL_NUMERIC_DELIMITER_OCTAL DAIJOUBU_CHARACTER(L'o')
	#define DAIJOUBU_LITERAL_NUMERIC_DELIMITER_PREFIX DAIJOUBU_CHARACTER(L'0')
	#define DAIJOUBU_LITERAL_NUMERIC_HEXIDECIMAL_FIRST_HIGH DAIJOUBU_CHARACTER(L'9')
	#define DAIJOUBU_LITERAL_NUMERIC_HEXIDECIMAL_FIRST_LOW DAIJOUBU_CHARACTER(L'0')
	#define DAIJOUBU_LITERAL_NUMERIC_HEXIDECIMAL_SECOND_HIGH DAIJOUBU_CHARACTER(L'F')
	#define DAIJOUBU_LITERAL_NUMERIC_HEXIDECIMAL_SECOND_LOW DAIJOUBU_CHARACTER(L'A')
	#define DAIJOUBU_LITERAL_NUMERIC_OCTAL_HIGH DAIJOUBU_CHARACTER(L'7')
	#define DAIJOUBU_LITERAL_NUMERIC_OCTAL_LOW DAIJOUBU_CHARACTER(L'0')
	#define DAIJOUBU_LITERAL_NUMERIC_UNARY_NEGATION DAIJOUBU_CHARACTER(L'−')
	#define DAIJOUBU_LITERAL_NUMERIC_UNARY_NEGATION_SIMPLE DAIJOUBU_CHARACTER(L'-')
	#define DAIJOUBU_LITERAL_STRING_CLOSE DAIJOUBU_CHARACTER(L'”')
	#define DAIJOUBU_LITERAL_STRING_CLOSE_SIMPLE DAIJOUBU_CHARACTER(L'>')
	#define DAIJOUBU_LITERAL_STRING_OPEN DAIJOUBU_CHARACTER(L'“')
	#define DAIJOUBU_LITERAL_STRING_OPEN_SIMPLE DAIJOUBU_CHARACTER(L'<')
	#define DAIJOUBU_SUBSCRIPT_LOW DAIJOUBU_CHARACTER(L'₀')
	#define DAIJOUBU_SUBSCRIPT_HIGH DAIJOUBU_CHARACTER(L'₉')
	#define DAIJOUBU_SUPERSCRIPT_FIRST_LOW DAIJOUBU_CHARACTER(L'²')
	#define DAIJOUBU_SUPERSCRIPT_FIRST_HIGH DAIJOUBU_CHARACTER(L'¹')
	#define DAIJOUBU_SUPERSCRIPT_SECOND_LOW DAIJOUBU_CHARACTER(L'⁰')
	#define DAIJOUBU_SUPERSCRIPT_SECOND_HIGH DAIJOUBU_CHARACTER(L'⁹')

	enum {
		DAIJOUBU_CONSTANT_E = 0,
		DAIJOUBU_CONSTANT_NULL,
		DAIJOUBU_CONSTANT_PI,
	};

	#define DAIJOUBU_CONSTANT_MAX DAIJOUBU_CONSTANT_PI

	static const std::wstring DAIJOUBU_CONSTANT_STR[] = {
		L"e", L"π", L"null",
		};

	static const std::set<std::wstring> DAIJOUBU_CONSTANT_SET(
		DAIJOUBU_CONSTANT_STR, 
		DAIJOUBU_CONSTANT_STR + (DAIJOUBU_CONSTANT_MAX + 1)
		);

	#define IS_DAIJOUBU_CONSTANT_TYPE(_STR_) \
		(DAIJOUBU_CONSTANT_SET.find(_STR_) != DAIJOUBU_CONSTANT_SET.end())

	enum {
		DAIJOUBU_CONTROL_BREAK = 0,
		DAIJOUBU_CONTROL_CONTINUE,
		DAIJOUBU_CONTROL_ELIF,
		DAIJOUBU_CONTROL_ELSE,
		DAIJOUBU_CONTROL_FINAL,
		DAIJOUBU_CONTROL_FOR,
		DAIJOUBU_CONTROL_IF,
		DAIJOUBU_CONTROL_RETURN,
		DAIJOUBU_CONTROL_SWITCH,
	};

	#define DAIJOUBU_CONTROL_MAX DAIJOUBU_CONTROL_SWITCH

	static const std::wstring DAIJOUBU_CONTROL_STR[] = {
		L"break", L"continue", L"elif", L"else", L"final", L"for", L"if", L"return", 
		L"switch",
		};

	static const std::set<std::wstring> DAIJOUBU_CONTROL_SET(
		DAIJOUBU_CONTROL_STR, 
		DAIJOUBU_CONTROL_STR + (DAIJOUBU_CONTROL_MAX + 1)
		);

	#define IS_DAIJOUBU_CONTROL_TYPE(_STR_) \
		(DAIJOUBU_CONTROL_SET.find(_STR_) != DAIJOUBU_CONTROL_SET.end())

	enum {
		DAIJOUBU_LITERAL_BOOLEAN_FALSE = 0,
		DAIJOUBU_LITERAL_BOOLEAN_TRUE,
	};

	#define DAIJOUBU_LITERAL_BOOLEAN_MAX DAIJOUBU_LITERAL_BOOLEAN_TRUE

	static const std::wstring DAIJOUBU_LITERAL_BOOLEAN_STR[] = {
		L"false", L"true",
		};

	static const std::set<std::wstring> DAIJOUBU_LITERAL_BOOLEAN_SET(
		DAIJOUBU_LITERAL_BOOLEAN_STR, 
		DAIJOUBU_LITERAL_BOOLEAN_STR + (DAIJOUBU_LITERAL_BOOLEAN_MAX + 1)
		);

	#define IS_DAIJOUBU_LITERAL_BOOLEAN_TYPE(_STR_) \
		(DAIJOUBU_LITERAL_BOOLEAN_SET.find(_STR_) != DAIJOUBU_LITERAL_BOOLEAN_SET.end())

	enum {
		DAIJOUBU_MODIFIER_ADDITION = 0,
		DAIJOUBU_MODIFIER_EQUALS,
		DAIJOUBU_MODIFIER_SUBTRACTION,
	};

	#define DAIJOUBU_MODIFIER_MAX DAIJOUBU_MODIFIER_SUBTRACTION

	static const std::wstring DAIJOUBU_MODIFIER_STR[] = {
		L"₊", L"₌", L"₋",
		};

	static const std::set<std::wstring> DAIJOUBU_MODIFIER_SET(
		DAIJOUBU_MODIFIER_STR, 
		DAIJOUBU_MODIFIER_STR + (DAIJOUBU_MODIFIER_MAX + 1)
		);

	#define IS_DAIJOUBU_MODIFIER_TYPE(_STR_) \
		(DAIJOUBU_MODIFIER_SET.find(_STR_) != DAIJOUBU_MODIFIER_SET.end())

	enum {
		DAIJOUBU_NATIVE_SHOW = 0,
	};

	#define DAIJOUBU_NATIVE_MAX DAIJOUBU_NATIVE_SHOW

	static const std::wstring DAIJOUBU_NATIVE_STR[] = {
		L"show",
		};

	static const std::set<std::wstring> DAIJOUBU_NATIVE_SET(
		DAIJOUBU_NATIVE_STR,
		DAIJOUBU_NATIVE_STR + (DAIJOUBU_NATIVE_MAX + 1)
		);

	#define IS_DAIJOUBU_NATIVE_TYPE(_STR_) \
		(DAIJOUBU_NATIVE_SET.find(_STR_) != DAIJOUBU_NATIVE_SET.end())

	enum {
		DAIJOUBU_OPERATOR_ADDITION = 0,
		DAIJOUBU_OPERATOR_ARC_COSECANT,
		DAIJOUBU_OPERATOR_ARC_COSINE,
		DAIJOUBU_OPERATOR_ARC_COTANGENT,
		DAIJOUBU_OPERATOR_ARC_SECANT,
		DAIJOUBU_OPERATOR_ARC_SINE,
		DAIJOUBU_OPERATOR_ARC_TANGENT,
		DAIJOUBU_OPERATOR_CARDINALITY,
		DAIJOUBU_OPERATOR_CEILING,
		DAIJOUBU_OPERATOR_COALESCENCE,
		DAIJOUBU_OPERATOR_COSECANT,
		DAIJOUBU_OPERATOR_COSINE,
		DAIJOUBU_OPERATOR_DISTANCE,
		DAIJOUBU_OPERATOR_DIVISION,
		DAIJOUBU_OPERATOR_EQUALS,
		DAIJOUBU_OPERATOR_EXPONENT,
		DAIJOUBU_OPERATOR_FACTORIAL,
		DAIJOUBU_OPERATOR_FLOOR,
		DAIJOUBU_OPERATOR_GENERIC_0,
		DAIJOUBU_OPERATOR_GENERIC_1,
		DAIJOUBU_OPERATOR_GENERIC_2,
		DAIJOUBU_OPERATOR_GENERIC_3,
		DAIJOUBU_OPERATOR_GENERIC_4,
		DAIJOUBU_OPERATOR_GENERIC_5,
		DAIJOUBU_OPERATOR_GENERIC_6,
		DAIJOUBU_OPERATOR_GRADE_DOWN,
		DAIJOUBU_OPERATOR_GRADE_UP,
		DAIJOUBU_OPERATOR_GREATER_THAN,
		DAIJOUBU_OPERATOR_GREATER_THAN_EQUALS,
		DAIJOUBU_OPERATOR_INDEX_OF,
		DAIJOUBU_OPERATOR_INTERSECTION,
		DAIJOUBU_OPERATOR_LESS_THAN,
		DAIJOUBU_OPERATOR_LESS_THAN_EQUALS,
		DAIJOUBU_OPERATOR_LOGARITHM,
		DAIJOUBU_OPERATOR_LOGICAL_AND,
		DAIJOUBU_OPERATOR_LOGICAL_NEGATION,
		DAIJOUBU_OPERATOR_LOGICAL_OR,
		DAIJOUBU_OPERATOR_LOGICAL_XOR,
		DAIJOUBU_OPERATOR_MAP,
		DAIJOUBU_OPERATOR_MEMBERSHIP,
		DAIJOUBU_OPERATOR_MODULO,
		DAIJOUBU_OPERATOR_MULTIPLICATION,
		DAIJOUBU_OPERATOR_NATURAL_LOGARITHM,
		DAIJOUBU_OPERATOR_NOT_EQUALS,
		DAIJOUBU_OPERATOR_RANDOM,
		DAIJOUBU_OPERATOR_RANGE,
		DAIJOUBU_OPERATOR_SECANT,
		DAIJOUBU_OPERATOR_SINE,
		DAIJOUBU_OPERATOR_SQUARE_ROOT,
		DAIJOUBU_OPERATOR_SUBTRACTION,
		DAIJOUBU_OPERATOR_TANGENT,
		DAIJOUBU_OPERATOR_TERNARY_CONDITIONAL,
		DAIJOUBU_OPERATOR_UNARY_DECREMENT,
		DAIJOUBU_OPERATOR_UNARY_INCREMENT,
		DAIJOUBU_OPERATOR_UNION,
	};

	#define DAIJOUBU_OPERATOR_MAX DAIJOUBU_OPERATOR_UNION

	static const std::wstring DAIJOUBU_OPERATOR_STR[] = {
		L"+", L"arccsc", L"arccos", L"arccot", L"arcsec", L"arcsin", L"arctan", L"#", 
		L"⊤", L"✓", L"csc", L"cos", L"↔", L"/", L"=", L"^", 
		L"!", L"⊥", L"⊙", L"⊕", L"⊖", L"⊗", L"⊘", L"⊜", 
		L"⌾", L"⍒", L"⍋", L">", L"≥", L"⍷", L"∩", L"<", 
		L"≤", L"log", L"∧", L"¬", L"∨", L"⊻", L"↦", L"∈", 
		L"%", L"⋅", L"ln", L"≠", L"☘", L"…", L"sec", L"sin", 
		L"√", L"−", L"tan", L"?", L"¦", L"‡", L"∪",
		};

	static const std::set<std::wstring> DAIJOUBU_OPERATOR_SET(
		DAIJOUBU_OPERATOR_STR, 
		DAIJOUBU_OPERATOR_STR + (DAIJOUBU_OPERATOR_MAX + 1)
		);

	#define IS_DAIJOUBU_OPERATOR_TYPE(_STR_) \
		(DAIJOUBU_OPERATOR_SET.find(_STR_) != DAIJOUBU_OPERATOR_SET.end())

	enum {
		DAIJOUBU_OPERATOR_SIMPLE_ADDITION = 0,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_COSECANT,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_COSINE,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_COTANGENT,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_SECANT,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_SINE,
		DAIJOUBU_OPERATOR_SIMPLE_ARC_TANGENT,
		DAIJOUBU_OPERATOR_SIMPLE_CARDINALITY,
		DAIJOUBU_OPERATOR_SIMPLE_CEILING,
		DAIJOUBU_OPERATOR_SIMPLE_COALESCENCE,
		DAIJOUBU_OPERATOR_SIMPLE_COSECANT,
		DAIJOUBU_OPERATOR_SIMPLE_COSINE,
		DAIJOUBU_OPERATOR_SIMPLE_DISTANCE,
		DAIJOUBU_OPERATOR_SIMPLE_DIVISION,
		DAIJOUBU_OPERATOR_SIMPLE_EQUALS,
		DAIJOUBU_OPERATOR_SIMPLE_EXPONENT,
		DAIJOUBU_OPERATOR_SIMPLE_FACTORIAL,
		DAIJOUBU_OPERATOR_SIMPLE_FLOOR,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_0,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_1,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_2,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_3,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_4,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_5,
		DAIJOUBU_OPERATOR_SIMPLE_GENERIC_6,
		DAIJOUBU_OPERATOR_SIMPLE_GREATER_THAN,
		DAIJOUBU_OPERATOR_SIMPLE_GREATER_THAN_EQUALS,
		DAIJOUBU_OPERATOR_SIMPLE_INDEX_OF,
		DAIJOUBU_OPERATOR_SIMPLE_LESS_THAN,
		DAIJOUBU_OPERATOR_SIMPLE_LESS_THAN_EQUALS,
		DAIJOUBU_OPERATOR_SIMPLE_LOGARITHM,
		DAIJOUBU_OPERATOR_SIMPLE_LOGICAL_AND,
		DAIJOUBU_OPERATOR_SIMPLE_LOGICAL_NEGATION,
		DAIJOUBU_OPERATOR_SIMPLE_LOGICAL_OR,
		DAIJOUBU_OPERATOR_SIMPLE_LOGICAL_XOR,
		DAIJOUBU_OPERATOR_SIMPLE_MAP,
		DAIJOUBU_OPERATOR_SIMPLE_MEMBERSHIP,
		DAIJOUBU_OPERATOR_SIMPLE_MODULO,
		DAIJOUBU_OPERATOR_SIMPLE_MULTIPLICATION,
		DAIJOUBU_OPERATOR_SIMPLE_NATURAL_LOGARITHM,
		DAIJOUBU_OPERATOR_SIMPLE_NOT_EQUALS,
		DAIJOUBU_OPERATOR_SIMPLE_RANDOM,
		DAIJOUBU_OPERATOR_SIMPLE_RANGE,
		DAIJOUBU_OPERATOR_SIMPLE_SECANT,
		DAIJOUBU_OPERATOR_SIMPLE_SINE,
		DAIJOUBU_OPERATOR_SIMPLE_SQUARE_ROOT,
		DAIJOUBU_OPERATOR_SIMPLE_SUBTRACTION,
		DAIJOUBU_OPERATOR_SIMPLE_TANGENT,
		DAIJOUBU_OPERATOR_SIMPLE_TERNARY_CONDITIONAL,
		DAIJOUBU_OPERATOR_SIMPLE_UNARY_DECREMENT,
		DAIJOUBU_OPERATOR_SIMPLE_UNARY_INCREMENT,
	};

	#define DAIJOUBU_OPERATOR_SIMPLE_MAX DAIJOUBU_OPERATOR_SIMPLE_UNARY_INCREMENT

	static const std::wstring DAIJOUBU_OPERATOR_SIMPLE_STR[] = {
		L"+", L"arccsc", L"arccos", L"arccot", L"arcsec", L"arcsin", L"arctan", L"#", 
		L"+%", L"?:", L"csc", L"cos", L"<_>", L"/", L"=", L"^", 
		L"!", L"-%", L"@!", L"@@", L"@$", L"@%", L"@^", L"@&", 
		L"@*", L">", L">=", L".=", L"<", L"<=", L"log", L"&&", 
		L"~", L"||", L"><", L"_>", L"?=", L"%", L"*", L"ln", 
		L"~=", L"??", L"..", L"sec", L"sin", L"~^", L"-", L"tan", 
		L"?", L"--", L"++",
		};

	static const std::set<std::wstring> DAIJOUBU_OPERATOR_SIMPLE_SET(
		DAIJOUBU_OPERATOR_SIMPLE_STR, 
		DAIJOUBU_OPERATOR_SIMPLE_STR + (DAIJOUBU_OPERATOR_SIMPLE_MAX + 1)
		);

	#define IS_DAIJOUBU_OPERATOR_SIMPLE_TYPE(_STR_) \
		(DAIJOUBU_OPERATOR_SIMPLE_SET.find(_STR_) != DAIJOUBU_OPERATOR_SIMPLE_SET.end())

	typedef enum {
		DAIJOUBU_RADIX_36 = 0,
		DAIJOUBU_RADIX_BINARY,
		DAIJOUBU_RADIX_DECIMAL,
		DAIJOUBU_RADIX_HEXIDECIMAL,
		DAIJOUBU_RADIX_OCTAL,
	} daijoubu_radix_t;

	#define DAIJOUBU_RADIX_MAX DAIJOUBU_RADIX_OCTAL

	enum {
		DAIJOUBU_STATEMENT_ASSIGNMENT = 0,
		DAIJOUBU_STATEMENT_CALL_FUNCTION,
		DAIJOUBU_STATEMENT_CALL_NATIVE,
		DAIJOUBU_STATEMENT_CONTROL,
		DAIJOUBU_STATEMENT_DEFINE_FUNCTION,
		DAIJOUBU_STATEMENT_UNARY,
	};

	#define DAIJOUBU_STATEMENT_MAX DAIJOUBU_STATEMENT_UNARY

	static const std::wstring DAIJOUBU_STATEMENT_STR[] = {
		L"ASSIGNMENT", L"FUNCTION_CALL", L"NATIVE_CALL", L"CONTROL", 
		L"FUNCTION_DEFINITION", L"UNARY",
		};

	enum {
		DAIJOUBU_SYMBOL_ACCESS_BRACKET_CLOSE = 0,
		DAIJOUBU_SYMBOL_ACCESS_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_ARGUMENT_DELIMITER,
		DAIJOUBU_SYMBOL_ASSIGNMENT,
		DAIJOUBU_SYMBOL_ASSIGNMENT_SWAP,
		DAIJOUBU_SYMBOL_EMPTY_SET,
		DAIJOUBU_SYMBOL_BLOCK_BRACKET_CLOSE,
		DAIJOUBU_SYMBOL_BLOCK_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_CONTEXT_SEPERATOR,
		DAIJOUBU_SYMBOL_FOLLOW,
		DAIJOUBU_SYMBOL_FUNCTION_BRACKET_CLOSE,
		DAIJOUBU_SYMBOL_FUNCTION_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_MEMBER_ACCESS,
		DAIJOUBU_SYMBOL_POINTER,
		DAIJOUBU_SYMBOL_STATEMENT_TERMINATOR,
		DAIJOUBU_SYMBOL_TERNARY_DELIMITER,
	};

	#define DAIJOUBU_SYMBOL_MAX DAIJOUBU_SYMBOL_TERNARY_DELIMITER

	static const std::wstring DAIJOUBU_SYMBOL_STR[] = {
		L"]", L"[", L",", L"⇐", L"⇔", L"∅", L"}", L"{", 
		L"|", L"\'", L")", L"(", L".", L"*", L";", L":", 
		};

	static const std::set<std::wstring> DAIJOUBU_SYMBOL_SET(
		DAIJOUBU_SYMBOL_STR, 
		DAIJOUBU_SYMBOL_STR + (DAIJOUBU_SYMBOL_MAX + 1)
		);

	#define IS_DAIJOUBU_SYMBOL_TYPE(_STR_) \
		(DAIJOUBU_SYMBOL_SET.find(_STR_) != DAIJOUBU_SYMBOL_SET.end())

	enum {
		DAIJOUBU_SYMBOL_SIMPLE_ACCESS_BRACKET_CLOSE = 0,
		DAIJOUBU_SYMBOL_SIMPLE_ACCESS_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_SIMPLE_ARGUMENT_DELIMITER,
		DAIJOUBU_SYMBOL_SIMPLE_ASSIGNMENT,
		DAIJOUBU_SYMBOL_SIMPLE_ASSIGNMENT_SWAP,
		DAIJOUBU_SYMBOL_SIMPLE_BLOCK_BRACKET_CLOSE,
		DAIJOUBU_SYMBOL_SIMPLE_BLOCK_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_SIMPLE_CONTEXT_SEPERATOR,
		DAIJOUBU_SYMBOL_SIMPLE_FOLLOW,
		DAIJOUBU_SYMBOL_SIMPLE_FUNCTION_BRACKET_CLOSE,
		DAIJOUBU_SYMBOL_SIMPLE_FUNCTION_BRACKET_OPEN,
		DAIJOUBU_SYMBOL_SIMPLE_MEMBER_ACCESS,
		DAIJOUBU_SYMBOL_SIMPLE_POINTER,
		DAIJOUBU_SYMBOL_SIMPLE_STATEMENT_TERMINATOR,
		DAIJOUBU_SYMBOL_SIMPLE_TERNARY_DELIMITER,
	};

	#define DAIJOUBU_SYMBOL_SIMPLE_MAX DAIJOUBU_SYMBOL_SIMPLE_TERNARY_DELIMITER

	static const std::wstring DAIJOUBU_SYMBOL_SIMPLE_STR[] = {
		L"]", L"[", L",", L"<-", L"<->", L"}", L"{", L"|", 
		L"\'", L")", L"(", L".", L"&", L";", L":", 
		};

	static const std::set<std::wstring> DAIJOUBU_SYMBOL_SIMPLE_SET(
		DAIJOUBU_SYMBOL_SIMPLE_STR, 
		DAIJOUBU_SYMBOL_SIMPLE_STR + (DAIJOUBU_SYMBOL_SIMPLE_MAX + 1)
		);

	#define IS_DAIJOUBU_SYMBOL_SIMPLE_TYPE(_STR_) \
		(DAIJOUBU_SYMBOL_SIMPLE_SET.find(_STR_) != DAIJOUBU_SYMBOL_SIMPLE_SET.end())

	enum {
		DAIJOUBU_TYPE_BOOLEAN = 0,
		DAIJOUBU_TYPE_BYTE,
		DAIJOUBU_TYPE_BYTE_UNSIGNED,
		DAIJOUBU_TYPE_FLOAT,
		DAIJOUBU_TYPE_INTEGER,
		DAIJOUBU_TYPE_INTEGER_UNSIGNED,
		DAIJOUBU_TYPE_STRING,
	};

	#define DAIJOUBU_TYPE_MAX DAIJOUBU_TYPE_STRING

	static const std::wstring DAIJOUBU_TYPE_STR[] = {
		L"bool", L"byte", L"ubyte", L"float", L"int", L"uint", L"string", 
		};

	static const std::set<std::wstring> DAIJOUBU_TYPE_SET(
		DAIJOUBU_TYPE_STR, 
		DAIJOUBU_TYPE_STR + (DAIJOUBU_TYPE_MAX + 1)
		);

	#define IS_DAIJOUBU_TYPE_TYPE(_STR_) \
		(DAIJOUBU_TYPE_SET.find(_STR_) != DAIJOUBU_TYPE_SET.end())

	typedef enum {
		DAIJOUBU_TOKEN_BEGIN = 0,
		DAIJOUBU_TOKEN_CONSTANT,
		DAIJOUBU_TOKEN_CONTROL,
		DAIJOUBU_TOKEN_END,
		DAIJOUBU_TOKEN_IDENTIFIER,
		DAIJOUBU_TOKEN_LITERAL_BOOLEAN,
		DAIJOUBU_TOKEN_LITERAL_NUMERIC,
		DAIJOUBU_TOKEN_LITERAL_STRING,
		DAIJOUBU_TOKEN_MODIFIER,
		DAIJOUBU_TOKEN_NATIVE,
		DAIJOUBU_TOKEN_OPERATOR,
		DAIJOUBU_TOKEN_OPERATOR_SIMPLE,
		DAIJOUBU_TOKEN_STATEMENT,
		DAIJOUBU_TOKEN_SUBSCRIPT,
		DAIJOUBU_TOKEN_SUPERSCRIPT,
		DAIJOUBU_TOKEN_SYMBOL,
		DAIJOUBU_TOKEN_SYMBOL_SIMPLE,
		DAIJOUBU_TOKEN_TYPE,
	} daijoubu_token_t;

	#define DAIJOUBU_TOKEN_MAX DAIJOUBU_TOKEN_TYPE

	#define INVALID_TOKEN_SUBTYPE INVALID_TYPE(uint16_t)
	#define INVALID_TOKEN_TYPE INVALID_TYPE(daijoubu_token_t)

	static const std::wstring DAIJOUBU_TOKEN_STR[] = {
		L"BEGIN", L"CONSTANT", L"CONTROL", L"END", L"IDENTIFIER", L"BOOLEAN", 
		L"NUMERIC", L"STRING", L"MODIFIER", L"NATIVE", L"OPERATOR", L"OPERATOR",
		L"STATEMENT", L"SUBSCRIPT", L"SUPERSCRIPT", L"SYMBOL", L"SYMBOL", 
		L"TYPE",
		};

	#define DAIJOUBU_TOKEN_STRING(_TYPE_) \
		((_TYPE_) > (unsigned) DAIJOUBU_TOKEN_MAX ? INVALID : \
		CHECK_STRING(DAIJOUBU_TOKEN_STR[_TYPE_]))

	static const size_t DAIJOUBU_TOKEN_SUBTYPE_LEN[] = {
		0, (DAIJOUBU_CONSTANT_MAX + 1), (DAIJOUBU_CONTROL_MAX + 1), 0, 0,
		(DAIJOUBU_LITERAL_BOOLEAN_MAX + 1), 0, 0, (DAIJOUBU_MODIFIER_MAX + 1), 
		(DAIJOUBU_NATIVE_MAX + 1), (DAIJOUBU_OPERATOR_MAX + 1), 
		(DAIJOUBU_OPERATOR_SIMPLE_MAX + 1), (DAIJOUBU_STATEMENT_MAX + 1), 0, 0, 
		(DAIJOUBU_SYMBOL_MAX + 1), (DAIJOUBU_SYMBOL_SIMPLE_MAX + 1), 
		(DAIJOUBU_TYPE_MAX + 1),
		};

	#define DAIJOUBU_TOKEN_SUBTYPE_LENGTH(_TYPE_) \
		((_TYPE_) > (unsigned) DAIJOUBU_TOKEN_MAX ? 0 : \
		DAIJOUBU_TOKEN_SUBTYPE_LEN[_TYPE_])

	static const std::wstring *DAIJOUBU_TOKEN_SUBTYPE_STRS[] = {
		NULL, DAIJOUBU_CONSTANT_STR, DAIJOUBU_CONTROL_STR, NULL, NULL,
		DAIJOUBU_LITERAL_BOOLEAN_STR, NULL, NULL, DAIJOUBU_MODIFIER_STR,
		DAIJOUBU_NATIVE_STR, DAIJOUBU_OPERATOR_STR, DAIJOUBU_OPERATOR_SIMPLE_STR, 
		DAIJOUBU_STATEMENT_STR, NULL, NULL, DAIJOUBU_SYMBOL_STR, 
		DAIJOUBU_SYMBOL_SIMPLE_STR, DAIJOUBU_TYPE_STR,
		};

	#define DAIJOUBU_TOKEN_SUBTYPE_STRINGS(_TYPE_) \
		((_TYPE_) > (unsigned) DAIJOUBU_TOKEN_MAX ? NULL : \
		DAIJOUBU_TOKEN_SUBTYPE_STRS[_TYPE_])

	extern std::wstring convert_subscript_to_string(
		__in const std::wstring &input
		);

	extern std::wstring convert_superscript_to_string(
		__in const std::wstring &input
		);

	extern uint16_t determine_token_subtype(
		__in const std::wstring &input,
		__in daijoubu_token_t type
		);

	extern uint32_t string_as_value(
		__in const std::string &input,
		__in daijoubu_radix_t radix
		);

	extern long double unicode_string_as_value(
		__in const std::wstring &input,
		__in daijoubu_radix_t radix,
		__in_opt bool simple = false
		);

	extern std::wstring token_subtype_as_unicode_string(
		__in daijoubu_token_t type,
		__in uint16_t subtype
		);
}

#endif // DAIJOUBU_LANGUAGE_H_
