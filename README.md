# CSA02 - C Programming - Assignment 2 (CO2)

**Student:** PROBIR SAHA SHOHOM  
**Register number:** 1911260319  
**Course:** CSA02 - C Programming  
**Repository:** https://github.com/Probir127/CSA02-1911260319-Assignment2

All assignment programs are C17 `.c` files with `.h` headers where needed. The optional runner is Bash.

## Compile and run

On this Mac `gcc` is Apple Clang 21.0.0 (arm64); see compiler.txt. From the repository root:

```sh
bash tools/run_all.sh
```

The script contains the exact compile/run commands and runs every program, repeat measurements and AddressSanitizer/UndefinedBehaviorSanitizer checks. It stops on failed assertions or commands and stores executables in ignored build/. Task output files are refreshed, so timings may differ from the report's recorded runs. Assertions must remain enabled; do not add -DNDEBUG.

Manual commands (run `mkdir -p build` first):

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task01/billing.c -o build/task1
./build/task1
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task02/short_circuit.c -o build/task2
./build/task2
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task03/complete_code.c -o build/task3_complete
./build/task3_complete
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task03/register_tests.c -o build/task3
./build/task3
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task04/complete_code.c -o build/task4_complete
./build/task4_complete
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task04/fallthrough.c -o build/task4_fallthrough
./build/task4_fallthrough
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task04/classifier.c -o build/task4
./build/task4
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task05/complete_code.c -o build/task5_complete
./build/task5_complete
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task05/full_trial.c -o build/task5_full
./build/task5_full
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task05/loops.c Task05/prime.c -o build/task5
./build/task5
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task06/main.c Task06/loan.c -lm -o build/task6
./build/task6
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 Task07/redesign.c Task05/prime.c -o build/task7
./build/task7
```

Q1 undefined_example.c is compiled with the same warning flags and `-c` to record its diagnostic; **never execute it**. Q4 fallthrough.c is an intentional logic-error experiment, with correct alternatives alongside it. The sanitizer commands in tools/run_all.sh add `-O1 -fsanitize=address,undefined -fno-omit-frame-pointer` and require a compiler that supports those sanitizers.

## Results

| Question | Recorded result |
| --- | --- |
| Q1 | Three predictions verified; corrected payable amounts Rs892.50, Rs998.95 and Rs532.82 |
| Q2 | Same 233 concessions; 834 card calls versus 1000 |
| Q3 | Expected 00000101/00000110; all 256 register counts verified |
| Q4 | Grade implementations agree on 105 inputs; income boundaries checked |
| Q5 | Improved remainder counts 8, 1, 87, 999; four loop variants agree through 10000 |
| Q6 | Six-month loan; interest Rs 645.38; non-amortizing and 360-month safeguards verified |
| Q7 | 273750 query remainders reduced to 0 after sieve setup; all 1000004 domain values agree |

Each Task folder contains source, inputs.txt documenting embedded fixtures, explanation, captured raw output and a labelled output preview. SOLUTIONS.md and the PDF contain the full report. PREDICTIONS.md was committed before execution. Q5's `checks` follows the supplied remainder-test convention; guard divisions are reported separately. Q7 includes initialization/marking costs and explicitly compares setup-inclusive performance. Q1 tax/rebate order and Q4 scholarship thresholds are stated assumptions where the brief is incomplete.

The output previews render actual saved transcripts. Capture personal terminal screenshots when running the commands, then share/submit the repository link to your faculty.
