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
#define __NO_SET__
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
const int maxn = 1010;
const int maxb = 10005;

Num n, b;
struct Edge {
    int y, next;
};

// Tree stuff
Edge edges[maxn];
int child[maxn];
int cost[maxn];
int val[maxn];
int cnt; // edges
#define root 0

// DP stuff
Num dp[maxn+1][maxb+1];
set<int> elems[maxn+1][maxb+1];
int path[maxn+1];
int pathcost, pathlen;
#define MAX(a,b) a = max(a,b)

inline void insert(int x, int y, int c, int d) {
    cnt++;
    edges[cnt].y = y;
    edges[cnt].next = child[x];
    child[x] = cnt;
    cost[y] = c;
    val[y] = d;
}

void dfs(int u) {
    FOR(i,0,b) {
        dp[u][i] = val[u];
#ifdef __NO_SET__
        elems[u][i].clear();
        elems[u][i].insert(u);
#endif
    }

    for (int t = child[u]; t; t = edges[t].next) {
        int v = edges[t].y;
        dfs(v);
        for (int j = b; j >= 0; j--)
            for (int k = cost[v]; j + k <= b; k++) {
                if (DBG && dp[u][j] + dp[v][k-cost[v]] > dp[u][j+k])
                    D("dp[%d][%d]=%d (from %d)\n", u, j+k,
                            dp[u][j] + dp[v][k-cost[v]], dp[u][j+k]);

                if (dp[u][j+k] < dp[u][j] + dp[v][k-cost[v]]) {
                    dp[u][j+k] = dp[u][j] + dp[v][k-cost[v]];
#ifdef __NO_SET__
                        elems[u][j+k] = elems[u][j];
                        set<int> &setB(elems[v][k-cost[v]]);
                        elems[u][j+k].insert(setB.begin(), setB.end());
#endif
                }
        }
    }
}

void dump() {
    printf("---- dp ----\n");
    REP(i,n) {
        REP(j,b)
            printf("%d ", dp[i][j]);
        printf("\n");
    }
}

void print_path(int u, int b) {
   for (every(it,elems[u][b])) {
       if (!*it) continue;
       path[pathlen++] = *it;
       pathcost += cost[*it];
   }
}

void solve() {
    dfs(root);

#if DBG
    dump();
#endif

    pathcost = pathlen = 0;

    print_path(root, b);

    printf("%d %d\n", dp[root][b], pathlen);
    D("\tpathcost=%d\n", pathcost);
    REP(i,pathlen) {
        printf("%d ", path[i]);
        D("(%d)\t", val[path[i]]);
    }
    printf("\n");
}

int main() {
#if BENCH
//  freopen("files/4_test.txt","r",stdin);
    freopen("files/4_sample.txt","r",stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        scanf("%d%d", &n, &b);
        CLRN(child, n + 1);
        cnt = 0;
        REP(i,n) {
            int x, y, c, d;
            scanf("%d%d%d%d", &x, &y, &c, &d);
            insert(x, y, c, d);
        }

        printf("Case #%d\n", tc + 1);
        solve();
    }
    return 0;
}
