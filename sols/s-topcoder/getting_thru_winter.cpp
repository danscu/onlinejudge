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

#ifdef BENCH
# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH
#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);

const int maxn = 1005;
const int maxk = 1005;

typedef long long Num;

const Num INF = 10000000;
Num N,K,B;

struct Pt {
	Num x, y;
	bool operator<(const Pt& b) const {
		return x < b.x || (x == b.x && y < b.y);
	}
};

enum EndType {
	SINGLE, DOUBLE, ETMAX
};

struct State {
	Num area;		// cover area
	Num top; 		// last top index or index for both if et==DOUBLE
	Num bottom;		// last bottom index
	State (Num area = 0, Num top = 0, Num bot = 0)
	: area(area), top(top), bottom(bot) { }
};

ostream &operator<<(ostream &os, State &s) {
	os << "(" << s.area << "," << s.top << "," << s.bottom << ")";
	return os;
}

Pt p[maxn];
State s[maxn][maxk][ETMAX]; // s[i]: best solution for [1..i] trees

Num solve() {
	int i,j;
	sort(p+1, p+1+N);
	//base
	s[0][0][SINGLE] = State(0, -INF, -INF);
	s[0][0][DOUBLE] = State(0, -INF, -INF);
	for (i=1;i<=N;i++) {
		s[i][0][SINGLE] = State(INF, -INF, -INF);
		s[i][0][DOUBLE] = State(INF, -INF, -INF);
	}

	for (j=1;j<=K;j++) {
		for (i=1;i<=N;i++) {
			// add or extend a bar
			Num addArea = s[i-1][j-1][SINGLE].area + 1;
			Num addAreaDouble = s[i-1][j-1][DOUBLE].area + 1;
			Num extendArea = s[i-1][j][SINGLE].area + p[i].x -
					(p[i].y == 2 ? s[i-1][j][SINGLE].top : s[i-1][j][SINGLE].bottom);

			if (min(addArea, addAreaDouble) <= extendArea) {
				s[i][j][SINGLE] = s[i-1][j-1][addArea <= addAreaDouble ? SINGLE : DOUBLE];
				s[i][j][SINGLE].area = min(addArea, addAreaDouble);
			} else {
				s[i][j][SINGLE] = s[i-1][j][SINGLE];
				s[i][j][SINGLE].area = extendArea;
			}
			if (p[i].y == 2)
				s[i][j][SINGLE].top = p[i].x;
			else
				s[i][j][SINGLE].bottom = p[i].x;

			// add or extend a new double-bar
			addArea = p[i-1].x == p[i].x ? INF : s[i-1][j-1][SINGLE].area + 2;
			addAreaDouble = s[i-1][j-1][DOUBLE].area + 2;
			extendArea = s[i-1][j][DOUBLE].area + (p[i].x - s[i-1][j][DOUBLE].top) * 2;
			if (min(addArea, addAreaDouble) <= extendArea)
			{
				s[i][j][DOUBLE] = s[i-1][j-1][addArea <= addAreaDouble ? SINGLE : DOUBLE];
				s[i][j][DOUBLE].area = min(addArea, addAreaDouble);
			} else {
				s[i][j][DOUBLE] = s[i-1][j][DOUBLE];
				s[i][j][DOUBLE].area = extendArea;
			}
			s[i][j][DOUBLE].top = p[i].x;
		}
	}

#if DBG
	for (i=1;i<=N;i++) {
		for (j=1;j<=K;j++)
			cout << s[i][j][SINGLE] << " ";
		cout << endl;
	}
	cout << endl;
	for (i=1;i<=N;i++) {
		for (j=1;j<=K;j++)
			cout << s[i][j][DOUBLE] << " ";
		cout << endl;
	}

#endif
	Num minArea = numeric_limits<Num>::max();
	for (j=1; j<=K; j++) {
		Num areaj = min(s[N][j][DOUBLE].area, s[N][j][SINGLE].area);
		minArea = min(minArea, areaj);
	}
	return minArea;
}

int main() {
	int T,i;
#if BENCH
	freopen("getting_thru_winter.txt","r",stdin);
#endif
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N >> K >> B;
		for (i=1;i<=N;i++) {
			Num r,c;
			cin >> r >> c;
			p[i].y = r; p[i].x = c;
		}
		cout << solve() << endl;
	}
	return 0;
}
