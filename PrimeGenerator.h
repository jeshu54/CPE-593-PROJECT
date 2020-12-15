// For std::set
#include <set>
// For uint64_t
#include <stdint.h>
// For using mpz_t and gmp functions
#include <gmp.h>

// disable if PrimeGenerator is not the main function
#define MAIN false

class PrimeGenerator{
private:
  /* 
  * List of the first few known prime values to check primality with trial division
  * This can be expanded or generated with a sieve in the future
  */
  int knownPrimes[70] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                        31, 37, 41, 43, 47, 53, 59, 61, 67,
                        71, 73, 79, 83, 89, 97, 101, 103,
                        107, 109, 113, 127, 131, 137, 139,
                        149, 151, 157, 163, 167, 173, 179,
                        181, 191, 193, 197, 199, 211, 223,
                        227, 229, 233, 239, 241, 251, 257,
                        263, 269, 271, 277, 281, 283, 293,
                        307, 311, 313, 317, 331, 337, 347, 349 };

  /* 
  * GMP random generation state
  */
  gmp_randstate_t randState;

  /* 
  * Number of iterations for Miller Rabin primality test
  */
  uint16_t iterations;

  /*
  * Number of bits mpz random numbers should work with
  */
  uint64_t numBits;

public:
  /* 
  * Default Constructor
  */
  PrimeGenerator();

  /* 
  * Secondary constructor
  */
  PrimeGenerator(uint16_t);

  /* 
  * Tertiary constructor
  */
  PrimeGenerator(uint16_t, uint64_t);

  /* 
  * Destructor 
  */
  ~PrimeGenerator(){}

  /*
  * Set the number of bits when generating random numbers
  */
  void setNumBits(uint64_t bits);

  /*
  * Set the random number generator seed to the seed passed in
  */
  void setSeed(uint64_t seed);

  /*
  * Generate a random number with numBits number of bits
  */
  void getRandom(mpz_t result);

  /*
  * Gets random number of length numBits in length
  * and ensures it is prime before returning
  * Utilizes MillerRabin test with iterations passed into constructor
  * (defaults to 20)
  */
  void getPrimeNumber(mpz_t result);

  /*
  * Determine if a given value is prime or not
  */ 
  bool isPrime(mpz_t);

  /*
  * Returns false if composite, true if probably prime
  */
  bool millerRabin(mpz_t d, mpz_t n);

};

