#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

/**
   * n number of numbers to check
   * G random number
   * a user A private key
   * b user B private key
   * p prime number 
   **/
bool secretkeygenerator(mpz_t result, uint64_t n, mpz_t G, mpz_t a, mpz_t b, mpz_t p)
{
  //gmp_printf("prime : %Zd\n", p);
  mpz_t x, y;
  mpz_init(x);
  mpz_init(y);
  // shared secret keys ***********************
  // x = fmod(pow(G, a), p);
  // x = G^a
  mpz_pow_ui(x, G, mpz_get_ui(a));
  // mod(x, p)
  mpz_mod(x, x, p);
  //gmp_printf("x : %Zd\n", x);
  // Shared key 1 ***************************
  // y = fmod(pow(G, b), p)
  // y = G^a
  mpz_pow_ui(y, G, mpz_get_ui(b));
  // mod(y, p)
  mpz_mod(y, y, p);
  //gmp_printf("y : %Zd\n", y);
  // Shared key 2 ****************************
  mpz_t secretKey, secretKey2;
  mpz_init(result);
  mpz_init(secretKey2);
  // Shared secret key 1 *********************
  mpz_pow_ui(result, x, mpz_get_ui(b));
  mpz_mod(result, result, p);
  // Shared secret key 2 *********************
  mpz_pow_ui(secretKey2, y, mpz_get_ui(a));
  mpz_mod(secretKey2, secretKey2, p);
  //gmp_printf("secretkey : %Zd\n", secretKey2);

  return (mpz_cmp(secretKey2, result) == 0);
}
