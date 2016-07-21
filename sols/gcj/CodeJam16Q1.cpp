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
Num N;

Num solve() {
    if (N == 0)
        return -1;

    bool usedDigit[10] = { false, };

    Num cur = 0;
    int cntDigits = 0;
    do {
        cur += N;
        Num tmp = cur;
        do {
            int c = tmp % 10;
            if (!usedDigit[c]) {
                usedDigit[c] = true;
                cntDigits++;
            }
            tmp /= 10;
        } while (tmp);
    } while (cntDigits != 10);

	return cur;
}

int main() {
	// input
	string basename("A-large");
	string in(basename + ".in");
	string out(basename + ".out");
#if BENCH
	freopen(in.c_str(), "r", stdin);
	if (1) // write to file
		freopen(out.c_str(), "w", stdout);
#endif
	int TC, tc;
	cin >> TC;
	for (tc = 0; tc < TC; tc++) {
		cin >> N;
		Num res = solve();
		cout << "Case #" << (tc + 1) << ": ";
		if (res >= 0)
		    cout << res;
		else
		    cout << "INSOMNIA";
		cout << endl;
	}
	return 0;
}
