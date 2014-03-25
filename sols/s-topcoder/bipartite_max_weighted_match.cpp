/**
 * There may be a bug in this program. I used it for TopCoder SRM 371 Div 1 (500)
 * but it is missing Test Case 4.
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <bitset>

using namespace std;

#define DBG 0
#if DBG
#define D(x) x
#else
#define D(x)
#endif

int Answer;
int N;

// graph
#define MAXN 1001		// n workers
#define MAXM 1001		// m jobs

// unweighted bipartite graph
struct Graph {
	int n, m;			// n workers and m jobs
	int wt[MAXN][MAXM];	// -1 means not connected

	void init(int n, int m) {
		this->n = n; this->m = m;
		memset(wt, -1, sizeof wt);
	}

	void addEdge(int from, int to, int wt) {
		this->wt[from][to] = wt;
	}

	void dump() {
		int i, j;
		for (i = 0; i < n; i++) {
			cout << i << ": ";
			for (j = 0; j < m; j++)
				cout << wt[i][j] << " ";
			cout << endl;
		}
	}
};

Graph g;

// find augpath for bpm
bool augpath(Graph &g, int worker, bool seen[], int matchR[]) {
	for (int job = 0; job < g.m; job++) {
		if (g.wt[worker][job] >=0 && !seen[job]) {
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
int maxBpm(Graph &g, int matchR[]) {
	int cardin = 0;
	for (int worker = 0; worker < g.n; worker++) {
		bool seen[g.m];
		memset(seen, 0, sizeof seen);
		if (augpath(g, worker, seen, matchR))
			cardin++;
	}
	return cardin;
}

// maximum weighted bipartite matching, returns max weight
// Hungarian algorithm
int hungarian(Graph g) {
	int i, j;
	int maxw;

	int cover_u[g.n];
	int cover_v[g.m];

	// init step
	for (i = 0; i < g.n; i++) {
		maxw = -1;
		for (j = 0; j < g.m; j++)
			if (g.wt[i][j] >= 0)
				maxw = max(maxw, g.wt[i][j]);
		cover_u[i] = maxw;
	}

	for (j = 0; j < g.m; j++)
		cover_v[j] = 0;

	D(int iter = 0;)

	// iteration
	do {
		/**
		 * Form equality graph G_u,v (eg) and find maximum matching M in it
		 */
		Graph eg;
		eg.init(g.n, g.m);

		for (i = 0; i < g.n; i++) {
			maxw = -1;
			for (j = 0; j < g.m; j++)
				if (g.wt[i][j] >= 0 && g.wt[i][j] == cover_u[i] + cover_v[j])
					eg.addEdge(i, j, g.wt[i][j]);
		}

D(
		cout << endl << "Iter: " << ++iter << endl;
		for (i = 0; i < g.n; i++)
			cout << cover_u[i] << " ";
		cout << endl;
		for (i = 0; i < g.m; i++)
			cout << cover_v[i] << " ";
		cout << endl;
		eg.dump();
)

		/**
		 * Find a maximum matching in the equality graph G_u,v (not maximum weight matching)
		 * This can be done with bpm algorithm
		 */
		int matchR[g.m];
		memset(matchR, -1, sizeof matchR);
		int cardin = maxBpm(eg, matchR);
		if (cardin == g.m) {
			int sumWt = 0;
			for (j = 0; j < g.m; j++)
				if (matchR[j] != -1)
					sumWt += g.wt[matchR[j]][j];
			return sumWt;
		}

D(
		cout << "matchR: ";
		for (j = 0; j < g.m; j++)
			cout << matchR[j] << " ";
		cout << endl;
)

		/**
		 * Find vertex cover Q of size |M| for G_u,v. Q = {matchR[j]}_j
		 *
		 * R = X \intersect Q
		 * T = Y \intersect Q
		 *
		 */
		int min_excess = INT_MAX;
		bool R[g.n];
		bool T[g.m];
		memset(R, 0, sizeof R);
		memset(T, 0, sizeof T);

		for (j = 0; j < g.m; j++) {
			int q = matchR[j];
			if (q != -1) {
				R[q] = true;
				T[j] = true;
			}
		}

D(
		cout << "Cardinality of matching of Guv: " << cardin << endl;
		cout << "Free vertices R in X of Guv:";
		for (i = 0; i < g.n; i++)
			if (R[i])
				cout << " " << i;
		cout << endl;
		cout << "Free vertices T in Y of Guv:";
		for (i = 0; i < g.m; i++)
			if (T[i])
				cout << " " << i;
		cout << endl;
)

		D(cout << "Excess matrix" << endl;)

		for (i = 0; i < g.n; i++) {
			for (j = 0; j < g.m; j++) {
				if (!R[i] && !T[j])
					min_excess = min(
							min_excess,
							cover_u[i] + cover_v[j] - g.wt[i][j]);
				D(cout << cover_u[i] + cover_v[j] - g.wt[i][j] << " ";)
			}
			D(cout << endl;)
		}

		D(cout << "e = " << min_excess << endl;)

		/**
		 * Update u_i and v_j
		 */
		for (i = 0; i < g.n; i++)
			cover_u[i] -= min_excess;

		for (j = 0; j < g.m; j++)
			if (T[j])
				cover_v[j] += min_excess;

	} while (true);

	return -1;
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
	freopen("bipartite_max_weighted_match.txt", "r", stdin);
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
				int e, wt;
				cin >> e >> wt; e--;
				g.addEdge(i, e, wt); // forward
			}
		}

		cout << "Case #" << test_case + 1 << endl;

		D(g.dump());

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = hungarian(g);

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;
}
