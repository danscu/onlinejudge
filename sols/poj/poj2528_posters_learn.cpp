/* segment tree + discretization */
/* poj 2528, uva 10587 */

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

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 25000;
//const int maxn = 100;
const int MAXIND = 3*maxn;

bool stree[MAXIND];

struct Poster {
    int pos, num;
} posters[maxn];

int ntree;
bool newVis;

bool cmpPos(const Poster &a, const Poster &b) {
    return a.pos < b.pos;
}

bool cmpPosNum(const Poster &a, const Poster &b) {
    return a.num > b.num || (a.num == b.num && a.pos < b.pos);
}

void __stree_init(int node, int b, int e) {
    stree[node] = false;
    int mid = (b + e) / 2;
    if (b != e) {
        __stree_init(node*2, b, mid);
        __stree_init(node*2+1, mid+1, e);
    }
}

void __stree_dump(int node, int b, int e) {
    if (b > e)
        return; // invalid
    printf("[%d] %d-%d %d\n", node, b, e, stree[node]);
    if (b == e)
        return;
    __stree_dump(2*node, b, (b+e)/2);
    __stree_dump(2*node+1, (b+e)/2+1, e);
}

void __stree_query(int node, int b, int e, int i, int j) {
    if (stree[node])
        return;

    // the interval is exactly [i,j]
    if (b == i && e == j) {
        stree[node] = true;
        newVis = true; // the new poster is visible
        return;
    }

    if (j <= (b+e)/2)
        __stree_query(2*node, b, (b+e)/2, i, j);
    else if (i >= (b+e)/2+1)
        __stree_query(2*node+1, (b+e)/2+1, e, i, j);
    else {
        __stree_query(2*node, b, (b+e)/2, i, (b+e)/2);
        __stree_query(2*node+1, (b+e)/2+1, e, (b+e)/2+1, j);
    }

    stree[node] = stree[2*node] & stree[2*node+1];
}

int main() {
	// input
#if BENCH
	freopen("files/poj2528_poster_learn.txt", "r", stdin);
#endif
	int i;
	int tc, c, n;
	cin >> c;
	for (tc =0; tc<c;tc++) {
        cin >> n;
        for (i = 0; i < n; i ++) {
            cin >> posters[2*i].pos >> posters[2*i+1].pos;
            posters[2*i].num = posters[2*i+1].num = i;
        }

        sort(posters, posters+2*n, cmpPos);

        // discretization
        int k = 0, pre = 0;
        for (i=0; i<2*n; i++) {
            if (posters[i].pos != pre) {
                pre = posters[i].pos;
                posters[i].pos = ++k;
            } else
                posters[i].pos = k;
        }

        // ? necessary?
//        for (ntree = 1; ntree < k; ntree *= 2)
//            ;
        ntree = k;

        __stree_init(1, 1, ntree); /* TODO try (1, 0, k) */

        sort(posters,posters+2*n,cmpPosNum);
        int ans = 0;

        for (i = 0; i < 2*n; i += 2) {
            int left = posters[i].pos;
            int right = posters[i+1].pos;
            newVis = false;
            __stree_query(1, 1, ntree, left, right);
            if (newVis) ans++;
#if DBG
            printf("treedump------------------\n");
            __stree_dump(1, 1, ntree);
#endif
        }

        printf("%d\n", ans);
	}
	return 0;
}
