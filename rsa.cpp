#include<iostream>
#include<math.h>
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

int main() {
   double o = 9;
   cout<<"Enter the message(in number) : ";
   cin>>o;
   double p = 47, q = 29;
   double n=p*q;

   double track;
   double phi= (p-1)*(q-1);                           //calculate phi
   
   double e=27;                                       //public key

   while(e<phi) {                                    //to check e and phi(n) are coprime.
      track = gcd(e,phi);
      if(track==1)
         break;
      else
         e++;
   }

   double d1 = 1/e;                                 //private key
   double d=  fmod(d1,phi);

   double enc = pow(o,e);                           //encryption key
   double dec = pow(enc ,d);                        //decryption key                     
   
   enc =fmod(enc ,n);                               //encrypt the message
   dec =fmod(dec ,n);                               //decrypt the message

   cout<<"\n"<<"p = "<<p<<"\t\tq = "<<q;
   cout<<"\n"<<"n=p*q = "<<n<<"\tphi = "<<phi;
   cout<<"\n"<<"e = "<<e<<"\t\td = "<<d;
   cout<<"\n--------------------------------------------------------------";
   cout<<"\n"<<"Encrypted value = "<<enc ;
   cout<<"\n"<<"Decrypted value = "<<dec;
   cout<<"\n--------------------------------------------------------------";
    return 0;
}