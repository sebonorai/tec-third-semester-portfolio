# Third Semester Portfolio — Computer Technology Engineering (ITC)

Coursework and projects from my third semester at Tecnologico de Monterrey, Campus Monterrey (August 2026 – in progress).

This repository collects the work where I actually wrote code. Each folder has its own README explaining the problem, the approach, and how to run it. It grows as the semester goes on.

---

## Contents

| Folder | Course | What's in it |
| --- | --- | --- |
| [`data-structures/`](data-structures) | TC1031 — Data Structures and Fundamental Algorithms | Complexity analysis, sorting and searching with comparison counts, a log analyzer (merge sort + binary search), a templated singly linked list, a log range search over a merge-sorted list, and a binary search tree in C++. |
| [`iot/`](iot) | TC1004B — Internet of Things (Group 503, Team 3) | A NodeMCU (ESP8266) node that shares sensor readings over MQTT, and a Node.js + MySQL REST API for sensor data. |

---

## Where to look first

- **Linked list** — [`data-structures/linked-list/`](data-structures/linked-list): generic singly linked list with `reverse()`, a circular `shift(n)`, `operator==`, and deep-copy semantics (copy constructor, `operator=`, `operator+=`).
- **Binary search tree** — [`data-structures/binary-search-tree/`](data-structures/binary-search-tree): the four traversals, `ancestors`, `maxWidth`, `nearestRelative`, `remove`, deep copy and structural `operator==`.
- **Log analyzer** — [`data-structures/act-1.3-log-analysis/`](data-structures/act-1.3-log-analysis): parses a server log, sorts it by date with merge sort, and answers date-range queries with binary search.
- **Sorting and searching, measured** — [`data-structures/act-1.2-search-sort/`](data-structures/act-1.2-search-sort): every algorithm counts its comparisons, so the O(n²) vs O(n log n) gap shows up in the output.

---

## Notes

- No credentials are committed. The IoT projects read Wi-Fi and database credentials from local, git-ignored files (see [`iot/README.md`](iot)).
- Acts 1.3 and 2.3 were pair projects and the IoT work was a team project; each README says so.

---

## About

Sebastian Noriega Olavarrieta — B.S. Computer Technology Engineering, Tecnologico de Monterrey.
Currently building [Casora](https://casoramx.com), an online furniture marketplace.
