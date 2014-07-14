/* 树状数组 */
/* poj 2352 stars */

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

const int maxn = 15001;
const int maxm = 32002;
int a[maxm];
int ans[maxn];
int n;

inline int lowbit(int x) {
	return x & -x;
}

void bit_update(int idx, int val) {
	while (idx <= maxm) {
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

int main() {
	// input
#if BENCH
	freopen("files/poj2352_stars.txt", "r", stdin);
#endif

	int t;
	scanf("%d", &n);

	int i, x, y;
	for (i = 0; i < n; i++) {
		scanf("%d%d",&x,&y);
		x+=1; // idx cannot be 0
		ans[bit_read(x)]++;
		bit_update(x,1);
	}

	for (i = 0; i < n; i++)
		printf("%d\n", ans[i]);

	return 0;
}
