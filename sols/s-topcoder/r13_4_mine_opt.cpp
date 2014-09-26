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

#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const int maxn = 1010;
const int maxb = 10005;

Num n, b;
// Represents an outgoing edge from a node
struct Edge {
    int y;          // child node on the edge
    int next;       // link to next edge of the same node
};

// Tree stuff
Edge edges[maxn];   // stores all edges of the tree
int child[maxn];    // link to first child node for a node
int cost[maxn];     // cost of the node
int val[maxn];      // diamonds on the node
int cnt;            // total number of edges
#define root 0      // id of the root node (for clarity)

// DP stuff
Num dp[maxn+1][maxb+1];         // [u][b]: max number of diamonds in subtree of u, budget b
int elems[maxn+1][maxb+1][2];   // data for reconstruct the optimal node set
int parent[maxn+1];             // parent of node u
set<int> optSet;                // the optimal node set to be found

inline void insert(int x, int y, int c, int d) {
    cnt++;
    edges[cnt].y = y;
    edges[cnt].next = child[x];
    child[x] = cnt;             // insert a child node into the linked list
    cost[y] = c;                // store cost
    val[y] = d;                 // store number of diamonds
}

void dfs(int u, int b) {
    for (int t = child[u]; t; t = edges[t].next) {
        int v = edges[t].y;
        for (int i = 0; i <= b; i++) {
            dp[v][i] = dp[u][i] + val[v];       // inherit the maximum of diamonds found so far
            elems[v][i][0] = elems[u][i][0];    // inherit the optimal node set
            elems[v][i][1] = elems[u][i][1];
            parent[v] = u;                      // store parent node
        }
        dfs(v, b - cost[v]);                    // recursion
        for (int i = b; i - cost[v] >= 0; i--) {
            if (dp[u][i] < dp[v][i - cost[v]]) {
                dp[u][i] = dp[v][i - cost[v]];  // more diamonds found by using a child node
                elems[u][i][0] = v;             // update optimal set
                elems[u][i][1] = i - cost[v];
            }
        }
    }
}

void buildSet(int u, int b) {
    if (elems[u][b][0] != -1)
        buildSet(elems[u][b][0], elems[u][b][1]);   // recursively build the optimal set

    // Add all ancestors of the node u
    while (u != root) {
        set<int>::iterator itFind = optSet.find(u);
        if (itFind != optSet.end())
            break; // the node and all ancestors have been added
        optSet.insert(u);
        u = parent[u];
    }
}

void solve() {
    CLRN(dp[root], b+1);            // initialize max diamonds to 0
    CLRVN(elems[root], -1, b+1);    // initialize optimal set to empty
    dfs(root, b);                   // call DFS to solve the problem

    optSet.clear();                 // clear optimal set
    buildSet(root, b);              // build optimal set

    // print solution
    printf("%d %d\n", dp[root][b], optSet.size());
    for (every(it,optSet))
        printf("%d ", *it);
    printf("\n");
}

int main() {
    freopen("files/r13_4_sample.txt","r",stdin);
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
