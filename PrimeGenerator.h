// For std::set
#include <set>
// For uint64_t
#include <stdint.h>

// Type of values we are using
// This may change to BigInteger, so typedef for all instances
typedef uint64_t uint_Type;

class PrimeGenerator{
private:
  // Known primes are stored in a set (sorted) to get known values rather than
  // compute the next one if the situation comes up
  std::set<uint_Type> knownPrimes;

public:
  // Constructor
  PrimeGenerator();

  // Destructor 
  ~PrimeGenerator(){}

  // Determine if a given value is prime or not
  bool isPrime(uint_Type);

  // Gets the next prime following the given value
  uint_Type getNextPrime(uint_Type);

  // Gets the next prime following the last index of saved primes
  uint_Type getNextPrime();
};

