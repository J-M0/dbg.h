#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <wchar.h>

#ifdef DBG_INTERNAL_DEBUG
#define dbg_debug_type_(type) fprintf(stderr, "[dbg_internal] type is "#type"\n")
#else
#define dbg_debug_type_(type) ((void)0)
#endif

#define dbg_gen_(func_name, type, default_fmt, ...) \
static inline type dbg_ ## func_name ## _(char const* file, int line, char const* format, char const* expr, type value) { \
	dbg_debug_type_(type); \
	fprintf(stderr, "[dbg] %s:%d: %s = ", file, line, expr); \
	if (!format) { \
		fprintf(stderr, #default_fmt"\n", __VA_ARGS__); \
	} else { \
		fprintf(stderr, format, value); \
		fputc('\n', stderr); \
	} \
	return value; \
}

#define dbg_gen_1_var_(type, default_fmt, ...) dbg_gen_(type, type, default_fmt, __VA_ARGS__)
#define dbg_gen_2_var_(t1, t2, default_fmt, ...) dbg_gen_(t1 ## _ ## t2, t1 t2, default_fmt, __VA_ARGS__)
#define dbg_gen_3_var_(t1, t2, t3, default_fmt, ...) dbg_gen_(t1 ## _ ## t2 ## _ ## t3, t1 t2 t3, default_fmt, __VA_ARGS__)

#define dbg_gen_1_(type, default_fmt) dbg_gen_1_var_(type, default_fmt, value)
#define dbg_gen_2_(t1, t2, default_fmt) dbg_gen_2_var_(t1, t2, default_fmt, value)
#define dbg_gen_3_(t1, t2, t3, default_fmt) dbg_gen_3_var_(t1, t2, t3, default_fmt, value)

#define dbg_gen_p_1_(type, default_fmt) dbg_gen_(type ## _p, type*, default_fmt, value)

#define dbg_gen_complex_1_(type, default_fmt) dbg_gen_2_var_(type, _Complex, default_fmt, ((type*)&value)[0], ((type*)&value)[1])
#define dbg_gen_complex_2_(t1, t2, default_fmt) dbg_gen_3_var_(t1, t2, _Complex, default_fmt, ((t1 t2*)&value)[0], ((t1 t2*)&value)[1])

dbg_gen_1_var_(_Bool, %s, value ? "true" : "false")

dbg_gen_1_(char, '%c')

dbg_gen_2_(signed, char, %hhd)
dbg_gen_1_(short, %hd)
dbg_gen_1_(int, %d)
dbg_gen_1_(long, %ld)
dbg_gen_2_(long, long, %lld)

dbg_gen_2_(unsigned, char, %hhu)
dbg_gen_2_(unsigned, short, %hu)
dbg_gen_2_(unsigned, int, %u)
dbg_gen_2_(unsigned, long, %lu)
dbg_gen_3_(unsigned, long, long, %llu)

dbg_gen_1_(float, %f)
dbg_gen_1_(double, %f)
dbg_gen_2_(long, double, %Lf)

dbg_gen_p_1_(char, %s)
dbg_gen_p_1_(wchar_t, %ls)
dbg_gen_p_1_(void, %p)

dbg_gen_complex_1_(float, %f%+fi)
dbg_gen_complex_1_(double, %f%+fi)
dbg_gen_complex_2_(long, double, %Lf%+Lfi)

#undef dbg_gen_
#undef dbg_gen_1_
#undef dbg_gen_2_
#undef dbg_gen_3_
#undef dbg_gen_p_
#undef dbg_gen_p_1_
#undef dbg_gen_complex_1_
#undef dbg_gen_complex_2_
#undef dbg_debug_type_

#define dbg_generic_(expr) _Generic((expr), \
	_Bool: dbg__Bool_, \
	\
	char: dbg_char_, \
	\
	signed char: dbg_signed_char_, \
	short: dbg_short_, \
	int: dbg_int_, \
	long: dbg_long_, \
	long long: dbg_long_long_, \
	\
	unsigned char: dbg_unsigned_char_, \
	unsigned short: dbg_unsigned_short_, \
	unsigned int: dbg_unsigned_int_, \
	unsigned long: dbg_unsigned_long_, \
	unsigned long long: dbg_unsigned_long_long_, \
	\
	float: dbg_float_,\
	double: dbg_double_,\
	long double: dbg_long_double_,\
	\
	float _Complex: dbg_float__Complex_, \
	double _Complex: dbg_double__Complex_, \
	long double _Complex: dbg_long_double__Complex_, \
	\
	char*: dbg_char_p_, \
	wchar_t*: dbg_wchar_t_p_, \
	void*: dbg_void_p_ \
)

/// Print the result of an expression to stderr using a format specifier and return it
#define dbgfmt(expr, format) dbg_generic_(expr) (__FILE__, __LINE__, #format, #expr, (expr))

/// Print the result of an expression to stderr and return it
#define dbg(expr) dbg_generic_(expr) (__FILE__, __LINE__, NULL, #expr, (expr))

#endif // DBG_H
