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
    mpz_t e,orig, de, en, dk, pq;
    mpz_init(e);
    mpz_init(en);
    mpz_init(de);
    mpz_init(orig);
    mpz_init(dk);
    mpz_init(pq);

    //pubkey(e, p, q);
    //cout << "Enter the message : ";
    //getline(cin, orig);

    pg->setNumBits(500);
    pg->getRandom(orig);
    //mpz_init_set(en, orig);
    

    rsagen(e, p, q, dk, pq);

    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tRSA Key Generation(at Point A)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\nGenerating Encryption Key = " << e;
    cout << "\n\nGenerating Decryption Key = " << dk;
    cout<<"\n\n\n";

    // Create and open a encryptionkey text file
    ofstream rsaen("encryptionkey.txt");
    rsaen << e;               // Write to the file
    rsaen.close();

    // Create and open a decryptionkey text file
    ofstream rsadk("decryptionkey.txt");
    rsadk << e;               // Write to the file
    rsadk.close();

    // Create and open a primemultiple n=p*q text file
    ofstream rsan("primemultiple.txt");
    rsan << pq;               // Write to the file
    rsan.close();

    rsaenc(en, orig, e, pq);              //c = m^e mod n

    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tAES-256 (from Point A to Point B)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\n\nThe Encryption Key to send using AES = " << e;
    cout << "\n\nThe n to send using AES = " << pq;
    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tRSA Encrypt(at Point B)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\nThe Original text = " << orig;
    cout << "\n\nThe Encrypted text = " << en;
    cout<<"\n\n\n";

    // Create and open a RSAencryptedtext text file
    ofstream rsae("RSAencryptedtext.txt");
    rsae << en;               // Write to the file
    rsae.close();

    rsadec(de, en, dk, pq);               //m = c^d mod n

    // Create and open a RSAdecryptedtext text file
    ofstream rsad("RSAdecryptedtext.txt");
    rsad << en;               // Write to the file
    rsad.close();

    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tAES-256 (from Point B to Point E)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\n\nThe Encryption Text to send using AES = " << en;
    cout<<"\n\n\n";
    cout<<"\n---------------------------------------------------------------------";
    cout<<"\n\t\tRSA Decrypt (at Point A)";
    cout<<"\n---------------------------------------------------------------------";
    cout << "\n\nThe Decrypted text = " << de;

    if (mpz_cmp(orig, de) == 0)
    {
        cout<<"\n\n\n";
        cout<<"\n---------------------------------------------------------------------";
        cout<<"\n\tThe Original Text matches the Decrypted Text!!";
        cout<<"\n---------------------------------------------------------------------\n\n\n";
    }

    return 0;
}