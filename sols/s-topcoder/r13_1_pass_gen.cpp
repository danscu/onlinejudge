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

typedef unsigned long long Num;
const int maxn = 4010;
const int maxk = 4010;
const int maxm = 2010;
const Num INF = numeric_limits<Num>::max();
const Num MOD = 1000000007ll;

int n, k, m;

int main() {
#if BENCH
    freopen("files/1_rand.txt","w",stdout);
#endif
	int T = 10;
	int sym[maxk];

	printf("%d\n", T);
	for (int tc = 0; tc < T; tc++) {
//	    n = maxn - rand() % 100;
//	    k = maxk - rand() % 100;
//	    m = maxm - rand() % 100;

	    // G2
	    n = 100;
	    k = 6;
	    m = 20;

	    // G3
//	    n = 1000;
//	    k = 200;
//	    m = 20;
		printf("%d %d %d\n", n, k, m);
		REP(i,m) {
		    int l = 4;
			printf("%d ", l);
			REP(j,l)
			    printf("%d ", rand() % k);
			printf("\n");
		}
	}
	return 0;
}
