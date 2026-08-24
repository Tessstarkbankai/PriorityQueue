# Persistent Priority Queue (C++)

## Implementation Note

This is a **binary min-heap** backed by a plain text file (`pq_data.txt`) for persistence.

**Data structure:** Array-based binary min-heap. Each element stores a `{val, pri}` pair. The heap property ensures the minimum-priority element is always at index 0, giving O(1) peek and O(log n) insert/extract_min. `extract_max` does a linear scan since a min-heap doesn't track the maximum — an acceptable trade-off for simplicity.

**Persistence:** The heap is serialized as `priority value` per line in a text file. Every public method reloads from disk before operating and saves after any mutation, so the queue survives restarts.

**Note:** `delete` is a reserved keyword in C++, so the method is named `remove`.

**Complexity summary:**

| Operation   | Time       |
|-------------|------------|
| insert      | O(n) disk + O(log n) heap |
| extract_min | O(n) disk + O(log n) heap |
| extract_max | O(n) disk + O(n) scan     |
| peek        | O(n) disk + O(1) heap     |
| update      | O(n) disk + O(n) find + O(log n) fix |
| delete      | O(n) disk + O(n) find + O(log n) fix |
| is_empty    | O(n) disk + O(1)          |

## Real-World Use Cases

- **Task scheduling** — OS schedulers pick the next process using a priority queue.
- **Dijkstra's algorithm** — shortest-path computation relies on a min-priority queue.
- **Event-driven simulation** — events processed in timestamp order.
- **Job queues** — background workers process high-priority jobs first.
- **Hospital triage** — patients treated by severity, not arrival time.

## Build & Run

Requires a C++17 compiler (for `std::optional`).

```bash
g++ -std=c++17 -o test module.cpp test.cpp
./test
```

On Windows with MSVC:
```cmd
cl /std:c++17 /EHsc module.cpp test.cpp /Fe:test.exe
test.exe
```

State is persisted to `pq_data.txt` in the working directory.
