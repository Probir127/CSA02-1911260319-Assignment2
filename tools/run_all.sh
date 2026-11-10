#!/usr/bin/env bash
set -eu
cd "$(dirname "$0")/.."
mkdir -p build
CC=${CC:-gcc}
flags=(-std=c17 -Wall -Wextra -Wpedantic -O2)
compile() { local exe=$1; shift; "$CC" "${flags[@]}" "$@" -o "build/$exe"; }
run() { local out=$1; shift; "$@" > "$out" 2>&1; printf 'PASS %s\n' "$out"; }
"$CC" --version > compiler.txt
compile task1 Task01/billing.c
run Task01/output.txt build/task1
# This statement has undefined behaviour: compile for diagnostics, never execute.
"$CC" "${flags[@]}" -c Task01/undefined_example.c -o build/undefined_example.o 2> Task01/compiler_warning.txt
compile task2 Task02/short_circuit.c
run Task02/output.txt build/task2
compile task3_complete Task03/complete_code.c
run Task03/complete_code_output.txt build/task3_complete
compile task3 Task03/register_tests.c
run Task03/output.txt build/task3
compile task4_complete Task04/complete_code.c
run Task04/complete_code_output.txt build/task4_complete
compile task4_fallthrough Task04/fallthrough.c
run Task04/fallthrough_output.txt build/task4_fallthrough
compile task4 Task04/classifier.c
run Task04/output.txt build/task4
compile task5_complete Task05/complete_code.c
run Task05/complete_code_output.txt build/task5_complete
compile task5_full Task05/full_trial.c
run Task05/full_trial_output.txt build/task5_full
compile task5 Task05/loops.c Task05/prime.c
run Task05/output.txt build/task5
compile task6 Task06/main.c Task06/loan.c -lm
run Task06/output.txt build/task6
compile task7 Task07/redesign.c Task05/prime.c
run Task07/output.txt build/task7
for attempt in 2 3; do run "Task07/run_$attempt.txt" build/task7; done
for task in 3 4 5 6 7; do
    case "$task" in
        3) sources=(Task03/register_tests.c);;
        4) sources=(Task04/classifier.c);;
        5) sources=(Task05/loops.c Task05/prime.c);;
        6) sources=(Task06/main.c Task06/loan.c -lm);;
        7) sources=(Task07/redesign.c Task05/prime.c);;
    esac
    compile "sanitized_$task" -O1 -fsanitize=address,undefined -fno-omit-frame-pointer "${sources[@]}"
    run "Task0$task/sanitizer_output.txt" "build/sanitized_$task"
done
printf 'All C programs, assertions and sanitizer checks passed.\n'
