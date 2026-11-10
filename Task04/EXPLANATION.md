## Q4 - Grade and scholarship classifier (6 marks)

### Rules, validation and two implementations
Grades are S for 90..100, A for 80..89, B for 70..79, C for 60..69, D for 50..59 and F for 0..49. Outside 0..100 is '?'. Every implementation checks this domain before selecting a branch or indexing a table. The ladder tests descending lower bounds. The switch uses marks/10, combining cases 10 and 9 for S; the completed supplied code returns directly from each case.

The required inputs 100,90,89,0,-1,101 produce S,S,A,F,?,? in all three correct implementations. Without the validation, 101/10=10 could incorrectly give S, while -1/10=0 under truncation toward zero could give F. Omitting case 10 would mishandle 100. The test set uses b-1,b,b+1 at every boundary 50,60,70,80,90 plus domain edges -1,0,1,99,100,101. All 105 integer inputs from -2 through 102 are also compared across ladder, switch and table.

```text
100:S 95:S 83:A 50:D 49:F -5:?
```

### Deliberate fall-through experiment
In a separate copy, only the S return is removed. Cases 10 and 9 then fall into case 8, so 100 and 95 become A. The other supplied outputs stay unchanged:

```text
100:A 95:A 83:A 50:D 49:F -5:?
```

A switch using assignments requires break unless fall-through is intentional. A direct return also exits the function, so the correct supplied exercise needs no additional break. Standard C case labels require integer constant expressions; case 75..84 is not standard C range syntax. marks/10 works for these decade-aligned ranges, but it cannot distinguish an arbitrary 75..84 band, which spans parts of two buckets. A ladder with explicit comparisons is easier to adapt to irregular boundaries. Compiler-specific case-range extensions are avoided.

### Scholarship decision and explicit missing-policy assumption
The brief does not supply income bands or scholarship categories. To demonstrate the structure, the following illustrative policy is used, not presented as the university's actual policy: income <=Rs250000 with grade S/A gives full scholarship; grade B in that band gives partial; income above Rs250000 and <=Rs500000 with grade S/A gives partial; all other valid cases give none. Negative income or invalid marks are rejected.

Nested if is chosen because there are two ordered income bands and simple grade membership checks. It expresses the band boundaries directly and handles invalid input before policy selection. Tests cover incomes 250000,250001,500000,500001 and grades S,A,B,C. A switch inside an if is reasonable if each grade gets a separate rule. A lookup table is useful for a larger stable grade-by-band policy, but then the mapping from incomes to bands still requires validation/comparisons.

### Lookup alternative and complexity
```c
static const char grades[11] = {'F','F','F','F','F','D','C','B','A','S','S'};
if (marks < 0 || marks > 100) return '?';
return grades[marks / 10];
```
The table uses 11 char bytes and O(1) indexing after validation. A generalized ladder has O(k) worst-case comparisons for k grade bands and O(1) extra working state, with O(k) source branches. With six fixed grades all methods are bounded constant time. A compiler may implement a switch with a jump table, comparison tree or linear tests, so its exact machine cost cannot be assumed from source syntax alone. This solution claims semantic agreement and boundary coverage, not a measured speed superiority.

```text
marks,ladder,switch,lookup
-1,?,?,?
0,F,F,F
1,F,F,F
49,F,F,F
50,D,D,D
51,D,D,D
59,D,D,D
60,C,C,C
61,C,C,C
69,C,C,C
70,B,B,B
71,B,B,B
79,B,B,B
80,A,A,A
81,A,A,A
89,A,A,A
90,S,S,S
91,S,S,S
99,S,S,S
100,S,S,S
101,?,?,?
marks,income,scholarship(0=none;1=partial;2=full)
95,250000,2
95,250001,1
95,500000,1
95,500001,0
85,250000,2
85,250001,1
85,500000,1
85,500001,0
75,250000,1
75,250001,0
75,500000,0
75,500001,0
65,250000,0
65,250001,0
65,500000,0
65,500001,0
105 marks inputs and scholarship boundaries verified.
```
