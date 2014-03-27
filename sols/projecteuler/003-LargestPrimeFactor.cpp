#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRV(x,v) memset(x, v, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;
const Num N = 600851475143;
const Num Nr = 775146; // sqrt(N);

bool sieve[Nr+1];

int main() {
	CLRV(sieve, 1);
	Num factor = 2;
	Num largest = factor;

	// Find factors
	while (factor <= Nr) {
		while (factor <= Nr && !sieve[factor])
			factor++;
		if (factor <= Nr) {
			largest = factor;
			Num test = factor * 2;
			while (test <= Nr) {
				sieve[test] = 0;
				test += factor;
			}
		}
		if (factor == 2)
			factor++;
		else
			factor+=2;
	}

	// Search for factors
	while (largest > 0) {
		if (N % largest == 0) {
			cout << largest;
			break;
		}
		while (!sieve[--largest]) ;
	}
	if (!largest)
		cout << "Not found" << endl;
	return 0;
}
