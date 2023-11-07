#ifndef DBG_H
#define DBG_H

#include <stdio.h>

#define dbg(expr, format) fprintf(stderr, "[dbg] "#expr" = "#format"\n", (expr))

#endif // DBG_H
