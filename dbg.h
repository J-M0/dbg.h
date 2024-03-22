/* SPDX-License-Identifier: MPL-2.0 */

/** @file
 * dbg.h v0.8.0: Quick and dirty print debuging
 * Copyright (C) 2024 James Morris
 * https://github.com/J-M0/dbg.h
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DBG_H
#define DBG_H

#include <stddef.h>
#include <stdio.h>

#ifdef DBG_INTERNAL_DEBUG
#define DBG_INTERNAL_DEBUG_TYPE(T) fputs("[dbg_internal] type is "#T"\n", stderr)
#else
#define DBG_INTERNAL_DEBUG_TYPE(T) ((void)0)
#endif

#define DBG_INTERNAL_MAKE(func_name, T, default_fmt, ...) \
static inline T dbg_internal_ ## func_name (char const* file, int line, char const* format, char const* expr, T value) { \
	DBG_INTERNAL_DEBUG_TYPE(T); \
	fprintf(stderr, "[dbg] %s:%d: %s = ", file, line, expr); \
	if (!format) { \
		fprintf(stderr, #default_fmt"\n", __VA_ARGS__); \
	} else { \
		fprintf(stderr, format, value); \
		fputc('\n', stderr); \
	} \
	return value; \
}

#define DBG_INTERNAL_MAKE_1_VAR(T, default_fmt, ...) DBG_INTERNAL_MAKE(T, T, default_fmt, __VA_ARGS__)
#define DBG_INTERNAL_MAKE_2_VAR(T1, T2, default_fmt, ...) DBG_INTERNAL_MAKE(T1 ## _ ## T2, T1 T2, default_fmt, __VA_ARGS__)
#define DBG_INTERNAL_MAKE_3_VAR(T1, T2, T3, default_fmt, ...) DBG_INTERNAL_MAKE(T1 ## _ ## T2 ## _ ## T3, T1 T2 T3, default_fmt, __VA_ARGS__)

#define DBG_INTERNAL_MAKE_1(T, default_fmt) DBG_INTERNAL_MAKE_1_VAR(T, default_fmt, value)
#define DBG_INTERNAL_MAKE_2(T1, T2, default_fmt) DBG_INTERNAL_MAKE_2_VAR(T1, T2, default_fmt, value)
#define DBG_INTERNAL_MAKE_3(T1, T2, T3, default_fmt) DBG_INTERNAL_MAKE_3_VAR(T1, T2, T3, default_fmt, value)

#define DBG_INTERNAL_MAKE_P_1(T, default_fmt) DBG_INTERNAL_MAKE(T ## _p, T*, default_fmt, value)
#define DBG_INTERNAL_MAKE_P_2(T1, T2, default_fmt) DBG_INTERNAL_MAKE(T1 ## _ ## T2 ## _p, T1 T2*, default_fmt, value)

#define DBG_INTERNAL_MAKE_COMPLEX_1(T, default_fmt) DBG_INTERNAL_MAKE_2_VAR(T, _Complex, default_fmt, ((T*)&value)[0], ((T*)&value)[1])
#define DBG_INTERNAL_MAKE_COMPLEX_2(T1, T2, default_fmt) DBG_INTERNAL_MAKE_3_VAR(T1, T2, _Complex, default_fmt, ((T1 T2*)&value)[0], ((T1 T2*)&value)[1])

DBG_INTERNAL_MAKE_1_VAR(_Bool, %s, value ? "true" : "false")

DBG_INTERNAL_MAKE_1(char, '%c')

DBG_INTERNAL_MAKE_2(signed, char, %hhd)
DBG_INTERNAL_MAKE_1(short, %hd)
DBG_INTERNAL_MAKE_1(int, %d)
DBG_INTERNAL_MAKE_1(long, %ld)
DBG_INTERNAL_MAKE_2(long, long, %lld)

DBG_INTERNAL_MAKE_2(unsigned, char, %hhu)
DBG_INTERNAL_MAKE_2(unsigned, short, %hu)
DBG_INTERNAL_MAKE_2(unsigned, int, %u)
DBG_INTERNAL_MAKE_2(unsigned, long, %lu)
DBG_INTERNAL_MAKE_3(unsigned, long, long, %llu)

DBG_INTERNAL_MAKE_1(float, %f)
DBG_INTERNAL_MAKE_1(double, %f)
DBG_INTERNAL_MAKE_2(long, double, %Lf)

DBG_INTERNAL_MAKE_P_1(char, %s)
DBG_INTERNAL_MAKE_P_1(wchar_t, %ls)
DBG_INTERNAL_MAKE_P_1(void, %p)

DBG_INTERNAL_MAKE_P_2(char, const, %s)
DBG_INTERNAL_MAKE_P_2(wchar_t, const, %ls)
DBG_INTERNAL_MAKE_P_2(void, const, %p)

DBG_INTERNAL_MAKE_COMPLEX_1(float, %f%+fi)
DBG_INTERNAL_MAKE_COMPLEX_1(double, %f%+fi)
DBG_INTERNAL_MAKE_COMPLEX_2(long, double, %Lf%+Lfi)

#undef DBG_INTERNAL_MAKE
#undef DBG_INTERNAL_MAKE_1_VAR
#undef DBG_INTERNAL_MAKE_2_VAR
#undef DBG_INTERNAL_MAKE_3_VAR
#undef DBG_INTERNAL_MAKE_1
#undef DBG_INTERNAL_MAKE_2
#undef DBG_INTERNAL_MAKE_3
#undef DBG_INTERNAL_MAKE_P_1
#undef DBG_INTERNAL_MAKE_COMPLEX_1
#undef DBG_INTERNAL_MAKE_COMPLEX_2
#undef DBG_INTERNAL_DEBUG_TYPE

#define DBG_INTERNAL_GENERIC(expr) _Generic((expr), \
	_Bool: dbg_internal__Bool, \
	\
	char: dbg_internal_char, \
	\
	signed char: dbg_internal_signed_char, \
	short: dbg_internal_short, \
	int: dbg_internal_int, \
	long: dbg_internal_long, \
	long long: dbg_internal_long_long, \
	\
	unsigned char: dbg_internal_unsigned_char, \
	unsigned short: dbg_internal_unsigned_short, \
	unsigned int: dbg_internal_unsigned_int, \
	unsigned long: dbg_internal_unsigned_long, \
	unsigned long long: dbg_internal_unsigned_long_long, \
	\
	float: dbg_internal_float,\
	double: dbg_internal_double,\
	long double: dbg_internal_long_double,\
	\
	float _Complex: dbg_internal_float__Complex, \
	double _Complex: dbg_internal_double__Complex, \
	long double _Complex: dbg_internal_long_double__Complex, \
	\
	char const*: dbg_internal_char_const_p, \
	wchar_t const*: dbg_internal_wchar_t_const_p, \
	void const*: dbg_internal_void_const_p, \
	\
	char*: dbg_internal_char_p, \
	wchar_t*: dbg_internal_wchar_t_p, \
	void*: dbg_internal_void_p \
)

/**
 * Print the result of an expression to stderr using a format specifier and return it
 * @param expr the expression to print
 * @param format a printf format specifier
 */
#define dbgfmt(expr, format) DBG_INTERNAL_GENERIC(expr) (__FILE__, __LINE__, #format, #expr, (expr))

/**
 * Print the result of an expression to stderr and return it
 * @param expr the expression to print
 */
#define dbg(expr) DBG_INTERNAL_GENERIC(expr) (__FILE__, __LINE__, NULL, #expr, (expr))

#endif // DBG_H
