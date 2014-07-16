/* LCA tarjan */
/* poj 1986 */

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
#define D printf
# else
#define D(...) do {} while (0);
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
const Num maxn = 40010;
const Num maxq = 10010;
struct Edge {
    int x, y, next;
    int val;
};

template<int maxn, int maxq>
struct LCA {
    Edge map[2*(maxn+1)];
    int child[maxn+1], parent[maxn+1], rank[maxn+1], ancestor[maxn+1];
    bool color[maxn+1], visited[maxn+1];
    int cnt;

    Edge qmap[2*(maxq+1)];
    int qfirst[2*(maxq+1)];
    int qcnt;
    int nq;

    // results
    int dist[maxn+1]; // 根到节点距离
    int qlca[maxq+1];

    void insert(int x, int y, int cost) {
        cnt++;
        map[cnt].y = y;
        map[cnt].val = cost;
        map[cnt].next = child[x];
        child[x] = cnt;
    }

    void insertQuery(int x, int y) {
    	qmap[qcnt].x = x;
    	qmap[qcnt].y = y;
    	qmap[qcnt].next = qfirst[x];
    	qfirst[x] = qcnt;

    	qmap[qcnt + nq].x = y;
    	qmap[qcnt + nq].y = x;
    	qmap[qcnt + nq].next = qfirst[y];

    	qfirst[y] = qcnt + nq;
    	qcnt++;
    }

    void init(int n) {
        cnt = qcnt = 0;
        CLRN(child, n + 1);
        CLRN(color, n + 1);
        CLRN(qfirst, n + 1);
        CLRN(visited, n + 1);
    }

    void makeSet(int u) {
    	parent[u] = u;
    	rank[u] = 0;
    }

    int findSet(int x) {
        if (parent[x] == x) return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void mergeSet(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (rank[u] > rank[v])
        	parent[v] = u;
        else if (rank[u] < rank[v])
        	parent[u] = v;
        else if (u != v) {
        	parent[v] = u;
        	rank[u]++;
        }
    }

    void tarjan(int u) {
    	makeSet(u);
    	ancestor[u] = u;
        for (int t = child[u]; t; t = map[t].next) {
        	int v = map[t].y;
        	if (visited[v]) continue;
        	// 已访问标记和费用
        	visited[v] = true;
        	dist[v] = dist[u] + map[t].val;
            tarjan(v);
            mergeSet(u, v);
            ancestor[findSet(u)] = u;
        }
        color[u] = true;
        // 处理查询
        for (int t = qfirst[u]; t; t = qmap[t].next) {
        	int v = qmap[t].y;
        	if (color[v]) {
        		int lca = ancestor[findSet(v)];
        		qlca[t % nq] = lca;
        	}
        }
    }
};

LCA<maxn,maxq> lca;

int main() {
#if BENCH
    freopen("files/poj1986_lca_distance.txt","r",stdin);
#endif
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        int x, y, d;
        char ch;
        lca.init(n);
        REP(i,m) {
			scanf("%d%d%d %c ", &x, &y, &d, &ch);
			lca.insert(x, y, d);
			lca.insert(y, x, d);
        }
        scanf("%d", &lca.nq);
        REP(j,lca.nq) {
        	scanf("%d%d", &x, &y);
        	lca.insertQuery(x, y);
        }
        int root = 1; // any node
        CLRN(lca.visited, n+1);
        FOR(i,1,n) lca.parent[i] = i;
        lca.dist[root] = 0;
        lca.visited[root] = true;
        lca.tarjan(root);
        REP(j,lca.nq)
        	printf("%d\n", lca.dist[lca.qmap[j].x] + lca.dist[lca.qmap[j].y] -
        	               2 * lca.dist[lca.qlca[j]]);
    }
    return 0;
}
