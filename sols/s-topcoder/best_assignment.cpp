#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;

int Answer;
int N;

#define DBG 0
#if DBG
#define D(x) x
#else
#define D(x)
#endif

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

// find augpath, returns prefs delta
int augpath(Graph &g, int worker, bool workers[], bool seen[], int matchL[], int matchR[], int value) {
	// base case (cycle)
	if (workers[worker])
		return value;

	for (int job = 0; job < g.m; job++) {
		if (g.wt[worker][job] >=0 && !seen[job]) {
			seen[job] = true;

			// new value after new job assignment
			int newVal = value;
			if (matchL[worker] < 0 || job < matchL[worker])
				newVal++;
			else if (job > matchL[worker])
				newVal--;
			else
				continue; // no change

			// check if other jobs can be assigned
			int pathVal = newVal;
			if (matchR[job] < 0 ||
					0 < (pathVal = augpath(g, matchR[job], workers, seen, matchL, matchR, newVal))) {
				if (matchL[worker] >= 0)
					matchR[matchL[worker]] = -1;
				matchL[worker] = job;
				matchR[job] = worker;
				return pathVal;
			}
		}
	}
	return value; // no path
}

// maximum bipartite matching, returns cardinality
bool bpm(Graph &g, int matchL[], int matchR[]) {
	for (int worker = 0; worker < g.n; worker++) {
		bool seen[g.m];
		bool workers[g.n];
		memset(seen, 0, sizeof seen);
		memset(workers, 0, sizeof workers);
		int valDelta = augpath(g, worker, workers, seen, matchL, matchR, 0);
		if (valDelta > 0)
			return true;
	}
	return false;
}

/**
 * Returns 1 if best assignment exists, 0 if not
 *
 * Tentative algorithm:
 *
 * Iteration:
 * Try to reassign a worker to a new job which increases total preferences
 *
 * For each worker i
 *     For each job j
 *         if !assigned[j] || augpath(
 */
int solve(Graph &g) {
	const int maxIter = 100;
	int matchL[g.n];
	int matchR[g.m];
	memset(matchL, -1, sizeof matchL);
	memset(matchR, -1, sizeof matchR);

	int iter, i;
	for (iter = 0; iter < maxIter; iter++) {
		bool morePath = bpm(g, matchL, matchR);

#if DBG
		cout << "matchL:";
		for (i = 0; i < g.n; i++)
			cout << " " << matchL[i];
		cout << endl;

		cout << "matchR:";
		for (i = 0; i < g.m; i++)
			cout << " " << matchR[i];
		cout << endl;

		g.dump();
#endif

		if (!morePath)
			break;
	}

	return iter < maxIter;
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
	freopen("best_assignment.txt", "r", stdin);
#endif
	int T, i, j;
	cin >> T;

	for(test_case = 0; test_case < T; test_case++)
	{
		cin >> N;

		g.init(N, N);

		int iworker;

		for (i = 0; i < N; i++) {
			int nprefs;
			cin >> iworker;
			cin >> nprefs;
			for (j = 0; j < nprefs; j++) {
				int ijob;
				cin >> ijob;
				g.addEdge(iworker - 1, ijob - 1, j + 1 /* weight */);
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
		Answer = solve(g);

		// Print the answer to standard output(screen).
		cout << "" << Answer << endl;;
	}

	return 0;//Your program should return 0 on normal termination.
}
