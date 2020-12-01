#include "PrimeGenerator.h"
// For numeric limit max()
#include <limits>
// For find()
#include <algorithm>

#include <iostream>

using namespace std;

/*
* Default constructor, sets upu the random generator state
* and sets number of Miller Rabin iterations to 20
*/
PrimeGenerator::PrimeGenerator()
{
  iterations = 20;
  gmp_randinit_default(randState);
}

/*
* Secondary constructor, sets upu the random generator state
* and sets the number of Miller Rabin iterations
*/
PrimeGenerator::PrimeGenerator(uint16_t v) : iterations(v)
{
  gmp_randinit_default(randState);
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
void PrimeGenerator::getRandom(mpz_t& result, uint64_t numBits){
  mpz_init(result);
  mpz_rrandomb(result, randState, numBits);
}

/*
* Gets random number of length numBits in length
* and ensures it is prime before returning
* Utilizes MillerRabin test with iterations passed into constructor
* (defaults to 20)
*/
void PrimeGenerator::getPrimeNumber(mpz_t& result, uint64_t numBits = 100) {
  try{
  // Initialize return value
  mpz_init(result);
  bool primeFound = false;
  // loop until a prime value is found
  while(!primeFound){
    // get random number
    getRandom(result, numBits);
    primeFound = isPrime(result);
  }
  }
  catch(exception err){
    std::cout << err.what();
  }
}

bool PrimeGenerator::isPrime(mpz_t& result){

  mpz_t tmp;
  int count = 0;
  mpz_init(tmp);
  bool doContinue = true;
  // test divisibility by first few prime values
  for (int i = 0; doContinue && i < sizeof(knownPrimes); i++) {
    // divisible by one of the prime numbers
    // do not continue checking this value
    if (mpz_mod_ui(tmp, result, knownPrimes[i]) == 0) {
      doContinue = false;
      break;
    }
  }

  if (doContinue) {
    gmp_printf("Random number: %Zd\n", result);
    return true;
  }
  // Miller rabin test
  while (doContinue && count < iterations) {
    count++;
  }

  return false;
}

int main() {
  PrimeGenerator *pg = new PrimeGenerator(20);
  mpz_t value;
  pg->setSeed(10);
  pg->getPrimeNumber(value);
}





/*
*
// Determine if a given value is prime or not
bool PrimeGenerator::isPrime(mpz_t& val)
{
  // Placeholder for efficient algorithm
  for (int i = 2; i <= val / 2; i++)
  {
    if (val % i == 0)
    {
      return false;
      break;
    }
  }
  return true;
}

// Gets the next prime following the given value
mpz_t& PrimeGenerator::getNextPrime(mpz_t& val)
{
  // Check if we already have the next prime number
  // Lookup would be ideal over finding the next prime number manually
  set<mpz_t&>::iterator index = find(knownPrimes.begin(), knownPrimes.end(), val);
  if (index != knownPrimes.end() && *(++index)){
    // already incremented in the if statement, return the value
    return *index;
  }
  // We don't already have the prime saved, find the next one
  // Only look at odd numbers
  if (val % 2 == 0){ 
    val += 1;
  }
  // Find the next prime value
  for (mpz_t& i = val; i < numeric_limits<mpz_t&>::max(); i += 2)
  {
    if (isPrime(i))
    {
      // Found a prime, save it and return
      knownPrimes.insert(i);
      return i;
    }
  }
  // Base case return 0
  return 0;
}

// Gets the next prime following the last index of saved primes
mpz_t& PrimeGenerator::getNextPrime()
{
  // From the last known prime, increment by 2 looking for the next value
  for (mpz_t& i = *knownPrimes.end(); i < numeric_limits<mpz_t&>::max(); i += 2)
  {
    if (isPrime(i))
    {
      // Found a prime, save it and return
      knownPrimes.insert(i);
      return i;
    }
  }
  // Base case return 0
  return 0;
}

*/