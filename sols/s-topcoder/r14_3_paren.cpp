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
#define DBG 0 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stdout, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef unsigned long long Num;
const Num maxn = 100006;
const Num MOD = 1000000007;

/*
 * Total symbols 2N, currently K open, M close, how many continuations?
 * D(K,M,N) = Binom(2N - M - K, N - M) - Binom(2N - M - K, N - M + 1)
 *
 * Let A = 2N - M - K, B = N - M
 * The number can be simplified to be
 *   Binom(A, B) (2B - A + 1) / (B + 1)
 *
 * So D(K,M,N) = Binom(2N - M - K, N - M) (K - M + 1) / (N - M + 1)
 *
 * Algorithm:
 * 1. For each character in the string
 * 2.     if the character is (, K++
 * 3.        tmp = string before ( and add a )
 * 4.        idx += D(k,m,n) for tmp
 * 5.     if the character is ), M++
 * 6. idx is the result
 */

char str[maxn];
int n;

Num getBinom(int n, int k) {
	Num t = 1;
	if (k < n - k)
		for (int i = n; i >= n - k + 1; i--)
			t = t * i / (n - i + 1) % MOD;
	else
		for (int i = n; i >= k + 1; i--)
			t = t * i / (n - i + 1) % MOD;
	return t;
}

Num getD(int K, int M, int N) {
	Num d = getBinom(2*N - M - K, N - M) * (K - M + 1) / (N - M + 1) % MOD;
	D("getD K=%d M=%d N=%d D(k,m,n)=%lld\n", K,M,N,d);
	return d;
}

Num index_correct(const char *s, int L) {
	Num idx = 0;
	int open = 0;
	int close = 0;
	for (int i = 0; i < L; i++) {
		if (s[i] == '(') {
			if (open)
				idx = (idx + getD(open, close + 1, L / 2)) % MOD;
			open++;
		} else {
			// ')'
			close++;
		}
	}
	return idx;
}

void solve() {
    int open = 0;
    int swaps = 0;
    REP(i,n) {
        if (str[i] == '(') {
            open++;
        } else {
            // )
            if (open == 0) {
                // invalid, search
                int j = i + 1;
                while (j < n && str[j] != '(') j++;
                if (j < n) {
                    swap(str[i], str[j]); swaps++;
                    open++;
                } else {
                    printf("-1\n");
                    return;
                }
            } else
                open--;
        }
    }
    if (open) {
        printf("-1\n");
        return;
    }
    //Num idx = index_slow(str, 0, n, n / 2);
    Num idx = index_correct(str, n);
    printf("%d %lld\n", swaps, (1 + idx) % MOD) ;
}

int main() {
#if BENCH
    freopen("files/r14_3_gen.txt","r",stdin);
#endif
    int nlim = 30000;
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        scanf("%s", str); n = strlen(str);
        printf("Case #%d\n", tc + 1);
        if (nlim && n > nlim)
            printf("-1\n");
        else
            solve();
    }
    return 0;
}
