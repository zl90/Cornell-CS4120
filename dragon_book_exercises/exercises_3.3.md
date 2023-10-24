# Exercises for Section 3.3

## Exercise 3.3.1
### (i)
(a) Invalid C input characters: "@", "`", "~"

### (ii)
(b) Lexical form of numerical constants in C++: 
integer-literal:
binary-literal integer-suffixopt
octal-literal integer-suffixopt
decimal-literal integer-suffixopt
hexadecimal-literal integer-suffixopt

https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4296.pdf

### (iii)
(b) Lexical form of identifiers in C++:
identifier:
identifier-nondigit
identifier identifier-nondigit
identifier digit

https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4296.pdf

## Exercise 3.3.2:
Describe the languages denoted by the following regular expressions:
a) **a(a|b)\*a** --> {a, aa, aaa, aba, aaba, aaaa, abaa, abba ... }
b) **(([empty]|a)b\*)\*** --> {[empty], b, a, ab, abb, bb, bbb, aaa, aaab ... }
c) **(a|b)\*a(a|b)(a|b)** --> 0 or more instances of {a, b} concatenated with {aaa, aab, aba, abb}
d) **a\*ba\*ba\*ba\*** --> string contains any number of "a"s, but must contain a total of 3 "b"s.

## Exercise 3.3.3:
In a string of length N, how many of the following are there?
a) Prefixes: N + 1
b) Suffixes: N + 1
c) Proper prefixes: N

