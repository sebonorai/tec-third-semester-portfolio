# Data Structures and Fundamental Algorithms (TC1031)

C++ implementations from the course. Everything builds with `g++ -std=c++17`. Source comments are in Spanish, as submitted.

| Folder | What it does |
| --- | --- |
| [`act-1.1-complexity/`](act-1.1-complexity) | Sum of 1..n computed three ways: iterative (O(n)), recursive (O(n)) and closed formula (O(1)). |
| [`act-1.2-search-sort/`](act-1.2-search-sort) | Exchange, bubble and merge sort, plus sequential and binary search. Each one counts its comparisons. |
| [`act-1.3-log-analysis/`](act-1.3-log-analysis) | Reads a server log, merge-sorts it by date, and binary-searches the start of a date range. *(Pair project.)* |
| [`linked-list/`](linked-list) | Header-only `Node<T>` and `LinkedList<T>` with the usual operations plus `reverse`, `shift` and `operator==`. |
| [`array-list-and-search/`](array-list-and-search) | A fixed-capacity array list, and a program that compares sequential vs binary search by number of comparisons. |

---

## act-1.1-complexity

Input: the number of test cases `s`, then one `n` per line. Output: the three results per case (they must match).

```bash
g++ -std=c++17 -o act1_1 act1_1_sum_complexity.cpp
printf '3\n1\n5\n100\n' | ./act1_1
# 1 1 1
# 15 15 15
# 5050 5050 5050
```

## act-1.2-search-sort

Input: `n`, then `n` integers, then `b`, then `b` values to search for.
Output: first line is the comparison count of exchange sort, bubble sort and merge sort. Then one line per search: `seqPos seqComps binPos binComps` (`-1` means not found). Sequential search runs on the original array, binary search on the sorted one, so the positions differ.

```bash
g++ -std=c++17 -o act1_2 act1_2_search_sort.cpp
printf '6\n5 2 9 1 5 6\n3\n5 1 7\n' | ./act1_2
# 15 15 11        <- exchange, bubble, merge
# 0 1 2 1         <- search 5
# 3 4 0 2         <- search 1
# -1 6 -1 3       <- search 7 (not found)
```
(The program also prints input prompts; they are omitted above.)

## act-1.3-log-analysis

Reads `bitacora.txt` from the working directory. Each line looks like `Sep 4 05:56:38 <ip>:<port> Failed password for admin`. The program sorts all entries by date (merge sort, O(n log n)), asks for a start and end month/day, finds the first entry in range with binary search, then prints entries until the end date and the total.

A 200-line sample is included. The IP addresses in it are synthetic (some octets are above 255), so don't read anything into them.

```bash
g++ -std=c++17 -o act1_3 act1_3_log_analysis.cpp
printf 'Sep\n1\nSep\n30\n' | ./act1_3
```

## linked-list

Header-only. `LinkedList.h` includes `Node.h`.

```cpp
#include "LinkedList.h"

LinkedList<int> list;
for (int i = 1; i <= 5; i++) list.addLast(i);   // 1 2 3 4 5
list.reverse();                                   // 5 4 3 2 1
list.reverse();
list.shift(2);                                    // 4 5 1 2 3
```

Operations: `addFirst`, `addLast`, `add(data, pos)`, `deleteFirst`, `deleteLast`, `del(pos)`, `deleteAll`, `get`, `set`, `change(pos1, pos2)`, `getSize`, `isEmpty`, `print`, `reverse`, `shift(n)` and `operator==`.

## array-list-and-search

- `Lista.h` — array-backed list with capacity 100 (`insert`, `erase`, `getData`, `getSize`, `print`).
- `search_comparison.cpp` — fills a `Lista` with `N` random values (keep `N` ≤ 100), then repeatedly asks for a value and reports how many comparisons sequential search and binary search needed. Enter a negative number to stop.
- `array_list_demo.cpp` — standalone version of the same class with a small `main`.

```bash
g++ -std=c++17 -o search search_comparison.cpp
./search
```
