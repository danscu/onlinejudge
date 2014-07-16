/* LCA tarjan */
/* poj 1470 */

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
const Num maxn = 910;
const Num maxq = 500000;
struct Edge {
    int y, next;
};

template<int maxn, int maxq>
struct LCA {
    Edge map[maxn+1];
    int child[maxn+1], parent[maxn+1], rank[maxn+1], ancestor[maxn+1];
    bool visited[maxn+1];
    int cnt;

    Edge qmap[maxq+1];
    int qfirst[maxq+1];
    int qcnt;

    // results
    std::map<int,int> ances;

    void insert(int x, int y) {
        cnt++;
        map[cnt].y = y;
        map[cnt].next = child[x];
        child[x] = cnt;
    }

    void insertQuery(int x, int y) {
    	qcnt++;
    	qmap[qcnt].y = y;
    	qmap[qcnt].next = qfirst[x];
    	qfirst[x] = qcnt;
    }

    void init(int n) {
        cnt = qcnt = 0;
        CLRN(child, n + 1);
        CLRN(visited, n + 1);
        CLRN(qfirst, n + 1);
        ances.clear();
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
            tarjan(v);
            mergeSet(u, v);
            ancestor[findSet(u)] = u;
        }
        visited[u] = true;
        // process queries
        for (int t = qfirst[u]; t; t = qmap[t].next) {
        	int v = qmap[t].y;
        	if (visited[v]) {
        		int lca = ancestor[findSet(v)];
        		std::map<int,int>::iterator it = ances.find(lca);
        		if (it == ances.end())
        			ances[lca] = 1;
        		else
        			it->second++;
        	}
        }
    }
};

LCA<maxn,maxq> lca;

int main() {
#if BENCH
    freopen("files/poj1470_lca_closest_common_ancestors.txt","r",stdin);
#endif
    int n, nq;
    while (~scanf("%d", &n)) {
        int x, y;
        lca.init(n);
        REP(i,n) {
        	int nc;
            scanf("%d:(%d)", &x, &nc);
            REP(j,nc) {
            	scanf("%d", &y);
            	lca.insert(x, y);
            	lca.visited[y] = true;
            }
        }
        scanf("%d ", &nq);
        REP(j,nq) {
        	scanf("(%d%d) ", &x, &y);
        	lca.insertQuery(x, y);
        	lca.insertQuery(y, x);
        }
        // find lca of x,y
        int root = 0;
        FOR(i,1,n)
            if (!lca.visited[i]) {
                root = i;
                break;
            }
        CLRN(lca.visited, n+1);
        FOR(i,1,n) lca.parent[i] = i;
        lca.tarjan(root);
        for (std::map<int,int>::iterator it = lca.ances.begin();
        	 it != lca.ances.end(); ++it)
        	printf("%d:%d\n", it->first, it->second);
    }
    return 0;
}
