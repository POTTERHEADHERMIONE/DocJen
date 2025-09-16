# DocJen

DocJen is a project implementing simple **lock-free data structures** 
(Stack and Queue) in C++17 for **multi-core CPUs**.

## Features
- Lock-Free Stack (Treiber algorithm).
- Lock-Free Queue (Michael-Scott algorithm).
- Demo (`main.cpp`) showcasing push/pop & enqueue/dequeue.
- Microbenchmark (`benchmark.cpp`) to measure throughput.
- Tests (`tests.cpp`) to validate correctness.

⚠️ **Note**: These implementations are for educational/demo purposes. 
No memory reclamation (hazard pointers, epochs) is implemented. 
Running long workloads may cause memory leaks.

---

## Build
```bash
mkdir build && cd build
cmake ..
cmake --build . -- -j
