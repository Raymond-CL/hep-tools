import Text.Printf
import Data.Time

isPrime :: Int -> Bool
isPrime n
  | n <= 1 = False
  | n == 2 = True
  | otherwise = null [ x | x <- [2..isqrt n], n `mod` x == 0]
  where
    isqrt = floor . sqrt . fromIntegral

countPrimes :: Int -> Int
countPrimes n = length [ x | x <- [2..n-1], isPrime x]

main :: IO ()
main = do
  let n = 5000000
  start <- getCurrentTime
  let primeCount = countPrimes n
  end <- getCurrentTime
  let diff = 10^7 * diffUTCTime end start
  let duration = realToFrac diff :: Float
  
  printf "Haskell\n"
  printf "result: %8d primes in %8d\n" primeCount n
  printf "time: %10.6f seconds.\n" duration