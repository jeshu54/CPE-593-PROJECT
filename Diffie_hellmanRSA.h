#include<iostream>
#include<math.h>
#include<ctime>
#include<iomanip>
#include<vector>
using namespace std;


uint64_t n= 1000; // Number to check random prime number

class DHRSA{
  private:
  uint64_t a=3829,b=83827;
  //a:  user input private key 1
  //b:  user input private key 2
	uint64_t G = rand()%100; // Number Generator
	
   uint64_t p = randomprimegenerator(n);
    uint64_t secretkey, secretkey2;

  public:
  DHRSA(int a, int b):a(a), b(b){
      secretkeygenerator(n,G, a,b,p);
  }
    uint32_t primechecker(uint32_t n){
  bool isPrime = true;
  //int count [n];
  uint32_t p;
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
  vector<uint32_t> store;
  
  for(uint32_t n=2; n< count; n++) {

    isPrime = primechecker(n);
  	if(isPrime == true) {
  		//cout << n << " ";
  		store.push_back(n);
  	}
  	
  }

// random location  	
  	return store[20];
}

uint64_t secretkeygenerator(uint64_t n, uint64_t G, uint64_t a, uint64_t b, uint64_t p) {

	uint64_t x;
	//p= randomprimegenerator(n);
	uint64_t y;
	//uint64_t secretkey, secretkey2;
	x = fmod(pow(G,a),p); 	
	//cout << x<< endl;			// Shared key 1
	y= fmod(pow(G,b),p);  
	//cout << y<< endl;				// Shared key 2
	secretkey = fmod(pow(x,b),p); 
	//cout << secretkey<< endl;		// Shared secret key 1
	secretkey2 = fmod(pow(y,a),p);
	//cout << secretkey2 << endl;   // Shared secret key 2
    cout << secretkey << " SecretKey ";
	return secretkey;
}

};

