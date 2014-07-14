/* 2D 树状数组 */
/* poj 1195 mobile phones, IOI 2001 */

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

const int maxn = 1024 + 1;
int C[maxn][maxn];
int n;

inline int lowbit(int x) {
	return x & -x;
}

void bit2_update(int x, int y, int val) {
	int i, j;
    for (i = x; i <= n; i += lowbit(i))
        for (j = y; j <= n; j+= lowbit(j))
            C[i][j] += val;
}

/* compute the cumulative sum for index x */
int bit2_read(int x, int y) {
	int i,j,sum = 0;
	for (i = x; i > 0; i -= lowbit(i))
	    for (j = y; j > 0; j -= lowbit(j))
	        sum += C[i][j];
	return sum;
}

int bit2_rect_sum(int x1, int y1, int x2, int y2) {
    return bit2_read(x2, y2) - bit2_read(x1 - 1, y2) -
           bit2_read(x2, y1 - 1) +
           bit2_read(x1 - 1, y1 -1 );
}

int main() {
	// input
#if BENCH
	freopen("files/poj1195_mobile_phones.txt", "r", stdin);
#endif

	int x, y, op, l, b, r, t, a;
	while (scanf("%d",&op) != EOF)
	{
		switch (op) {
		case 0:
		    scanf("%d", &n);
		    REP(i,n+1)
		        CLRN(C[i], n+1);
		    break;
		case 1:
		    scanf("%d%d%d",&x,&y,&a);
		    bit2_update(x+1, y+1, a);
		    break;
		case 2:
		    scanf("%d%d%d%d",&l,&b,&r,&t);
		    int ans = bit2_rect_sum(l+1,b+1,r+1,t+1);
		    printf("%d\n",ans);
		    break;
		}
	}
	return 0;
}
