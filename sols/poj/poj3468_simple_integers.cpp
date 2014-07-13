/* segment tree rmq */
/* poj 3468 ACed, bzoj(61.187.179.132) 3212 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <limits>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;

const int maxn = 101000;
const int MAXIND = maxn*4;
typedef long long Num;

Num val[maxn];
Num stree[MAXIND];
Num add[MAXIND];

void stree_pushup(int node) {
	stree[node] = stree[2 * node] + stree[2 * node + 1];
}

void stree_pushdown(int node, int x) {
	if (add[node]) {
		add[node*2] += add[node];
		add[node*2+1] += add[node];
		stree[node*2] += (Num)(x - (x/2)) * (Num) add[node];
		stree[node*2+1] += (Num)(x/2) * (Num) add[node];
		add[node] = 0;
	}
}

void stree_init(int node, int b, int e) {
	add[node] = 0;
	if (b == e) {
        stree[node] = val[b];
        return;
    }

	stree_init(2 * node, b, (b + e) / 2);
	stree_init(2 * node + 1, (b + e) / 2 + 1, e);
	stree_pushup(node);
}

void stree_update(int node, int b, int e, int i, int j, int d) {
    if (i <= b && j >= e) {
    	add[node] += d;
    	stree[node] += (Num)d * (Num)(e - b + 1);
    	return;
    }

    stree_pushdown(node, e - b + 1);

    if (i <= (b+e)/2)
    	stree_update(2*node, b, (b+e)/2, i, j, d);
    if (j > (b+e)/2)
    	stree_update(2*node+1, (b+e)/2+1, e, i, j, d);

    stree_pushup(node);
}

Num stree_query(int node, int b, int e, int i, int j) {
	if (i <= b && j >= e)
		return stree[node];

	stree_pushdown(node, e - b + 1);

	Num tmp = 0;
    if (i <= (b+e)/2)
    	tmp += stree_query(2*node, b, (b+e)/2, i, j);
    if (j > (b+e)/2)
    	tmp += stree_query(2*node+1, (b+e)/2+1, e, i, j);

    return tmp;
}

int main() {
#if BENCH
	freopen("files/poj3468_simple_integers.txt", "r", stdin);
#endif
	int i;
	int n, k;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i ++)
		scanf("%I64d", &val[i]);

	stree_init(1, 1, n);

	for (i = 0; i < k; i++) {
		char cmd = 0;
		int low, high;
		while (cmd != 'Q' && cmd != 'C') cmd = getchar();
		scanf("%d%d",&low,&high);

		if (cmd == 'Q')
			printf("%lld\n", stree_query(1, 1, n, low, high));
		else {
			int diff; scanf("%d",&diff);
			stree_update(1, 1, n, low, high, diff);
		}
	}
	return 0;
}
