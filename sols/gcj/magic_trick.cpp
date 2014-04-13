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
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

int ans1, ans2;
int data[2][4][4];

void solve() {
	set<int> cards;
	REP(i,4)
		cards.insert(data[0][ans1][i]);
	int cnt = 0, card = -1;
	REP(i,4)
		if (cards.find(data[1][ans2][i]) != cards.end()) {
			if (cnt++ == 0)
				card = data[1][ans2][i];
		}
	if (cnt == 0)
		cout << "Volunteer cheated!";
	else if (cnt == 1)
		cout << card;
	else
		cout << "Bad magician!";
	cout << endl;
}

int main() {
	int T;
#if BENCH
	freopen("A-small-attempt0.in","r",stdin);
	freopen("magic_trick.out","w",stdout);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> ans1; ans1--;
		REP(i,4)
		REP(j,4)
			cin >> data[0][i][j];
		cin >> ans2; ans2--;
		REP(i,4)
		REP(j,4)
			cin >> data[1][i][j];
		cout << "Case #" << tc + 1 << ": ";
		solve();
	}
	return 0;
}
