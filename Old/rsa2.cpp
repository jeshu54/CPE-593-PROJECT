#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<string>
#include"Diffie_hellmanRSA.h"
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

string rsaenc(string a,double e,double p,double q)
{
    double phi= (p-1)*(q-1);                          //calculate phi
    double n=p*q;
    double o,t,m;
    int c=0;
    for(int i=0;i<a.length();i++)
    {
        t=int(a[i]);
        cout<<t<<" ";
        c=0;
        for(int j=t;j>0;j/=10)
        c++;
        m=pow(10,c);
        o=o*m+t;
    }
    cout<<"\no ="<<o<<endl;
    long double enck = pow(o,e);                          //encryption key

    double d1 = 1/e;                                 
    double d=  fmod(d1,phi);                        //private key

    double deck = pow(enck ,d);                         //decryption key 
    
    double enc =fmod(enck ,n);                            //encrypt the message
    
    string en;
   for(int i=a.length();i>0;i--)
    {
        en[i]=fmod(enc,10);
        enc/=10;
    }
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Encrypted value = "<<enc ;
    cout<<"\n"<<"Encrypted char = "<<en ;
    cout<<"\n--------------------------------------------------------------";
        
    double dec =fmod(deck ,n);                              //decrypt the message
    char de=char(dec);
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Decrypted value = "<<dec;
    cout<<"\n"<<"Decrypted char = "<<de;
    cout<<"\n--------------------------------------------------------------";
    //cout<<"\npublic key"<<e;
    return en;
}

string rsadec(string a,double e,double p,double q)
{
    double enck;
    for(int i=0;i<a.length();i++)
    {
        enck=int(a[i]);
    if(i<a.length()-1)
        enck*=10;
    }
    double phi= (p-1)*(q-1);                           //calculate phi
    double n=p*q;

    double d1 = 1/e;                                 
    double d=  fmod(d1,phi);                        //private key
    double deck = pow(enck ,d);                         //decryption key 
     
    double dec =fmod(deck ,n);                              //decrypt the message
    string de;
   for(int i=a.length();i>0;i--)
    {
        de[i]=fmod(dec,10);
        dec/=10;
    }
    
    cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
    cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
    cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
    cout<<"\n--------------------------------------------------------------";
    cout<<"\n"<<"Decrypted value = "<<dec;
    cout<<"\n"<<"Decrypted char = "<<de;
    cout<<"\n--------------------------------------------------------------";
    return de;
}

double pubkey(double p,double q)
{
    double e=rand()%10;
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
int main() {
  /* BigInteger a = pow(2,7830457);
   cout<<a;
   */
    double p = 31, q = 29;
    string orig,de,en;
    double e= pubkey(p,q);
    cout<<"Enter the message : ";
    //cin>>orig;
    getline(cin,orig);
    de=en=orig;
    //for(int i=0;i<orig.length();i++)
    //en[i]=rsaenc(orig[i],e,p,q);
    en=rsaenc(orig,e,p,q);
    //for(int i=0;i<orig.length();i++)
    //de[i]=rsadec(en[i],e,p,q);
    cout<<endl<<en;
    //cout<<endl<<de;
    return 0;
}