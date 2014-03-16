/*
 * UVa 10245
 */

#include <iostream>
#include <set>
#include <cstdio>
#include <algorithm> // std:sort
#include <climits>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

#define MAXN 10001

int N;

struct Pt {
	double x, y;
	int index;
};

double dist(const Pt &a, const Pt &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Pt pt[MAXN];

struct AscendX {
	bool operator()(const Pt &a, const Pt &b) {
		return a.x < b.x;
	}
} ascendX;

struct ascendByY {
	bool operator()(const Pt* a, const Pt* b) {
		return a->y < b->y || (a->y == b->y && a->x < b->x); // and x for equivalence check
	}
};

double closestPairSlow(Pt pt[], int n) {
	double mindist = FLT_MAX;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			mindist = min(mindist, dist(pt[i], pt[j]));
	return mindist;
}

/**
 * Keep a set 'box' sorted by Y, whose elements's x-coords
 * are within h of pt[i]
 */
double closestPair(Pt pt[], int n) {
	typedef set<Pt*, ascendByY> Box;
	Box box; // points whose x cords are within h of pt[i]
	double h = FLT_MAX;		// shortest distance so far

	sort(pt, pt + n, ascendX);

	int k = 0; // first in box
	size_t i;

	for (i = 0; i < n; i++) {
		// searching box for shortest and update h
		for (Box::iterator it = box.begin(); it != box.end(); ++it) {
			double d = dist(pt[i], **it);
			if (d < h)
				h = d;
		}

		// popping elements from box by moving k
		int inth = h + 1;
		while (k < i && pt[k].x <= pt[i].x - inth) {
			// remove pt[k] from box
			box.erase(&pt[k]);
			k++;
		}

		// add pt[i] into box
		box.insert(&pt[i]);
	}

	return h;
}

int main() {
	int i;

#if BENCH
	freopen("closest_pair.txt", "r", stdin);
#endif

	cout.precision(4);
	cout.setf(ostream::fixed);

	while (cin >> N) {
		if (!N) break;
		// input
		for (i=0;i<N;i++) {
			cin >> pt[i].x >> pt[i].y;
			pt[i].index = i;
		}
		// solve
		if (N <= 1)
			cout << "INFINITY" << endl;
		else {
			double ans = closestPair(pt, N);
//			double ans = closestPairSlow(pt, N);
			if (ans > 10000)
				cout << "INFINITY" << endl;
			else
				cout << ans << endl;
		}
	}

	return 0;
}
