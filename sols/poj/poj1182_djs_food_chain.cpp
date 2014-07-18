/* LCA tarjan, weighted LCA */
/* poj 1182 */

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
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

/* Data structures */
typedef int Num;
#if !DBG
const Num maxn = 50010;
#else
const Num maxn = 500;
#endif
const Num INF = numeric_limits<Num>::max();

/* Weighted disjoint set */
template<int maxn>
struct DisjointSetWt {
    int parent[maxn+1];
    int size[maxn+1];
    int wt[maxn+1];    /* wt represents: relation value r(root,u) */

    void init(int n) {
        FOR(i, 1, n) { /* check range */
            parent[i] = i;
            size[i] = 1;
            wt[i] = 0;
        }
    }

    int findSet(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    void unite(int x, int y, int delta) {
        int rx = findSet(x);
        int ry = findSet(y);
        if (rx == ry)
            return; // impossible in this use case
        /* merge tree y into root(x), while making r(x,y)=pathSum(y)-pathSum(x)=delta */
        int vy = pathSum(y);
        int vx = pathSum(x);
        D("\t v[%d] = %d  v[%d] = %d\n", y, vy, x, vx);
        wt[ry] = (3 + vx + delta - vy) % 3;
        D("\twt[%d] = %d\n", ry, wt[ry]);
        parent[ry] = rx;
        D("\tparent[%d] = %d\n", ry, rx);
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }

    int pathSum(int x) {
        int sum = 0;
        while (parent[x] != x) {
            sum += wt[x];
            x = parent[x];
        }
        return sum % 3;
    }
};

DisjointSetWt<maxn> ds;

int main() {
#if BENCH
    freopen("files/poj1182_djs_food_chain.txt","r",stdin);
#endif
    int n,m;
    while (~scanf("%d%d", &n, &m)) {
        int cmd,x,y,ans = 0;
        ds.init(n);
        REP(i,m) {
            scanf("%d%d%d", &cmd, &x, &y);
            D("\n\t%d,%d,%d\n", cmd, x, y);
            if (x > n || y > n) { ans++; continue; }
            int rx = ds.findSet(x);
            int ry = ds.findSet(y);
            D("\tsets %d,%d\n", rx, ry);
            if (rx != ry)
                ds.unite(x,y,cmd - 1);
            else {
                int vx = ds.pathSum(x);
                int vy = ds.pathSum(y);
                if ((3 + vy - vx) % 3 != cmd - 1) {
                    D("\t- %d,%d,%d\n", cmd, x, y);
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
        break;
    }
    return 0;
}
