//!! Not completed

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
#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;
int K, C, S;

void solve() {
    Num totalSize = 1;
    int i, j;
    for (i = 0; i < C; i++) {
        totalSize *= K;
    }

    // required length
    int R = K - (C - 1);

    if (S < R) {
        cout << "IMPOSSIBLE";
        return;
    }

    // Checking character i in original string
    // number of the form iii in base K. There are C digits in total.
    // i increments by 2
    for (i = 0; i < C; i++) {
        Num index = 0;
        Num groupSize = totalSize / K;

        for (j = 0; j < C; j++) {
            index += groupSize * (i * 2);
            groupSize /= K;
        }

        if (i) cout << " ";
        cout << index + 1;
    }
}

int main() {
    // input
    string basename("D-test");
    string in(basename + ".in");
    string out(basename + ".out");
#if BENCH
    freopen(in.c_str(), "r", stdin);
    if (0) // write to file
        freopen(out.c_str(), "w", stdout);
#endif
    int TC, tc;
    cin >> TC;
    for (tc = 0; tc < TC; tc++) {
        cin >> K >> C >> S;
        cout << "Case #" << (tc + 1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
