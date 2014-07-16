/* LCA */
/* poj 1330 */

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
#  define D(x) printf;
# else
#  define D(...) do {} while (0);
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
const Num maxn = 10001;
const Num INF = numeric_limits<Num>::max();

struct Edge {
    int x, y, next;
};

template<int maxn>
struct LCA {
    Edge map[maxn+1];
    int first[maxn+1], parent[maxn+1];
    bool united[maxn+1];
    int n;
    int cnt;

    void insert(int x, int y) {
        cnt++;
        map[cnt].x = x;
        map[cnt].y = y;
        map[cnt].next = first[x];
        first[x] = cnt;
    }

    void init(int n) {
        this->n = n;
        cnt = 0;
        CLRN(first, n + 1);
        CLRN(united, n + 1);
        memset(parent, -1, sizeof(parent[0])*(n+1));
    }

    int get(int x) {
        if (parent[x] == x) return x;
        parent[x] = get(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int fx = get(x);
        parent[y] = fx;
    }

    int dfs(int x, int qx, int qy) {
        for (int t = first[x]; t; t = map[t].next) {
            int ans = dfs(map[t].y, qx, qy);
            if (ans >= 0) return ans;
            unite(x, map[t].y);
            united[map[t].y] = true;
        }
        if (qx == x && united[qy])
            return get(qy);
        if (qy == x && united[qx])
            return get(qx);
        return -1;
    }
};

LCA<maxn> lca;

int main() {
#if BENCH
    freopen("files/poj1330_lca_nearest_common_ancestors.txt","r",stdin);
#endif
    int tc = 0;
    int n;
    scanf("%d", &tc);
    while (tc--) {
        int x,y;
        scanf("%d", &n);
        lca.init(n);
        REP(i,n-1) {
            scanf("%d%d", &x, &y);
            lca.insert(x, y);
            lca.united[y] = true;
        }
        scanf("%d%d", &x, &y);
        // find lca of xy
        int root = 0;
        FOR(i,1,n) {
            if (!lca.united[i]) {
                root = i;
                break;
            }
        }
        CLRN(lca.united, n+1);
        FOR(i,1,n) lca.parent[i] = i;
        printf("%d\n", lca.dfs(root, x, y));
    }
    return 0;
}
