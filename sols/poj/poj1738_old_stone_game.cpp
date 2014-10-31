/*
 * POJ 1738 An old stone game
 * Problem: Minimium cost binary tree
 * Solution: Garcia Wachs algorithm
 */
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
#define DBG 1 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 500005;
const Num INF = numeric_limits<Num>::max();

int n, T;
Num data[maxn];
Num ans;

void combine(int k) {
	int tmp = data[k] + data[k-1], j;
	ans += tmp;
	FOR(i,k,T-2) data[i]=data[i+1];
	T--;
	for (j = k - 1; j > 0 && data[j-1] < tmp; j--)
		data[j] = data[j - 1];
	data[j] = tmp;
	while (j >= 2 && data[j] >= data[j - 2])
		tmp = T - j, combine(j-1), j = T - tmp;
}

// Garcia-Wachs algorithm for min-cost binary tree
Num solve() {
	T = 1, ans = 0;
	FOR(i,1,n-1) {
		data[T++] = data[i];
		while (T >= 3 && data[T-3] <= data[T-1])
			combine(T-2);
	}
	while (T>1) combine(T-1);
	return ans;
}

int main() {
#if BENCH
	freopen("files/poj1738_old_stone_game.txt","r",stdin);
#endif
	while (scanf("%d", &n), n) {
		REP(i,n)
			scanf("%d", &data[i]);
		printf("%d\n", solve());
	}
	return 0;
}
