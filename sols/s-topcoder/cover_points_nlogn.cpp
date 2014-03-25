#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <bitset>

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

#if DBG
ostream& operator<<(ostream& os, const Pt &p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}
#endif

struct UpwardRect {
	Pt bottomLeft;
	Pt topRight;
};

struct DownwardRect {
	Pt topLeft;
	Pt bottomRight;
};

Pt px[MAXN]; // sorted by x
Pt py[MAXN]; // sorted by y
int indexToPY[MAXN];
bitset<MAXN> upperCovered;
bitset<MAXN> lowerCovered;

bool sortByX(const Pt &a, const Pt &b) {
	return a.x < b.x;
}

bool sortByY(const Pt &a, const Pt &b) {
	return a.y < b.y;
}

bool inBox(UpwardRect &rect, Pt &pt) {
	return pt.x >= rect.bottomLeft.x && pt.y >= rect.bottomLeft.y &&
		   pt.x <= rect.topRight.x && pt.y <= rect.topRight.y;
}

bool inBox(DownwardRect &rect, Pt &pt) {
	return pt.x >= rect.topLeft.x && pt.y <= rect.topLeft.y &&
		   pt.x <= rect.bottomRight.x && pt.y >= rect.bottomRight.y;
}

// return covered points
int getUpper(Pt &leftMost, int side, int &iPy) {
	int cnt = 0;

	// search topmost point st. y <= leftMost.y + side
	UpwardRect box;
	box.bottomLeft = box.topRight = leftMost;
	box.topRight.x += side;
	box.topRight.y += side;

	int topY = py[iPy].y;
	int i = iPy;
	while (i < N && py[i].y <= leftMost.y + side) {
		if (inBox(box, py[i])) {
			topY = py[i].y;
			iPy = i;
		}
		i++;
	}

	// adjust box
	box.topRight.y = topY;
	box.bottomLeft.y = topY - side;

	// count points included (can be optimized)
#if DBG
	cout << "upper: side=" << side << " " << endl;
#endif
	upperCovered.reset();
	i = iPy;
	while (i >= 0 && py[i].y >= box.bottomLeft.y) {
		if (inBox(box, py[i])) {
			cnt++;
			upperCovered.set(py[i].index, 1);
#if DBG
			cout << py[i] << " ";
#endif
		}
		i--;
	}
#if DBG
	cout << endl;
#endif

	return cnt;
}

// return covered points
int getBottomRight(Pt &rightMost, int side, int &iPy) {
	int cnt = 0;
	// search topmost point st. y <= leftMost.y + side
	UpwardRect box;
	box.bottomLeft = box.topRight = rightMost;
	box.bottomLeft.x -= side;
	box.bottomLeft.y -= side;

	int bottomY = py[iPy].y;
	int i = iPy;
	while (i > 0 && py[i].y >= rightMost.y - side) {
		if (inBox(box, py[i])) {
			bottomY = py[i].y;
			iPy = i;
		}
		i--;
	}

	// adjust box
	box.bottomLeft.y = bottomY;
	box.topRight.y = bottomY + side;

	// count points included (can be optimized)
#if DBG
	cout << "upper(comp): side=" << side << " " << endl;
#endif
	i = iPy;
	while (i < N && py[i].y <= box.topRight.y) {
		if (inBox(box, py[i])) {
			if (!upperCovered[py[i].index]) {
				cnt++;
#if DBG
			cout << py[i] << " ";
#endif
			}
		}
		i++;
	}
#if DBG
	cout << endl;
#endif

	return cnt;
}

// return newly covered points
int getLower(Pt &leftMost, int side, int &iPy) {
	int cnt = 0;
	// search topmost point st. y <= leftMost.y + side
	DownwardRect box;
	box.topLeft = box.bottomRight = leftMost;
	box.bottomRight.x += side;
	box.bottomRight.y -= side;

	int bottomY = py[iPy].y;
	int i = iPy;
	while (i > 0 && py[i].y >= leftMost.y - side) {
		if (inBox(box, py[i])) {
			bottomY = py[i].y;
			iPy = i;
		}
		i--;
	}

	// adjust box
	box.bottomRight.y = bottomY;
	box.topLeft.y = bottomY + side;

	// count points included (can be optimized)
#if DBG
	cout << "lower: side=" << side << " " << endl;
#endif
	i = iPy;
	lowerCovered.reset();
	while (i < N && py[i].y <= box.topLeft.y) {
		if (inBox(box, py[i])) {
			cnt++;
			lowerCovered.set(py[i].index, 1);
#if DBG
			cout << py[i] << " ";
#endif
		}
		i++;
	}
#if DBG
	cout << endl;
#endif

	return cnt;
}


// return covered points
int getTopRight(Pt &rightMost, int side, int &iPy) {
	int cnt = 0;
	// search topmost point st. y <= leftMost.y + side
	DownwardRect box;
	box.bottomRight = box.topLeft = rightMost;
	box.topLeft.x -= side;
	box.topLeft.y += side;

	int topY = py[iPy].y;
	int i = iPy;
	while (i < N && py[i].y <= rightMost.y + side) {
		if (inBox(box, py[i])) {
			topY = py[i].y;
			iPy = i;
		}
		i++;
	}

	// adjust box
	box.topLeft.y = topY;
	box.bottomRight.y = topY - side;

	// count points included (can be optimized)
#if DBG
	cout << "lower(comp): side=" << side << " " << endl;
#endif
	i = iPy;
	while (i >= 0 && py[i].y >= box.bottomRight.y) {
		if (inBox(box, py[i])) {
			cnt++;
			lowerCovered.set(py[i].index, 1);
#if DBG
			cout << py[i] << " ";
#endif
		}
		i--;
	}
#if DBG
	cout << endl;
#endif

	return cnt;
}

int solve() {
	int i;

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
	int upperYi = indexToPY[ leftMost.index ]; // upper bound of top rect
	int upCYi = indexToPY[ rightMost.index ];

	int lowerYi = indexToPY[ leftMost.index ]; // lower bound of bottom rect
	int lowerCYi = indexToPY[ rightMost.index ];

	int side;

	// TODO -- find min step in other orders

	for (i = 1; i < N; i++) {
		side = px[i].x - leftMost.x;

		// Layout 1
		int upperPts = getUpper(leftMost, side, upperYi);
		int complementPts = getBottomRight(rightMost, side, upCYi);

		if (upperPts + complementPts == N)
			break;

		// Layout 2
		int lowerPts = getLower(leftMost, side, lowerYi);
		complementPts = getTopRight(rightMost, side, lowerCYi);

		if (lowerPts + complementPts == N)
			break;
	}

	return side;
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
