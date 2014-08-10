/**
 * This version does not require all cells be covered.
 * It uses max flow to construct two paths from sources to sinks, and
 * reconstruct the paths. It can be used as a template for max flow and
 * path construction.
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
#include <bitset>
#include <queue>

using namespace std;

#ifdef BENCH
#define DBG 0 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 100010; // table size
const int D = 4;

int n;
int s1r, s1c, s2r, s2c, e1r, e1c, e2r, e2c;

const int MAXN = maxn * 2 + 2; // graph size
int V; // green + white + start + end
int graph[MAXN][D][2]; // [0]: edge, [1]: flow
int edges[MAXN];

int rGraph[MAXN][D][2]; // [0]: edge, [1]: flow
int rEdges[MAXN];

vector<int> path[2];

bool bfs(int g[MAXN][D][2], int en[MAXN], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int iv = 0; iv < en[u]; iv++) {
            int v = g[u][iv][0];
            if (!visited[v] && g[u][iv][1])
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int getVal(int g[MAXN][D][2], int en[MAXN], int u, int v) {
    for (int i = 0; i < en[u]; i++) {
        if (g[u][i][0] == v)
            return g[u][i][1];
    }
    return 0;
}

void changeVal(int g[MAXN][D][2], int en[MAXN], int u, int v, int val) {
    for (int i = 0; i < en[u]; i++) {
        if (g[u][i][0] == v)
            g[u][i][1] += val;
    }
}

int fordFulkerson(int s, int t)
{
    int u, v;
    for (u = 0; u < V; u++) {
        rEdges[u] = edges[u];
        for (v = 0; v < rEdges[u]; v++) {
             rGraph[u][v][0] = graph[u][v][0];
             rGraph[u][v][1] = graph[u][v][1];
        }
    }

    int parent[V];
    int max_flow = 0;

    while (max_flow < 2 && bfs(rGraph, rEdges, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, getVal(rGraph, rEdges, u, v));
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            changeVal(rGraph, rEdges, u, v, -path_flow);
            changeVal(rGraph, rEdges, v, u, path_flow);
        }

        max_flow += path_flow;
    }

    return max_flow;
}

inline int ROT(int x) {
    if (x < 0)
        x = n - 1;
    else if (x == n)
        x = 0;
    return x;
}

void addEdge(int x, int y, int val) {
    graph[x][edges[x]][0] = y;
    graph[x][edges[x]++][1] = val;
}

inline int nodeId(int r, int c) {
    r--, c--;
    bool white = (r + c) & 1;
    if (white)
        return n + c;
    else
        return c;
}

// zero-base
void getRC(int u, int &r, int &c) {
    bool white = u >= n;
    c = u % n;
    r = (c & 1) ^ white;
}

void dump() {
    int i, j;
    int r, c;
    for (i = 0; i < V; i++) {
        getRC(i, r, c);
        cout << i << "(" << r+1 << "," << c+1 << "): ";
        for (j = 0; j < edges[i]; j++) {
            getRC(graph[i][j][0], r, c);
            cout << graph[i][j][0] << " (" << r+1 << "," << c+1 << ") ";
        }
        cout << endl;
    }
}

void dumpR() {
    int i, j;
    int r, c;
    printf("--residual--\n");
    for (i = 0; i < V; i++) {
        getRC(i, r, c);
        cout << i << "(" << r+1 << "," << c+1 << "): ";
        for (j = 0; j < rEdges[i]; j++) {
            getRC(rGraph[i][j][0], r, c);
            cout << rGraph[i][j][0] << "[" << graph[i][j][1] - rGraph[i][j][1] << "] (" << r+1 << "," << c+1 << ") ";
        }
        cout << endl;
    }
}

bool pathBfs(int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int iv = 0; iv < rEdges[u]; iv++) {
            int v = rGraph[u][iv][0];
            int fl = graph[u][iv][1] - rGraph[u][iv][1];
            if (!visited[v] && fl == 1)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

void findPath(int s, int t, vector<int> &path) {
    int parent[V];
    path.clear();
    bool ret = pathBfs(s, t, parent);
    if (ret) {
        for (int v = t; v != s; v = parent[v])
            if (v != t)
                path.push_back(v);
        path.push_back(s);
    }
}

int main() {
#if BENCH
    freopen("files/r13_2_sample.txt","r",stdin);
#endif
	int T;

	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		scanf("%d%d%d%d", &s1r, &s1c, &s2r, &s2c);
		scanf("%d%d%d%d", &e1r, &e1c, &e2r, &e2c);

		V = 2 * n + 2;
		CLRN(edges, V);

		REP(r,2)
		    REP(c,n) {
		    bool white = (r + c) & 1;
		    if (white) {
		        addEdge(n + c, ROT(c - 1), 1);
		        addEdge(n + c, c, 1);
		        addEdge(n + c, ROT(c + 1), 1);
		    } else {
		        addEdge(c, n + ROT(c - 1), 1);
		        addEdge(c, n + c, 1);
		        addEdge(c, n + ROT(c + 1), 1);
		    }
		}

		int s = 2 * n;
		int t = 2 * n + 1;

		addEdge(s, nodeId(s1r, s1c), 1);
		addEdge(s, nodeId(s2r, s2c), 1);

		addEdge(nodeId(e1r, e1c), t, 1);
		addEdge(nodeId(e2r, e2c), t, 1);

#if DBG
		dump();
#endif

		int ans = fordFulkerson(s, t);

#if DBG
		dumpR();
#endif

		if (ans == 2) {
	        printf("Case #%d\n", tc + 1);
		    int parent[V];
		    findPath(nodeId(s1r, s1c), t, path[0]);
		    findPath(nodeId(s2r, s2c), t, path[1]);
		    REP(i,2) {
		        printf("%u\n", path[i].size());
		        for (vector<int>::reverse_iterator it = path[i].rbegin();
		                it != path[i].rend(); ++it) {
		            int u = *it, r, c;
		            getRC(u, r, c);
		            printf("%d %d\n", r + 1, c + 1);
		        }
		    }
		} else {
	        printf("Case #%d\n", tc + 1);
	        printf("-1\n");
		}

	}
	return 0;
}
