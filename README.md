# DocJen

DocJen is a C++17 project implementing **lock-free stack and queue data structures** optimized for **multi-core CPUs**. Unlike traditional thread-safe data structures that use mutexes, DocJen uses **atomic operations** for non-blocking concurrency, minimizing contention and maximizing throughput in multi-threaded environments.

## Features

* Lock-Free Stack (Treiber algorithm).
* Lock-Free Queue (Michael–Scott algorithm) with hazard pointers to avoid ABA issues.
* Demo (`main.cpp`) showcasing push/pop & enqueue/dequeue.
* Microbenchmark (`benchmark.cpp`) to measure throughput.
* Tests (`tests.cpp`) to validate correctness.

## Implementation Highlights

* Fully written in **C++17**, leveraging `std::atomic` for thread-safe operations.
* Stack uses the **Treiber algorithm** for lock-free LIFO behavior.
* Queue uses **Michael–Scott algorithm**, a standard lock-free FIFO algorithm.
* Hazard pointers used for safe memory reclamation.
* Compatible with Linux and Windows.

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build . -- -j
```

**Executables produced:**

* `docjen` → runs the demo (`main.cpp`)
* `docjen_bench` → runs benchmarks (`benchmark.cpp`)
* `docjen_tests` → runs unit tests (`tests.cpp`)

## Use Cases

* High-performance multithreaded systems.
* Low-latency applications where locks are a bottleneck.
* Real-time or embedded systems.
* In-memory databases and concurrent data structures research.

## License

MIT License
