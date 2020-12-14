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

long rsaenc(char &val,long e,long p,long q)
{
    cout<<int(val)<<endl;
    long phi= (p-1)*(q-1);                          //calculate phi
    long n=p*q;

    long o=long(val);
    long enck = pow(o,e);                          //encryption key
    cout<<"enck ="<<enck<<" = "<<o<<" ^ "<<e<<" mod "<<n<<endl;                            
     long d,k,f=0;
    for(int i=0;f!=1;i++)
    {
        k=(1+i*phi);
        if(fmod(k,e)==0)
        f=1;
    }
    d=k/e;                                     //private key
    long deck = pow(enck ,d);                         //decryption key 
    
    long enc =fmod(enck ,n);                            //encrypt the message
    val=char(enc);
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Encrypted value = "<<enc ;
    cout<<"\n"<<"Encrypted char = "<<val ;
    cout<<"\n--------------------------------------------------------------";

    //cout<<"\npublic key"<<e;
    return enc;
}

void rsadec(char &val,long e,long p,long q,long enck)
{
    cout<<"val = "<<val<<endl;
    
    long phi= (p-1)*(q-1);                           //calculate phi
    long n=p*q;
    
    long d,k,f=0;
    for(int i=0;f!=1;i++)
    {
        k=(1+i*phi);
        if(fmod(k,e)==0)
        f=1;
    }
    d=k/e;
    cout<<d;                            //private key
    long deck = pow(enck ,d);                         //decryption key 
     
    long dec =fmod(deck ,n);                              //decrypt the message
    val=char(dec);
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Decrypted value = "<<dec;
    cout<<"\n"<<"Decrypted char = "<<val;
    cout<<"\n--------------------------------------------------------------";
}

long pubkey(long p,long q)
{
    long e=rand()%10;
    long phi= (p-1)*(q-1);                          //calculate phi
    long track;
    
    while(e<phi) {                                    //to check e and phi(n) are coprime.
        track = gcd(e,phi);                 
        if(track==1)
            break;
        else
            e++;
    }
    return e;                              //public key
}
int main() {
  /* BigInteger a = pow(2,7830457);
   cout<<a;
   */
    long p = 61, q = 53;
    string orig,de,en;
    long e= pubkey(p,q);
    cout<<"Enter the message : ";
    //cin>>orig;
    getline(cin,orig);
    en=orig;
    long k[orig.length()];
    for(int i=0;i<orig.length();i++)
    k[i]=rsaenc(en[i],e,p,q);
    de=en;
    for(int i=0;i<orig.length();i++)
    {
    cout<<"\nen["<<i<<"] = "<<int(en[i])<<"  k["<<i<<"] = "<<k[i]<<endl;
    rsadec(de[i],e,p,q,k[i]);
    }
    cout<<"\nThe encrypted text = "<<en;
    cout<<"\nThe decrypted text = "<<de;
    return 0;
}