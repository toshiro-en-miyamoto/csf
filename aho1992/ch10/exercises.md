# Chapter 10. Patterns, Automata and Regular Expressions

## §10.5 Regular Expressions

Q.10.5.1: In Example 10.13 we considered the regular expression `(a|ab)(c|bc)`,
and saw that its language consisted of the three strings `ac`, `abc`, and `abbc`, that is, an `a` and a `c`, separated by from zero to two `b`’s. Write two other regular expressions that define the same language.

- `ac|abc|abbc`
- `a(ε|b|bb)c`
- `a(c|bc|bbc)`
- `a(c|b(c|bc))`

Q.10.5.2.a: Write regex `R` for `L(R) = {=,<=,<,>=,>,!=}`.

- `= | != | <= | >= | < | >` &equiv; `(ε|!)= | (<|>)(=|ε)`
- `= | != | <= | >= | < | >` &equiv; `= | (!|<|>)= | <|>`

Q.10.5.2.b: Write regex for all strings of `0`s and `1`s that end in `0`.

- L(R) includes
  - `0`, `00`, `10`, `000`, `010`, `100`, `110`, and so on
  - `R` seems to be `(ε|(0|1)|(00|01|10|11)|...)0`
- thus, `R = ((0|1)*)0`

```bash
$ egrep '^((0|1)*)0$' 01.txt | awk '{printf "%s, ", $0}END{print ""}'
0, 00, 10, 000, 010, 100, 110, 0000, 0010, 0100, 0110, 1000, 1010, 1100, 1110, 00000, 
```

Q.10.5.2.c: Write regex for all strings of `0`s and `1`s with at least one `1`.

- L(R) includes
  - ~~`0`~~, `1`
  - ~~`00`~~, `01`, `10`, `11`
  - ~~`000`~~, `001`, `010`, `011`, `100`, `101`, `110`, `111`
  - ~~`0000`~~, `0001`, `0010`, `0011`, `0100`, `0101`, `0110`, `0111`
  - `1000`, `1001`, `1010`, `1011`, `1100`, `1101`, `1110`, `1111`, and so on
- likely `R = ((0|1)*)1((0|1)*)`
  - `L(ε1ε) = {1}`
  - `L((0|1)1ε) = {01,11}`
  - `L(ε1(0|1)) = {10,11}`
  - `L((0|1)(0|1)1ε) = {001,011,101,111}`
  - `L((0|1)1(0|1)) = {010,011,110,111}`
  - `L(ε1(0|1)(0|1)) = {100,101,110,111}`
  - `L((0|1)(0|1)(0|1)1ε) = {0001,0011,0101,0111,1001,1011,1101,1111}`
  - `L((0|1)(0|1)1(0|1)) = {0010,0011,0110,0111,1010,1011,1110,1111}`
  - `L((0|1)1(0|1)(0|1)) = {0100,1100,0101,1101,0110,1110,0111,1111}`
  - `L(ε1(0|1)(0|1)(0|1)) = {1000,1001,1010,1011,1100,1101,1110,1111}`
- thus `L(((0|1)*)1((0|1)*)) =`
  - `{1,01,10,11,001,010,011,100,101,110,111}` &cup;
  - `{0001,0010,0011,0100,0101,0110,0111}` &cup;
  - `{1000,1001,1010,1011,1100,1101,1110,1111}` and so on

```bash
$ egrep '^((0|1)*)1((0|1)*)$' 01.txt | awk '{printf "%s, ", $0}END{print ""}'
1, 01, 10, 11, 001, 010, 011, 100, 101, 110, 111, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111, 
```

Q.10.5.2.d: Write regex for all strings of `0`s and `1`s with at most one `1`.

- L(R) includes
  - `0`, `1`
  - `00`, `01`, `10`, ~~`11`~~
  - `000`, `001`, `010`, ~~`011`~~, `100`, ~~`101`, `110`, `111`~~
  - `0000`, `0001`, `0010`, ~~`0011`~~, `0100`, ~~`0101`, `0110`, `0111`~~
  - `1000`, ~~`1001`, `1010`, `1011`, `1100`, `1101`, `1110`, `1111`~~, and so on
- likely `R = (0*)(0|1)(0*)`
  - `L(ε(0|1)ε) = {0,1}`
  - `L(0(0|1)ε) = {00,01}`
  - `L(ε(0|1)0) = {00,10}`
  - `L(00(0|1)ε) = {000,001}`
  - `L(0(0|1)0) = {000,010}`
  - `L(ε(0|1)00) = {000,100}`
  - `L(000(0|1)ε) = {0000,0001}`
  - `L(00(0|1)0) = {0000,0010}`
  - `L(0(0|1)00) = {0000,0100}`
  - `L(ε(0|1)000) = {0000,1000}`
- thus `L((0*)(0|1)(0*)) =`
  - `{0,1,00,01,10,000,001,010,100,0000,0001,0010,0100,1000}` and so on

```bash
$ egrep '^(0*)(0|1)(0*)$' 01.txt | awk '{printf "%s, ", $0}END{print ""}'
0, 1, 00, 01, 10, 000, 001, 010, 100, 0000, 0001, 0010, 0100, 1000, 00000, 
```

Q.10.5.2.e: Write regex for all strings of `0`s and `1`s such that the third position from the right end is 1.

