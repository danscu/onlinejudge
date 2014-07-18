/* Aho-Corasick */
/* hdu 2222 */

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

#define D(fmt,...) do { if (DBG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRV(x, v) memset(x, v, sizeof x);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 1000007;
const Num INF = numeric_limits<Num>::max();

template<int maxn, int maxm>
struct ACAuto {
	int next[maxn][maxm], fail[maxn], data[maxn], size;
	int que[maxn], head, tail;

	int code(char c) {
		return c - 'a';
	}

	void clear(int x) {
		CLRV(next[x], -1);
		fail[x] = -1; data[x] = 0;
	}

	void init() {
		clear(0);
		size = 1;
	}

	void insert(const char *str) {
		int p = 0, idx;
		while (*str) {
			idx = code(*str);
			if (next[p][idx] == -1) {
				clear(size);
				next[p][idx] = size++;
			}
			p = next[p][idx];
			str++;
		}
		data[p]++;
	}

	void buildAC() {
		int p, pp, fp, fpp;
		head = tail = 0;
		que[tail++] = 0;
		while (head < tail) {
			p = que[head++];
			for (int i = 0; i < maxm; i++) {
				if ((pp = next[p][i]) != -1) {
					for (fp = fail[p]; fp != -1; fp = fail[fp]) {
						if ((fpp = next[fp][i]) != -1) {
							fail[pp] = fpp;
							break;
						}
					}
					if (fp == -1) fail[pp] = 0;
					que[tail++] = pp;
				} else {    // next?
					if (p == 0) next[p][i] = 0;
					else next[p][i] = next[fail[p]][i];
				}
			}
		}
	}

	int query(char *str) {
		int p = 0, ret = 0, idx, pp;
		while (*str) {
			idx = code(*str);
			p = next[p][idx];
			for (pp = p; pp != -1 && data[pp] != -1; pp = fail[pp]) {
				ret += data[pp];
				data[pp] = -1;
			}
			++str;
		}
		return ret;
	}
};

ACAuto<maxn,26> ac;
char str[maxn];

int main() {
#if BENCH
	freopen("files/hdu2222_ac_keyword_search.txt","r",stdin);
#endif
	int T, n;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		ac.init();
		REP(i,n) {
			scanf("%s", str);
			ac.insert(str);
		}
		ac.buildAC();
		scanf("%s", str);
		printf("%d\n", ac.query(str));
	}
	return 0;
}
