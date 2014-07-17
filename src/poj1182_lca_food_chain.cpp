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
    int y, next;
};

template<int maxn>
struct LCA {
    Edge map[maxn+1];
    int child[maxn+1], parent[maxn+1];
    bool visited[maxn+1];
    int n;
    int cnt;

    void insert(int x, int y) {
        cnt++;
        map[cnt].y = y;
        map[cnt].next = child[x];
        child[x] = cnt;
    }

    void init(int n) {
        this->n = n;
        cnt = 0;
        CLRN(child, n + 1);
        CLRN(visited, n + 1);
        memset(parent, -1, sizeof(parent[0])*(n+1));
    }

    int findSet(int x) {
        if (parent[x] == x) return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void mergeSet(int x, int y) {
        int fx = findSet(x);
        parent[y] = fx;
    }

    int tarjan(int x, int qx, int qy) {
        for (int t = child[x]; t; t = map[t].next) {
            int ans = tarjan(map[t].y, qx, qy);
            if (ans >= 0) return ans;
            mergeSet(x, map[t].y);
            visited[map[t].y] = true;
        }
        if (qx == x && visited[qy])
            return findSet(qy);
        if (qy == x && visited[qx])
            return findSet(qx);
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
            lca.visited[y] = true;
        }
        scanf("%d%d", &x, &y);
        // find lca of x,y
        int root = 0;
        FOR(i,1,n)
            if (!lca.visited[i]) {
                root = i;
                break;
            }
        CLRN(lca.visited, n+1);
        FOR(i,1,n) lca.parent[i] = i;
        printf("%d\n", lca.tarjan(root, x, y));
    }
    return 0;
}
