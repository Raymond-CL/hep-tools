# VEGAS – Multidimensional Monte Carlo Integration

This directory provides example programs demonstrating the use of the **VEGAS algorithm**, a widely used Monte Carlo technique for **multidimensional numerical integration** in high-energy physics (HEP).  

VEGAS is particularly well-suited for problems where the integrand has localized peaks or singular behavior, as it adaptively refines sampling weights to improve convergence.

## Example 1 – GSL

The program `gsl_vegas.cpp` uses the **GSL VEGAS integrator** to estimate the volume of an $n$-dimensional sphere of radius $R$.

* The integrand is defined as an indicator function inside the sphere.
* VEGAS adaptively samples points in the hypercube $[-R, R]^n$.
* The result is compared against the **analytic formula** for the sphere’s volume.

### Compile and Run

```bash
g++ gsl_vegas.cpp -o gsl_vegas -lgsl -lgslcblas -lm
./gsl_vegas 3 1.0
```

If no arguments are provided, the program defaults to an *n*=15 and *R*=2.0.

## Example 2 – Cuba C++

Another example will use the **CUBA library** (C/C++ interface) to perform the same multidimensional integration with VEGAS, showcasing interoperability and performance.

## Example 3 – Cuba Fotran

Another example will use the **CUBA library** (Fortran interface) to perform the same multidimensional integration with VEGAS, showcasing interoperability and performance.

## Example 4 – Legacy

The original code in Lepage's paper.

## Example 5 – Numerical Recipes C++

A future example will demonstrate the VEGAS algorithm implemented via **Numerical Recipes**, applied to a similar test integral.

## Example 6 – Numerical Recipes Fortran 77

A future example will demonstrate the VEGAS algorithm implemented via **Numerical Recipes in Fortran**, applied to a similar test integral.

## Example 7 – Numerical Recipes Fortran 95

A future example will demonstrate the VEGAS algorithm implemented via **Numerical Recipes in Fortran**, applied to a similar test integral.

## References

* [Lepage, G.P., *A New Algorithm for Adaptive Multidimensional Integration*, J. Comput. Phys. 27 (1978) 192–203](https://doi.org/10.1016/0021-9991%2878%2990004-9)
* [CUBA Library](https://feynarts.de/cuba/)
* [GNU Scientific Library Documentation – Monte Carlo Integration](https://www.gnu.org/software/gsl/doc/html/montecarlo.html)
* [Numerical Recipes](http://numerical.recipes/)
