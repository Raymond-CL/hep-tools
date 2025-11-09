program main
  use iso_c_binding
  implicit none
  real(c_double) :: x

  interface
    function bes_j0(x) bind(C, name="bessel_j0_cpp") result(res)
      import :: c_double
      real(c_double), value :: x
      real(c_double) :: res
    end function bes_j0
  end interface

  x = 1d0
  print *, "Bessel_j0 of ", x, "is:", bes_j0(x)
end program main