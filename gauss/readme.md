# gauss - Gauss-Legendre integration

A simple C++ class for Gauss-Legendre 1-dimensional integration (quadrature) with pre-computed abscissas and weights.
The class offers n=4, 8, 16, 32, 64 points, which is usally enough for most functions.
It is better to perform on functions with m < n/2 oscillations within the integration range.

## Example

An example program is written for the usage of the "GaussLeg" class.

The analytic integration result is also included for reference.

Compile and run with:
```shell
g++ -o gauss.exe example.cpp
./gauss.exe
```

## References

* [Gaussian Quadrature Weights and Abscissae](https://pomax.github.io/bezierinfo/legendre-gauss.html)