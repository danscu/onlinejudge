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
int elems[maxn+1][maxb+1][2];
int parent[maxn+1];
set<int> path;
#define MAX(a,b) a = max(a,b)

inline void insert(int x, int y, int c, int d) {
    cnt++;
    edges[cnt].y = y;
    edges[cnt].next = child[x];
    child[x] = cnt;
    cost[y] = c;
    val[y] = d;
}

void dfs(int u, int b) {
    for (int t = child[u]; t; t = edges[t].next) {
        int v = edges[t].y;
        for (int i = 0; i <= b; i++) {
            dp[v][i] = dp[u][i] + val[v]; // push down
            elems[v][i][0] = elems[u][i][0];
            elems[v][i][1] = elems[u][i][1];
            parent[v] = u;
        }
        dfs(v, b - cost[v]);
        for (int i = b; i - cost[v] >= 0; i--) {
            if (dp[u][i] < dp[v][i - cost[v]]) {
                dp[u][i] = dp[v][i - cost[v]];
                elems[u][i][0] = v;
                elems[u][i][1] = i - cost[v];
            }
        }
    }
}

void print_path(int u, int b) {
    if (elems[u][b][0] != -1)
        print_path(elems[u][b][0], elems[u][b][1]);
    while (u != root) {
        path.insert(u);
        u = parent[u];
    }
}

void solve() {
    CLRN(dp[root], b+1);
    CLRVN(elems[root], -1, b+1);
    dfs(root, b);

    path.clear();
    print_path(root, b);

    printf("%d %d\n", dp[root][b], path.size());
    for (every(it,path)) {
        printf("%d ", *it);
        D("(%d)\t", val[*it]);
    }
    printf("\n");
}

int main() {
#if BENCH
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
