#include <gsl/gsl_sf_bessel.h>

extern "C" {
double bessel_j0_cpp(double x) {
  double result = gsl_sf_bessel_J0(x);
  return result;
}
}