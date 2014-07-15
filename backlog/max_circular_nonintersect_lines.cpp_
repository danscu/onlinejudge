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

/**
 * This program tests if maximum indepedent edge set on a circle
 * is a matroid, that is, can be solved with a Greedy algorithm.
 * It turns out to be false.
 *
 * However, it can be a very close approximation algorithm.
 */

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

	if (q11 == q21 || q11 == q22 || q12 == q21 || q12 == q22)
		return false;

	return (q11 < q21 && q21 < q12 && !(q11 <= q22 && q22 <= q12)) ||
			(q11 < q22 && q22 < q12 && !(q11 <= q21 && q21 <= q12));
}

int greedy() {
	int i, j;
	for (i = 0; i < m - 1; i++)
		for (j = i + 1; j < m; j++) {
			if (intersect(edges[i].first, edges[i].second, edges[j].first, edges[j].second))
				crossed[i]++, crossed[j]++;
		}

	bool removed[m];
	memset(removed, 0, sizeof removed);
	int cnt = 0;

	do {
		int min = INT_MAX, mini = 0;
		for (i = 0; i < m; i++)
			if (!removed[i] && crossed[i] < min)
				min = crossed[i], mini = i;
		if (min == INT_MAX)
			break;
		removed[mini] = true;
		for (int i = 0; i < m; i++) {
			if (intersect(edges[i].first, edges[i].second,
					edges[mini].first, edges[mini].second)) {
				removed[i] = true;
				for (j = 0; j < m; j++) {
					if (intersect(edges[i].first, edges[i].second,
							edges[j].first, edges[j].second))
						crossed[j]--;
				}
			}
		}
		cnt++;
	} while (1);

	return cnt;
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

	for (int T = 0; T < 1000; T++) {
		srand(time(NULL));

		n = 10;
		m = 20;

		set<pair<int,int> > es;
		while (es.size() < m) {
			int a = rand() % n;
			int b = rand() % n;
			if (a > b)
				swap(a, b);
			es.insert(make_pair(a, b));
		}

		edges.clear();
		edges.insert(edges.end(), es.begin(), es.end());

		memset(crossed, 0, sizeof crossed);
		int sizeGreedy = greedy();

		maxdep = 0;
		found.clear();
		memset(crossed, 0, sizeof crossed);
		brute(1,0);
		int sizeExhaustive = maxdep;

		cout << "Max size = " << maxdep << ", Greedy size = " << sizeGreedy << endl;

		if (maxdep != sizeGreedy) {
			cout << "Greedy failed" << endl;
			exit(0);
		}
	}

	cout << "greedy OK" << endl;

	return 0;
}
