#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <wchar.h>

#define dbgfmt(expr, format) fprintf(stderr, "[dbg] "#expr" = "#format"\n", (expr))

#define dbg(expr) do { \
	fputs("[dbg] "#expr" = ", stderr); \
	fprintf(stderr, \
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
		), \
		(expr) \
	); \
} while(0)

#endif // DBG_H
