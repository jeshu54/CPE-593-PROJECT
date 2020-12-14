#include<iostream>
#include<math.h>
#include<ctime>
#include<iomanip>
#include<vector>
#include "PrimeGenerator.h"
#include <gmp.h>
using namespace std;


uint32_t primechecker(uint32_t n){
  bool isPrime = true;
  //int count [n];
  
  if (n == 0 || n == 1) {
        isPrime = false;
    }
    else {
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
    }
  
   return isPrime;
}

uint32_t randomprimegenerator(uint32_t count) {
  bool isPrime;
  vector<uint64_t> store;
  
  for(uint64_t n=2; n< count; n++) {

    isPrime = primechecker(n);
    if(isPrime == true) {
      //cout << n << " ";
      store.push_back(n);
    }
    
  }
for (int l=0; l<store.size(); l++) 
cout << store[l]<< endl;  
// random location    
    return store[20];
}

  /**
   * n number of numbers to check
   * G random number
   * a user A private key
   * b user B private key
   * p prime number 
   **/
  bool secretkeygenerator(mpz_t result, uint64_t n, mpz_t G, mpz_t a, mpz_t b)
  {
  mpz_t p;
    PrimeGenerator* pg = new PrimeGenerator();
    pg->setNumBits(n);
    pg->getPrimeNumber(p);
    gmp_printf("prime : %Zd\n", p);
    mpz_t x, y;
    mpz_init(x);
    mpz_init(y);
    // shared secret keys
    // x = fmod(pow(G, a), p);
    // x = G^a
    mpz_pow_ui(x, G, mpz_get_ui(a));
    // mod(x, p)
    mpz_mod(x, x, p);
    gmp_printf("x : %Zd\n", x);
    //cout << x<< endl;     // Shared key 1
    // y = fmod(pow(G, b), p)
    // y = G^a
    mpz_pow_ui(y, G, mpz_get_ui(b));
    // mod(y, p)
    mpz_mod(y, y, p);
    gmp_printf("y : %Zd\n", y);
    //cout << y<< endl;       // Shared key 2
    mpz_t secretKey, secretKey2;
    mpz_init(result);
    mpz_init(secretKey2);
    // Shared secret key 1
    mpz_pow_ui(result, x, mpz_get_ui(b));
    mpz_mod(result, result, p);
    // Shared secret key 2
    mpz_pow_ui(secretKey2, y, mpz_get_ui(a));
    mpz_mod(secretKey2, secretKey2, p);
    gmp_printf("secretkey : %Zd\n", secretKey2);
  return (mpz_cmp(secretKey2, result) == 0);
  }


int main(){
  int seed = time(0);
    srand(seed);
  mpz_t G,a,b;
  mpz_init_set_ui(G, rand() % 100);
  mpz_init_set_ui(a, 32);
  mpz_init_set_ui(b, 42);
  uint64_t n = 1000;
  //a= 32; // private key 1
  //b= 42; // privare key 2
  //G= rand()%100; // Number Generator
  //n= 100; // Number to check random prime number
  //p = randomprimegenerator(n);
  //cout << G << endl;
  mpz_t result;
  mpz_init(result);
  if(secretkeygenerator(result, n,G, a,b)){
      gmp_printf("Secret Key: %Zd\n", result);
  }
  else {
    cout << "Keys do not match" << endl;
  }
  //cout << "Secret Key: " << result << endl;
}