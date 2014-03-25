#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define DBG 1

int Answer;
int N;

// graph
#define MAXN 1001		// n workers
#define MAXM 1001		// m jobs

// unweighted bipartite graph
struct Graph {
	int n, m;
	int conn[MAXN][MAXM];

	void init(int n, int m) {
		this->n = n; this->m = m;
		memset(conn, 0, sizeof conn);
	}

	void addEdge(int from, int to) {
		conn[from][to] = 1;
	}

	void dump() {
		int i, j;
		for (i = 0; i < n; i++) {
			cout << i << ": ";
			for (j = 0; j < m; j++)
				cout << conn[i][j] << " ";
			cout << endl;
		}
	}
};

Graph g;

// find augpath for bpm
bool augpath(Graph &g, int worker, bool seen[], int matchR[]) {
	for (int job = 0; job < g.m; job++) {
		if (g.conn[worker][job] && !seen[job]) {
			seen[job] = true;
			if (matchR[job] < 0 || augpath(g, matchR[job], seen, matchR)) {
				matchR[job] = worker;
				return true;
			}
		}
	}
	return false;
}

// maximum bipartite matching, returns cardinality
int maxBpm(Graph g) {
	int matchR[g.m];
	memset(matchR, -1, sizeof matchR);

	int cardin = 0;
	for (int worker = 0; worker < g.n; worker++) {
		bool seen[g.m];
		memset(seen, 0, sizeof seen);
		if (augpath(g, worker, seen, matchR))
			cardin++;
	}
	return cardin;
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
	freopen("bipartite_max_match.txt", "r", stdin);
#endif
	int T, i, j;
	cin >> T;

	for(test_case = 0; test_case < T; test_case++)
	{
		cin >> N;

		g.init(N, N);

		for (i = 0; i < N; i++) {
			int edges;
			cin >> edges;
			for (j = 0; j < edges; j++) {
				int e;
				cin >> e; e--;
				g.addEdge(i, e); // forward
			}
		}

		cout << "Case #" << test_case + 1 << endl;

#if DBG
		g.dump();
#endif

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = maxBpm(g);

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;
}
