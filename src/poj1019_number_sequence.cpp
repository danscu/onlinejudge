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

#define D(...) do { if (DBG) fprintf(stdout, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long Num;

Num n;

const int maxL = 9;

// S[D] Total length of numbers with 1 thru D+1 digits
// S[D] = 9*10^D*(D+1)
Num S[maxL];

// Length of cumulative string section with D+1 digits
Num L[maxL];

void makeTable() {
	Num tenPow = 1;
	FOR(i,0,maxL-1) {
		// For S
		Num s = 9 * tenPow * (i + 1);
		S[i] = s;

		// For L
		L[i] = ((i + 1) + (i + 1) * 9 * tenPow) * (9 * tenPow) / 2;
		D("S[%d] = %lld\tL[%d] = %lld\n", i, S[i], i, L[i]);

		tenPow *= 10;
	}
}

Num solve() {
	makeTable();

	int d = 0;
	int remain = n;

	D("n=%d\n", n);

	// Determine D
	while (remain >= L[d]) {
		remain -= L[d];
		d++;
	}

	D("d=%d remain=%d\n", d, remain);

	// Digits from 10^d

	return 0;
}

int main() {
#if BENCH
	freopen("files/poj1019_number_sequence.txt","r",stdin);
#endif
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		printf("%d\n", solve());
	}
	return 0;
}
