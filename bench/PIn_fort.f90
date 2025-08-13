function isprime(n)
  implicit none
  integer, intent(in) :: n
  logical :: isprime
  integer :: i
  if(n.eq.0 .or. n.eq.1) then
    isprime=.false.;  return
  endif
  do i = 2,int(sqrt(real(n)))+1
    if(mod(n,i).eq.0) then
      isprime=.false.;  return
    endif
  enddo
  isprime=.true.;  return
end function isprime

program main
  implicit none
  integer :: N, primes, i
  integer :: tstart,tstop
  real :: rate
  logical, external :: isprime
  call system_clock(tstart,rate)

  N = 5000000
  primes = 0
  do i=1,N
    if(isprime(i)) primes = primes + 1
  enddo

  call system_clock(tstop,rate)
  write(*,('(a)')) "Fortran"
  write(*,('(a,i8,a,i8)')) "result: ",primes," primes in ",N
  write(*,('(a,f10.6,a)')) "time: ",(tstop-tstart)/rate," seconds."
end program main