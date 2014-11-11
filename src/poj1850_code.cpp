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

typedef int Num;
const int maxn = 12;

int n;
char word[maxn];

Num fullLen(int l, int range) {
	Num res = 1;
	int r = range;

	// not possible
	if (range < l)
		return 0;

	FOR(i,1,l)
		res *= r-i+1;

	return res;
}

Num partial(int l, int firstRange, int range) {
	Num res = 0;
	FOR(i,0,firstRange) {
		int sub = 1;
		int r = range - i - 1;
		FOR(j,2,l)
			sub *= r--;
		res += sub;
	}

	return res;
}

Num solve() {
	int len = strlen(word);
	Num idx = 0;

	FOR(i,1,len - 1) {
		idx += fullLen(i, 26);
		D("full_len %d %d --> %d\n", i, fullLen(i, 26), idx);
	}

	int prior = 0;
	REP(i,len) {
		int c = word[i] - 'a';
		if (i >= 1 && c <= prior)
			return 0; // error
		idx += partial(len - i, c - 1 - prior,
				26 - c + 1 - prior);

		D("partial %d %d %d --> %d\n", len -i,
				c - 1 - prior,
				26 - c + 1 - prior,
				partial(len - i, c - 1 - prior,
								26 - c + 1 - prior),
								idx);

		prior = c;
	}

	return idx;
}

int main() {
#if BENCH
	freopen("files/poj1850_code.txt","r",stdin);
#endif
	while (~scanf("%s", word)) {
		printf("%d\n", solve());
	}
	return 0;
}
