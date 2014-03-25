#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <bitset>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 5001;

struct Loc {
	int row;
	int col;
	int index;
	Loc(int row = 0, int col = 0, int index = 0)
		: row(row), col(col), index(index)
	{ }

	Loc(Loc &a) {
		row = a.row;
		col = a.col;
		index = a.index;
	}

	Loc& operator=(Loc &a) {
		row = a.row;
		col = a.col;
		index = a.index;
		return *this;
	}
};

struct Dist {
	int dist;
	Loc *a;
	Loc *b;
};

struct ByDist {
	bool operator()(const Dist &a, const Dist &b) {
		return a.dist < b.dist;
	}
} byDist;

Loc H[maxn];
Loc O[maxn];

int dist(const Loc &a, const Loc &b) {
	return max(abs(a.row - b.row), abs(a.col - b.col));
}

Dist d[maxn][maxn]; // office, hotel
int dom[maxn][maxn]; // dom[i][j] : i is dominated by j for times

// m(nlogn + n)
void undom_hotels(int n /*hotel*/, int m /*office*/) {
	// prep dist
	int i, j, k;

	for (j = 0; j < n; j++)
		memset(&dom[j], 0, sizeof(int)*maxn);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			d[i][j].dist = dist(O[i], H[j]);
			d[i][j].a = &O[i];
			d[i][j].b = &H[j];
		}
		// sort
		sort(d[i], d[i] + n, byDist);

		// mark
		for (j = 0; j < n - 1; j++)
			for (k = j + 1; k < n; k++) {
				if (d[i][j].dist < d[i][k].dist) {
					int iclose = d[i][j].b->index;
					int ifar = d[i][k].b->index;
					dom[iclose][ifar]++;
				}
			}
	}

	bool dominated[maxn]; memset(dominated, 0, sizeof dominated);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (dom[i][j] == m)
				dominated[j] = true;

	for (i = 0; i < n; i++)
		if (!dominated[i])
			cout << i + 1 << " ";
	cout<<endl;
}

int main() {
	int T;
	int n, m;
	int i;
	int row, col;

#if BENCH
	freopen("good_hotels.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n >> m;

		// hotels
		for (i = 0; i < n; i++) {
			cin >> row >> col;
			H[i].row = row;
			H[i].col = col;
			H[i].index = i;
		}

		// offices
		for (i = 0; i < m; i++) {
			cin >> row >> col;
			O[i].row = row;
			O[i].col = col;
			O[i].index = i;
		}

		cout << "Case #" << tc + 1 << endl;

		undom_hotels(n, m);
	}

	return 0;
}
