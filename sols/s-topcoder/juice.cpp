#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

typedef int Num;
const Num maxn = 501;
const Num maxw = 10005;
const Num INF = 10000000;

struct Juice {
    Num price;
    Num weight;
};

Juice juice[maxn];
int n, empty, full;

int dp[maxw];

Num solve() {

#if DBG
    REP(i,n) {
        cout << juice[i].price << " " << juice[i].weight <<
                " " << juice[i].pw << endl;
    }
#endif

    int W = full - empty;
    int i,j;

    for (i=1,dp[0]=0; i<=W; i++)
        dp[i]=INF;

    for (i=0;i<n;i++) {
       for (j=juice[i].weight; j<=W; j++)
           dp[j] = min(dp[j], dp[j-juice[i].weight] + juice[i].price);
    }

    if (dp[W]!=INF)
        cout << dp[W] << endl;
    else
        cout << "impossible" << endl;

    return 0;
}

int main() {
    int T;
    Num i, j;
#if BENCH
    freopen("files/juice_sample_input.txt","r",stdin);
#endif

    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        cin >> empty >> full;
        cin >> n;
        for (i = 0; i < n; i++)
            cin >> juice[i].price >> juice[i].weight;
        solve();
    }
    return 0;
}

