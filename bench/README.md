# compiler_bench

Simple program to benchmark different compiler performance. \
Current algorithm is the Pi(n) function. \
which is finding the number of prime numbers less than n. \
For following compilers are tested:

| Language | Compiler           | Flags            | time in secs (`N=5000000`) | timer          |
| -------- | ------------------ | ---------------- | -------------------------- | -------------- |
| Fortran  | `gfortran`         | `-O3`            | 0.923                      | `system_clock` |
| C++      | `g++`              | `-O3`            | 0.929                      | `chrono`       |
| Haskell  | `ghc`              | `-O2`            | 3.860                      | `Data.Time`    |
| Rust     | `rustc`            | `-C opt-level=3` | 0.940                      | `Instant`      |
| Python   | `cython3` + `gcc`  | `-O2`            | 17.73                      | `time`         |
| Julia    | | | | |

unit: Microsoft Surface Pro 9 \
system: Ubuntu 24.04 x86-64, Linux 5.15-microsoft-standard-WSL2, Windows 11 \
hardware: Intel i7-1255U, 2600Mhz, 2P+8E Cores, 8GB RAM

Note: The `.py` python script file is first converted to `.c` using `cython3`, then compiled as a standalone executable using `gcc` compiler. \
Haskell time resolution might be wrong for WSL2, see [this](https://github.com/microsoft/WSL/issues/6029) article.

> I tried to compile all the codes, then run them simultaneously by opening a new shell for each executable. \
> Not very elegant, you might have to uncomment this option in `Makefile`.
