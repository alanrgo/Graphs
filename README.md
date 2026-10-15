# Graphs Assignments (P3, P4, P5)

This repository contains three graph-algorithm programming assignments implemented in C++:

- `p3.cpp`
- `p4.cpp`
- `p5.cpp`

## Assignment Overview

| Assignment | File | Problem formulation | Algorithm |
|---|---|---|---|
| P3 | `p3.cpp` | Water-supply network with a virtual reservoir vertex (vertex `0`) | Prim's Minimum Spanning Tree (MST) |
| P4 | `p4.cpp` | Weighted interval scheduling as a compatibility DAG shortest-path problem with negated weights | Shortest path in DAG (via `minpathcpp.h`) |
| P5 | `p5.cpp` | Perfect matching in a bipartite graph (rows vs. columns) | Edmonds–Karp maximum flow |

---

## P3 — Water Supply with Virtual Reservoir + Prim MST (`p3.cpp`)

### Idea
Each district can:
- connect to a virtual reservoir vertex `0` with cost equal to building its own reservoir, or
- connect to another district by paying pipe cost.

The code builds this graph and runs Prim's MST algorithm so every district gets water at minimum total cost.

### Expected input
1. `n m`  
   - `n`: number of districts  
   - `m`: number of possible pipes
2. `n` lines with one integer each: reservoir cost for district `1..n`
3. `m` lines: `i j c` meaning a pipe between districts `i` and `j` with cost `c`

### Output
- One integer: minimum total cost to supply all districts with water.

### Complexity
- Prim with priority queue: `O((V + E) log V)`
- Here `V = n + 1` (virtual vertex included), and `E = m + n` (pipes + reservoir edges), so:
  - `O((m + n) log n)` up to constant factors.

### Build and run
```bash
g++ -std=c++11 p3.cpp -o p3
./p3 < input.txt
```

---

## P4 — Weighted Interval Scheduling via Compatibility DAG (`p4.cpp`)

### Idea
Intervals are converted into a DAG:
- one vertex per interval,
- edges connect compatible intervals,
- interval values are negated on edges so maximizing total value becomes a shortest-path problem.

The implementation also creates virtual source/sink vertices and computes shortest path, then prints:
1. maximum value
2. selected interval indices (in path order printed by the code)

### Expected input
1. `n` (number of intervals)
2. `n` lines: `start end value`

### Output
- First line: maximum total value of a compatible interval subset
- Second line: interval indices chosen by the recovered path

### Dependency and build note
`p4.cpp` includes:

```cpp
#include "minpathcpp.h"
```

So `minpathcpp.h` (and any required implementation for `Grafo`) must be available to the compiler.

### Complexity
- Building compatibility edges uses nested checks over intervals: `O(n^2)`
- Shortest path in the resulting DAG is `O(V + E)` and `E` can be `O(n^2)`
- Overall: `O(n^2)` time, `O(n^2)` space in the worst case.

### Build and run
```bash
g++ -std=c++11 p4.cpp -o p4
./p4 < input.txt
```

If `minpathcpp.h` is not in the same directory, compile with an include path (example):

```bash
g++ -std=c++11 -I/path/to/header p4.cpp -o p4
```

---

## P5 — Bipartite Matching via Edmonds–Karp Max Flow (`p5.cpp`)

### Idea
The input matrix defines a bipartite graph:
- left side: row vertices `1..n`
- right side: column vertices `n+1..2n`
- edge `(row i, column j)` exists when matrix entry `a(i,j) = 1`

Then the code adds:
- source `0` to all left vertices (capacity `1`)
- all right vertices to sink `2n+1` (capacity `1`)

Running Edmonds–Karp gives maximum matching size.  
If flow equals `n`, the code prints `SIM`; otherwise `NAO`.

### Expected input
1. `n`
2. `n x n` matrix of `0/1` integers

### Output
- `SIM` if a perfect matching exists
- `NAO` otherwise

### Complexity
- Edmonds–Karp: `O(VE^2)`
- Here `V = 2n + 2`, `E = O(n^2)`, so worst-case polynomial complexity follows from max-flow bounds.

### Build and run
```bash
g++ -std=c++11 p5.cpp -o p5
./p5 < input.txt
```
