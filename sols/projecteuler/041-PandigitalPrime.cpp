#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRV(x,v) memset(x, v, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

//const int N = 987654321;
//const int N = 10000;
const int N = 7654321;

bitset<N> sv;

void sieve(int limit) {
	int fac = 3, faclim = sqrt(limit);
	for (int i = 4; i <= limit; i+=2)
		sv[i] = true;
	while (fac <= faclim) {
		while (sv[fac] && fac <= faclim)
			fac++;
		if (fac > faclim) break;
		int visit = fac * 2;
		while (visit <= limit) {
			sv[visit] = true;
			visit += fac;
		}
		fac+=2;
	}
}

bool isPrime(int n) {
	int faclim = sqrt(n);
	for (int i = 2; i < faclim; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

bool pandigitalPrime(int n) {
	bool hasDigit[10];
	CLR(hasDigit);
	int c = 0;
	while (n) {
		c++;
		hasDigit[n%10] = true;
		n /= 10;
	}
	return (hasDigit + c + 1 ==
			find(hasDigit + 1, hasDigit + c + 1, false));
}

int main() {
	sieve(N);
	cout << "sieve done" << endl;
	int k = N;
	while (k > 0) {
		if (isPrime(k) && pandigitalPrime(k)) {
			cout << k;
			return 0;
		}
		k--;
	}
	return 0;
}
