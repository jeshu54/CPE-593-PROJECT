#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<string>

//#include "BigIntegerLibrary.hh" 
    
using namespace std;

int gcd(int a, int b) {
    int tmp;
    for(;;) {
        tmp= a%b;
        if(tmp==0)
        return b;
        a = b;
        b = tmp;
    }
}

double rsaenc(char &val,double e,double p,double q)
{
    double phi= (p-1)*(q-1);                          //calculate phi
    double n=p*q;

    double o=double(val);
    double enck = pow(o,e);                          //encryption key

    double d1 = 1/e;                                 
    double d=  fmod(d1,phi);                        //private key
    double deck = pow(enck ,d);                         //decryption key 
    
    double enc =fmod(enck ,n);                            //encrypt the message
    val=char(enc);
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Encrypted value = "<<enc ;
    cout<<"\n"<<"Encrypted char = "<<val ;
    cout<<"\n--------------------------------------------------------------";

    //cout<<"\npublic key"<<e;
    return enck;
}

void rsadec(char &val,double e,double p,double q,double enck)
{
    double phi= (p-1)*(q-1);                           //calculate phi
    double n=p*q;

    double d1 = 1/e;                                 
    double d=  fmod(d1,phi);                        //private key
    double deck = pow(enck ,d);                         //decryption key 
     
    double dec =fmod(deck ,n);                              //decrypt the message
    char de=char(dec);
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Decrypted value = "<<dec;
    cout<<"\n"<<"Decrypted char = "<<de;
    cout<<"\n--------------------------------------------------------------";
}

double pubkey(double p,double q)
{
    double e=rand()%100;
    double phi= (p-1)*(q-1);                          //calculate phi
    double track;
    
    while(e<phi) {                                    //to check e and phi(n) are coprime.
        track = gcd(e,phi);
        if(track==1)
            break;
        else
            e++;
    }
    return e;                              //public key
}