/* kmp + stepping fail func */
/* poj 2406 */

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
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 1000007;

template<int maxw>
struct KMP {
	int wlen;
	int fail[maxw];

	// Pre-process the pattern
	// next[i]: Let pre[i] denote the prefix of pattern of length i
	//          fail[i] is -1 + the length of the longest suffix ending at i which is also a prefix of pre[i].
	void buildFailureFunction(char *w) {
		int i, j = -1;
		wlen = strlen(w);
		fail[0] = -1;
		for (i = 1; i <= wlen; i++) {
			while (j > -1 && w[j + 1] != w[i])
				j = fail[j];
			if (w[j + 1] == w[i]) j++;
			fail[i] = j;
		}
	}
};

char w[maxn];
KMP<maxn> kmp;

int main() {
#if BENCH
	freopen("files/poj2406_kmp_power_strings.txt","r",stdin);
#endif
	while (~scanf("%s", w) && strcmp(w, ".")) {
		kmp.buildFailureFunction(w);
		// stepping the fail func
		int l = kmp.wlen - (kmp.fail[kmp.wlen - 1] + 1); // remaining part

		/* Longest prepostfix is |P| = 1 + kmap.fail[kmp.wlen - 1] by KMP
		   Case 1: |P| < |W|/2
		        l = |W| - |P| > |W|/2, so kmp.wlen % l != 0. Report 1. Correct.
		   Case 2: |P| >= |W| / 2
		        l < |W| / 2, W[1..l] is also a prepostfix. So only need to check
		        if its power is the full string
		*/
		if (kmp.wlen % l)
			printf("1\n");
		else
			printf("%d\n", kmp.wlen / l);
	}
	return 0;
}
