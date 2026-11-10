## Q5 - Count the work done by a loop (7 marks)

### Derive the stopping condition
If n=a*b and both factors were greater than sqrt(n), their product would exceed n. Therefore a composite n has a factor no greater than sqrt(n), including equality for perfect squares. Starting at divisor 2, test only while i*i<=n. For large unsigned long values i*i can wrap and corrupt the condition; signed multiplication could instead overflow with undefined behaviour. Since i is positive, i<=n/i expresses the same bound without multiplying. n<2 is rejected before the loop. Return immediately when a remainder is zero.

The completed-code exercise fills only the TODO region. It uses the equivalent overflow-safe guard i<=n/i. As in the expected output, checks counts the divisibility operations n%i; it does not count the division introduced by the safe guard. loops.c reports those guard divisions separately, so the displayed expected counts are not misrepresented as every division expression in the program. A compiler can combine quotient/remainder calculations, so source operation counts also do not claim hardware instruction counts.

### Predicted and observed work
| Ticket | Prime? | Full trial prediction / actual | Improved prediction / actual |
| --- | --- | --- | --- |
| 97 | Yes | 95 / 95 | 8 / 8 |
| 100 | No | 1 / 1 | 1 / 1 |
| 7919 | Yes | 7917 / 7917 | 87 / 87 |
| 1000003 | Yes | 1000001 / 1000001 | 999 / 999 |

For prime 97 the candidates are 2..9: eight checks. For 7919 they are 2..88: 87. For 1000003 they are 2..1000: 999. Ticket 100 stops at divisor 2. Changing only the guard to i<n produces the full-trial counts above. The complete exercise prints:

```text
97  prime      divisions = 8
     100  not prime  divisions = 1
    7919  prime      divisions = 87
 1000003  prime      divisions = 999
```

### for, while and do-while
for and while check the bound before their first body execution. The do-while body runs at least once, so n=2 and n=3 must return true first; otherwise testing divisor 2 would incorrectly reject 2. For n>=4, divisor 2 is always within the square-root bound and is safe as the first body execution. All three improved versions perform the same remainder tests; do-while saves its initial guard division after those small-value checks.

```text
n,prime,full_remainders,for_remainders,while_remainders,do_remainders,for_guard_divisions,do_guard_divisions
0,0,0,0,0,0,0,0
1,0,0,0,0,0,0,0
2,1,0,0,0,0,1,0
3,1,1,0,0,0,1,0
4,0,1,1,1,1,1,0
9,0,2,2,2,2,2,1
97,1,95,8,8,8,9,8
100,0,1,1,1,1,1,0
7919,1,7917,87,87,87,88,87
1000003,1,1000001,999,999,999,1000,999
All four versions agree for 0..10000.
```

The output includes 0,1,2,3,4 and 9 to expose non-primes below two, small primes and perfect squares. All four variants agree on 0..10000. The exhaustive redesign check in Q7 covers all values through the maximum ticket. A return is used for early composite detection; break would require a flag and a correct post-loop result. A continue belongs only where the divisor progression is guaranteed, otherwise it can accidentally skip an increment in a while loop. The sieve in Q7 uses continue to skip composite base candidates.

### Complexity and sieve alternative
Full trial uses O(n) remainder tests in the prime worst case and O(1) working space. Improved trial uses O(sqrt(n)) tests, with O(1) state; both can return after one test for an even composite. The count here treats fixed-width arithmetic as O(1). Arbitrary-precision arithmetic would require a separate bit-complexity model.

For many bounded queries, sieve an array once:
```text
allocate flags[0..N], initially true
flags[0] = flags[1] = false
for p = 2 while p <= N/p:
    if flags[p] is false: continue
    for multiple = p*p to N in steps of p:
        flags[multiple] = false
answer each ticket n with flags[n], after checking 0 <= n <= N
```
Starting at p*p avoids redoing multiples already covered by smaller primes. Preprocessing takes O(N log log N), queries O(1), and storage O(N). The inclusive 0..N indexing needs N+1 flags, not N flags. For a few tickets or very large N, trial division avoids setup and a large allocation. Q7 implements and measures this alternative for the bounded repeated-query case.
