# Data Structures and Fundamental Algorithms (TC1031)

C++ implementations from the course. Everything builds with `g++ -std=c++17`. Source comments are in Spanish, as submitted.

| Folder | What it does |
| --- | --- |
| [`act-1.1-complexity/`](act-1.1-complexity) | Sum of 1..n computed three ways: iterative (O(n)), recursive (O(n)) and closed formula (O(1)). |
| [`act-1.2-search-sort/`](act-1.2-search-sort) | Exchange, bubble and merge sort, plus sequential and binary search. Each one counts its comparisons. |
| [`act-1.3-log-analysis/`](act-1.3-log-analysis) | Reads a server log, merge-sorts it by date, and binary-searches the start of a date range. *(Pair project.)* |
| [`linked-list/`](linked-list) | Header-only `Node<T>` and `LinkedList<T>` with the usual operations plus `reverse`, `shift`, `operator==`, copy constructor, `operator=` and `operator+=`. |
| [`act-2.3-log-ip-range/`](act-2.3-log-ip-range) | Reads a server log into a singly linked list, merge-sorts it by IP directly on the nodes, and prints every record in an IP range. *(Pair project.)* |
| [`binary-search-tree/`](binary-search-tree) | A binary search tree of ints: insert, search, remove, the four traversals, height, ancestors, node level, maximum width, nearest common ancestor, deep copy and structural equality. |
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

Header-only. `LinkedList.h` includes `Node.h`. This is the version after Act 2.1 and 2.2, so it also has the copy constructor, assignment and concatenation.

```cpp
#include "LinkedList.h"

LinkedList<int> list;
for (int i = 1; i <= 5; i++) list.addLast(i);   // 1 2 3 4 5
list.reverse();                                   // 5 4 3 2 1
list.reverse();
list.shift(2);                                    // 4 5 1 2 3

LinkedList<int> copy(list);                       // deep copy
copy += list;                                     // 4 5 1 2 3 4 5 1 2 3
```

Operations: `addFirst`, `addLast`, `add(data, pos)`, `deleteFirst`, `deleteLast`, `del(pos)`, `deleteAll`, `get`, `set`, `change(pos1, pos2)`, `getSize`, `isEmpty`, `print`, `reverse`, `shift(n)`, `operator==`, the copy constructor, `operator=` (deep copy, safe for `a = a`) and `operator+=` (appends a copy of the other list; `a += a` doubles it).

`demo_linked_list.cpp` runs every operation and has the expected output in its comments.

```bash
g++ -std=c++17 -o demo_linked_list demo_linked_list.cpp
./demo_linked_list
```

## act-2.3-log-ip-range

Reads `bitacora.txt` (same format as Act 1.3), stores every line in a singly linked list that keeps a `tail` pointer (O(1) append), sorts it by IP and port with a merge sort that relinks the existing nodes, and then asks for a start IP and an end IP. It prints every record of each of the two IPs and then all the records in between. *(Pair project.)*

IPs are compared numerically, octet by octet (`Registro::ipANumero`), not as text, so `9.x` sorts before `10.x`. Octets are packed in base 1000 because the sample IPs are synthetic and some octets are above 255.

| Step | Complexity |
| --- | --- |
| Read the log (`addLast` with `tail`) | O(n) |
| Merge sort on the nodes | O(n log n) time, O(log n) extra space |
| Range query (`printRange`) | O(k + m): skip k nodes, print m |

```bash
g++ -std=c++17 -o act23 main.cpp
printf '25.79.393.38\n26.52.207.87\nn\n' | ./act23
```

The last block of the output:

```
--- Registros en el rango 25.79.393.38 a 26.52.207.87 ---
Jun 20 06:23:54 25.79.393.38:6876 Failed password for admin
Jul 1 21:00:02 26.52.207.87:6158 Illegal user
Total: 2 registro(s)
```

The write-up for this activity asked whether a doubly linked list would fit better. The conclusion was no: queries only walk forward and never delete a node from the middle, so a `prev` pointer would cost 8 extra bytes per node and extra bookkeeping in the merge sort for no gain. It would pay off for descending traversal, or for O(1) deletion when you already hold the node.

## binary-search-tree

A binary search tree of `int`s: `BST.h`, with `NodeT.h` as the node. Duplicates are ignored. Every method documents its precondition, postcondition and complexity in a comment (n = nodes, h = height).

| Added in | Methods |
| --- | --- |
| Act 3.1 | `add`, `search`, `isEmpty`, `getSize`, `height`, `print(Traversal)` (preorder, inorder, postorder or level by level), `ancestors`, `whatLevelAmI` |
| Act 3.2 | `maxWidth`, `nearestRelative(a, b)`, copy constructor, `operator==` (same data and same shape), `remove` (leaf, one child, or two children via the in-order successor) |

With the 13 values inserted in `demo_bst_traversals.cpp` (8 15 21 40 7 18 9 5 2 1 4 11 6), the program prints:

```
Recorrido en preorden: 8 7 5 2 1 4 6 15 9 11 21 18 40
Recorrido en entreorden: 1 2 4 5 6 7 8 9 11 15 18 21 40
Recorrido nivel x nivel: 8 7 15 5 9 21 2 6 11 18 40 1 4
Ancestros de 4: 2 5 7 8
```

```bash
g++ -std=c++17 -o demo_bst_traversals demo_bst_traversals.cpp && ./demo_bst_traversals
g++ -std=c++17 -o demo_bst_operations demo_bst_operations.cpp && ./demo_bst_operations
```

Notes:
- `whatLevelAmI` numbers levels from 0 (the root), while `height()` counts levels (0 for an empty tree, 1 for a single node).
- There is no `operator=` for `BST` (the activity only asks for the copy constructor). Copy with `BST b(a);`; writing `b = a;` would share nodes and free them twice.

## array-list-and-search

- `Lista.h` — array-backed list with capacity 100 (`insert`, `erase`, `getData`, `getSize`, `print`).
- `search_comparison.cpp` — fills a `Lista` with `N` random values (keep `N` ≤ 100), then repeatedly asks for a value and reports how many comparisons sequential search and binary search needed. Enter a negative number to stop.
- `array_list_demo.cpp` — standalone version of the same class with a small `main`.

```bash
g++ -std=c++17 -o search search_comparison.cpp
./search
```
