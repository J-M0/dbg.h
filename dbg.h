#ifndef DBG_H
#define DBG_H

#ifndef NDEBUG

#include <stdio.h>
#include <wchar.h>

#define dbg_impl_(expr, format) (fprintf(stderr, "[dbg] "__FILE__":%d: "#expr" = ", __LINE__), fprintf(stderr, (format), (expr)))
#define dbg_bool_impl_(expr) fprintf(stderr, "[dbg] "__FILE__":%d: "#expr" = %s\n", __LINE__, (expr) ? "true" : "false")

#define dbgfmt(expr, format) dbg_impl_(expr, #format"\n")

#define dbg(expr) _Generic((expr), \
		_Bool: dbg_bool_impl_(expr), \
		default: dbg_impl_(expr, _Generic((expr), \
			_Bool: 0, /* not used, just make the compiler happy */ \
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
	) \
)

#else

#define dbgfmt(expr, format) ((void)0)
#define dbg(expr) ((void)0)

#endif // NDEBUG

#endif // DBG_H
