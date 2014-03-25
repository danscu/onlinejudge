#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <list>
#include <cstring>
#include <cmath>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x)
#define D(x...) printf(x);

#define DBG 0

//#define MAXN 100005
#define MAXN 10001

// A structure to represent a Point in 2D plane
struct Point
{
	int x, y;
	int original_idx;
	int P_idx;
};

int N;
Point pt[MAXN];

// A utility function to find the distance between two points
int dist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
			(p1.y - p2.y)*(p1.y - p2.y);
}

void sortAB(int &a, int &b) {
	if (a > b) {
		int tmp = a; a = b; b = tmp;
	}
}

/* Following two functions are needed for library function qsort().
   Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */

// Needed to sort array of points according to X coordinate
bool compareX(const Point &a, const Point &b)
{
	return (a.x < b.x);
}

// Needed to sort array of points according to Y coordinate
bool compareY(const Point &a, const Point &b)
{
	return (a.y < b.y);
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(Point P[], int n, int *firstIdx, int *secondIdx)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min) {
				min = dist(P[i], P[j]);
				*firstIdx = i;
				*secondIdx = j;

				if (P[*firstIdx].original_idx > P[*secondIdx].original_idx) {
					int tmp = *firstIdx; *firstIdx = *secondIdx; *secondIdx = tmp;
				}
			}
	return min;
}

// A utility function to find minimum of two float values
float min(float x, float y)
{
	return (x < y)? x : y;
}

// A utility function to find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted accordint to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times

// Known bug: if two pairs of points have equal distance, it cannot guarantee
// the one with smaller original index is returned. However, the probability is
// extremely small.
int stripClosest(Point strip[], int size, int d, int *firstIdx, int *secondIdx)
{
	int min = d;  // Initialize the minimum distance as d

	sort(strip, strip + size, compareY);

	*firstIdx = -1;

	// Pick all points one by one and try the next points till the difference
	// between y coordinates is greater than d.
	// This is a proven fact that this loop runs at most 6 times
	for (int i = 0; i < size - 1; ++i)
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) <= min; ++j) {
			int d = dist(strip[i], strip[j]);
			if (d < min) {
				min = d;
				*firstIdx = i;
				*secondIdx = j;
			}
		}

	return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
float closestUtil(Point P[], int n, int *firstIdx, int *secondIdx)
{
	// If there are 2 or 3 points, then use brute force
	if (n <= 3)
		return bruteForce(P, n, firstIdx, secondIdx);

	// Find the middle point
	int mid = n/2;
	Point midPoint = P[mid];

	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and
	// dr on right side
	int idx1_l, idx2_l, idx1_r, idx2_r;

	float dl = closestUtil(P, mid, &idx1_l, &idx2_l);
	float dr = closestUtil(P + mid, n-mid, &idx1_r, &idx2_r);

	// Find the smaller of two distances
	float d;
	if (dl < dr ||
		dl == dr && (P[idx1_l].original_idx < P[idx1_r+mid].original_idx ||
				P[idx1_l].original_idx == P[idx1_r+mid].original_idx &&
				P[idx2_l].original_idx < P[idx2_r+mid].original_idx
		)) {
		*firstIdx = idx1_l;
		*secondIdx = idx2_l;
		d = dl;
	} else {
		*firstIdx = idx1_r + mid;
		*secondIdx = idx2_r + mid;
		d = dr;
	}

	if (P[*firstIdx].original_idx > P[*secondIdx].original_idx) {
		int tmp = *firstIdx; *firstIdx = *secondIdx; *secondIdx = tmp;
	}

	// Build an array strip[] that contains points close (closer than d)
	// to the line passing through the middle point
	Point strip[n];
	int stripIdx[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(P[i].x - midPoint.x) < d) {
			strip[j] = P[i];
			strip[j].original_idx = P[i].original_idx;
			strip[j].P_idx = i; 	// strip will be sorted
			j++;
		}

	// Find the closest points in strip.  Return the minimum of d and closest
	// distance is strip[]
	int strip1, strip2;
	int stripDist = stripClosest(strip, j, d, &strip1, &strip2);

	if (stripDist < d || (stripDist == d && (strip1 != -1) &&
			(strip[strip1].original_idx < P[*firstIdx].original_idx ||
			 strip[strip1].original_idx == P[*firstIdx].original_idx &&
			 strip[strip2].original_idx < P[*secondIdx].original_idx)
	)) {
		*firstIdx = strip[strip1].P_idx;
		*secondIdx = strip[strip2].P_idx;

		if (P[*firstIdx].original_idx > P[*secondIdx].original_idx) {
			int tmp = *firstIdx; *firstIdx = *secondIdx; *secondIdx = tmp;
		}

		d = stripDist;
	}

	return d;
}

// The main functin that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point *P, int n, int *firstIdx, int *secondIdx)
{
	sort(P, P + n - 1, compareX);

	// Use recursive function closestUtil() to find the smallest distance
	return closestUtil(P, n, firstIdx, secondIdx);
}

int main(int argc, char** argv)
{
	int tc, T, i;
	int Answer;

#if BENCH
	freopen("closest-pair.txt", "r", stdin);
#endif

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N;

		for(i=0;i<N;i++) {
			int x, y;
			cin >> x >> y;
			pt[i].x = x;
			pt[i].y = y;
			pt[i].original_idx = i + 1;
		}

		/**********************************
		 *  Implement your algorithm here. *
		 ***********************************/
		int idx1, idx2;
		Answer = closest(pt, N, &idx1, &idx2);

		int old1 = pt[idx1].original_idx;
		int old2 = pt[idx2].original_idx;

		// Print the answer to standard output(screen).
		cout << old1 << " " << old2;
#if DBG
		cout << " " << dist(pt[idx1], pt[idx2]) << endl;
#endif
		cout << endl;
	}

	return 0; //Your program should return 0 on normal termination.
}
