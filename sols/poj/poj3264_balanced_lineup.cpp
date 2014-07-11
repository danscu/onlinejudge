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

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 10000;
const int MAXIND = 1 << 18;

int val[maxn];
int stree[MAXIND];
int stree_max[MAXIND];
int ntree;

void __stree_init(int node, int b, int e) {
    if (b == e) {
        stree[node] = stree_max[node] = b;
    } else {
        // compute the values in the left and right subtrees
        __stree_init(2 * node, b, (b + e) / 2);
        __stree_init(2 * node + 1, (b + e) / 2 + 1, e);
        // search for the minimum value in the first and second half of the interval
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

int  __stree_query(int node, int b, int e, int i, int j) {
    int p1, p2;

    // if the current interval doesn't intersect, the query interval, return -1
    if (i > e || j < b)
        return -1;

    // if the current interval is included in the query interval, return stree[node]
    if (b >= i && e <= j)
        return stree[node];

    // compute the minimum position in the left and right part of the interval
    p1 = __stree_query(2*node, b, (b+e)/2, i, j);
    p2 = __stree_query(2*node+1, (b+e)/2+1, e, i, j);

    // return the position where the overall minimum is
    if (p1 == -1)
        return stree[node] = p2;
    if (p2 == -1)
        return stree[node] = p1;
    if (val[p1] <= val[p2])
        return stree[node] = p1;
    return stree[node] = p2;
}

int  __stree_query_max(int node, int b, int e, int i, int j) {
    int p1, p2;

    // if the current interval doesn't intersect, the query interval, return -1
    if (i > e || j < b)
        return -1;

    // if the current interval is included in the query interval, return stree[node]
    if (b >= i && e <= j)
        return stree_max[node];

    // compute the minimum position in the left and right part of the interval
    p1 = __stree_query_max(2*node, b, (b+e)/2, i, j);
    p2 = __stree_query_max(2*node+1, (b+e)/2+1, e, i, j);

    // return the position where the overall minimum is
    if (p1 == -1)
        return stree_max[node] = p2;
    if (p2 == -1)
        return stree_max[node] = p1;
    if (val[p1] >= val[p2])
        return stree_max[node] = p1;
    return stree_max[node] = p2;
}

int main() {
	// input
#if BENCH
	freopen("files/poj3264_balanced_lineup.txt", "r", stdin);
#endif
	int i;
	int n, k;
	cin >> n >> k;

	for (ntree = 1; ntree <= n; ntree *= 2)
	    ;

	for (i = 0; i < n; i ++)
	    cin >> val[i];

	__stree_init(1, 0, ntree);

	for (i = 0; i < k; i++) {
	    int low, high;
	    cin >> low >> high;
	    low--; high--;
	    cout << val[__stree_query_max(1, 0, ntree, low, high)] -
	            val[__stree_query(1, 0, ntree, low, high)] << endl;
	}
	return 0;
}
