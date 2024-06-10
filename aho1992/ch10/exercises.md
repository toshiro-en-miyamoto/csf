# Chapter 10. Patterns, Automata and Regular Expressions

## §10.5 Regular Expressions

### Q.10.5.1

In Example 10.13 we considered the regular expression `(a|ab)(c|bc)`,
and saw that its language consisted of the three strings `ac`, `abc`, and `abbc`, that is, an `a` and a `c`, separated by from zero to two `b`’s. Write two other regular expressions that define the same language.

- `ac|abc|abbc`
- `a(ε|b|bb)c`
- `a(c|bc|bbc)`
- `a(c|b(c|bc))`

### Q.10.5.2.a

Write regex `R` for `L(R) = {=,<=,<,>=,>,!=}`.

- `= | != | <= | >= | < | >` &equiv; `(ε|!)= | (<|>)(=|ε)`
- `= | != | <= | >= | < | >` &equiv; `= | (!|<|>)= | <|>`

### Q.10.5.2.b

Write regex R for
- all strings of 0's and 1's that end in 0.

L(¬R) can be described as
- all strings of 0's and 1's that end in 1.

For strings of 3 digits or less, L(R) should

- include: 0, 00, 10, 000, 010, 100, 110
- exclude: ε, 1, 01, 11, 001, 011, 101, 111

Answer: `(0|1)*0`

| `(0\|1)*`     | `(0\|1)*0`
|---------------|------------
| ε             | {0}
| (0\|1)        | {00, 10}
| (0\|1)(0\|1)  | {000, 010, 100, 110}

```bash
$ cat Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 100, 101, 110, 111,

$ egrep '^(0|1)*0$' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
0, 00, 10, 000, 010, 100, 110,
```

### Q.10.5.2.c

Write regex R for
- all strings of 0's and 1's with at least one 1.

The condition for L(R) should be:
- 1 &le; the number of 1's

