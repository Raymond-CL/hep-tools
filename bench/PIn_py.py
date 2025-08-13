import math
import time

def isPrime(n):
  if(n==0 or n==1):
    return False
  for i in range(2,int(math.sqrt(n))+1):
    if(n%i==0):
      return False
  return True

start_time = time.time()

N = 5000000
primes = 0
for i in range(1,N):
  primes+=isPrime(i)
  
end_time = time.time()
print("Python")
print(f"result: {primes:8} primes in {N:8}")
print(f"time: {(end_time-start_time):10.6f} seconds.")