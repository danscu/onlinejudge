#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <climits>

using namespace std;

#define MAXN 100001
#define DBG 1

int Answer;
int N;

struct Pt {
	int x, y;
	int index;
	Pt(int _x = 0, int _y = 0) {
		x = _x; y = _y;
	}
};

Pt pt[MAXN];

int solve() {
	// Consider two configurations
	// *11---------------%21
	//  |                |
	//  |                |
	// %22---------------*12
	// Optimal solutions must include two points * (conf. 1) or
	// two points % (conf. 2)
	// Assign each point (xi,yi) to the closest points
	// in each configuration. Then, find which of the two
	// configurations is best.

	int top = INT_MIN, bottom = INT_MAX, left = INT_MAX, right = INT_MIN;
	int i;

	for (i = 0; i < N; i++) {
		top = max(top, pt[i].y);
		bottom = min(bottom, pt[i].y);
		left = min(left, pt[i].x);
		right = max(right, pt[i].x);
	}

	// Config 1 --- (left, top) (right, bottom)
	// Config 2 --- (left, bottom) (right, top)

	int mlen1 = 0; // len for config 1
	int mlen2 = 0; // len for config 2

	for (i = 0; i < N; i++) {
		int len11 = max(pt[i].x - left, top - pt[i].y);
		int len12 = max(right - pt[i].x, pt[i].y - bottom);
		int len21 = max(right - pt[i].x, top - pt[i].y);
		int len22 = max(pt[i].x - left, pt[i].y - bottom);

		int len1 = min(len11, len12);
		int len2 = min(len21, len22);

		mlen1 = max(mlen1, len1);
		mlen2 = max(mlen2, len2);
	}

	return min(mlen1, mlen2);
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
    freopen("cover_points.txt", "r", stdin);
#endif

    int T;
    cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> N;

		int i;
		for (i = 0; i < N; i++)
			cin >> pt[i].x >> pt[i].y;

		cout << "Case #" << test_case + 1 << endl;

		Answer = solve();

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;
}
