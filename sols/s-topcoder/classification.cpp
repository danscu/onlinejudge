#include <iostream>
#include <cstdio>
#include <stack>
#include <cfloat>
#include <cmath>
#include <algorithm> // std::min/max
#include <climits>

using namespace std;

// 1/10 of total iterations
#define NDEC_ITERS 500000

#define MAXN 128
#define DBG 0

int N;

// used to find initial values
int xmin, ymin, xmax, ymax;

double w0;
double w1;
double w2;

struct Pt {
	int x, y; // x - row, y - column
	int c;
	Pt(int _x = 0, int _y = 0, int _c = 0) {
		x = _x; y = _y;
		c = _c;
	}
};

Pt p[MAXN];

double h(double x, double y) {
	return (double)1.0 / (1.0 + exp( - (w0 + w1 * x + w2 * y) ));
}

// returns error
double solve() {
	double err;
	double deltaWt;

	int iter = NDEC_ITERS * 10 - 1;
	int i;

	double lw0, lw1, lw2;

	// Initial values
	// Slope = 1, passing (minx, miny) and (maxx, maxy)
#if 0
	double a = (double)(ymax - ymin) / (xmax - xmin);
	double b = ymax - a * xmax;
#endif

	w2 = 0.4;
	w1 = 0.7;
	w0 = 1.0;

	// learning rate
	double lrate = 0.005;
//	double lrate_e = 0.001;

	do {
		// Last values
		lw0 = w0;
		lw1 = w1;
		lw2 = w2;

		// Compute intermediates
		double s0 = 0, s1 = 0, s2 = 0;

#if DBG
		err = 0;
#endif

		for (i = 0; i < N; i++) {
			double hxy = h(p[i].x, p[i].y);
			double m3 = (p[i].c - hxy) * hxy * (hxy - 1);
#if DBG
			err += fabs(p[i].c - hxy);
#endif

			s0 += m3;
			s1 += m3 * p[i].x;
			s2 += m3 * p[i].y;
		}

		// Update weights
		w0 = w0 - 2 * lrate * s0;
		w1 = w1 - 2 * lrate * s1;
		w2 = w2 - 2 * lrate * s2;

		deltaWt = fabs(w0 - lw0);
		deltaWt = max(deltaWt, fabs(w1 - lw1));
		deltaWt = max(deltaWt, fabs(w2 - lw2));

#if DBG
		cout << "Iter #" << iter << " err = " << err << endl;
#endif

	} while (deltaWt > 1e-5 && --iter);

	return err;
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
    freopen("classification.txt", "r", stdin);
#endif

    int T;
    cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> N;
#if 0
		ymin = xmin = INT_MAX;
		ymax = xmax = INT_MIN;
#endif
		int i;
		for (i = 0; i < N; i++) {
			cin >> p[i].x >> p[i].y >> p[i].c;
#if 0
			xmin = min(xmin, p[i].x);
			xmax = max(xmax, p[i].x);
			ymin = min(ymin, p[i].y);
			ymax = max(ymax, p[i].y);
#endif
		}

		solve();

		// Print the answer to standard output(screen).
		cout.setf(ios::fixed);
		cout.precision(4);
		cout << w0 << " " << w1 << " " << w2 << endl;
	}

	return 0;
}
