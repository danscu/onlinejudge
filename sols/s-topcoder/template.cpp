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

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#endif // BENCH

typedef int Num;
const Num maxn = 1000006;
const Num INF = 10000000;

Num data[maxn];

Num solve() {
	return 0;
}

int main() {
	int T;
	Num n, i, j;
#if BENCH
	freopen("template.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		for (i = 0; i < n; i++) {
			cin >> data[i];
		}
		cout << "Case #" << tc + 1 << endl << solve() << endl;
	}
	return 0;
}
