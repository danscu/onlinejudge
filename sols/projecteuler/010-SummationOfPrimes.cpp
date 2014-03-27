/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a2 + b2 = c2
For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

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

const Num Nr = 2000000;
//const Num Nr = 10;

bool sieve[Nr+1];

int main() {
	CLRV(sieve, 1);
	Num factor = 2;

	// Find factors
	while (factor <= Nr) {
		while (factor <= Nr && !sieve[factor])
			factor++;
		if (factor <= Nr) {
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

	Num ans = 0;
	FOR(i,2,Nr)
		ans += sieve[i] ? i : 0;
	cout << ans << endl;
	return 0;
}
