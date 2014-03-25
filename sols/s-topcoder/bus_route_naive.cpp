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
int e[MAXN][MAXN]; // route count for edge (i,j)
int vis[MAXN]; // visited

list<int> topo_open, open;    // bfs search

// topological ordering
int tm[MAXN][MAXN];
int tin[MAXN];
int cnt;

void visit(int from, int mx) {
	int i;
	if (from==N) {
		cnt+=mx;
		return;
	}

	for (i=1;i<=N;i++)
		if (m[from][i] && !vis[i]) {
			vis[i]=1;
			visit(i, mx * m[from][i]);
			vis[i]=0;
		}
}

int solve() {
	cnt = 0;
	for (int i=1;i<=N;i++)
		if (!in[i])
			visit(i, 1);
	return cnt;
}

int main(int argc, char** argv)
{
	int tc, T, i;
	int Answer;

	freopen("/home/danke/workspace/skymap/src/bus_route_x.txt", "r", stdin);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N >> M;

		CLR(m);
		CLR(out);
		CLR(in);
		CLR(r);
		CLR(e);
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