- L(R) includes
  - ~~`000`, `001`, `010`, `011`~~, `100`, `101`, `110`, `111`
  - ~~`0000`, `0001`, `0010`, `0011`~~, `0100`, `0101`, `0110`, `0111`
  - ~~`1000`, `1001`, `1010`, `1011`~~, `1100`, `1101`, `1110`, `1111`
- likely `R = ((0|1)*)1(0|1)(0|1)`
  - `L(ε1(0|1)(0|1)) = {100,101,110,111}`
  - `L((0|1)1(0|1)(0|1)) = {0100,0101,0110,0111,1100,1101,1110,1111}`

```bash
$ egrep '^((0|1)*)1(0|1)(0|1)$' 01.txt | awk '{printf "%s, ", $0}END{print ""}'
100, 101, 110, 111, 0100, 0101, 0110, 0111, 1100, 1101, 1110, 1111, 
```

Q.10.5.2.f: Write regex for all strings of lower-case letters that are in sorted order.

- Let lower-case letters be composed of `{a,b,c,d}`.
- Then `R = a*a | a*b*b | a*b*c*c | a*b*c*d*d`
  - or `a*(a|b*(b|c*(c|d*d)))`

```bash
$ egrep '^(a*(a|b*(b|c*(c|d*d))))$' abcd.txt | awk '{printf "%s, ", $0}END{print ""}'
a, b, c, d, aa, ab, ac, ad, bb, bc, bd, cc, cd, dd, aaa, aab, aac, aad, abb, abc, abd, acc, acd, add, bbb, bbc, bbd, bcc, bcd, bdd, ccc, ccd, cdd, ddd, aaaa, aaab, aaac, aaad, aabb, aabc, aabd, aacc, aacd, aadd, abbb, abbc, abbd, abcc, abcd, abdd, accc, accd, acdd, addd, bbbb, bbbc, bbbd, bbcc, bbcd, bbdd, bccc, bccd, bcdd, bddd, cccc, cccd, ccdd, cddd, dddd, 
```

Q.10.5.3.a: Write regex for all strings of `a`'s and `b`'s such that all runs of `a`'s are of even length.

- `R = (aa)*b*`

<table>
<tr>
<th><th>ε<th>b<th>bb
<tr>
<th>ε<td>ε<td>b<td>bb
<tr>
<th>A=aa<td>A<td>Ab<td>Abb
<tr>
<th>AA=aaaa<td>AA<td>AAb<td>AAbb
</table>

- `R = ((aa)*b*)*`

<table>
<tr>
<th><th>ε<th>b<th>bb<th>A<th>Ab<th>Abb<th>AA<th>AAb<th>AAbb
<tr>
<th>ε<td>ε<td>b<td>bb<td>A<td>Ab<td>Abb<td>AA<td>AAb<td>AAbb
<tr>
<th>b<td>b<td>bb<td>bbbb<td>bA<td>bAb<td>bAbb<td>bAA<td>bAAb<td>bAAbb
<tr>
<th>bb<td>bb<td>bbb<td>bbbb<td>bbA<td>bbAb<td>bbAbb<td>bbAA<td>bbAAb<td>bbAAbb
<tr>
<th>A<td>A<td>Ab<td>Abb<td>AA<td>AAb<td>AAbb<td>AAA<td>AAAb<td>AAAbb
<tr>
<th>Ab<td>Ab<td>Abb<td>Abbb<td>AbA<td>AbAb<td>AbAbb<td>AbAA<td>AbAAb<td>AbAAbb
<tr>
<th>Abb<td>Abb<td>Abbb<td>Abbbb<td>AbbA<td>AbbAb<td>AbbAbb<td>AbbAA<td>AbbAAb<td>AbbAAbb
<tr>
<th>AA<td>AA<td>AAb<td>AAbb<td>AAA<td>AAAb<td>AAAbb<td>AAAA<td>AAAAb<td>AAAAbb
<tr>
<th>AAb<td>AAb<td>AAbb<td>AAbbb<td>AAbA<td>AAbAb<td>AAbAbb<td>AAbAA<td>AAbAAb<td>AAbAAbb
<tr>
<th>AAbb<td>AAbb<td>AAbbb<td>AAbbbb<td>AAbbA<td>AAbbAb<td>AAbbAbb<td>AAbbAA<td>AAbbAAb<td>AAbbAAbb
</table>

```bash
$ cat ab.txt

bbbaabaaaa
aaaabb
abbabaa
aaa

$ egrep '^(((aa)*b*)*)$' ab.txt

bbbaabaaaa
aaaabb
```

Q.10.5.3.b: Write regex for strings that represent numbers of type `float` in C.

| | syntax
|-|--------
| a whole number    | *digits+* *exponent*
| a fraction number | [*digits?*] `.` [*digits?*] [*exponent*]

where
- *digits?* := `[0-9]*`
- *digits+* := `[0-9]*[0-9]`
- *exponent* := `e(ε|+|-)[0-9]*[0-9]`

`R` for numbers of type `float`:
- `= ([0-9]*[0-9])e(ε|+|-)[0-9]*[0-9]`
- `| (([0-9]*).([0-9]*)(ε|e(ε|+|-)[0-9]*[0-9]))`

The language includes:
- 0
