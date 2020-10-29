#include<iostream>
#include<math.h>
#include<ctime>
#include<iomanip>
#include<vector>
using namespace std;


uint32_t primechecker(uint32_t n){
  bool isPrime;
  //int count [n];
  uint32_t p;
  for(int i = 2; i <= n/2; i++) {
    if (n%i == 0) {
      isPrime = false;
      break; 
      }
      
    else{
      isPrime = true;
      break;
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
  	return store[6];
}

uint64_t secretkeygenerator(uint64_t n, uint64_t G, uint64_t a, uint64_t b, uint64_t p) {

	uint64_t x;
	//p= randomprimegenerator(n);
	uint64_t y;
	uint64_t secretkey, secretkey2;
	x = fmod(pow(G,a),p); 	
	//cout << x<< endl;			// Shared key 1
	y= fmod(pow(G,b),p);  
	//cout << y<< endl;				// Shared key 2
	secretkey = fmod(pow(x,b),p); 
	//cout << secretkey<< endl;		// Shared secret key 1
	secretkey2 = fmod(pow(y,a),p);
	//cout << secretkey2 << endl;   // Shared secret key 2
	return secretkey;
}


int main(){
	int seed = time(0);
    srand(seed);
	uint64_t G,a,b,n,p;
	a= 3; // private key 1
	b= 4; // privare key 2
	G= rand()%100; // Number Generator
	n= 1000; // Number to check random prime number
	p = randomprimegenerator(n);
	//cout << G << endl;
	cout << "Secret Key: " <<secretkeygenerator(n,G, a,b,p);
}