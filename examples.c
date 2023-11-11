#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include "dbg.h"

#define eputs(s) (fputs((s), stderr) != EOF ? fputc('\n', stderr) : EOF)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

int main(void) {
	eputs("Booleans:");
	bool b = true;
	dbg(b);
	dbg(false);
	eputs("");

	eputs("Characters:");
	char c = 'c';
	dbg(c);
	eputs("");

	eputs("Signed ints:");
	signed char sc = 1;
	dbg(sc);
	short s = 2;
	dbg(s);
	int i = 3;
	dbg(i);
	long l = 4;
	dbg(l);
	long long ll = 5;
	dbg(ll);
	eputs("");

	eputs("Unsigned ints:");
	unsigned char uc = 6;
	dbg(uc);
	unsigned short us = 7;
	dbg(us);
	unsigned int ui = 8;
	dbg(ui);
	unsigned long ul = 9;
	dbg(ul);
	unsigned long long ull = 10;
	dbg(ull);
	eputs("");

	eputs("Floats and doubles:");
	float f = 11.0f;
	dbg(f);
	double d = 12.0;
	dbg(d);
	long double ld = 13.0;
	dbg(ld);
	eputs("");

	eputs("Strings and pointers:");
	char* cp = "14";
	dbg(cp);
	wchar_t* wp = L"15";
	dbg(wp);
	void* vp = cp;
	dbg(vp);
	eputs("");

	struct { int x; int y; } point = {100, 200};

	eputs("Struct members");
	dbg(point.x);
	dbg(point.y);
	eputs("");

	eputs("Arbitrary expressions:");
	void* vp2 = dbg(malloc(sizeof(char[10])));
	dbg(vp2);
	free(vp2);

	eputs("");
	dbg(i = 2 + 4);
	dbg(i);

	return 0;
}