/* Disjoint set */
/* poj 2524 */

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
const Num maxn = 50000;
const Num INF = numeric_limits<Num>::max();

template<int maxn>
struct DisjointSet {
    int count;
    int parent[maxn];
    int height[maxn];

    void init(int n) {
        FOR(i, 1, n) {
            parent[i] = i;
            height[i] = 0;
        }
        count = n;
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
        count--;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

DisjointSet<maxn> ds;

int main() {
#if BENCH
    freopen("files/poj2524_djs_religions.txt","r",stdin);
#endif
    int tc = 0;
    int n,m;
    while (~scanf("%d%d", &n, &m) && n) {
        ds.init(n);
        REP(i,m) {
            int a,b;
            scanf("%d %d", &a, &b);
            ds.unite(a, b);
        }
        printf("Case %d: %d\n", ++tc, ds.count);
    }
    return 0;
}
