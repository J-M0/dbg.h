# Changelog

## 0.8.0
* Support for `char const*`, `wchar_t const*`, and `void const*` types
* Internal code reorganization

## 0.7.0
* `dbgfmt()` can now return the result of its expression just like `dbg()`
* Macros can no longer be disabled with `NDEBUG` to be more in line with `dbg!`'s philosophy
* Doc comments now play nicely with Doxygen
* wchar.h is no longer included

## 0.6.0
* Add support for complex numbers
* `char`s are now printed with single quotes

## 0.5.1
* Fix a bug where macros were not properly disabled under `NDEBUG`
* Code cleanup and consolidation

## 0.5.0
* Support for all fundamental integer and float types
* Support for strings and wide strings
* Support for void pointers