The condition for L(¬R) should be
- ¬(1 &le; the number of 1's), which is equivalent to
- the number of 1's &lt; 1, which is equivalent to
- the number of 1's = 0

For strings of 3 digits or less, L(R) should

- include: 1, 01, 10, 11, 001, 010, 011, 100, 101, 110, 111
- exclude: ε, 0, 00, 000

Answer: `(0|1)*1(0|1)*`

| `(0\|1)*`     | 1 | `(0\|1)*`     | `(0\|1)*1(0\|1)*`
|---------------|---|---------------|-------------------
| ε             | 1 | ε             | {1}
| (0\|1)        | 1 | ε             | {01, 11}
| ε             | 1 | (0\|1)        | {10, 11}
| (0\|1)(0\|1)  | 1 | ε             | {001, 011, 101, 111}
| (0\|1)        | 1 | (0\|1)        | {010, 011, 110, 111}
| ε             | 1 | (0\|1)(0\|1)  | {100, 101, 110, 111}

```bash
$ cat Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 100, 101, 110, 111,

$ egrep '^(0|1)*1(0|1)*$' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
1, 01, 10, 11, 001, 010, 011, 100, 101, 110, 111,
```

Alternative answer: `[01]*1[01]`

```bash
$ cat  Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 100, 101, 110, 111,

S sed -n '/^[01]*1[01]*$/p' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
1, 01, 10, 11, 001, 010, 011, 100, 101, 110, 111,

$ sed '/^0*$/d' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
1, 01, 10, 11, 001, 010, 011, 100, 101, 110, 111,

$ sed -n '/^0*$/p' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
, 0, 00, 000,
```

### Q.10.5.2.d

Write regex R for
- all strings of 0's and 1's with at most one 1.

The condition for L(R) should be:
- the number of 1's &le; 1

The condition for L(¬R) should be
- ¬(the number of 1's &le; 1), which is equivalent to
- 1 &lt; the number of 1's

For strings of 3 digits or less, L(R) should

- include: 0, 1, 00, 01, 10, 000, 001, 010, 100
- exclude: ε, 11, 011, 101, 110, 111

Answer: `0*(0|1)0*`

| `0*`  | `0\|1`  | `0*`  | `0*(0\|1)0*`
|-------|---------|-------|----------
| ε     | {0, 1}  | ε     | {0, 1}
| 0     | {0, 1}  | ε     | {00, 01}
| ε     | {0, 1}  | 0     | {00, 10}
| 00    | {0, 1}  | ε     | {000, 001}
| 0     | {0, 1}  | 0     | {000, 010}
| ε     | {0, 1}  | 00    | {000, 100}

```bash
$ cat Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 100, 101, 110, 111,

$ egrep '^0*(0|1)0*$' Q.10.5.2.b.txt | awk '{printf "%s, ", $0}'
0, 1, 00, 01, 10, 000, 001, 010, 100,
```

### Q.10.5.2.e

Write regex for all strings of `0`s and `1`s such that the third position from the right end is 1.

For strings of 4 digits or less, L(R) should

- include: 100, 101, 110, 111, 0100, 0101, 0110, 0111, 1100, 1101, 1110, 1111
- exclude: ε, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 0000, 0001, 0010, 0011, 1000, 1001, 1010, 1011

Answer: `(0|1)*1(0|1)(0|1)`

| `(0\|1)*` | 1 | `(0\|1)(0\|1)`    | `(0\|1)*1(0\|1)(0\|1)`
|-----------|---|-------------------|------------------------
| ε         | 1 | {00, 01, 10, 11}  | {100, 101, 110, 111}
| 0         | 1 | {00, 01, 10, 11}  | {0100, 0101, 0110, 0111}
| 1         | 1 | {00, 01, 10, 11}  | {1100, 1101, 1110, 1111}

```bash
$ cat Q.10.5.2.e.txt | awk '{printf "%s, ", $0}'
, 0, 1, 00, 01, 10, 11, 000, 001, 010, 011, 100, 101, 110, 111, 0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111,

$ egrep '^(0|1)*1(0|1)(0|1)$' Q.10.5.2.e.txt | awk '{printf "%s, ", $0}'
100, 101, 110, 111, 0100, 0101, 0110, 0111, 1100, 1101, 1110, 1111,
```

### Q.10.5.2.f

Write regex for all strings of lower-case letters that are in sorted order.

- Let lower-case letters be composed of `{a,b,c,d}`.
- Then `R = a*a | a*b*b | a*b*c*c | a*b*c*d*d`
  - or `a*(a|b*(b|c*(c|d*d)))`

```bash
$ cat Q.10.5.2.f.txt | awk '{printf "%s, ", $0}'
, a, b, c, d, aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc, dd, aaa, aab, aac, aad, aba, abb, abc, abd, aca, acb, acc, acd, ada, adb, adc, add, baa, bab, bac, bad, bba, bbb, bbc, bbd, bca, bcb, bcc, bcd, bda, bdb, bdc, bdd, caa, cab, cac, cad, cba, cbb, cbc, cbd, cca, ccb, ccc, ccd, cda, cdb, cdc, cdd, daa, dab, dac, dad, dba, dbb, dbc, dbd, dca, dcb, dcc, dcd, dda, ddb, ddc, ddd, aaaa, aaab, aaac, aaad, aaba, aabb, aabc, aabd, aaca, aacb, aacc, aacd, aada, aadb, aadc, aadd, abaa, abab, abac, abad, abba, abbb, abbc, abbd, abca, abcb, abcc, abcd, abda, abdb, abdc, abdd, acaa, acab, acac, acad, acba, acbb, acbc, acbd, acca, accb, accc, accd, acda, acdb, acdc, acdd, adaa, adab, adac, adad, adba, adbb, adbc, adbd, adca, adcb, adcc, adcd, adda, addb, addc, addd, baaa, baab, baac, baad, baba, babb, babc, babd, baca, bacb, bacc, bacd, bada, badb, badc, badd, bbaa, bbab, bbac, bbad, bbba, bbbb, bbbc, bbbd, bbca, bbcb, bbcc, bbcd, bbda, bbdb, bbdc, bbdd, bcaa, bcab, bcac, bcad, bcba, bcbb, bcbc, bcbd, bcca, bccb, bccc, bccd, bcda, bcdb, bcdc, bcdd, bdaa, bdab, bdac, bdad, bdba, bdbb, bdbc, bdbd, bdca, bdcb, bdcc, bdcd, bdda, bddb, bddc, bddd, caaa, caab, caac, caad, caba, cabb, cabc, cabd, caca, cacb, cacc, cacd, cada, cadb, cadc, cadd, cbaa, cbab, cbac, cbad, cbba, cbbb, cbbc, cbbd, cbca, cbcb, cbcc, cbcd, cbda, cbdb, cbdc, cbdd, ccaa, ccab, ccac, ccad, ccba, ccbb, ccbc, ccbd, ccca, cccb, cccc, cccd, ccda, ccdb, ccdc, ccdd, cdaa, cdab, cdac, cdad, cdba, cdbb, cdbc, cdbd, cdca, cdcb, cdcc, cdcd, cdda, cddb, cddc, cddd, daaa, daab, daac, daad, daba, dabb, dabc, dabd, daca, dacb, dacc, dacd, dada, dadb, dadc, dadd, dbaa, dbab, dbac, dbad, dbba, dbbb, dbbc, dbbd, dbca, dbcb, dbcc, dbcd, dbda, dbdb, dbdc, dbdd, dcaa, dcab, dcac, dcad, dcba, dcbb, dcbc, dcbd, dcca, dccb, dccc, dccd, dcda, dcdb, dcdc, dcdd, ddaa, ddab, ddac, ddad, ddba, ddbb, ddbc, ddbd, ddca, ddcb, ddcc, ddcd, ddda, dddb, dddc, dddd,

$ egrep '^a*(a|b*(b|c*(c|d*d)))$' Q.10.5.2.f.txt | awk '{printf "%s, ", $0}'
a, b, c, d, aa, ab, ac, ad, bb, bc, bd, cc, cd, dd, aaa, aab, aac, aad, abb, abc, abd, acc, acd, add, bbb, bbc, bbd, bcc, bcd, bdd, ccc, ccd, cdd, ddd, aaaa, aaab, aaac, aaad, aabb, aabc, aabd, aacc, aacd, aadd, abbb, abbc, abbd, abcc, abcd, abdd, accc, accd, acdd, addd, bbbb, bbbc, bbbd, bbcc, bbcd, bbdd, bccc, bccd, bcdd, bddd, cccc, cccd, ccdd, cddd, dddd,
```

### Q.10.5.3.a

Write regex for all strings of `a`'s and `b`'s such that all runs of `a`'s are of even length.

Let a file contains five lines (the first line is empty):

```bash
$ cat Q.10.5.3.a.txt

bbbaabaaaa
aaaabb
abbabaa
aaa
```

With the above file, L(R) should

- include: `bbbaabaaaa` and `aaaabb`
- exclude: ε, `abbabaa` and `aaa`

Answer: `b*(aab*)+`

| `aab*`          | `aab*aab*`
|-----------------|------------
| {aa, aab, aabb} | {aaaa, aaaab, aaaabb}
|                 | {aabaa, aabaab, aabaabb}
|                 | {aabbaa, aabbaab, aabbaabb}

```bash
$ egrep '^b*(aab*)+$' Q.10.5.3.a.txt
bbbaabaaaa
aaaabb
```

### Q.10.5.3.b

Write regex for strings that represent numbers of type `float` in C++. The syntax of [floating-point literal](https://en.cppreference.com/w/cpp/language/floating_literal) is as follows; where `(?)` denotes optional:

- sign(?) digits exponent
- sign(?) digits . exponent(?)
- sign(?) digits(?) . digits exponent(?)

The language includes:

| syntax | literal
|--------|---------
| sign(?) digits exponent                 | 1e1
| sign(?) digits . exponent(?)            | +1., -2.e0
| sign(?) digits(?) . digits exponent(?)  | +.2, -0.2, -.2E+3, 0.2e-3

Let

- sign(?) := `[-+]?`
- digits := `[0-9]+`
- digits(?) := `[0-9]*`
- exponent := `[eE][-+]?[0-9]+`
- exponent(?) := `([eE][-+]?[0-9]+)?`

then the regex `R`

- `= [-+]?[0-9]+[eE][-+]?[0-9]+`
- `| [-+]?[0-9]+\.([eE][-+]?[0-9]+)?`
- `| [-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?`

The regex works as shown below:

```bash
$ cat Q.10.5.3.b.txt

0
1e1
+1.
-2.e0
+.2
-0.2
-.2E+3
0.2e-3

$ egrep '^[-+]?[0-9]+[eE][-+]?[0-9]+$' Q.10.5.3.b.txt
1e1

$ egrep '^[-+]?[0-9]+\.([eE][-+]?[0-9]+)?$' Q.10.5.3.b.txt
+1.
-2.e0

$ egrep '^[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?$' Q.10.5.3.b.txt
+.2
-0.2
-.2E+3
0.2e-3
```

For your reference, the following code compiles with C++20:

```c++
// float_literal.cpp
#include <type_traits> 

void float_literal()
{
  // 0 is int
  static_assert(std::is_floating_point_v<decltype(0)> == false);
  // sign(?) digits exponent : 1e1
  static_assert(std::is_floating_point_v<decltype(1e1)>);
  // sign(?) digits . exponent(?) : +1., -2.e0
  static_assert(std::is_floating_point_v<decltype(+1.)>);
  static_assert(std::is_floating_point_v<decltype(-2.e0)>);
  // sign(?) digits(?) . digits exponent(?) : +.2, -0.2, -.2E+3, 0.2e-3
  static_assert(std::is_floating_point_v<decltype(+.2)>);
  static_assert(std::is_floating_point_v<decltype(-0.2)>);
  static_assert(std::is_floating_point_v<decltype(-.2E+3)>);
  static_assert(std::is_floating_point_v<decltype(0.2e-3)>);
}
```
