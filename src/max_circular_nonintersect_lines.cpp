#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 100;
const int maxe = 100;
vector<pair<int,int> > edges;
int crossed[maxe]; // the number of times the edge has been intersected
vector<int> found;
int n, m;
int maxdep;

// find if line (p11, p12) and line (p21, p22) intersect
// the values are index on a circle
bool intersect(int p11, int p12, int p21, int p22) {
	int q11 = min(p11, p12), q12 = max(p11, p12);
	int q21 = min(p21, p22), q22 = max(p21, p22);

	return (q11 < q21 && q21 < q12 && !(q11 <= q22 && q22 <= q12)) ||
			(q11 < q22 && q22 < q12 && !(q11 <= q21 && q21 <= q12));
}

int greedy() {
	return 0;
}

void brute(int dep, int edge) {
	if (!crossed[edge]) {
		for (int i = 0; i < m; i++) {
			if (intersect(edges[i].first, edges[i].second,
					edges[edge].first, edges[edge].second))
				crossed[i]++;
		}

		// check max
		found.push_back(edge);
		if (dep > maxdep)
			maxdep = dep;

		if (edge + 1 < m)
			brute(dep + 1, edge + 1);

		for (int i = 0; i < m; i++) {
			if (intersect(edges[i].first, edges[i].second,
					edges[edge].first, edges[edge].second))
				crossed[i]--;
		}
		found.pop_back();
	}

	if (edge + 1 < m)
		brute(dep, edge + 1);
}

int main() {
	// input
#if BENCH
	freopen("max_circular_nonintersect_lines.txt", "r", stdin);
#endif
	while (cin >> n >> m) {
		// n nodes, m edges
		edges.reserve(m);
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			edges.push_back(make_pair(a, b));
		}
	}

	int sizeGreedy = greedy();
	maxdep = 0;
	brute(1,0);
	int sizeExhaustive = maxdep;

	cout << "Max size = " << maxdep << ", Greedy size = " << sizeGreedy << endl;

	return 0;
}
