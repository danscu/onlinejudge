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

typedef long long Num;
const int maxn = 12;

int n;
char word[maxn];

Num C[27][27];

Num binom(int a, int b) {
	Num r = 1;
	if (a - b < b) b = a - b;
	for (int i = a; i > a - b; i--)
		r *= i;
	for (int i = b; i > 1; i--)
		r /= i;
	return r;
}

void makeTable() {
	REP(i,27)
		REP(j,27)
			C[i][j] = binom(i,j);
}

Num getBinom(int a, int b) {
	if (b < 0 || b > a)
		return 0;
	return C[a][b];
}

Num solve() {
	int len = strlen(word);
	Num idx = 0;

	FOR(i,1,len - 1) {
		idx += getBinom(26, i);
		D("full_len %d %d --> %d\n", i, getBinom(26, i), idx);
	}

	int prior = 0;
	REP(i,len) {
		int c = word[i] - 'a';
		if (c < prior)
			return 0; // err
		FOR(j, prior, c - 1) {
			idx += getBinom(26 - j - 1, len - i - 1);
			D("partial j=%d from=%d choose=%d binom=%d --> %d\n",
					j,
					26 - j - 1, len - i - 1,
					getBinom(26 - j - 1, len - i - 1),
					idx);
		}
		prior = c + 1;
	}

	idx++;

	return idx;
}

int main() {
#if BENCH
	freopen("files/poj1850_code.txt","r",stdin);
#endif
	makeTable();
	while (~scanf("%s", word)) {
		printf("%lld\n", solve());
	}
	return 0;
}
