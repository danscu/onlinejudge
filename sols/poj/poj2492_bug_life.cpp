/* Disjoint set */
/* poj 2492 */

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

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

/* Data structures */
typedef int Num;
const Num maxn = 2001 * 2;
const Num INF = numeric_limits<Num>::max();

template<int maxn>
struct DisjointSet {
    int parent[maxn];
    int height[maxn];

    void init(int n) {
        FOR(i, 1, n) {
            parent[i] = i;
            height[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        else
            return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x==y)
            return;
        if (height[x] < height[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if (height[x] == height[y])
                ++height[x];
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

DisjointSet<maxn*2> ds;

int main() {
#if BENCH
	freopen("files/poj2492_bug_life.txt","r",stdin);
#endif
    int T;
    int n,m;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
	    printf("Scenario #%d:\n", tc + 1);
	    scanf("%d%d", &n, &m);
	    ds.init(n * 2);
	    bool found = false;
	    REP(i,m) {
		    int a,b;
			scanf("%d %d", &a, &b);
			if (!found) {
			    if (ds.same(a, b)) {
                    printf("Suspicious bugs found!\n\n");
                    found = true;
			    }
			    ds.unite(a, b + n);
			    ds.unite(b, a + n);
			}
		}
	    if (!found) {
	        printf("No suspicious bugs found!\n\n");
	    }
	}
	return 0;
}
