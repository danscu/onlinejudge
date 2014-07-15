/* Disjoint set */
/* poj 1611 */

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
const Num maxn = 30000;
const Num INF = numeric_limits<Num>::max();

template<int maxn>
struct DisjointSet {
    int count;
    int parent[maxn+1];
    int height[maxn+1];
    int size[maxn+1];

    void init(int n) {
        FOR(i, 0, n) { /* check range */
            parent[i] = i;
            height[i] = 0;
            size[i] = 1;
        }
        count = n;
    }

    int findSet(int x) {
        if (parent[x] == x)
            return x;
        else
            return parent[x] = findSet(parent[x]);
    }

    void unite(int x, int y) {
        x = findSet(x);
        y = findSet(y);
        if (x==y)
            return;
        if (height[x] < height[y]) {
            parent[x] = y;
            size[y] += size[x];
        } else {
            parent[y] = x;
            size[x] += size[y];
            if (height[x] == height[y])
                ++height[x];
        }
        count--;
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }
};

DisjointSet<maxn> ds;

int main() {
#if BENCH
    freopen("files/poj1611_djs_sars.txt","r",stdin);
#endif
    int tc = 0;
    int n,m;
    while (scanf("%d%d", &n, &m) == 2 && n + m) {
        ds.init(n);
        REP(i,m) {
            int gsize, firstInGroup;
            scanf("%d", &gsize);
            if (!gsize) continue;
            scanf("%d", &firstInGroup);
            REP(j,gsize-1) {
                int a;
                scanf("%d", &a);
                ds.unite(a, firstInGroup);
            }
        }
        printf("%d\n", ds.size[ds.findSet(0)]);
    }
    return 0;
}
