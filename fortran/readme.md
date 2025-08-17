# Setting up Fortran

This guide provides a **step-by-step procedure** for installing and using **Fortran** in a high-energy physics computing environment, focusing on the **GNU Fortran (`gfortran`)** compiler.

It also includes a **sample test program** and **Makefile** to verify your installation.

## Install a Fortran Compiler

Fortran remains a core language in scientific computing, including many HEP simulation codes.

The most common open-source compiler is **GNU Fortran (`gfortran`)**, part of the GNU Compiler Collection (GCC).

```bash
sudo apt update
sudo apt install gfortran
```

To check the compiler version, simply `gfortran --version`.

## Test Program

This repository includes a `main.f90` demonstrating arrays, modules, and numerical operations.

It uses the *law of large numbers* to estimate the expected value of a uniform random variable.

It also shows the fast and simple **array operations** as compared to C/C++.

The included `Makefile`` automates compilation.

Build with `make` and run with `./ex_fortran`.

## Extras

If you have a large and complicated Fortran program with complex dependencies, you can install a simple program called **makedepf90** that creates Makefile dependency list for you.

Install simply `sudo apt install makedepf90`.

The usage is given in this [website](https://linux.die.net/man/1/makedepf90).

## References

* [GNU Fortran official documentation](https://gcc.gnu.org/fortran/)
* [gfortran compiler options](https://gcc.gnu.org/onlinedocs/gfortran/Option-Summary.html)
* [gfortran intrinsic procedures](https://gcc.gnu.org/onlinedocs/gfortran/Intrinsic-Procedures.html)
* [Fortran Wiki](https://fortranwiki.org/)
* [Fortran Lang Community](https://fortran-lang.org/)
* [Oxford Fortran course online](https://web.chem.ox.ac.uk/fortran/)
* [Algorithm compiled by John Burkardt](https://people.math.sc.edu/Burkardt/f_src/f_src.html)