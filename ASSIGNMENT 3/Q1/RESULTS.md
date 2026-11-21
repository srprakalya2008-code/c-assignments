# Q1 – Searching a Library Catalogue (binary search)

## Implemented logic (TODO 1 in `q1_binary_search.c`)
Standard iterative binary search on the sorted array `a[0..n-1]`:
`low = 0, high = n-1`; `mid = low + (high - low) / 2` (overflow-safe);
`steps++` counts every `a[mid]`-vs-`key` comparison; narrow the range until
found or `low > high`, then return -1.

## Actual vs expected output (`output_q1_main.txt`, `screenshot_q1.png`)
Matches the expected output exactly:

| Book | index | comparisons |
|------|-------|-------------|
| 1021 | 0     | 3 |
| 1305 | 5     | 3 |
| 1533 | 9     | 4 |
| 1400 (missing) | -1 | 4 |

The missing book needs 4 comparisons — as many as the worst successful
search — because 1400 falls in the deepest leaf path of the decision tree
(low=6,high=6 examines `a[6]` last before the range empties).

## Experiments (`q1_experiments.c`, `results_q1_experiments.csv`, `graph_q1.png`)
Linear vs binary comparisons for n = 1000 / 10000 / 100000:

| n | linear first/mid/last/missing | binary first/mid/last/missing |
|---|-------------------------------|-------------------------------|
| 1000 | 1 / 501 / 1000 / 1000 | 9 / 9 / 10 / 10 |
| 10000 | 1 / 5001 / 10000 / 10000 | 13 / 13 / 14 / 14 |
| 100000 | 1 / 50001 / 100000 / 100000 | 16 / 16 / 17 / 17 |

Agrees with theory: linear O(n) worst/average, O(1) best; binary O(log n)
(≈17 for n = 100000). `mid = low + (high-low)/2` avoids the signed-overflow
of `(low+high)/2` on large arrays.

## Alternative concept
Hash table (mod + linear probing): O(1) average search, O(n) extra space,
but degrades with clustering and needs resizing as books are added daily.
Interpolation search: O(log log n) average on uniform keys, O(n) worst.
Binary search stays the balanced choice for a mostly-static sorted catalogue.
