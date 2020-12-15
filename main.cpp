/**
 * GROUP 12: Karan Modi, Vincent Loud, Avro
 * Prime generator, RSA, and Diffie-Helman
 * Compile with: g++ -Wall .\PrimeGenerator.cpp  .\main.cpp -lgmp -lgmpxx 
 * */

#include "PrimeGenerator.h"
#include "Diffie_hellmanRSA.h"
#include "RSA.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    PrimeGenerator* pg = new PrimeGenerator();
    srand(time(NULL));
    pg->setSeed(rand());
    mpz_t pKeyA, pKeyB, randG, keyGenPrime;
    pg->setNumBits(rand() % 20);
    pg->getPrimeNumber(pKeyA);
    pg->setNumBits(rand() % 20);
    pg->getPrimeNumber(pKeyB);
    pg->setNumBits(rand() % 20);
    pg->getPrimeNumber(randG);
    pg->setNumBits(rand() % 1000);
    pg->getPrimeNumber(keyGenPrime);

    //cout << pKeyA << endl;
    //cout << pKeyB << endl;
    //cout << randG << endl;

    uint64_t n = 1000;
    cout<<"\n\n\n";
    mpz_t result;
    mpz_init(result);
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tDiffie Hellman Key Exchange (at Point A & B)";
    cout<<"\n---------------------------------------------------------------------";
    if (secretkeygenerator(result, n, randG, pKeyA, pKeyB, keyGenPrime))
    {
        gmp_printf("\nShared Secret Key: %Zd\n", result);
          
        // Create and open a sharedkey text file
        ofstream sk("sharedkey.txt");
        sk << result;               // Write to the file
        sk.close();
    }
    else
    {
        cout << "Keys do not match" << endl;
        return -1;
    }

    mpz_t p, q;
    pg->setNumBits(600);
    pg->getPrimeNumber(p);
    pg->setNumBits(700);
    pg->getPrimeNumber(q);

    //string orig, de, en;
    mpz_t e,orig, de, en,dk,pq;
    mpz_init(e);
    mpz_init(orig);
    mpz_init(dk);
    mpz_init(pq);

    pubkey(e, p, q);
    //cout << "Enter the message : ";
    //getline(cin, orig);

    pg->setNumBits(500);
    pg->getRandom(orig);
    mpz_init_set(en, orig);
    

    rsaenc(en, e, p, q, dk, pq);
    
    // Create and open a RSAencryptedtext text file
    ofstream rsae("RSAencryptedtext.txt");
    rsae << en;               // Write to the file
    rsae.close();

    // Create and open a decryptionkey text file
    ofstream rsadk("decryptionkey.txt");
    rsadk << dk;               // Write to the file
    rsadk.close();

    // Create and open a primemultiple n=p*q text file
    ofstream rsan("primemultiple.txt");
    rsan << pq;               // Write to the file
    rsan.close();
    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tRSA Encrypt(at Point A)";
    cout<<"\n---------------------------------------------------------------------";
    mpz_init_set(de, en);
    rsadec(de, dk, pq);
    cout << "\nThe Original text = " << orig;
    cout << "\n\nThe Encrypted text = " << en;
    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tAES-256 (from Point A to Point B)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\n\nThe Decryption Key to send using AES = " << dk;
    cout << "\n\nThe n to send using AES = " << pq;
    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tRSA Decrypt (at Point B)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\n\nThe Decrypted text = " << de;

    if (mpz_cmp(orig, de) == 0)
    {
        cout << "\n\n The Original Text matches the Decrypted Text!!";
    }

    return 0;
}