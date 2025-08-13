! sample module
module vec

  use iso_fortran_env, only : i8=>int32, r8=>real64
  implicit none
  integer(i8), parameter :: n=10000000
  real(r8) :: x(n)

contains

  subroutine init_vec()
    call random_number(x)
  end subroutine init_vec

  function get_sum() result(res)
    real(r8) :: res
    res = sum(x)
  end function get_sum

end module vec

! main program
program main
  use vec
  implicit none

  call init_vec()

  print *, "The law of large numbers states that:"
  print *, "the average:", get_sum() / n
  print *, "converges to expected value of 0.5."

end program main
