/* 2d segment tree */
/* poj 2155 */

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

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 1000 + 1;
const int MAXTREE = maxn * 3;
typedef double Num;

// Segment tree stuff
#define xlson kx<<1, xl, mid
#define xrson kx<<1|1, mid+1, xr
#define ylson ky<<1, yl, mid
#define yrson ky<<1|1, mid+1, yr

#define defmidx int mid = (xl + xr) >> 1
#define defmidy int mid = (yl + yr) >> 1

const int root=1;
bool tree[MAXTREE][MAXTREE];

int num;
int n;
int x1, y1_, x2, y2; /* y1 is already defined somewhere */

void editY(int kx, int ky, int yl, int yr) {
    if (y1_ <= yl && yr <= y2) {
        tree[kx][ky] = !tree[kx][ky];
        return;
    }
    defmidy;
    if (y1_ <= mid) editY(kx, ylson);
    if (y2 > mid) editY(kx, yrson);
}

void editX(int kx, int xl, int xr) {
    if (x1 <= xl && xr <= x2) {
        editY(kx, 1, 1, n);
        return;
    }
    defmidx;
    if (x1 <= mid) editX(xlson);
    if (x2 > mid) editX(xrson);
}

void queryY(int kx, int ky, int yl, int yr) {
    if (tree[kx][ky]) num++;
    if (yl==yr) return;
    defmidy;
    if (y1_ <= mid) queryY(kx,ylson);
    else queryY(kx,yrson);
}

void queryX(int kx, int xl, int xr) {
    queryY(kx, 1, 1, n);
    if (xl == xr) return;
    defmidx;
    if (x1 <= mid) queryX(xlson);
    else queryX(xrson);
}

int main() {
#if BENCH
	freopen("files/poj2155_matrix.txt", "r", stdin);
#endif

	int t;
	int tc;
	scanf("%d",&tc);
	while(tc--) {
	    CLR(tree);
        scanf("%d %d",&n,&t);
	    REP(i,t) {
	        char ch;
            scanf(" %c %d %d", &ch, &x1, &y1_);
            if (ch == 'C') {
                scanf("%d %d", &x2, &y2);
                editX(1,1,n);
            } else {
                num = 0;
                queryX(1,1,n);
                printf((num & 1) ? "1\n" : "0\n");
            }
        }
	    printf("\n");
	}
	return 0;
}
