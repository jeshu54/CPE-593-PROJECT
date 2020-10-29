#include "PrimeGenerator.h"
// For numeric limit max()
#include <limits>
// For find()
#include <algorithm>

using namespace std;

PrimeGenerator::PrimeGenerator()
{
  // First prime is 2, save it so we don't hit issues later
  knownPrimes.insert(2);
}

// Determine if a given value is prime or not
bool PrimeGenerator::isPrime(uint_Type val)
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
uint_Type PrimeGenerator::getNextPrime(uint_Type val)
{
  // Check if we already have the next prime number
  // Lookup would be ideal over finding the next prime number manually
  set<uint_Type>::iterator index = find(knownPrimes.begin(), knownPrimes.end(), val);
  if (index != knownPrimes.end() && *(++index)){
    return *(++index);
  }
  // We don't already have the prime saved, find the next one
  // Only look at odd numbers
  if (val % 2 == 0){ 
    val += 1;
  }
  // Find the next prime value
  for (uint_Type i = val; i < numeric_limits<uint_Type>::max(); i += 2)
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
uint_Type PrimeGenerator::getNextPrime()
{
  // From the last known prime, increment by 2 looking for the next value
  for (uint_Type i = *knownPrimes.end(); i < numeric_limits<uint_Type>::max(); i += 2)
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