#include<iostream>
#include<math.h>
#include<ctime>
#include<iomanip>
#include<vector>
#import "Cryptography.h"
#include <cryptopp/aes.h>
using namespace std;

#include "pch.h"
#include <iostream>
#include "aes.h"
#include <Windows.h>

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "aes.h"
using CryptoPP::AES;

#include "ccm.h"
using CryptoPP::CBC_Mode;

#include "assert.h"


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
	
	// Work in progress
	
	/*
	AutoSeededRandomPool prng;

	byte key[AES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key, sizeof(key));

	byte iv[AES::BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	string plain = "CBC Mode Test";
	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "iv: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		cout << "plain text: " << plain << endl;

		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(plain, true,
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter
		); // StringSource

#if 0
		StreamTransformationFilter filter(e);
		filter.Put((const byte*)plain.data(), plain.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		cipher.resize(ret);
		filter.Get((byte*)cipher.data(), cipher.size());
#endif
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// Pretty print
	encoded.clear();
	StringSource(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true,
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

#if 0
		StreamTransformationFilter filter(d);
		filter.Put((const byte*)cipher.data(), cipher.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		recovered.resize(ret);
		filter.Get((byte*)recovered.data(), recovered.size());
#endif

		cout << "recovered text: " << recovered << endl;
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	return 0; */
	
}
