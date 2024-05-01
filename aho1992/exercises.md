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

Q.10.5.2.e: Write regex for all strings of `0`s and `1`s such that the third position from the right end is 1.

- L(R) includes
  - ~~`000`, `001`, `010`, `011`~~, `100`, `101`, `110`, `111`
  - ~~`0000`, `0001`, `0010`, `0011`~~, `0100`, `0101`, `0110`, `0111`
  - ~~`1000`, `1001`, `1010`, `1011`~~, `1100`, `1101`, `1110`, `1111`
- likely `R = ((0|1)*)1(0|1)(0|1)`
  - `L(ε1(0|1)(0|1)) = {100,101,110,111}`
  - `L((0|1)1(0|1)(0|1)) = {0100,0101,0110,0111,1100,1101,1110,1111}`

Q.10.5.2.f: Write regex for all strings of lower-case letters that are in sorted order.

- Let lower-case letters be composed of `{a,b,c}`, then L(R) includes
  - `a`, `b`, `c`,
  - `aa`, `ab`, `ac`, ~~`ba`~~, `bb`, `bc`, ~~`ca`, `cb`~~, `cc`,
  - `aaa`, `aab`, `aac`, ~~`aba`~~, `abb`, `abc`, ~~`aca`, `acb`~~, `acc`,
  - ~~`baa`, `bab`, `bac`, `bba`~~, `bbb`, `bbc`, ~~`bca`, `bcb`~~, `bcc`,
  - ~~`caa`, `cab`, `cac`, `cba`, `cbb`, `cbc`, `cca`, `ccb`~~, `ccc`
- consider one-letter strings that are in sorted order
  - `R₁ = a|b|c`
- consider two-letter strings that are in sorted order
  - `R₂ = aa | ab|bb  | ac|bc|cc`
  - or `= aa | (a|b)b | (a|b|c)c`
- consider one- or two-letter strings that are in sorted order
  - `R₁₂ = R₁|R₂`
  - or `= a | aa | b | (a|b)b | c | (a|b|c)c`
- consider three-letter strings that are in sorted order
  - `R₃ = aaa | aab|abb|bbb | aac|abc|acc|bbc|bcc|ccc`
  - or `= aaa | (aa|ab|bb)b | (aa|ab|ac|bb|bc|cc)c`
- consider one-, two- or three-letter strings that are in sorted order
  - `R₁₂₃ = R₁₂|R₃`
  - or `= (ε|a|aa)a | (ε|a|b|aa|ab|bb)b | (ε|a|b|c|aa|ab|ac|bb|bc|cc)c`
  - or `= (ε|a|aa)a | (ε|a|aa|b|ab|bb)b | (ε|a|aa|b|ab|bb|c|ac|bc|cc)c`
  - or `= (ε|a|aa)a | (ε|a|aa)b | (ε|a|b)bb | (ε|a|aa)c | (ε|a|b)bc | (ε|a|b|c)cc`
  - or `= (ε|a|aa)(a|b|c) | (ε|a|b)b(b|c) | (ε|a|b|c)cc`
    - 1: `{a,b,c}`
    - 2: `{aa,ab,ac,bb,bc,cc}`
    - 3: `{aaa,aab,aac,abb,abc,bbb,bbc,acc,bcc,ccc}`
- Let lower-case letters be composed of `{a,b,c,d}`, then L(R) includes
  - `a`, `b`, `c`, `d`,
  - `aa`, `ab`, `ac`, `ad`, `bb`, `bc`, `bd`, `cc`, `cd`, `dd`,
  - `aaa`, `aab`, `aac`, `aad`, `abb`, `abc`, `abd`, `acc`, `acd`, `add`,
  - `bbb`, `bbc`, `bbd`, `bcc`, `bcd`, `bdd`,
  - `ccc`, `ccd`, `cdd`,
  - `ddd`,
  - `aaaa`, `aaab`, `aaac`, `aaad`, `aabb`, `aabc`, `aabd`, `aacc`, `aacd`, `aadd`,
  - `abbb`, `abbc`, `abbd`, `abcc`, `abcd`, `abdd`,
  - `accc`, `accd`, `acdd`,
  - `addd`,
  - `bbbb`, `bbbc`, `bbbd`, `bbcc`, `bbcd`, `bbdd`,
  - `bccc`, `bccd`, `bcdd`,
  - `bddd`,
  - `cccc`, `cccd`, `ccdd`,
  - `cddd`,
  - `dddd`
- consider one-letter strings that are in sorted order
  - `R₁ = a|b|c|d`
- consider two-letter strings that are in sorted order
  - `R₂ = aa|ab|bb | ac|bc|cc | ad|bd|cd|dd`
  - or `= aa|ab|bb | (a|b|c)c | (a|b|c|d)d`
- consider three-letter strings that are in sorted order,
  - the language is
    - `{aaa}` &cup;
    - `{aab|abb|bbb}` &cup;
    - `{aac|abc|bbc|acc|bcc|ccc}` &cup;
    - `{aad|abd|bbd|acd|bcd|ccd|add|bdd|cdd|ddd}`
  - `R₃ =`
    - `= aaa`
    - `| (aa|ab|bb)b`
    - `| (aa|ab|bb)c | (a|b|c)cc`
    - `| (aa|ab|bb)d | (a|b|c)cd | (a|b|c|d)dd`
- thus it is hard to write a simple regex for such strings
