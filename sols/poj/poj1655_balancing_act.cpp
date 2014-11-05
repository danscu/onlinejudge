/*
 * POJ 1655 Balancing Act
 * Find centroid of tree.
 */
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

#define INF 100000000

struct Edge {
    int y, next;
};

template<int maxn>
struct Tree {
    Edge map[maxn+1];	// edge store
    int child[maxn+1];	// first child for node
    bool visited[maxn+1];
    int map_sz;
    int n;

    // private
	int minBal;
	int nodeMinBal;

    void insert(int x, int y) {
    	D("insert (%d,%d)\n",x, y);
        map_sz++; // allocate edge memory
        map[map_sz].y = y;
        map[map_sz].next = child[x];
        child[x] = map_sz; // add to linked list
    }

    // n = max number of nodes
    void init(int n) {
        map_sz = 0;
        minBal = INF;
        this->n = n;
        CLRN(child, n + 1);
    }

    int dfs(int x) {
        CLRN(visited, n + 1);
        return __dfs(x);
    }

private:
    // DFS
    // Returns tree size
    int __dfs(int x) {
    	visited[x] = true;

    	int maxSubtree = 0;
    	int sz = 1; // self

        for (int idx = child[x]; idx; idx = map[idx].next) {
        	int y = map[idx].y;
        	if (visited[y]) continue;

        	int childSz = __dfs(y);
        	sz += childSz;

        	maxSubtree = max(maxSubtree, childSz);
        }

        // The subtree at parent side: n - sz
        maxSubtree = max(maxSubtree, n - sz);

        // Generate optimal result
        if (maxSubtree < minBal) {
        	minBal = maxSubtree;
        	nodeMinBal = x;
        } else if (maxSubtree == minBal && x < nodeMinBal)
        	nodeMinBal = x;

    	D("Node=%d maxSubtree=%d\n", x, maxSubtree);

        return sz;
    }
};

typedef int Num;
const Num maxn = 20005 * 2;

int n;
Tree<maxn> tree;

void solve() {
	tree.dfs(1);
	printf("%d %d\n", tree.nodeMinBal, tree.minBal);
}

int main() {
#if BENCH
	freopen("files/poj1655_balacing_act.txt","r",stdin);
#endif
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		tree.init(n);
		REP(i,n-1) {
			int x,y;
			scanf("%d%d", &x, &y);
			tree.insert(x, y);
			tree.insert(y, x);
		}

		solve();
	}
	return 0;
}
