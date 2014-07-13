/* segment tree rmq */
/* poj 3264, tju 2762 */
/* AC */

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

const int maxn = 50005;
const int MAXIND = maxn * 4;

typedef int Num;
Num val[maxn];
Num stree[MAXIND];
Num stree_max[MAXIND];
int ntree;

void __stree_init(int node, int b, int e) {
	if (b == e) {
		stree[node] = stree_max[node] = b;
	} else {
		__stree_init(2 * node, b, (b + e) / 2);
		__stree_init(2 * node + 1, (b + e) / 2 + 1, e);
		if (val[stree[2 * node]] <= val[stree[2 * node + 1]])
			stree[node] = stree[2 * node];
		else
			stree[node] = stree[2 * node + 1];

		if (val[stree_max[2 * node]] >= val[stree_max[2 * node + 1]])
			stree_max[node] = stree_max[2 * node];
		else
			stree_max[node] = stree_max[2 * node + 1];
	}
}

Num  __stree_query(int node, int b, int e, int i, int j) {
	Num p1, p2;

	if (i > e || j < b)
		return -1;

	if (b >= i && e <= j)
		return stree[node];

	p1 = __stree_query(2*node, b, (b+e)/2, i, j);
	p2 = __stree_query(2*node+1, (b+e)/2+1, e, i, j);

	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	if (val[p1] <= val[p2])
		return p1;
	return p2;
}

int  __stree_query_max(int node, int b, int e, int i, int j) {
	int p1, p2;

	if (i > e || j < b)
		return -1;

	if (b >= i && e <= j)
		return stree_max[node];

	p1 = __stree_query_max(2*node, b, (b+e)/2, i, j);
	p2 = __stree_query_max(2*node+1, (b+e)/2+1, e, i, j);

	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	if (val[p1] >= val[p2])
		return p1;
	return p2;
}

int main() {
	// input
#if BENCH
	freopen("files/poj3264_test.in", "r", stdin);
	freopen("files/poj3264_test.out.2", "w", stdout);
#endif
	int i;
	int n, k;
	scanf("%d%d",&n,&k);

	for (ntree = 1; ntree < n; ntree *= 2)
		;
	ntree--;

	for (i = 0; i < n; i ++)
		scanf("%d",&val[i]);

	__stree_init(1, 0, ntree);

	for (i = 0; i < k; i++) {
		int low, high;
		scanf("%d%d",&low,&high);
		low--; high--;
		if (low > high)
			swap(low, high);
		printf("%d\n", val[__stree_query_max(1, 0, ntree, low, high)] -
				val[__stree_query(1, 0, ntree, low, high)]);
	}
	return 0;
}
