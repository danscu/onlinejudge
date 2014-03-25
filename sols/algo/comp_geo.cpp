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

#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)

/**
 * Points, lines and line segments
 */
typedef int Num;
struct Pt {
	Num x, y;
	Pt(Num x, Num y) : x(x), y(y) { }
	Pt operator-(Pt b) {
		Pt c(x - b.x, y - b.y);
		return c;
	}
	Pt operator+(Pt b) {
		Pt c(x + b.x, y + b.y);
		return c;
	}
	// for sort
	bool operator<(Pt b) {
		return x < b.x || (x == b.x && y < b.y);
	}
};

#define SAME_SIGNS( a, b )	\
		(((long) ((unsigned long) a ^ (unsigned long) b)) >= 0 )

Num dotProd(Pt &a, Pt &b) {
	return a.x * b.x + a.y * b.y;
}

Num crossProd(Pt &a, Pt &b) {
	return a.x * b.y - a.y * b.x;
}

double dist(Pt &a, Pt &b) {
	Num d1 = a.x - b.x, d2 = a.y - b.y;
	return sqrt(d1 * d1 + d2 * d2);
}

bool lineIntersect(Pt &a, Pt &b, Pt &c, Pt &d, Pt *inter) {
	long a1, a2, b1, b2, c1, c2; /* Coefficients of line eqns. */
	long r1, r2, r3, r4;         /* 'Sign' values */
	long denom, offset, num;     /* Intermediate values */

	/* Compute a1, b1, c1, where line joining points 1 and 2
	 * is "a1 x  +  b1 y  +  c1  =  0".
	 */

	a1 = b.y - a.y;
	b1 = a.x - b.x;
	c1 = b.x * a.y - a.x * b.y;

	/* Compute r3 and r4.
	 */

	r3 = a1 * c.x + b1 * c.y + c1;
	r4 = a1 * d.x + b1 * d.y + c1;

	/* Check signs of r3 and r4.  If both point 3 and point 4 lie on
	 * same side of line 1, the line segments do not intersect.
	 */

	if ( r3 != 0 &&
			r4 != 0 &&
			SAME_SIGNS( r3, r4 ))
		return false;

	/* Compute a2, b2, c2 */

	a2 = d.y - c.y;
	b2 = c.x - d.x;
	c2 = d.x * c.y - c.x * d.y;

	/* Compute r1 and r2 */

	r1 = a2 * a.x + b2 * a.y + c2;
	r2 = a2 * b.x + b2 * b.y + c2;

	/* Check signs of r1 and r2.  If both point 1 and point 2 lie
	 * on same side of second line segment, the line segments do
	 * not intersect.
	 */

	if ( r1 != 0 &&
			r2 != 0 &&
			SAME_SIGNS( r1, r2 ))
		return false;

	/* Line segments intersect: compute intersection point.
	 */

	denom = a1 * b2 - a2 * b1;
	if ( denom == 0 )
		return false; // collinear
	offset = denom < 0 ? - denom / 2 : denom / 2;

	/* The denom/2 is to get rounding instead of truncating.  It
	 * is added or subtracted to the numerator, depending upon the
	 * sign of the numerator.
	 */

	if (inter) {
		num = b1 * c2 - b2 * c1;
		inter->x = ( num < 0 ? num - offset : num + offset ) / denom;
		num = a2 * c1 - a1 * c2;
		inter->y = ( num < 0 ? num - offset : num + offset ) / denom;
	}

	return true;
} /* lines_intersect */

// Distance of point C to line AB
double linePointDist(Pt &a, Pt &b, Pt &c, bool isSegment) {
	Pt ab = b - a;
	Pt ba = a - b;
	Pt ac = c - a;
	Pt bc = c - b;
	double d = ((double)crossProd(ab, ac)) / dist(a, b);
	if (isSegment) {
		int dot1 = dotProd(ab, bc);
		if (dot1 > 0)
			return dist(b, c);
		int dot2 = dotProd(ba, ac);
		if (dot2 > 0)
			return dist(a, c);
	}
	return abs(d);
}

double polygonArea(Pt p[], int n) {
	Num area = 0;
	for (int i = 1; i < n - 1; i++) {
		Pt e1 = p[i] - p[0];
		Pt e2 = p[i+1] - p[0];
		area += crossProd(e1, e2);
	}
	return abs(area / 2.0);
}

void convexHull(Pt x[], int n, vector<int> &hull) {
	hull.clear();
	int p = 0, i;
	// Find the leftmost point
	for (i = 1; i < n; i++)
		if (x[i] < x[p])
			p = i;

	int start = p;
	do {
		int next = -1;
		for (i = 0; i < n; i++) {
			// don't go back to the point you came from
			if (i == p) continue;

			// If there is no NEXT yet, set it to i
			if (next == -1) next = i;
			Pt pi = x[i] - x[p];
			Pt pn = x[next] - x[p];
			int cross = crossProd(pi, pn);

			if (cross < 0)
				next = i;
		}
		p = next;
		hull.push_back(next);
	} while (start != p);
}

/**
 * Rectangle
 */
struct Rect {
	Num left, right, top, bottom;
};

Rect rectIntersect(Rect &a, Rect &b) {
	Rect c;
	c.left = max(a.left, b.left);
	c.right = min(a.right, b.right);
	c.top = max(a.top, b.top);
	c.bottom = min(a.bottom, b.bottom);
	return c;
}

Rect rectUnion(Rect &a, Rect &b) {
	Rect c;
	c.left = min(a.left, b.left);
	c.right = max(a.right, b.right);
	c.top = min(a.top, b.top);
	c.bottom = max(a.bottom, b.bottom);
	return c;
}

bool pointIn(Pt &a, Rect &r) {
	return r.left <= a.x && a.x <= r.right &&
			r.bottom <= a.y && a.y <= r.top;
}

int main() {
	Pt a1(0, 0), a2(3, 0);
	Pt b1(1, 1), b2(1, -1);

	cout << "crossProd " << crossProd(b1, a2) << endl;

	cout << "intersect " << lineIntersect(a1, a2, b1, b2, 0) << endl;
	cout << "linePtDist " << linePointDist(a1, a2, b1, false) << endl;

	Pt poly[] = {a1, a2, b1};
	cout << "polygonArea " << polygonArea(poly, 3) << endl;

	Pt points[] = {a1, a2, b1, b2, Pt(2, 0) };
	vector<int> hull;
	convexHull(points, 5, hull);
	for(vector<int>::iterator it = hull.begin(); it != hull.end(); ++it)
		cout << *it << " ";
	cout << endl;

	return 0;
}
