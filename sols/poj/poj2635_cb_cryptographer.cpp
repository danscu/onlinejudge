/*
 * POJ 2635 Crytographer
 * Number theory + modulus of large number
 */
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifdef BENCH
#define DBG 1 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;
const Num maxn = 1000006;
const Num maxPrimes = 80000;

const int maxK = 110;
char K[maxK];

Num pri[maxPrimes];
bool p[maxn];
Num L;

// Decompose the number into this base
const int BASE = 1000000000;
int numSz, num[1000];

void makePrimeTable() {
	int i, j;
	memset(p, true, sizeof(p));
	// sieve
	for (i = 2; i * i < maxn; i++)
		if (p[i]) {
			for (j = i << 1; j < maxn; j+= i)
				p[j] = false;
		}
	// primes
	for (j = 0, i = 2; i < maxn; i++)
		if (p[i])
			pri[j++] = i;
}

// Mod operation using the formula
// (A + B) % C = ((A % C) + (B % C)) % C
int mod(Num mod) {
	Num ans = 0;
	for (int i = numSz; i >= 0; i--)
		ans = (ans * BASE + num[i]) % mod;
	return (int) ans;
}

Num solve() {
	CLR(num);
	int i, k;

	// Decompose K in to base BASE
	for (numSz = 0, k = 1, i = strlen(K)-1; i >= 0; i--, k *= 10) {
		if (k == BASE) {
			k = 1; numSz++;
		}
		num[numSz] += k * (K[i] - '0');
	}

	bool divisible = false;
	for (i = 0; pri[i] < L; i++) {
		if (mod(pri[i]) == 0) {
			divisible = true;
			break;
		}
	}

	if (divisible)
		printf("BAD %d\n", pri[i]);
	else
		printf("GOOD\n");
	return 0;
}

int main() {
#if BENCH
	freopen("files/poj2635_cryptographer.txt","r",stdin);
#endif
	makePrimeTable();
	while (~scanf("%s %d", K, &L) && L) {
		solve();
	}
	return 0;
}
