/*
a massive non-Mersenne prime which contains 2,357,207 digits: 28433×2^7830457+1.
Find the last ten digits of this prime number.
*/

#include <cstdio>
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

int main() {
	const Num MOD = 10000000000;

	Num ans = 28433;
	REP(i,7830457)
		ans = (ans * 2) % MOD;
	ans = (ans + 1) % MOD;

	cout << ans << endl;

	return 0;
}
