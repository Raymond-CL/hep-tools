#ifdef _OPENMP
#include <omp.h>
#endif

#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_sf_bessel.h>
#include <stdlib.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// #include "physconst.h"

struct parameters {
  // parameters from input file
  double CME;
  double ymin, ymax;
  double ptmin, ptmax;
  size_t ncall1, itm1;
  size_t ncall2, itm2;
};

template <typename... Args>
bool read_line(std::ifstream& fin, Args&... args);
void read_file(const std::string& filename, parameters& p);
void print_info(const parameters& p);
void init_limits(size_t& ndim, std::vector<double>& dx_lower,
                 std::vector<double>& dx_upper, const parameters& p);

double integrand(double* dx, size_t ndim, void* params) {
  (void)(ndim);  // unused
  auto* p = static_cast<parameters*>(params);

  double y1 = dx[0];
  double y2 = dx[1];

  double test = (y1 + y2) / (p->CME);

  return 1.0 + (test - test);
}

// main program
int main(int argc, char* argv[]) {
  // check command line arguments
  (void)(argc);  // unused
  (void)(argv);  // unused

  // start program timer
  auto start = std::chrono::high_resolution_clock::now();

  // setup Monte-Carlo integration environment
  gsl_rng_env_setup();

  // retrieve kinematics parameters from input file
  parameters p;

  // read input parameters from file
  p.CME = 5020.0;
  p.ptmin = 50.0;
  p.ptmax = 500.0;
  p.ymin = -1.0;
  p.ymax = +1.0;
  p.ncall1 = 100000;
  p.itm1 = 10;
  p.ncall2 = 1000000;
  p.itm2 = 1;

  const size_t ndim = 2;
  double dx_lower[ndim];
  double dx_upper[ndim];
  // init_limits(ndim, dx_lower, dx_upper, p);

  dx_lower[0] = p.ymin, dx_upper[0] = p.ymax;
  dx_lower[1] = p.ymin, dx_upper[1] = p.ymax;

  size_t nbin = 20;
  double hmin = p.ptmin;
  double hmax = p.ptmax;
  double bin = (hmax - hmin) / static_cast<double>(nbin);
  std::vector<double> bin_mid(nbin), results(nbin), errors(nbin);

// define OpenMP parallel region
#ifdef _OPENMP
#pragma omp parallel for
#endif

  // perform integration loop
  for (size_t i = 0; i < nbin; ++i) {
#ifdef _OPENMP
#pragma omp critical
    {
      std::cout << "Working on bin: " << i
                << "\t under thread: " << omp_get_thread_num() << std::endl;
    }
#else
    std::cout << "Working on bin: " << i << std::endl;
#endif

    // define bin parameters
    double binL = hmin + static_cast<double>(i) * bin;
    double binR = hmin + static_cast<double>(i + 1) * bin;
    bin_mid[i] = (binL + binR) / 2.0;
    double res, err;

    // local kinematics object (copied values from global k)
    parameters p_local = p;

    // local GSL monte rng and state
    gsl_rng* r = gsl_rng_alloc(gsl_rng_default);
    gsl_monte_vegas_state* s = gsl_monte_vegas_alloc(ndim);
    gsl_monte_function gmf = {&integrand, ndim, &p_local};
    gsl_monte_vegas_params vp;

    // warmup run: iteration=w, calls=n
    gsl_monte_vegas_params_get(s, &vp);
    vp.stage = 0;
    vp.iterations = p.itm1;
    gsl_monte_vegas_params_set(s, &vp);
    gsl_monte_vegas_integrate(&gmf, dx_lower, dx_upper, ndim, p.ncall1, r, s,
                              &res, &err);

    // final run: iteration=1, calls=f*n
    gsl_monte_vegas_params_get(s, &vp);
    vp.stage = 2;
    vp.iterations = p.itm2;
    gsl_monte_vegas_params_set(s, &vp);
    gsl_monte_vegas_integrate(&gmf, dx_lower, dx_upper, ndim, p.ncall2, r, s,
                              &res, &err);

    // free resources
    gsl_monte_vegas_free(s);
    gsl_rng_free(r);

    // store result and error in array
    results[i] = res;
    errors[i] = err;
  }

  // define print function
  auto print = [](std::ostream& out, const std::vector<double>& x,
                  const std::vector<double>& y, const std::vector<double>& e) {
    for (size_t i = 0; i < x.size(); ++i)
      out << x[i] << '\t' << y[i] << '\t' << e[i] << std::endl;
  };

  // print to console
  std::cout << "----------------------------------------" << std::endl
            << std::scientific << std::setprecision(6)
            << "#   x    \t    y    \t   error  " << std::endl;
  print(std::cout, bin_mid, results, errors);
  // print to file
  std::ofstream fout("results.txt", std::ios::out);
  print(fout, bin_mid, results, errors);
  fout.close();

  // display elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "----------------------------------------" << std::endl
            << "Elapsed time: " << std::defaultfloat << elapsed.count()
            << " seconds\n"
            << "----------------------------------------" << std::endl;

  return 0;
}