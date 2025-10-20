#ifndef PHYSCONST_H
#define PHYSCONST_H

namespace phys {
// mathematical constants
constexpr double PI = 3.14159265358979323846;
constexpr double twoPI = 2.0 * PI;
constexpr double PIsq = PI * PI;

// quantum constants
constexpr double PLANCK = 6.62607015e-34;
constexpr double PLANCK_BAR = PLANCK / twoPI;
constexpr double CHARGE = 1.602176634e-19;
constexpr double HBAR = PLANCK_BAR / CHARGE;
constexpr double LIGHT_SPEED = 299792458.0;
constexpr double HBARC = HBAR * LIGHT_SPEED;

// unit conversion constants
constexpr double GIGA = 1.0e9;
constexpr double femto = 1.0e-15;
constexpr double GeVfm = HBARC / GIGA / femto;

// particle masses
constexpr double M_pro = 0.93827208816;
constexpr double M_neu = 0.93956542052;
constexpr double M_ele = 0.00051;
constexpr double M_mu  = 0.10566;
constexpr double M_tau = 1.77686;
constexpr double Mp2 = M_pro * M_pro;
constexpr double Me2 = M_ele * M_ele;

// coupling constants
constexpr double Alphae0 = 1.0 / 137.036;
constexpr double AlphaeZ = 1.0 / 127.94;  // at Z pole
constexpr double Alphaesq = Alphae0 * Alphae0;
}

#endif