#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const double INF = 1e10;
double C, F, X;

double solve() {
	double time_get_n_farm = 0;
	double last_time_all_done = INF, time_all_done = 0;
	double rate = 2;

	for (int farm = 0; ; farm++) {
		time_all_done = time_get_n_farm + X / rate;
		if (time_all_done > last_time_all_done)
			break;
		time_get_n_farm += C / rate;
		rate += F;
		last_time_all_done = time_all_done;
	}
	return last_time_all_done;
}

int main() {
	int T;
#if BENCH
	freopen("cookie_clicker_alpha_large.txt","r",stdin);
	freopen("cookie_clicker_alpha_large.out","w",stdout);
#endif
	cout.precision(7);
	cout.setf(ios_base::fixed);
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> C >> F >> X;
		cout << "Case #" << tc + 1 << ": ";
		cout << solve() << endl;
	}
	return 0;
}
