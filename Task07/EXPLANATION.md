## Q7 - Diagnose, redesign and validate (13 marks)

### A. Diagnose the bottleneck (2 marks)
Q5's square-root trial repeats the same divisibility questions every time a ticket is checked. For 1000 queries cycling 97,100,7919,1000003, the measured workload is 273750 remainder tests plus 274500 safe-bound guard divisions; it returns 750 prime answers. The large prime alone causes 999 remainder tests on each of its 250 appearances, or 249750 tests, about 91.2% of the total. Switching for to while cannot remove this repeated mathematical work.

### B. Define a measurable objective (2 marks)
For ticket numbers bounded by 1000003, remove at least 99% of repeated query remainder tests on the same 1000-query workload while preserving every primality answer. Report preprocessing operations and memory separately. A second objective is O(1) lookup per future ticket. This is an operation-count objective, not a promise that a single short batch will run faster after including setup.

### C. Revised design and trade-offs (4 marks)
Build a Sieve of Eratosthenes once for the allowed ticket domain, then reuse it. The exploited property is that every composite has a prime factor no greater than its square root, so marking multiples of each prime identifies composites for all later queries. The table generalizes beyond a cache of the four repeated sample values: it supports any future ticket in range.

```text
allocate N+1 byte flags; reject allocation failure
initialize flags true; set flags 0 and 1 false
for candidate p=2 while p<=N/p:
    if flags[p] is false: continue
    mark p*p, p*p+p, ... up to N as composite
for each validated ticket in 0..N:
    answer using flags[ticket]
release flags when the reusable query session ends
```
The fixed N=1000003 keeps p*p and multiple+p within unsigned long range. A general implementation accepting arbitrary N would need additional size/allocation/loop-overflow checks. This program uses only known in-range fixtures and validates all possible domain answers. It handles allocation failure and frees the table. For an externally supplied ticket, domain validation must precede indexing.

Extra memory is 1000004 bytes for unsigned-char flags on this machine, plus small loop state. A bit-packed sieve could lower storage, but would add masking code. Setup is O(N log log N), a batch of q lookups is O(q), and persistent table storage is O(N). Square-root trial is O(q sqrt(N)) worst-case with O(1) state. For sparse enormous ticket numbers the array may be unaffordable; a segmented approach or trial division may be more suitable.

### D. Predict before execution (1 mark)
The recorded prediction was (8+1+87+999)*250=273750 original remainder tests versus zero query remainders for the sieve, 1000 direct lookups, 1000004 flag bytes and 750 prime answers. The prediction explicitly allowed nonzero initialization and marking work; it did not assume a free sieve build.

### E. Implement and validate (2 marks)

```text
method,queries,prime_answers,query_remainders,query_guard_divisions,flag_bytes
sqrt_trial,1000,750,273750,274500,0
sieve,1000,750,0,0,1000004
Preprocessing: initialized_flags=1000004 outer_tests=999 marking_writes=2122051
CPU_ms: trial=2.148 sieve_build=1.971 lookups=0.002
Exhaustive validation: all 1000004 inputs from 0 through 1000003 agree.
Measured objective: 100% fewer query remainder tests; preprocessing and memory are additional costs.
```

The same 1000 fixtures were evaluated by both methods. Additionally, every integer 0..1000003 was checked for agreement, including 0/1, primes, composites, perfect squares and the maximum ticket. Sanitized execution also passed. Exhaustive verification time is deliberately excluded from the displayed query/build timing; verification is a development cost, not a required step for each deployed batch.

| Measurement | Original square-root trial | Redesigned sieve |
| --- | --- | --- |
| Queries | 1000 | 1000 |
| Prime answers | 750 | 750 |
| Query remainder tests | 273750 | 0 |
| Query guard divisions | 274500 | 0 |
| Direct flag lookups | 0 | 1000 |
| Flag storage | 0 | 1000004 bytes |
| Initialization writes | 0 | 1000004 flags, plus clearing 0 and 1 |
| Sieve marking writes | 0 | 2122051 |
| Base-candidate flag tests | 0 | 999 |

The sieve's safe outer loop also evaluates its n/p bound 1000 times, including its final failed guard. Marking writes include repeated writes to an already-composite flag and are counted honestly. These operations have different costs; zero query remainders does not mean zero total work.

### F. Defend the result (2 marks)
The query-remainder reduction is 100%, exceeding the 99% objective. All 1000004 validation inputs agree, and the answer count stays 750. The memory/setup cost is the main new trade-off. Three executions produced:

| Run | Trial CPU ms | Sieve build CPU ms | Lookup CPU ms |
| --- | --- | --- | --- |
| 1 | 2.148 | 1.971 | 0.002 |
| 2 | 0.249 | 0.709 | 0.001 |
| 3 | 0.247 | 0.617 | 0.000 |

The median trial time is 0.249 ms, median build time 0.709 ms and median lookup time 0.001 ms. These short CPU-clock samples vary with warm-up, optimization and scheduling; a displayed 0.000 is below reported resolution, not zero elapsed time. On the median measurements, setup plus one batch is slower than trial division. Reusing an already-built table makes later queries cheap, and the measured operation-count objective is still achieved. More sustained workloads would be needed for a robust runtime crossover claim.

Retain trial division for occasional or unbounded queries. Use a reusable sieve for dense or repeated queries within a manageable known maximum, where its table can be amortized across many batches. This is a change in information reuse and algorithmic work, rather than a cosmetic replacement of a loop statement.
