# dbg.h: Quick and dirty print debugging

`dbg.h` is a header-only library for quick and dirty print debugging. It contains two macros inspired by Rust's [`dbg!`](https://doc.rust-lang.org/std/macro.dbg.html) macro: `dbg()` and `dbgfmt()`.

These macros are intentionally simple and are meant as a debugging aid. They probably shouldn't hang around in your code for a long time outside of tests and the like. Find a real logging library if you need more featureful logging.

## Requirements

* A complier that supports C11 or later

## Macros
### dbg()

`dbg()` works just about the same way as `dbg!`. It takes an expression and prints the result to `stderr` with the file name and source line.

```c
dbg(1 + 1); // prints: [dbg] main.c:1: 1 + 1 = 2
```

`dbg()` also returns the result of the expression, so it can be put in the middle of just about any other expression.

```c
int a = 2;
int b = dbg(a * 2) + 1; // prints: [dbg] main.c:1: a * 2 = 4
```

### dbgfmt()

`dbgfmt()` works in the same way as `dbg()` except that you can choose the format specifier to print the result with.

```c
// since wchar_t is just a typedef for some kind of integer type,
// you need to specify the `%lc` format if you want to display the
// character instead of the numerical value
wchar_t wc = L'a';

dbg(wc); // prints: [dbg] main.c:6: wc = 97
dbgfmt(wc, L'%lc'); // prints: [dbg] main.c:7: wc = L'a'

// control float precision
dbgfmt(0.1 * 0.2, %.2f); // prints [dbg] main.c:10: 0.1 * 0.2 = 0.02

// display numbers in hexadecimal
dbgfmt(127, 0x%x); // prints [dbg] main.c:13: 127 = 0x7f

// print and capture a result
int i = dbgfmt(0xdeadbeef + 0x10, %x); // prints [dbg] main.c:16: 0xdeadbeef + 0x10 = deadbeff
```
