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

typedef int Num;
const int maxn=200;
int N;

char data[maxn]; // 0: -, 1: +

Num solve() {
    int i, j, k;
    int cnt = 0;
    while (true) {
        for (i = 1; i < N; ++i) {
            if (data[i] != data[0])
                break;
        }

        if (i == N && data[0]) break; // done

        cnt++;

        // reverse
        for (j = 0, k = i - 1; j <= k; ++j, --k) {
            data[j] = !data[j];
            if (j != k) {
                data[k] = !data[k];
                swap(data[j], data[k]);
            }
        }
    };
    return cnt;
}

int main() {
    // input
    string basename("B-large");
    string in(basename + ".in");
    string out(basename + ".out");
#if BENCH
    freopen(in.c_str(), "r", stdin);
    if (1) // write to file
        freopen(out.c_str(), "w", stdout);
#endif
    int TC, tc, i;
    cin >> TC;
    for (tc = 0; tc < TC; tc++) {
        string line;
        cin >> line;
        N = line.length();
        for(i = 0; i < N; i++)
            data[i] = line[i] == '+';
        cout << "Case #" << (tc + 1) << ": " << solve() << endl;
    }
    return 0;
}
