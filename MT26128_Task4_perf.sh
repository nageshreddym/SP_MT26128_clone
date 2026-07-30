#!/bin/bash

THREADS=(1 2 4 8)

for t in "${THREADS[@]}"
do
    echo "Running with $t thread(s)..."

    perf stat -x, \
    -e task-clock,context-switches,cpu-cycles \
    ./matrix $t 2> thread${t}.csv

done

echo "Done."
