#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include <stdlib.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "ct11pdf.h"

// global constants
constexpr double PI = M_PI;             // pi from GNU, not C++ standard
constexpr double Nc = 3.0;              // number of colors
constexpr double Cf = 4.0 / 3.0;        // Casimir factor for quarks
constexpr double Ca = 3.0;              // Casimir factor for gluons
constexpr int Nf = 5;                   // number of active quark flavours
constexpr double gev2barn = 3.8938e-4;  // GeV^-2 to barn conversion factor

// amplitude function shortcuts to speed up calculations
static inline double ampA(double n1, double n2, double d) noexcept {
  constexpr double Cf_o_Ca = Cf / Ca;
  return Cf_o_Ca * (n1 * n1 + n2 * n2) / (d * d);
}
static inline double ampB(double n, double d1, double d2) noexcept {
  constexpr double twoCf_o_Casq = 2.0 * Cf / (Ca * Ca);
  return ampA(n, d1, d2) + ampA(n, d2, d1) - twoCf_o_Casq * (n * n) / (d1 * d2);
}
static inline double ampC(double n1, double n2, double d) noexcept {
  constexpr double Cfsq_o_Casq = (Cf * Cf) / (Ca * Ca);
  return Cfsq_o_Casq * (n1 * n1 + n2 * n2) / (n1 * n2) - ampA(n1, n2, d);
}
static inline double ampD(double n1, double n2, double n3) noexcept {
  constexpr double twoCa_o_Cf = 2.0 * Ca / Cf;
  return twoCa_o_Cf *
         (Ca - n1 * n2 / (n3 * n3) - n1 * n3 / (n2 * n2) - n2 * n3 / (n1 * n1));
}

// parameters shared between main and integrand
struct parameters {
  double CME;
  double ymin, ymax;
  double ptmin, ptmax;
  cteqpdf ct18anlo;
  bool do_Qjet, do_Gjet;
};

