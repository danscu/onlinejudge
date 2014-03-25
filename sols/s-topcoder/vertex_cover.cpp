#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define DBG 0

int Answer;
int N;

// graph
#define MAXN 1001
#define MAXV (2 * MAXN)
#define MAXDEG MAXN

struct Graph {
	int nvertices;
	int degrees[MAXV];
	int edges[MAXV][MAXDEG];
	int weight[MAXV][MAXDEG];
	int assign[MAXV][MAXV]; // assign[i][j] = 1 if worker i is assigned to job j
	int matched[MAXV];

	void init(int nver) {
		nvertices = nver;
		memset(degrees, 0, sizeof(int) * nver);
		memset(assign, 0, sizeof assign);
		memset(matched, 0, sizeof matched);
	}

	void addEdge(int from, int to, int wt) {
		// dups are not checked
		edges[from][degrees[from]] = to;
		weight[from][degrees[from]] = wt;
		degrees[from]++;
	}

	void dump() {
		int i, j;
		cout << "vertices: " << nvertices << endl;
		for (i = 0; i < nvertices; i++) {
			cout << i << ": ";
			for (j = 0; j < degrees[i]; j++)
				cout << edges[i][j] << "(" << weight[i][j] << ") ";
			cout << endl;
		}
	}
};

Graph g;

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
	freopen("vertex_cover.txt", "r", stdin);
#endif
	int T, i, j;
	cin >> T;

	for(test_case = 0; test_case < T; test_case++)
	{
		cin >> N;

		g.init(N);

		for (i = 0; i < N; i++) {
			int edges;
			cin >> edges;
			for (j = 0; j < edges; j++) {
				int e, w;
				cin >> e >> w;
				g.addEdge(i, e, w); // forward
			}
		}

		cout << "Case #" << test_case+1 << endl;

#if DBG
		g.dump();
#endif

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = 0; // solve();

		// Print the answer to standard output(screen).
		cout << "" << Answer << endl;;
	}

	return 0;
}
