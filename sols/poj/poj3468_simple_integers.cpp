/* segment tree rmq */

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

const int maxn = 100001;
const int MAXIND = 1 << 18;
int val[maxn];
int stree[MAXIND];
int stree_delta[MAXIND];
int ntree;

void __stree_init(int node, int b, int e) {
    if (b == e) {
        stree[node] = val[b];
    } else {
        // compute the values in the left and right subtrees
        __stree_init(2 * node, b, (b + e) / 2);
        __stree_init(2 * node + 1, (b + e) / 2 + 1, e);
        // search for the minimum value in the first and second half of the interval
        stree[node] = stree[2 * node] + stree[2 * node + 1];
    }
    stree_delta[node] = 0;
}

void __stree_update(int node, int b, int e, int i, int j, int d) {
    if (b == e) {
        stree_delta[node] += d;
        return;
    }

    // if the current interval doesn't intersect, the query interval, return -1
    if (i > e || j < b)
        return;

    // if the current interval is included in the query interval, return stree[node]
    if (b >= i && e <= j)
        stree_delta[node] += d;

    __stree_update(2*node, b, (b+e)/2, i, j, d);
    __stree_update(2*node+1, (b+e)/2+1, e, i, j, d);
}

int  __stree_query(int node, int b, int e, int i, int j) {
    int p1, p2;

    // if the current interval doesn't intersect, the query interval, return -1
    if (i > e || j < b)
        return -1;

    // if the current interval is included in the query interval, return stree[node]
    if (b >= i && e <= j)
        return stree[node] + stree_delta[node] * (e - b + 1);

    // compute the minimum position in the left and right part of the interval
    p1 = __stree_query(2*node, b, (b+e)/2, i, j);
    p2 = __stree_query(2*node+1, (b+e)/2+1, e, i, j);

    // return the position where the overall minimum is
    if (p1 == -1)
        return p2;
    if (p2 == -1)
        return p1;
    return p1 + p2;
}

int main() {
	// input
#if BENCH
	freopen("files/poj3468_simple_integers.txt", "r", stdin);
#endif
	int i;
	int n, k;
	cin >> n >> k;

	for (ntree = 1; ntree <= n; ntree *= 2)
	    ;
	ntree--;

	for (i = 0; i < n; i ++)
	    cin >> val[i];

	__stree_init(1, 0, ntree);

	for (i = 0; i < k; i++) {
	    char cmd;
	    int low, high;
	    cin >> cmd;
	    cin >> low >> high;
	    low--; high--;

	    if (cmd == 'Q')
	        cout << __stree_query(1, 0, ntree, low, high) << endl;
	    else {
	        int diff; cin >> diff;
	        __stree_update(1, 0, ntree, low, high, diff);
	    }
	}
	return 0;
}
