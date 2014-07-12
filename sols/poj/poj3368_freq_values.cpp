/* poj 3368, frequent values */
/* rmq */

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

#ifdef BENCH

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

#if DBG
const int maxn = 20;
#else
const int maxn = 100006;
#endif

typedef int Num;
Num raw[maxn];

// Sparse Table (ST algo)
Num D[maxn];
int MAX[maxn][20];

void st_prep(int n) {
    int i,j,k;
    REP(i,n)
        MAX[i][0] = D[i];
    k = log((double)(n+1)) / log(2.0);
    for (j = 1; j <= k; j++)
        for (i = 0; i + (1 << j) - 1 < n; i++)
            MAX[i][j] = max(MAX[i][j-1],
                            MAX[i + (1<<(j-1))][j-1]);
}

int st_rmq_max(int l, int r) {
    if (l > r)
        return 0;
    int k = log((double)(r-l+1)) / log(2.0);
    return max(MAX[l][k], MAX[r-(1<<k)+1][k]);
}

int main() {
    // input
#if BENCH
    freopen("files/poj3368_freq_values.txt", "r", stdin);
#endif
    int n, q;
    do {
        scanf("%d",&n);
        if (!n)
            break;

        scanf("%d",&q);
        REP(i,n)
            scanf("%d",&raw[i]);

        // count number chains
        CLRN(D,n);
        FOR(i,0,n-1) {
            if (i > 0 && raw[i] == raw[i-1])
                D[i] = D[i-1] + 1;
            else
                D[i]++;
        }

        // ST-prep
        st_prep(n);

        REP(i,q) {
            int first, last;
            scanf("%d%d",&first,&last);
            first--; last--;

            int start;
            for (start = first; start > 0 && start <= last && raw[start] == raw[start-1];)
                start++;

            int runLen = st_rmq_max(start, last);
            int ans = max(runLen, start - first);

            printf("%d\n", ans);
        }
    } while (1);
    return 0;
}
