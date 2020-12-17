#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <gmp.h>
#include "PrimeGenerator.h"

using namespace std;

void gcd(mpz_t result, mpz_t a, mpz_t b)
{
    mpz_t aTmp, bTmp;
    mpz_init_set(aTmp, a);
    mpz_init_set(bTmp, b);

    //cout << result << endl;
    mpz_t tmp;
    mpz_init(tmp);
    for (;;)
    {
        
        //cout << "a " << aTmp << endl;
        //cout << "b " << bTmp << endl;
        mpz_mod(tmp, aTmp, bTmp);
        //cout << "tmp " << tmp << endl;
        if (mpz_cmp_ui(tmp, 0) == 0){
            mpz_set(result, bTmp);
            return;
        }
        mpz_set(aTmp, bTmp);
        mpz_set(bTmp, tmp);
    }
}

    void rsaenc(mpz_t en, mpz_t orig,mpz_t e,mpz_t n)
    {
    mpz_powm(en, orig, e, n);              //c = m^e mod n
    }
    
    void rsadec(mpz_t de, mpz_t en,mpz_t dk,mpz_t n)
    {
        mpz_powm(de, en, dk, n);               //m = c^d mod n
    }
/*
void rsadec(mpz_t enck, mpz_t d,mpz_t n)
{
    mpz_t phi, n;
    mpz_init(phi);
    mpz_init(n);

    // set p - 1 and q - 1
    mpz_t ptmp, qtmp;
    mpz_init(ptmp);
    mpz_init(qtmp);
    mpz_sub_ui(ptmp, p, 1);
    mpz_sub_ui(qtmp, q, 1);

    // calculate phi
    mpz_mul(ptmp, ptmp, qtmp);
    mpz_set(phi, ptmp);

    mpz_mul(n, p, q);

    //private key
    mpz_t d, k,pktmp,one,i,f,mt;
    mpz_init(d);
    mpz_init(k);
    mpz_init(mt);
    mpz_init(pktmp);
    mpz_init_set_ui(one, 1);
    mpz_init_set_ui(i, 0);
    mpz_init_set_ui(f, 0);
    //cout<<"\nf = "<<f<<endl;
    for(;mpz_cmp_ui(f,1)!=0;mpz_add_ui(i, i, 1))
    {
        // phi (p-1 * q-1)
        // ((i * phi) + 1) % e == 0
        
        mpz_mul(pktmp, i, phi);
        //cout<<"Step 1 works\n";
        mpz_add_ui(k, pktmp,1);
        //cout<<"Step 2 works\n";
        mpz_mod(mt,k, e);
        if(mpz_cmp_ui(mt,0) == 0)
        {
        //    cout<<"Step if works\n";
        mpz_add_ui(f, f, 1);
        }
        //cout << e << endl;
    }

    mpz_div(d, k, e);

    mpz_t deck;
    mpz_init(deck);*/
    //decryption key
    //mpz_pow_ui(deck, enck, mpz_get_d(d));
    //cout<<"\ndeck = "<<deck<<"\nc^d = "<<enck<<"\n ^ \n"<<d;
    //mpz_t dec;
    //mpz_init(dec);
    //mpz_mod(dec, deck, n);
/*
    mpz_t deck;
    mpz_init(deck);
    mpz_powm(deck, enck, d, n);
    mpz_set(enck, deck);
    //cout<<"\ndeck = "<<deck<<"\nc^d = "<<enck<<"\n ^ \n"<<d;

    
    cout << "\n\n"
         << "p = " << p << "\nq = " << q;
    cout << "\n\n"
         << "n=p*q = " << n << "\n\nphi = " << phi;
    cout << "\n\n"
         << "e = " << e << "\n\nd = " << d;
    cout<<"\nc "<<enck;
    cout << "\n--------------------------------------------------------------";
    cout << "\n\n"
         << "Decrypted value = " << deck;
    cout << "\n\n"
         << "Decrypted char = " << val;
    cout << "\n--------------------------------------------------------------";
    
}
*/

