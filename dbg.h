#ifndef DBG_H
#define DBG_H

#ifndef NDEBUG

#include <stdio.h>
#include <wchar.h>

#define dbg_impl_(expr, format) do { \
	fprintf(stderr, "[dbg] "__FILE__":%d: "#expr" = ", __LINE__); \
	fprintf(stderr, (format), (expr)); \
} while(0)

#define dbgfmt(expr, format) dbg_impl_(expr, #format"\n")

#define dbg(expr) dbg_impl_(expr, \
	_Generic((expr), \
		signed char: "%hhd\n", \
		short: "%hd\n", \
		int: "%d\n", \
		long: "%ld\n", \
		long long: "%lld\n", \
		\
		unsigned char: "%hhu\n", \
		unsigned short: "%hu\n", \
		unsigned int: "%u\n", \
		unsigned long: "%lu\n", \
		unsigned long long: "%llu\n", \
		\
		float: "%f\n", \
		double: "%f\n", \
		long double: "%Lf\n", \
		\
		char*: "%s\n", \
		wchar_t*: "%ls\n", \
		void*: "%p\n" \
	) \
)

#else

#define dbgfmt(expr, format) ((void)0)
#define dbg(expr) ((void)0)

#endif // NDEBUG

#endif // DBG_H
