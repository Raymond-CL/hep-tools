#include <stdlib.h>

#include <cmath>
#include <iostream>

#include "gaussleg.h"

int main() {
  // Example integrand (highly oscillatory functions)
  // auto f = [](double x) { return j0(x) * j1(x); };
  auto f = [](double x) { return std::sin(x) * std::cos(x); };

  // Integration limits
  double xmin = 0.0;
  double xmax = 50.0;

  // Exact integral results
  // double exact = 0.5 * (j0(xmin) * j0(xmin) - j0(xmax) * j0(xmax));
  double exact = 0.25 * (std::cos(2. * xmin) - std::cos(2. * xmax));

  // Perform integrations
  double result4 = GaussLeg::integrate4(xmin, xmax, f);
  double result8 = GaussLeg::integrate8(xmin, xmax, f);
  double result16 = GaussLeg::integrate16(xmin, xmax, f);
  double result32 = GaussLeg::integrate32(xmin, xmax, f);
  double result64 = GaussLeg::integrate64(xmin, xmax, f);

  // Output results
  std::cout << "4-point integration result: " << result4 << std::endl;
  std::cout << "8-point integration result: " << result8 << std::endl;
  std::cout << "16-point integration result: " << result16 << std::endl;
  std::cout << "32-point integration result: " << result32 << std::endl;
  std::cout << "64-point integration result: " << result64 << std::endl;
  std::cout << "exact integral = " << exact << std::endl;
  return 0;
}