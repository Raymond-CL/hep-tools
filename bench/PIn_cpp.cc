#include <math.h>

#include <chrono>
#include <iomanip>
#include <iostream>

int isPrime(int n) {
  if (n == 0 || n == 1) return false;
  for (int i = 2; i <= sqrt(n) + 1; i++)
    if (n % i == 0) return false;
  return true;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  int N = 5000000;
  int primes = 0;
  for (int i = 0; i < N; i++) primes += isPrime(i);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "C++" << std::endl;
  std::cout << "result: " << std::setw(8) << primes << " primes in "
            << std::setw(8) << N << std::endl;
  std::cout << "time: " << std::setw(10) << elapsed.count() << " seconds."
            << std::endl;
}