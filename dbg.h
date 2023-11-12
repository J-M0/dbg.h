#ifndef DBG_H
#define DBG_H

#ifndef NDEBUG

#include <stdio.h>
#include <wchar.h>

#define dbg_gen_(func_name, type, fmt) \
static inline type dbg_ ## func_name ## _(char const* file, int line, char const* expr, type value) { \
	fprintf(stderr, "[dbg] %s:%d: %s = "#fmt"\n", file, line, expr, value); \
	return value; \
}

#define dbg_gen_1_(type, fmt) dbg_gen_(type, type, fmt)
#define dbg_gen_2_(t1, t2, fmt) dbg_gen_(t1 ## _ ## t2, t1 t2, fmt)
#define dbg_gen_3_(t1, t2, t3, fmt) dbg_gen_(t1 ## _ ## t2 ## _ ## t3, t1 t2 t3, fmt)

#define dbg_gen_p_1_(type, fmt) dbg_gen_(type ## _p, type*, fmt)

static inline _Bool dbg__Bool_(char const* file, int line, char const* expr, _Bool value) {
	fprintf(stderr, "[dbg] %s:%d: %s = %s\n", file, line, expr, value ? "true" : "false");
	return value;
}

dbg_gen_1_(char, %c)

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

#undef dbg_gen_
#undef dbg_gen_1_
#undef dbg_gen_2_
#undef dbg_gen_3_
#undef dbg_gen_p_
#undef dbg_gen_p_1_

/// Print the result of an expression to stderr using a format specifier
#define dbgfmt(expr, format) fprintf(stderr, "[dbg] "__FILE__":%d: "#expr" = "#format"\n", __LINE__, (expr))

/// Print the result of an expression to stderr and return it
#define dbg(expr) _Generic((expr), \
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
		char*: dbg_char_p_, \
		wchar_t*: dbg_wchar_t_p_, \
		void*: dbg_void_p_ \
	) (__FILE__, __LINE__, #expr, (expr))

#else

#define dbgfmt(expr, format) (expr)
#define dbg(expr) (expr)

#endif // NDEBUG

#endif // DBG_H
