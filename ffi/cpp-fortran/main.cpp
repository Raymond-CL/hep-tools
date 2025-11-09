#include <iostream>
#include <cmath>

extern "C" double f_bessel_j0(double x);

int main() {
  double x = 1.5;
  double result = f_bessel_j0(x);
  std::cout << "bessel_j0 of " << x << " is: " << result << std::endl;
  return 0;
}