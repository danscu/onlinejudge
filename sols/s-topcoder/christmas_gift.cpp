#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <algorithm> // std:min

#define DBG 0

using namespace std;

#define MAXN (200 + 200 + 5)

int N, M, V;
int g[MAXN][MAXN];

void printGraph(int g[MAXN][MAXN], int n) {
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < n; j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
}

bool bfs(int g[MAXN][MAXN], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[MAXN];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v]==false && g[u][v])
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(int graph[MAXN][MAXN], int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int rGraph[MAXN][MAXN]; // Residual graph where rGraph[i][j] indicates
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

int main(int argc, char** argv)
{
	int tc, T; // N = people#, M = gift#
	int i, j;

#if BENCH
	freopen("christmas-gift.txt", "r", stdin);
#endif
//    setbuf(stdout, NULL);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		cin >> N >> M;

		// init graph
		V = 2 + N + M;

		int u, v;
	    for (u = 0; u < V; u++)
	        for (v = 0; v < V; v++)
	             g[u][v] = 0;

		// people i
		for (i = 0; i < N; i++) {
			// source to people
			g[0][1 + i] = 1;

			int c; // # of prefs
			cin >> c;
			for (j = 0; j < c; j++) {
				int gift;
				cin >> gift;
				g[1 + i][N + gift] = 1;
			}
		}

		// gift to sink
		for (i = 0; i < M; i++) {
			g[N + 1 + i][N + M + 1] = 1;
		}

#if DBG
		printGraph(g, N + M + 2);
#endif

		// find max-flow of graph
		int ans = fordFulkerson(g, 0, N + M + 1);

		// Print the answer to standard output(screen).
		cout << ans << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
