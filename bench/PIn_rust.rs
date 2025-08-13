use std::f32;
use std::time::Instant;

fn isprime(n:i32)->bool{
  if n==0 || n==1{
    return false;
  }
  for i in 2..=(((n as f32).sqrt() as i32)+1){
    if n%i==0{
      return false;
    }
  }
  true
}

fn main(){
  let start = Instant::now();

  let n = 5_000_000;
  let mut primes = 0;
  for i in 1.. n{
    if isprime(i){
      primes+=1;
    }
  }

  let duration = start.elapsed();
  println!("Rust");
  println!("result: {:8} primes in {:8}",primes,n);
  println!("time: {:10.6} seconds.",duration.as_secs_f64());
}