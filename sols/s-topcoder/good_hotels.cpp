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

const int maxn = 1024*1024;

struct Loc {
	int row;
	int col;
	int index;
	Loc(int row = 0, int col = 0, int index = 0)
		: row(row), col(col), index(index)
	{ }
};

struct ByRow {
	bool operator()(const Loc& a, const Loc& b) {
		return a.row < b.row || (a.row == b.row && a.col < b.col);
	}
} byRow;

struct ByCol {
	bool operator()(const Loc& a, const Loc& b) {
		return a.col < b.col || (a.col ==  b.col && a.row < b.row);
	}
} byCol;

Loc Hx[maxn];
Loc Hy[maxn];
Loc O[maxn];

int dist(const Loc &a, const Loc &b) {
	return max(abs(a.row - b.row), abs(a.col - b.col));
}

inline int getInt(void *p, int offset) {
	return *(((int*)p) + offset);
}

int findClose(Loc H[], int target, int low, int high /* inclusive */, int offset) {
	while (low < high) {
		int mid = (low + high) / 2;
		int v = getInt(&H[mid], offset);
		if (v < target)
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}

void undom_hotels(int n /*hotel*/, int m /*office*/) {
	int i, j, k;

	/*
	stable_sort(Hx, Hx + n, byRow);
	stable_sort(Hy, Hy + n, byCol);
	*/

	bool undom[n];
	memset(undom, 0, sizeof undom);

	for (i = 0; i < m; i++) {
		vector<int> cans;
		int mindst = INT_MAX;
		for (j = 0; j < n; j++) {
			if (mindst > dist(O[i], Hx[j])) {
				cans.clear();
				mindst = dist(O[i], Hx[j]);
			}
			if (mindst == dist(O[i], Hx[j]))
				cans.push_back(j);
		}
		for (vector<int>::iterator it = cans.begin(); it != cans.end(); ++it)
			undom[*it] = true;
	}

	for (i = 0; i < n; i++)
		if (undom[i])
			cout << (i + 1) << " ";
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
			Hx[i].row = Hy[i].row = row;
			Hx[i].col = Hy[i].col =col;
			Hx[i].index = Hy[i].index = i;
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
