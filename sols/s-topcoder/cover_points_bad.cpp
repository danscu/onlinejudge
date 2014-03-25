#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <cassert>
#include <cstring>

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

Pt px[MAXN]; // sorted by x
Pt py[MAXN]; // sorted by y
int indexToPY[MAXN];
bool covered[MAXN];

bool sortByX(const Pt &a, const Pt &b) {
	return a.x < b.x;
}

bool sortByY(const Pt &a, const Pt &b) {
	return a.y < b.y;
}

int findIncrementOnLeft(Pt &base, int &iX, int &iYu, int &iYud, int &iYd, int &iYdu) {
	assert(iX + 1 < N);

	int iXNext = iX + 1;
	Pt &nextX = px[iXNext];

	// Upward square
	//
	int iYuNext = max(N-1, iYu + 1);
	Pt &nextYu = py[iYuNext];

	int dx = nextX.x - px[iX].x;
	int dyu = nextYu.y - py[iYu].y;

	int incre = min(dx, dyu);
	int sideX = px[iX].x - base.x + incre;

	// upward square must include a top point ptop if ptop.y - baseY < sideX
	while (iYuNext < N && py[iYuNext].y - base.y <= sideX)
		iYuNext++;

	int yud = py[iYuNext].y - sideX;

	if (yud > py[iYud].y) {
		while (iYud < N && py[iYud].y >= yud)
				iYud--;
	}

	while (iYud > 0 && py[iYud].y >= yud)
		iYud--;

	// Downward square
	//
	int iYdNext = min(0, iYud - 1);
	Pt &nextYd = py[iYdNext];

	int dyd = cur.y - nextYd.y;

	incre = min(dx, dyd);
	sideX = cur.x - base.x + incre;

	// upward square must include a top point ptop if ptop.y - baseY < sideX
	while (iYdNext > 0 && base.y - py[iYdNext].y <= sideX)
		iYdNext--;

	int ydu = py[iYdNext].y + sideX;
	while (iYdu < N && py[iYdu].y <= ydu)
		iYdu++;
}

int solve() {
	int len1 = 0, len2 = 0;
	int i, j;

	memset(covered, 0, N * sizeof(bool));

	// sort by x and y
	sort(px, px + N, sortByX);
	sort(py, py + N, sortByY);

	// index py and find
	for (i = 0; i < N; i++)
		indexToPY[py[i].index] = i;

#if DBG
	for (i = 0; i < N; i++) {
		cout << "(" << px[i].x << "," << px[i].y << ") ";
	}
	cout << endl;
#endif

	// configuration: bottom-left + top-right (upward) VS. top-left + bottom-right (downward)
	Pt &leftMost(px[0]);
	Pt &rightMost(px[N-1]);

	// search for different rectangle sizes (from small to large)
	int curiX = 0;		// current x index
	int curiYu, curiYd;	// current y index up and down

	for (i = 0; i < N; i++) {
		int newPts;
		int incre = findIncrementOnLeft(px[0], curiX, curiYu, curiYd);
		// count new pts in new square

	}

	return min(len1, len2);
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
		for (i = 0; i < N; i++) {
			cin >> px[i].x >> px[i].y;
			px[i].index = i;
			py[i] = px[i];
		}

		cout << "Case #" << test_case + 1 << endl;

		Answer = solve();

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;
}
