// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful.

#include <cstdio>
#include <iostream>
#include <algorithm> // std::min
#include <climits>
#include <list>
#include <cstring>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x)

#define MAXN 5001

int N,M;
int m[MAXN][MAXN]; // adjacency matrix for the DAG
int out[MAXN];     // outgoing degree for v
int in[MAXN];      // incoming degree for v

int r[MAXN]; // incoming routes for vertex
int s[MAXN]; // outgoing routes for vertex
int e[MAXN][MAXN]; // forward route count for edge (i,j)
int b[MAXN][MAXN]; // backward route count for edge (i,j)
int vis[MAXN]; // visited

list<int> topo_open, open;    // bfs search

// topological ordering
int tm[MAXN][MAXN];
int tin[MAXN];

#define D(x...) printf(x);

int solve() {
	int i,j,u,v;

	// result
	int busyCnt = 0;

	// add starting vertices
	topo_open.clear();
	for (i=1;i<=N;i++)
		if (!in[i]) {
			topo_open.push_back(i);
			r[i] = 1;

			// outgoing arcs
			for (u=1;u<=N;u++)
				if (m[i][u])
					e[i][u]=m[i][u]; // multiplied
		}

	// topological order
	open.clear();
	memcpy(tm, m, sizeof tm);
	memcpy(tin, in, sizeof tin);
	while (topo_open.size()) {
		int v = topo_open.front(); topo_open.pop_front();
		open.push_back(v);

		// remove incoming v
		for (i=1;i<=N;i++) {
			if (tm[v][i]) {
				tin[i]-=tm[v][i];
				tm[v][i]=0;
				if (!tin[i]) {
					topo_open.push_back(i);
				}
			}
		}
	}

	// process nodes in order
	for (list<int>::iterator it = open.begin(); it != open.end(); it++) {
		int v = *it;

		// compute r(v) = sum e[i][v] (exception: starting nodes r = 1)
		for (i=1;i<=N;i++)
			r[v]+=e[i][v];

		// out edges from v to i
		for (i=1;i<=N;i++)
			if (m[v][i])
				e[v][i]=r[v] * m[v][i]; // multiplied
	}

	s[N]=1;
	for (u=1;u<=N;u++)
		if (m[u][N])
			b[u][N]=m[u][N]; // multiplied

	// process nodes in order
	for (list<int>::reverse_iterator it = open.rbegin(); it != open.rend(); it++) {
		int v = *it;

		// process v

		// compute s(v) = sum b[v][i] (exception: ending nodes s = 1)
		for (i=1;i<=N;i++)
			s[v]+=b[v][i];

		// in edges from i to v
		for (i=1;i<=N;i++)
			if (m[i][v]) {
				b[i][v]=s[v];
				// max routes
				int x = e[i][v] * b[i][v];
				busyCnt = max(busyCnt, x);

				b[i][v] *=  m[i][v];  // multiplied
			}
	}

	return busyCnt;
}

int main(int argc, char** argv)
{
	int tc, T, i;
	int Answer;

	freopen("bus_route_x.txt", "r", stdin);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N >> M;

		CLR(m);
		CLR(out);
		CLR(in);
		CLR(r);
		CLR(s);
		CLR(e);
		CLR(b);
		CLR(vis);

		for(i=0;i<M;i++) {
			int from, to;
			cin >> from >> to;
			m[from][to]++;
			out[from]++;
			in[to]++;
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		Answer = solve();

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


