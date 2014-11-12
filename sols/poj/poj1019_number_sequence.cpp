/*
 * POJ 1019 Number sequence
 * Combinatorics
 * Find digit at ith position of a long sequence
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

#define D(...) do { if (DBG) fprintf(stdout, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;

Num n;

#if DBG
const int maxL = 20;
#else
const int maxL = 31267;
#endif

Num L[maxL+1];

void makeTable() {
	Num len = 0;
	Num tlen = 0;
	int wlen = 0;
	Num wLevel = 1;

	FOR(i,1,maxL) {
		if (i == wLevel) {
			wLevel *= 10;
			wlen++;
		}
		len += wlen;
		tlen += len;
		L[i] = tlen;
		D("L[%d] = %lld\n", i, L[i]);
	}
}

char solve() {
	D("n=%d\n",n);
	int nseq = 1;
	while (nseq <= maxL && n > L[nseq])
		nseq++;
	// L[nseq] contains the nth char
	D("seq# = %d, remaining n = %d\n", nseq, L[nseq] - n);
	n = n - L[nseq-1];
	Num i, wLevel = 1;
	int wlen = 0;
	for (i = 1;; i++) {
		if (i == wLevel) {
			wLevel *= 10;
			wlen++;
		}
		if (n <= wlen)
			break;
		n -= wlen;
	}
	D("number = %d\n", i);
	// i is the number
	ostringstream oss;
	oss << i;
	return oss.str()[n-1];
}

int main() {
#if BENCH
	freopen("files/poj1019_number_sequence.txt","r",stdin);
#endif
	int T;
	makeTable();
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		printf("%c\n", solve());
	}
	return 0;
}
