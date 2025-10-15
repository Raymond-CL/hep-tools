#include <stdlib.h>

#include <iomanip>
#include <iostream>
#include <string>

#include "EPPS21.h"
#include "ct11pdf.h"

int main() {
  string pdffile = "i2TAn2.00.pds";
  cteqpdf ct18anlo;
  ct18anlo.setct11(pdffile);

  double xmin = 1E-4, xmax = 1.0;
  int xn = 40;
  double dx = log(xmax / xmin) / xn;
  std::cout << std::scientific << std::setprecision(6);
  double Q = 1000.0;
  for (int i = 0; i < xn; ++i) {
    double binL = xmin * exp(i * dx);
    double binH = xmin * exp((i + 1) * dx);
    double x = (binL + binH) / 2.0;

    std::cout << x << '\t' 
      << x * ct18anlo.parton(0, x, Q) << '\t' 
      << x * ct18anlo.parton(1, x, Q) << '\t' 
      << x * ct18anlo.parton(2, x, Q) << '\t' 
      << x * ct18anlo.parton(-1, x, Q) << '\t' 
      << x * ct18anlo.parton(-2, x, Q) << '\t' << std::endl;
  }

  // double ruv, rdv, ru, rd, rs, rc, rb, rg;

  // EPPS21(0, 1, 208, x, Q, ruv, rdv, ru, rd, rs, rc, rb, rg);

  // std::cout << ruv << '\t' << rdv;

  ct18anlo.pdfexit();

  return 0;
}