void rsagen(mpz_t e, mpz_t p, mpz_t q,mpz_t d,mpz_t pq)
{
    // declare variables
    mpz_t enck, phi, n,track;
    gmp_randstate_t randState;
    gmp_randinit_default(randState);

    mpz_init(e);
    mpz_init(phi);
    mpz_init(track);
    mpz_init(n);
    // set e to rand
    mpz_urandomb(e, randState, 10);
    //cout << result << endl;
    
    // set p - 1 and q - 1
    mpz_t ptmp, qtmp;
    mpz_init(ptmp);
    mpz_init(qtmp);
    mpz_sub_ui(ptmp, p, 1);
    mpz_sub_ui(qtmp, q, 1);

    // calculate phi
    mpz_mul(ptmp, ptmp, qtmp);
    mpz_set(phi, ptmp);
    

    //cout << result << endl;
    //cout << phi << endl;
    //int count = 0;
    while (mpz_cmp(e, phi) < 0)
    {
        //cout << "count = " << ++count << endl;
        //cout << result << endl;
        //to check e and phi(n) are coprime.
        gcd(track, e, phi);
        //cout << "track = " << track << endl;
        if (mpz_cmp_ui(track, 1) == 0)
        {
            //cout << "done" << endl;
            break;
        }
        else
        {
            //cout << "Increment" << endl;
            mpz_add_ui(e, e, 1);
            //cout << "res = " << result << endl;
            //cout << "phi = " << phi << endl;
        }
        //cout << "cmp " <<  mpz_cmp(result, phi) << endl;
        
        //cout << result << endl;
    }

    mpz_mul(n, p, q);
    mpz_set(pq,n);
    /* setting o to the double char value
    mpz_t o;
    mpz_init(o);
    mpz_set(o, val);
    */
    // encryption key
    mpz_init(enck);
    // NOTE: Cannot raise to mpz_t power (too big anyway)
    
    //private key
    mpz_t k,pktmp,one,i,f,mt;
    mpz_init(k);
    mpz_init(mt);
    mpz_init(pktmp);
    mpz_init_set_ui(one, 1);
    mpz_init_set_ui(i, 0);
    mpz_init_set_ui(f, 0);
    //cout<<"\nf = "<<f<<endl;
    for(;mpz_cmp_ui(f,1)!=0/*&&mpz_cmp_ui(i,1000)!=0*/;mpz_add_ui(i, i, 1))
    {
        mpz_mul(pktmp, i, phi);
        //cout<<"Step 1 works\n";
        mpz_add_ui(k, pktmp,1);
        //cout<<"Step 2 works\n";
        mpz_mod(mt,k, e);
        if(mpz_cmp_ui(mt,0) == 0)
        {
        //    cout<<"Step if works\n";
        mpz_add_ui(f, f, 1);
        }
    }
    
    mpz_div(d, k, e);

    //cout<<"c = "<<enck<<endl;
    //decryption key
    //mpz_pow_ui(deck, enck, mpz_get_d(d));
    //cout<<"c^d = "<<deck<<endl;
    //encrypt the message
    // ?????
    //mpz_t enc;
    //mpz_init(enc);
    
    //mpz_pow_ui(enck, o, mpz_get_ui(e));
    //mpz_mod(enc, enck, n);

    //mpz_powm(enck, o, e, n);
    //mpz_set(val, enck);

    /*
    cout << "\n"
         << "p = " << p << "\nq = " << q;
    cout << "\n"
         << "n=p*q = " << n << "\nphi = " << phi;
    cout << "\n"
         << "e = " << e << "\nd = " << d;
    cout << "\n--------------------------------------------------------------";
    cout << "\n"
         << "Encrypted value = " << enc;
    cout << "\n"
         << "Encrypted char = " << val;
    cout << "\n--------------------------------------------------------------";
    */
}

/*
void pubkey(mpz_t &e, mpz_t p, mpz_t q)
{
    // random state
    gmp_randstate_t randState;
    gmp_randinit_default(randState);

    // declare variables
    mpz_t phi, track;
    mpz_init(e);
    mpz_init(phi);
    mpz_init(track);

    // set e to rand
    mpz_urandomb(e, randState, 10);
    //cout << result << endl;
    
    // set p - 1 and q - 1
    mpz_t ptmp, qtmp;
    mpz_init(ptmp);
    mpz_init(qtmp);
    mpz_sub_ui(ptmp, p, 1);
    mpz_sub_ui(qtmp, q, 1);

    // calculate phi
    mpz_mul(ptmp, ptmp, qtmp);
    mpz_set(phi, ptmp);
    

    //cout << result << endl;
    //cout << phi << endl;
    //int count = 0;
    while (mpz_cmp(e, phi) < 0)
    {
        //cout << "count = " << ++count << endl;
        //cout << result << endl;
        //to check e and phi(n) are coprime.
        gcd(track, e, phi);
        //cout << "track = " << track << endl;
        if (mpz_cmp_ui(track, 1) == 0)
        {
            //cout << "done" << endl;
            break;
        }
        else
        {
            //cout << "Increment" << endl;
            mpz_add_ui(e, e, 1);
            //cout << "res = " << result << endl;
            //cout << "phi = " << phi << endl;
        }
        //cout << "cmp " <<  mpz_cmp(result, phi) << endl;
        
        //cout << result << endl;
    }
    // returns public key in 'result' variable
}

int main()
{
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);
    PrimeGenerator* pg = new PrimeGenerator();
    pg->setNumBits(600);
    pg->getPrimeNumber(p);
    pg->setNumBits(700);
    pg->getPrimeNumber(q);

    string orig, de, en;
    mpz_t e;
    mpz_init(e);

    pubkey(e, p, q);
    cout << "Enter the message : ";
    getline(cin, orig);
    en = orig;

    mpz_t k[orig.length()];
    //mpz_init(k);

    for (int i = 0; i < orig.length(); i++)
        rsaenc(k[i], en[i], e, p, q);
    de = en;
    for (int i = 0; i < orig.length(); i++)
        rsadec(de[i], e, p, q, k[i]);
    cout << "The encrypted text = " << en<<endl;
    cout << "\nThe decrypted text = " << de;
    return 0;
}*/