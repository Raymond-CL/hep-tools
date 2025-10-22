#ifdef _OPENMP
#include <omp.h>
#endif
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_sf_bessel.h>
#include <stdlib.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <string>

#include "ct11pdf.h"

// shared parameters structure
struct parameters {
  double CME;
  double ymin, ymax;
  double ptmin, ptmax;
  cteqpdf ct18anlo;
};

// integrand function
double integrand(double* dx, size_t ndim, void* params) {
  (void)(ndim);  // unused
  auto* p = static_cast<parameters*>(params);
  // unpack variables
  double xa = dx[0];
  // double yc = dx[1];
  // double pt = dx[2];
  // // momentum fractions
  // double xt = 2.0 * pt / p->CME;
  // double xamin = (xt * std::exp(+yc)) / (2.0 - xt * std::exp(-yc));
  // if (xa < xamin || xa > 1.0) return 0.0;
  // double xb = (xa * xt * std::exp(-yc)) / (2.0 * xa - xt * std::exp(+yc));
  // if (xb < 0.0 || xb > 1.0) return 0.0;
  // // Mandelstam variables
  // double mans = +xa * xb * p->CME * p->CME;
  // double mant = -xa * pt * p->CME * std::exp(-yc);
  // double manu = -xb * pt * p->CME * std::exp(+yc);
  // // scales
  // double muren = pt;
  // double mufac = muren;
  // // coupling constant
  // double alphaS = 0.2;  // fixed coupling for testing

  // const int nf = 6;
  // double pdfa[nf] = {0.0}, pdfb[nf] = {0.0};
  // for (int i = 0; i < nf; i++) {
  //   pdfa[i] = p->ct18anlo.parton(0, xa, mufac);
  //   pdfb[i] = p->ct18anlo.parton(0, xb, mufac);
  // }

  // std::cout << "xa: " << xa << std::endl;

  double sum = 0.0;
  for (int i = 0; i < 11; i++) {
    sum += xa * p->ct18anlo.parton(i - 5, xa, 10000.0);
  }
  return sum;

  // matrix element
  // particle kinematics: a+b -> c+d
  // a (xa) --------- c (pt,yc)
  //            |
  // b (xb) --------- d (pt,yd)

  // -----     \   /    --  /
  //   |        ---       |X
  // -----     /   \    --  \ 

  // double temp = (4.0 * M_PI * alphaS * alphaS) / (mans * mans);
  // double temp2 = 2.0 * xa * xb / (M_PI * (2.0 * xa - xt * std::exp(+yc)));
  // return temp * temp2;
}

// main program
int main(int argc, char* argv[]) {
  (void)(argc);  // unused
  (void)(argv);  // unused

  // start program timer
  auto start = std::chrono::high_resolution_clock::now();

  // display initial message
  std::cout << "--------------------------------------------" << std::endl
            << "    Single Inclusive Jet Production @ LO    " << std::endl
            << "--------------------------------------------" << std::endl;

  // setup Monte-Carlo integration environment
  gsl_rng_env_setup();

  // set parameters
  parameters p;
  p.CME = 5020.0;
  p.ptmin = 40.0;
  p.ptmax = 1000.0;
  p.ymin = -2.8;
  p.ymax = +2.8;

  // integration settings
  size_t ncall1 = 100000;
  size_t itm1 = 10;
  size_t ncall2 = 1000000;
  size_t itm2 = 1;

  // define integration limits
  const size_t ndim = 1;  // 3;
  double dx_lower[ndim];
  double dx_upper[ndim];

  // define histogram bins
  const size_t nbin = 1;  // 16;
  double hmin = p.ptmin;
  double hmax = p.ptmax;
  double bin = (hmax - hmin) / static_cast<double>(nbin);
  double bin_mid[nbin], results[nbin], errors[nbin];

  // initialize PDF
  string pdffile = "i2TAn2.00.pds";
  p.ct18anlo.setct11(pdffile);

// define OpenMP parallel region
#ifdef _OPENMP
#pragma omp parallel for
#endif
  // perform integration loop
  for (size_t i = 0; i < nbin; ++i) {
// print current bin info
#ifdef _OPENMP
#pragma omp critical
    // {
    std::cout << "Working on bin: " << i
              << "\t under thread: " << omp_get_thread_num() << std::endl;
// }
#else
    std::cout << "Working on bin: " << i << std::endl;
#endif

    // define bin parameters
    double binL = hmin + static_cast<double>(i) * bin;
    double binR = hmin + static_cast<double>(i + 1) * bin;
    bin_mid[i] = (binL + binR) * 0.5;
    double res, err;

    // lower limits
    dx_lower[0] = 0.0;
    // dx_lower[1] = p.ymin;
    // dx_lower[2] = binL;
    // upper limits
    dx_upper[0] = 1.0;
    // dx_upper[1] = p.ymax;
    // dx_upper[2] = binR;

    // local kinematics object (copied values from global p)
    parameters p_local = p;

    // local GSL monte rng and state
    gsl_rng* r = gsl_rng_alloc(gsl_rng_default);
    gsl_monte_vegas_state* s = gsl_monte_vegas_alloc(ndim);
    gsl_monte_function gmf = {&integrand, ndim, &p_local};
    gsl_monte_vegas_params vp;

    // warmup run
    gsl_monte_vegas_params_get(s, &vp);
    vp.stage = 0;
    vp.iterations = itm1;
    gsl_monte_vegas_params_set(s, &vp);
    gsl_monte_vegas_integrate(&gmf, dx_lower, dx_upper, ndim, ncall1, r, s,
                              &res, &err);

    // final run
    gsl_monte_vegas_params_get(s, &vp);
    vp.stage = 2;
    vp.iterations = itm2;
    gsl_monte_vegas_params_set(s, &vp);
    gsl_monte_vegas_integrate(&gmf, dx_lower, dx_upper, ndim, ncall2, r, s,
                              &res, &err);

    // free resources
    gsl_monte_vegas_free(s);
    gsl_rng_free(r);

    // store result and error in array
    results[i] = res; // / bin;  // normalize by bin width
    errors[i] = err;
  }

  // print header
  std::cout << "--------------------------------------------" << std::endl
            << std::scientific << std::setprecision(6)
            << "#   x    \t    y    \t   error  " << std::endl;

  // define print function
  auto print = [nbin](std::ostream& out, const double* x, const double* y,
                      const double* e) {
    for (size_t i = 0; i < nbin; ++i)
      out << x[i] << '\t' << y[i] << '\t' << e[i] << std::endl;
  };

  // print to console
  print(std::cout, bin_mid, results, errors);

  // print to file
  std::ofstream fout("results.txt", std::ios::out);
  print(fout, bin_mid, results, errors);
  fout.close();

  // display elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "--------------------------------------------" << std::endl
            << " Elapsed time: " << std::defaultfloat << elapsed.count()
            << " seconds\n"
            << "--------------------------------------------" << std::endl;

  return 0;
}