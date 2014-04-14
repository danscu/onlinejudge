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
#include <iomanip>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

int N;
const int MOD = 1000;

template<int size>
struct Mat {
	int dat[size][size];
	Mat operator*(const Mat &rhs) const {
		Mat res;
		REP(i, size)
		REP(j, size) {
			res.dat[i][j] = 0;
			REP(k, size) {
				res.dat[i][j] += dat[i][k] * rhs.dat[k][j];
				res.dat[i][j] %= MOD;
			}
		}
		return res;
	}

	Mat operator+(const Mat &rhs) const {
		Mat res;
		REP(i, size)
		REP(j, size)
			res.dat[i][j] = (dat[i][j] + rhs.dat[i][j]) % MOD;
		return res;
	}

	Mat(int diag = 0) {
		REP(i,size) {
			memset(dat[i], 0, sizeof(dat[i]));
			dat[i][i] = diag;
		}
	}
};

Mat<2> mp[32];

void prep() {
	Mat<2> m1;
	m1.dat[0][0] = 3;
	m1.dat[0][1] = 5;
	m1.dat[1][0] = 1;
	m1.dat[1][1] = 3;

	mp[0] = m1;
	FOR(i,1,31) {
		m1 = m1 * m1;
		mp[i] = m1;
	}
}

int solve() {
	prep();
	// (3 + #5)^n = 2An - (3 - #5)^n
	// [A(n), B(n)] = [3 5; 1 3] * [A(n-1), B(n-1)]
	// A1 = 3, B1 = 1

	// get m^n
	int n = N - 1;
	Mat<2> mat(1);

	for (int i = 0; n; i++, n>>=1)
		if (n & 1)
			mat = mat * mp[i];

	int a0 = 3, b0 = 1;
	if (N > 1)
		a0 = (a0 * mat.dat[0][0] + b0 * mat.dat[0][1]) % MOD;

	return (2 * a0 - 1) % MOD;
}

int main() {
	int T;
#if BENCH
	freopen("2008_R1A_numbers_large.txt","r",stdin);
	freopen("2008_R1A_numbers_large.out","w",stdout);
#endif
	prep();
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N;
		cout << "Case #" << tc + 1 << ": ";
		cout << setfill('0') << setw(3) << solve() << endl;
	}
	return 0;
}
