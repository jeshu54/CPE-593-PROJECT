#include<iostream>
using namespace std;


void printsieve(int *p) {

// first mark all the odd number's prime
	for(uint64_t i = 3; i <= 10000 ; i+=2){
		p[i] =1;
	}

	// Sieve
	for(uint64_t i=3; i<= 10000; i+=2) {
		if(p[i]==1) {
			for(uint64_t j = i*i; j<= 10000; j=j+i) {
				p[j] =0;
			}
		}
	}
// special cases
	p[2] = 1;
	p[1] = p[0] = 0;

}




int main() {

int n;
cin >> n;
int p[10005] = {0};
printsieve(p);

for (int i=0; i <= n; i++) {
	if(p[i]==1){
	cout << i << " ";   
}
}

return 0;

}