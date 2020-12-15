/**
 * Karan Modi, Vincent Loud, Avro
 * Prime generator, RSA, and Diffie-Helman
 * Compile with: g++ -Wall .\PrimeGenerator.cpp  .\main.cpp -lgmp -lgmpxx 
 * */

#include "PrimeGenerator.h";
#include "Diffie_hellmanRSA.h";
#include "RSA.h";
#include <stdlib.h>
#include <time.h>
#include <iostream>

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

    mpz_t result;
    mpz_init(result);
    if (secretkeygenerator(result, n, randG, pKeyA, pKeyB, keyGenPrime))
    {
        gmp_printf("Secret Key: %Zd\n", result);
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
    mpz_t e,orig, de, en;
    mpz_init(e);
    mpz_init(orig);

    pubkey(e, p, q);
    //cout << "Enter the message : ";
    //getline(cin, orig);

    pg->setNumBits(500);
    pg->getRandom(orig);
    mpz_init_set(en, orig);
    

    rsaenc(en, e, p, q);
    


    mpz_init_set(de, en);
    rsadec(de, e, p, q);
    cout << "\nThe Original text = " << orig;
    cout << "\nThe Encrypted text = " << en;
    cout << "\nThe Decrypted text = " << de;

    if (mpz_cmp(orig, de) == 0)
    {
        cout << "\n Everything Works!!";
    }

    return 0;
}