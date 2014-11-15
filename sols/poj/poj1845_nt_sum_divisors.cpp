/*
 * POJ 1845 SumDiv
 * Find modulus of sum of all factors.
 * 1. Find prime factorization of the number a: a = p1^c1 * p2^c2 * ... * pk^ck
 * 2. a^b = p1^(b*c1) * p2^(b*c2) * ... * pk^(b*ck)
 * 2. sum(all factors in a^b) = prod_k(sum_{j=0)^{b*ck} pk^j)
 *
 * That is, the sum of all factors = product of sums of
 * powers of each factor.
 *
 * Use divide and conquer for sums for geometric series.
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
#define DBG 0 // modify this for enabling/disable debug
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
const Num maxn = 50000010;
const Num INF = numeric_limits<Num>::max();
const int maxPrimes = 10000;
const int MOD = 9901;

Num a,b;
Num pri[maxPrimes], cnt[maxPrimes];

Num pow(Num p, Num n) {
	Num prod = 1;
	while (n) {
		if (n & 1)
			prod = (prod * p) % MOD;
		n >>= 1;
		p = p * p % MOD;
	}
	return prod;
}

Num sum(Num p, Num n) {
	if (n == 0) return 1;
	if (n & 1)
		return ((1 + pow(p, n/2+1)) * sum(p, n/2)) % MOD;
	else
		return ((1 + pow(p, n/2+1)) * sum(p, n/2 - 1) +
				pow(p, n/2)) % MOD;
}

Num solve() {
	// Factorize A
	// Don't need to find primes first -- trying smaller
	// factors first, any factor found is prime
	int i, k;
	for (k = 0, i = 2; i * i <= a; i++)
		if (a % i == 0) {
			pri[k] = i;
			while (a % i == 0) {
				cnt[k]++;
				a /= i;
			}
			k++;
		}

	if (a != 1) {
		pri[k] = a;
		cnt[k++] = 1;
	}

#if DBG
	REP(j,k)
		cout << pri[j] << endl;
#endif

	Num ans = 1;
	for (i = 0; i < k; i++)
		ans = ans * (sum(pri[i], cnt[i] * b) % MOD) % MOD;
	return ans;
}

int main() {
#if BENCH
	freopen("files/poj1845_nt_sum_divisors.txt","r",stdin);
#endif
	scanf("%lld %lld", &a, &b);
	printf("%lld\n", solve());
	return 0;
}
