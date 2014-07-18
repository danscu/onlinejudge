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
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 1000007;
const int maxw = 10005;

template<int maxw>
struct KMP {
	int wlen, tlen;
	char fail[maxw];
	char *w, *t;

	// Pre-process the pattern
	// next[i]: Let pre[i] denote the prefix of pattern of length i
	//          fail[i] is -1 + the length of the longest suffix ending at i which is also a prefix of pre[i].
	void buildFailureFunction() {
		int i, j = -1;
		fail[0] = -1;
		for (i = 1; i <= wlen; i++) {
			while (j > -1 && w[j + 1] != w[i])
				j = fail[j];
			if (w[j + 1] == w[i]) j++;
			fail[i] = j;
		}
	}

	int kmp(char *w, char *t) {
		int cnt = 0;
		this->w = w, this->t = t;
		wlen = strlen(w);
		tlen = strlen(t);

		int i, j = -1;
		buildFailureFunction();

		for (i = 0; i < tlen; i++) {
			while (j != -1 && w[j + 1] != t[i])
				j = fail[j];
			if (w[j+1] == t[i])
				j++;
			if (j == wlen - 1)
				cnt++;
		}

		return cnt;
	}
};

KMP<maxw> kmp;

char txt[maxn];
char w[maxw];

int main() {
	int T;
#if BENCH
	freopen("files/poj3461_kmp_oulipo.txt","r",stdin);
#endif

	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%s%s", w, txt);
		printf("%d\n", kmp.kmp(w, txt));
	}
	return 0;
}
