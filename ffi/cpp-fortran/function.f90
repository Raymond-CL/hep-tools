module fortmod
  use iso_c_binding
  implicit none
contains

  function f_bessel_j0(x) bind(C, name="f_bessel_j0") result(res)
    real(c_double), value :: x
    real(c_double) :: res
    res = bessel_j0(x)
  end function f_bessel_j0

end module fortmod