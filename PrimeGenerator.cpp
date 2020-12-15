#include "PrimeGenerator.h"
// For numeric limit max()
#include <limits>
// For find()
#include <algorithm>
// Seed for random numbers
#include <time.h>

// io if main function exists
#if MAIN
#include <iostream>
#endif // MAIN

using namespace std;

/*
* Default constructor, sets upu the random generator state
* and sets number of Miller Rabin iterations to 20
*/
PrimeGenerator::PrimeGenerator()
{
  iterations = 20;
  gmp_randinit_default(randState);
  numBits = 100;
}

/*
* Secondary constructor, sets up the random generator state
* and sets the number of Miller Rabin iterations
*/
PrimeGenerator::PrimeGenerator(uint16_t v) : iterations(v)
{
  gmp_randinit_default(randState);
  numBits = 100;
}

/*
* Secondary constructor, sets up the random generator state
* and sets the number of Miller Rabin iterations and number of bits
*/
PrimeGenerator::PrimeGenerator(uint16_t v, uint64_t b) : iterations(v), numBits(b)
{
  gmp_randinit_default(randState);
}

/*
* Set the number of bits when generating random numbers
* Expected to be 7+ bits to find prime values with the checker
*/
void PrimeGenerator::setNumBits(uint64_t bits){
  numBits = (bits > 7 ? bits : 7);
}

/*
* Set the random number generator seed to the seed passed in
*/
void PrimeGenerator::setSeed(uint64_t seed) {
  gmp_randseed_ui(randState, seed);
}

/*
* Generate a random number with numBits number of bits
*/
void PrimeGenerator::getRandom(mpz_t result){
  mpz_init(result);
  mpz_rrandomb(result, randState, numBits);
}

/*
* Gets random number of length numBits in length
* and ensures it is prime before returning
* Utilizes MillerRabin test with iterations passed into constructor
* (defaults to 20)
*/
void PrimeGenerator::getPrimeNumber(mpz_t result) {
  // Initialize return value
  mpz_init(result);
  bool primeFound = false;
  // loop until a prime value is found
  while(!primeFound){
    // get random number
    getRandom(result);
    primeFound = isPrime(result);
  }
}

bool PrimeGenerator::isPrime(mpz_t result){

  mpz_t tmp;
  int count = 0;
  mpz_init(tmp);
  // test divisibility by first few prime values
  for (int i = 0; i < sizeof(knownPrimes) / sizeof(mpz_t); i++) {
    // divisible by one of the prime numbers
    // do not continue checking this value
    if (mpz_mod_ui(tmp, result, knownPrimes[i]) == 0) {
      return false;
    }
  }

  // passed trial division by known primes, do miller rabin test
  // Miller rabin test
  // Find r such that n = 2^d * r + 1 for some r >= 1
  mpz_t d;
  mpz_init(d);
  mpz_sub_ui(d, result, 1);
  while(mpz_divisible_ui_p(d, 2) != 0){
    mpz_div_ui(d, d, 2);
  }

  while (count < iterations) {
    if (!millerRabin(d, result)) {
      return false;
    }
    count++;
  }
  // cleanup
  mpz_clear(tmp);
  mpz_clear(d);
  // probably prime
  return true;
}

bool PrimeGenerator::millerRabin(mpz_t d, mpz_t n){
  
  mpz_t rand, x, nMinus1;
  mpz_init(nMinus1);
  mpz_sub_ui(nMinus1, n, 1);
  mpz_init_set_ui(rand, 0);
  mpz_init(x);
  // [2, n-2]
  while (mpz_cmp(n, rand) < 0 || mpz_cmp_d(rand, 2) < 0){
    getRandom(rand);
  }
  // powermod
  mpz_powm(x, rand, d, n);
  if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, nMinus1) == 0){
    return true;
  }

  // square x while:
  // d does not reach nMinus1
  // x^2 % n is not 1
  // x^2 % n is not nMinus1
  while (mpz_cmp(d, nMinus1) != 0){
    // power mod x
    mpz_powm_ui(x, x, 2, n);
    // double d
    mpz_mul_ui(d, d, 2);
    // conditions
    if (mpz_cmp_ui(x, 1) == 0){
      return false;
    }
    if (mpz_cmp(x, nMinus1) == 0){
      return true;
    }
  }
  // cleanup
  mpz_clear(nMinus1);
  mpz_clear(rand);
  mpz_clear(d);
  mpz_clear(n);
  mpz_clear(x);
  // condition never reached, return composite
  return false;
}

#if MAIN
int main(int argc, char** argv) {
  try {
    PrimeGenerator *pg = new PrimeGenerator(30, 1000);
    pg->setSeed( static_cast<uint64_t> (time(NULL)));
    pg->setNumBits(100);

    switch (argc) {
    case 1:
      break;
    case 2:
      pg->setNumBits(atoll(argv[1]));
      break;
    case 3:
      pg->setNumBits(atoll(argv[1]));
      pg->setSeed(atoll(argv[2]));
      break;
    }

    mpz_t value;
    mpz_init(value);

    pg->getPrimeNumber(value);
    gmp_printf("Prime value: %Zd\n", value);
  }
  catch (exception err)
  {
    std::cout << err.what() << std::endl;
  }
  return 0;
}
#endif // MAIN