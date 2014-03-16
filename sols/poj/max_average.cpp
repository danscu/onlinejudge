/**
 * HDU 2993
 * 
 * Runtime Error (access_violation) ??
 */

#include <iostream>
#include <cstring>
#include <cstdio>
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

#define VERIFY 0

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define MAXN 100005
int s[MAXN];
list<int> curv; // 下凸折线

int getnum() {
	char cc;
	int dd;
	while (cc = getchar(), cc<'0'||cc>'9');
	dd=cc-'0';
	while (cc = getchar(), cc>='0'&&cc<='9')
		dd = dd*10+cc-'0';
	D(cout <<dd<<endl;)
	return dd;
}

double slope(int i, int j) {
	return 1.0*(s[i] - s[j]) / (i - j);
}

void prnum(int &n) {
	cout << n << " ";
}

double solve(int n, int k) {
	int i, j;
	double ans = 0;

	// add first point in bottom envelope
	curv.clear();
	curv.push_back(0);

	// search for maximum slope for i
	for (i = k; i <= n; i++) {
		j = i - k + 1; // first point in search set of i

		// pop front elements to find largest slope
		list<int>::iterator nextIt = curv.begin();
		while (curv.size()>1 && slope(i, curv.front()) <= slope(i, *(++nextIt)))
			curv.pop_front();

		// update slope for i
		ans = max(ans, slope(i, curv.front()));

		// before pushing j to curve, pop previous points which are popped
		// above j
		list<int>::reverse_iterator prevIt = curv.rbegin();
		while (curv.size()>1 &&
				slope(curv.back(), *(++prevIt)) >= slope(j, curv.back()))
			curv.pop_back();

		curv.push_back(j);
	}
	return ans;
}

int main() {
	int n,k,i;
	double ans = 0;

#if BENCH
	freopen("max_average.txt","r",stdin);
#endif

#if VERIFY
	srand(time(NULL));
	for (int tc=0;tc<1000;tc++) {
		n = 1 + rand()%10000;
		k = 1 + rand()%n;
#else
	while (cin>>n>>k) {
#endif

		// cumulative sums
		s[0]=0;
		for (i=1;i<=n;i++)
			s[i]=s[i-1]+
#if !VERIFY
			getnum();
#else
		rand() % 4000;
#endif

		D(for_each(s, s+n, prnum); cout<<endl;)

		ans = solve(n, k);

		cout.precision(2);
		cout << fixed << ans << endl;
	}

	return 0;
}
