/*
 * POJ 3252 Round Numbers
 * For numbers in a range [a,b], find how many whose 0s >= 1s in binary form.
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

typedef unsigned long long Num;

#if DBG
const int maxn = 12;
#else
const int maxn = 128;
#endif

int digits;
Num from, to;
Num table[maxn + 1][2 * maxn + 1];		// round number with n bin digits (including 0)

Num getNum(int width, int zeroNum) {
	// Find round numbers with k digits, k <= n
	return table[width][digits + zeroNum];
}

Num binomial(int n, int k) {
	Num r = 1;

	if (n - k < k)
		k = n - k;

	FOR(i,n-k+1,n)
		r *= i;

	FOR(i,1,k)
		r /= i;

	return r;
}

void makeTable(int digits) {
	// b = bits, z = priorZeros
	FOR(b,0,digits) {
		int priorDigs = digits - b;
		// zeros in prior digs
		FOR(z,-priorDigs,priorDigs) {
			Num r = 0;
			// i = number of zeros in new section
			for (int i = b; i + z >= digits - (i + z) && i + z > 0; i--)
				r += binomial(b, i);
			table[b][digits + z] = r;
		}
	}

#if DBG
	FOR(b,1,digits) {
		cout << b << " bits: ";
		FOR(z,-digits,digits)
			cout << "(" << z << ")" << table[b][digits+z] << "\t";
		cout << endl;
	}
#endif
}

Num countPrior(int start, int zeroNum) {
	// make sure zeroNum + new zeros - new ones >= 0
	Num res = getNum(start, zeroNum);

	// first one
	if (start == digits - 1)
		res--;

	return res;
}

Num findRoundNumbers(Num n) {
	// Convert to bin
	char bin[maxn];
	Num tmp = n;
	int i = 0;
	while (tmp) {
		bin[i++] = tmp & 1;
		tmp >>= 1;
	}

	Num priors = 0;

	// Split the number
	int zeroNum = 0;
	for (int j = i - 1; j >= 0; j--) {
		if (bin[j] == 1) {
			priors += countPrior(j, zeroNum);
			zeroNum--;
		} else {
			zeroNum++;
		}
	}

	return priors;
}

Num solve() {
	// Find number of bin digits
	digits = 0;
	Num tmp = to;
	while (tmp) {
		digits++;
		tmp >>= 1;
	}

	// Make table
	makeTable(digits);

	return findRoundNumbers(to) - findRoundNumbers(from - 1);
}

int main() {
#if BENCH
	freopen("files/poj3252_round_numbers.txt","r",stdin);
#endif
	while (~scanf("%llu%llu", &from, &to)) {
		printf("%llu\n", solve());
	}
	return 0;
}
