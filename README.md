# dbg.h: super simple print debugging

`dbg.h` is a header-only library for quick and dirty print debugging. It contains two macros inspired by Rust's [`dbg!`](https://doc.rust-lang.org/std/macro.dbg.html) macro: `dbg()` and `dbgfmt()`. They can be enabled or disabled like `assert` by defining `NDEBUG`.

These macros are intentionally simple and are meant as a debugging aid. Find a real logging library if you need more featureful logging.

## dbg()

`dbg()` works just about the same way as `dbg!`. It takes an expression and prints the result to `stderr` with the file name and source line.

```c
dbg(1 + 1); // prints: [dbg] main.c:1: 1 + 1 = 2
```

`dbg()` also returns the result of the expression, so it can be put in the middle of just about any other expression.

```c
int a = 2;
int b = dbg(a * 2) + 1; // prints: [dbg] main.c:1: a * 2 = 4
```

## dbgfmt()

`dbgfmt()` works similarly to `dbg()` with two differences:

1. You can choose the format specifier to print the result with
2. It does ***not*** return the result of its expression (this might change in a later version)

```c
// since wchar_t is just a typedef for some kind of integer type,
// you need to specify the `%lc` format if you want to display the
// character instead of the numerical value
wchar_t wc = L'a';

dbg(wc); // prints: [dbg] main.c:6: wc = 97
dbgfmt(wc, L'%lc'); // prints: [dbg] main.c:7: wc = L'a'

// control float precision
dbgfmt(0.1 * 0.2, %.2f) // prints [dbg] main.c:10: 0.1 * 0.2 = 0.02 
```
