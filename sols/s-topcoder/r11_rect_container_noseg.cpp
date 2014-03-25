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

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 1005;
typedef unsigned Num;
#define INF 1000000
#define MAXITER 20

struct Rect {
	int x, y;
	int width, height;
};

struct ByBottomLeft {
	bool operator()(const Rect *a, const Rect *b) {
		return a->x < b->x || (a->x == b->x && a->y < b->y);
	}
} byBottomLeft;

int N;
Num side[maxn];
list<Rect*> freeRects;
Rect rectArr[maxn*maxn];
int ridx; // allocation ptr for rectArr
typedef set<Rect*,ByBottomLeft> Cells;
Cells cells;
typedef vector<Rect*> Rects;
Rects rects;
int boundX, boundY;

int bestArea, bestW, bestH;
int bestRectI;
Rect bestRects[maxn];

bool desc(const Num& a, const Num& b) {
	return a > b;
}

void printNum(Num &a) {
	cout << a << " ";
}

Rect *newRect(int w, int h) {
	Rect *res;
	if (/*!freeRects.empty()*/0) {
		res = freeRects.back(); freeRects.pop_back();
		memset(res, 0, sizeof(Rect));
	} else {
		res = &rectArr[ridx++];
	}

	res->width = w; res->height = h;
	res->x = res->y = -1;
	return res;
}

void removeRect(Rect *ptr) {
	freeRects.push_back(ptr);
}

void initCells(int maxHeight, int maxWidth = INF) {
	for (Cells::iterator it = cells.begin(); it != cells.end(); ++it)
		removeRect(*it);
	cells.clear();
	Rect *r = newRect(maxWidth, maxHeight);
	r->x = r->y = 0;
	cells.insert(r);
}

void insertCell(Rect *r) {
	cells.insert(r);
}

bool findSpaceInCells(int &x, int &y, int size, Rect *&rect) {
	if (cells.empty()) {
		x=y=0;
		rect = 0;
		return true;
	}
	// find first column and first row
	for (Cells::iterator it = cells.begin(); it != cells.end(); ++it) {
		Rect &r(**it);
		if (r.height >= size && r.width >= size) {
			rect = &r;
			x=r.x; y = r.y;
			return true;
		}
	}
	return false;
}

void allocFromCell(Rect &cell, Rect &rect) {
	// tricky
	int leftCol = rect.x - cell.x;
	int bottomRow = rect.y - cell.y;
	int topRow = cell.y + cell.height - (rect.y + rect.height);
	int rightRow = cell.x + cell.width - (rect.x + rect.width);

	Rect *r;
	int oldCellHeight = cell.height;
	int oldCellX = cell.x;
	int oldCellY = cell.y;

	// cell is removed
	if (!leftCol && !bottomRow) {
		cells.erase(&cell);
		removeRect(&cell);
	} else {
		if (leftCol)
			cell.width = leftCol;
		if (bottomRow) {
			// below rect
			if (leftCol) {
				// add
				r = newRect(rect.x, bottomRow);
				r->x = cell.x + leftCol;
				r->y = cell.y;
				insertCell(r);
			} else {
				// modify current
				cell.height = bottomRow;
				cell.width = rect.width;
			}
		}
	}

	if (topRow) {
		// above rect
		r = newRect(rect.width, topRow);
		r->x = oldCellX + leftCol;
		r->y = rect.y + rect.height;
		insertCell(r);
	}
	if (rightRow) {
		// right of rect
		r = newRect(rightRow, oldCellHeight);
		r->x = rect.x + rect.width;
		r->y = oldCellY;
		insertCell(r);
	}
}

void clearRects() {
	boundX = boundY = 0;
	for (Rects::iterator it = rects.begin(); it != rects.end(); ++it)
		removeRect(*it);
	rects.clear();
	rects.reserve(N);
}

void addRect(Rect &r) {
	boundX = max(boundX, r.x + r.width);
	boundY = max(boundY, r.y + r.height);
	rects.push_back(&r);
}

void copyToBest(Rect *r) {
	bestRects[bestRectI++] = *r;
}

bool basicGreedy(int &w, int &h) {
	int i;

	// init
	h = side[0];

	w = 0;

	Rect *lastCell(0);
	int x,y;
	for (i=0; i<N; i++) {
		// greedy alloc
		bool ok = findSpaceInCells(x, y, side[i], lastCell);

		if (ok) {
			// place the rect in cell
			Rect &newR = *newRect(side[i], side[i]);
			newR.x = x;
			newR.y = y;
			allocFromCell(*lastCell, newR);
			addRect(newR);
		} else
			return false;
	}

	w = boundX;
	h = boundY;
	return true;
}

int idealArea() {
	int i;
	int area = 0;
	for (i=0;i<N;i++)
		area += side[i]*side[i];
	return area;
}

bool tryPack(int w, int h) {
	initCells(h, w);
	clearRects();

	int gw, gh;
	bool ok = basicGreedy(gw, gh);

	return ok;
}

void saveSol(int w, int h) {
	bestArea = w * h;
	bestW = w;
	bestH = h;
	bestRectI = 0;
	for_each(rects.begin(), rects.end(), copyToBest);
}

void solve() {
	int i,j,d;

	// sort by pos (asc)
	sort(side, side+N, desc);

	// init
	initCells(side[0]);
	clearRects();
	bestArea = -1;

	// find upperbound with greedy
	int wu, hu;
	basicGreedy(wu, hu);
	saveSol(wu, hu); // baseline solution

	int areaU = wu * hu, areaL = idealArea();

	D(cout << "DEBUG greedy w = " << wu << " height " << hu << endl);

	int iters = 0;
	int tryw = wu - 1, tryh = hu + 1;

	// Search with at most MAXITER iterations
	while (iters++ < MAXITER) {
		D(cout << "ITER#" << iters << " area=" << tryw * tryh << "(" << tryw << "x" << tryh << ")" << endl;)

					bool possible = tryPack(tryw, tryh);

		if (possible) {
			// Save solution
			if (tryw * tryh < bestArea)
				saveSol(tryw, tryh);
			tryw -= max(1, tryw / (1 + MAXITER - iters));
		} else
			tryh += max(1, tryh / (1 + MAXITER - iters));

		D(cout << possible<<endl;)
	}

	// print best results
	cout << bestW << " " << bestH << endl;
	for (i = 0; i<bestRectI; i++)
		cout << bestRects[i].width << " " << bestRects[i].x << " " << bestRects[i].y << endl;
}

int main(int argc, char** argv)
{
	int tc, T, i;

#if BENCH
	freopen("rect_container_large.in", "r", stdin);
#endif

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N;
		for(i=0;i<N;i++)
			cin >> side[i];

		// clear data
		ridx = 0;

		// Print the answer to standard output(screen).
		cout << "Case #" << tc + 1 << endl;

		solve();
	}

	return 0;
}
