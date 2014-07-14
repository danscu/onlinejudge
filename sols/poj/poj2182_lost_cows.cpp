/* 树状数组 */
/* poj 2182 */

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
#include <fstream>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 8004;
stack<int> s;
int a[maxn];
int ans[maxn];
int n;

inline int lowbit(int x) {
	return x & -x;
}

void bit_update(int idx, int val) {
	while (idx <= n) {
		a[idx] += val;
		idx += lowbit(idx);
	}
}

/* compute the cumulative sum for index x */
int bit_read(int idx) {
	int sum = 0;
	while (idx > 0) {
		sum += a[idx];
		idx -= lowbit(idx);
	}
	return sum;
}

int bsearch(int l, int r, int x) {
	while (l < r) {
		int mid = (l + r) >> 1;
		if (x <= bit_read(mid))
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main() {
	// input
#if BENCH
	freopen("files/poj2182_lost_cows.txt", "r", stdin);
#endif

	int t;
	while (scanf("%d", &n) != EOF) {
		CLRN(a, n + 2);
		int i;
		for (i = 1; i < n; i++) {
			bit_update(i+1, 1);
			scanf("%d",&t);
			s.push(t);
		}

		while (i > 1) {
			int x = bsearch(1, n, s.top());
			ans[i--] = x;
			bit_update(x, -1);
			s.pop();
		}

		ans[1] = bsearch(1, n, 0);

		for (i = 1; i <= n; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
