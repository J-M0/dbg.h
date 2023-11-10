#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include "dbg.h"

int main(void) {
	bool b = true;
	dbg(b);

	char c = 'c';
	dbg(c);

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

	float f = 11.0f;
	dbg(f);
	double d = 12.0;
	dbg(d);
	long double ld = 13.0;
	dbg(ld);

	char* cp = "14";
	dbg(cp);
	wchar_t* wp = L"15";
	dbg(wp);
	void* vp = cp;
	dbg(vp);

	struct { int x; int y; } point = {100, 200};

	dbg(point.x);
	dbg(point.y);

	void* vp2 = dbg(malloc(sizeof(char[10])));
	dbg(vp2);
	free(vp2);

	i = dbg(2 + 4);
	dbg(i);

	return 0;
}