// integrand function
double integrand(double* dx, size_t ndim, void* params) {
  (void)(ndim);  // unused
  auto* p = static_cast<parameters*>(params);
  // integration follows: Rev.Mod.Phys. 59, 465 (1987), eq. (A3)
  // particle kinematics: a(xa) + b(xb) -> c(pt,yc) + d(pt,yd)
  // different from dijet, single inclusive jet measures only one jet "c"
  // this means only yc should be within rapidity limit, yd can be anything
  double xa = dx[0];
  double yc = dx[1];
  double pt = dx[2];
  // transverse momentum fraction
  double xt = 2.0 * pt / p->CME;
  // Given xb below, solve xa when xb==1
  double xamin = (xt * std::exp(+yc)) / (2.0 - xt * std::exp(-yc));
  if (xa < xamin || xa > 1.0) return 0.0;
  // Given s,t,u below, solve xb when s+t+u==0
  double xb = (xa * xt * std::exp(-yc)) / (2.0 * xa - xt * std::exp(+yc));
  // the range of xb is bounded by xamin, but for safety check
  if (xb < 0.0 || xb > 1.0) return 0.0;   
  // Mandelstam variables
  double mans = +xa * xb * p->CME * p->CME;
  double mant = -xa * pt * p->CME * std::exp(-yc);
  double manu = -xb * pt * p->CME * std::exp(+yc);
  // renormalization and factorization scales
  // One can vary the scale by a small factor (typically between 0.5 and 2)
  double muren = pt * 1.0;    // * 0.5, * 2.0
  double mufac = muren;
  // coupling constant
  // One can use a one-loop expression or a fixed value
  // Here we read directly from PDF
  double alphaS = p->ct18anlo.alphas(mufac);  
  // parton distribution functions (PDF)
  // flavour:   bb, cb, sb, db, ub,  g,  u,  d,  s,  c,  b
  // index(i):  -5  -4  -3  -2  -1   0   1   2   3   4   5
  // Nf + i:     0   1   2   3   4   5   6   7   8   9   10
  double pdfa[2 * Nf + 1] = {0.0};
  double pdfb[2 * Nf + 1] = {0.0};
  for (int i = -Nf; i <= +Nf; ++i) {
    pdfa[Nf + i] = p->ct18anlo.parton(i, xa, mufac);
    pdfb[Nf + i] = p->ct18anlo.parton(i, xb, mufac);
  }  // off-set by +Nf
  // matrix element calculation
  // Rev.Mod.Phys. 59, 465 (1987)
  // QCD and Collider Physics, Ellis, Stirling and Webber, 1996
  double QJcs = 0.0, GJcs = 0.0;
  double dis;  // temporary variable to store distributions per channel
  /*
  Here I am using a different summation scheme compared to other codes
  consider the following: q + g -> q + g
    a(xa) -----+~~~~~ X
               |
    b(xb) ~~~~~+----- Y
  We first fix the initial PDF, which means quark carries xa, and gluon carries
  xb. If we are measuring X(pt,yc), then we are measuring a gluon jet, with
  t-channel amplitude. If we are measuring Y(pt,yd), then we are measuring a
  quark jet, with t<->u exchange in amplitude. In inclusive jet measurement, we
  measure both jets and sum both contributions. This is easily extended to
  other, especially asymmetric observables like inclusive hadron, hadron-jet.
  Because we know the exact flavour of the measured parton.
  */
  // q + q' -> q + q'
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    for (int j = 1; j <= Nf; ++j) {
      if (i == j) continue;
      dis += pdfa[Nf + i] * pdfb[Nf + j];
      dis += pdfa[Nf + i] * pdfb[Nf - j];
      dis += pdfa[Nf - i] * pdfb[Nf + j];
      dis += pdfa[Nf - i] * pdfb[Nf - j];
    }
  }
  QJcs += dis * ampA(mans, manu, mant);
  QJcs += dis * ampA(mans, mant, manu);
  // q + qb -> q' + qb'
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf + i] * pdfb[Nf - i];
    dis += pdfa[Nf - i] * pdfb[Nf + i];
  }
  dis *= (Nf - 1);  // sum over q' not equal to q
  QJcs += dis * ampA(mant, manu, mans);
  QJcs += dis * ampA(manu, mant, mans);
  // q + q -> q + q
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf + i] * pdfb[Nf + i];
    dis += pdfa[Nf - i] * pdfb[Nf - i];
  }
  dis *= 0.5;  // identical final state
  QJcs += dis * ampB(mans, mant, manu);
  QJcs += dis * ampB(mans, manu, mant);
  // q + qb -> q + qb
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf + i] * pdfb[Nf - i];
    dis += pdfa[Nf - i] * pdfb[Nf + i];
  }
  QJcs += dis * ampB(manu, mans, mant);
  QJcs += dis * ampB(mant, mans, manu);
  // q + qb -> g + g
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf + i] * pdfb[Nf - i];
    dis += pdfa[Nf - i] * pdfb[Nf + i];
  }
  dis *= 0.5;  // identical final state
  GJcs += dis * 6.0 * ampC(mant, manu, mans);
  GJcs += dis * 6.0 * ampC(manu, mant, mans);
  // g + g -> q + qb
  dis = 0.0;
  dis = pdfa[Nf] * pdfb[Nf];
  dis *= Nf;  // sum over all final quark flavours
  QJcs += dis * (27.0 / 32.0) * ampC(mant, manu, mans);
  QJcs += dis * (27.0 / 32.0) * ampC(manu, mant, mans);
  // g + q -> g + q
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf] * pdfb[Nf + i];
    dis += pdfa[Nf] * pdfb[Nf - i];
  }
  GJcs += dis * (-9.0 / 4.0) * ampC(mans, manu, mant);
  QJcs += dis * (-9.0 / 4.0) * ampC(mans, mant, manu);
  // q + g -> q + g
  dis = 0.0;
  for (int i = 1; i <= Nf; ++i) {
    dis += pdfa[Nf + i] * pdfb[Nf];
    dis += pdfa[Nf - i] * pdfb[Nf];
  }
  QJcs += dis * (-9.0 / 4.0) * ampC(mans, manu, mant);
  GJcs += dis * (-9.0 / 4.0) * ampC(mans, mant, manu);
  // g + g -> g + g
  dis = 0.0;
  dis = pdfa[Nf] * pdfb[Nf];
  dis *= 0.5;  // identical final state
  GJcs += dis * ampD(mans, mant, manu);
  GJcs += dis * ampD(mans, manu, mant);
  // combine quark and gluon jet contributions
  double total_amp_sq = (p->do_Qjet ? QJcs : 0.0) + (p->do_Gjet ? GJcs : 0.0);
  // |M|^2 to dσ/dt factor
  double ampsq_to_dsdt = PI * alphaS * alphaS / (mans * mans);
  // pre-factor from momentum fraction 
  double pre_factor = 2.0 / PI * xa * xb / (2.0 * xa - xt * std::exp(+yc));
  // Jacobian: E*d^3σ/d^3p = 1/(2*pi*pt) * d^2σ/(dpt dy)
  double jacobian = 2.0 * PI * pt;
  // final differential cross section
  double diff_cs = jacobian * pre_factor * ampsq_to_dsdt * total_amp_sq;
  // convert dsig/dpt to dsig/dpt/dy
  double diff_rap = 1.0 / (2.0 * p->ymax);
  // convert GeV^{-2} to nano barn
  double gev_to_nb = gev2barn * 1e9;
  // final integrand return value
  return diff_cs * diff_rap * gev_to_nb;
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
  // set parameters (usually from input data file)
  parameters p;
  p.CME = 2760.0;       // 2760.0, 5020.0
  p.ptmin = 30.0;       // 30, 40
  p.ptmax = 500.0;      // 500, 1000
  p.ymin = -2.1;        // -2.1, -2.8
  p.ymax = +2.1;        // +2.1, +2.8
  p.do_Qjet = true;
  p.do_Gjet = true;
  // integration settings (usually from input data file)
  size_t ncall1 = 10000;
  size_t itm1 = 10;
  size_t ncall2 = 100000;
  size_t itm2 = 1;
  // define integration limits
  const size_t ndim = 3;
  double dx_lower[ndim];
  double dx_upper[ndim];
  // define histogram bins
  const size_t nbin = 188;  // 188, 192
  double hmin = p.ptmin;
  double hmax = p.ptmax;
  double bin = (hmax - hmin) / static_cast<double>(nbin);
  double bin_mid[nbin], results[nbin], errors[nbin];
  // initialize PDF
  string pdffile = "i2TAn2.00.pds";
  p.ct18anlo.setct11(pdffile);
  // perform integration loop
  for (size_t i = 0; i < nbin; ++i) {
    std::cout << "Working on bin: " << i << std::endl;
    // define bin parameters
    double binL = hmin + static_cast<double>(i) * bin;
    double binR = hmin + static_cast<double>(i + 1) * bin;
    bin_mid[i] = (binL + binR) * 0.5;
    double res, err;
    // lower limits
    dx_lower[0] = 0.0;
    dx_lower[1] = p.ymin;
    dx_lower[2] = binL;
    // upper limits
    dx_upper[0] = 1.0;
    dx_upper[1] = p.ymax;
    dx_upper[2] = binR;
    // local GSL monte rng and state
    gsl_rng* r = gsl_rng_alloc(gsl_rng_default);
    gsl_monte_vegas_state* s = gsl_monte_vegas_alloc(ndim);
    gsl_monte_function gmf = {&integrand, ndim, &p};
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
    results[i] = res / bin;  // normalize by bin width
    errors[i] = err;
  }
  // print header
  std::cout << "--------------------------------------------" << std::endl
            << "#   x    \t    y    \t   error  " << std::endl;
  // define print function
  auto print = [nbin](std::ostream& out, const double* x, const double* y,
                      const double* e) {
    out << std::scientific << std::setprecision(6);
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