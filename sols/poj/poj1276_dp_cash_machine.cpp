/* poj 1276 */
/* dp, multiple backsack, convert to 0-1 backsack using binary representation */

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
const Num maxn = 11;
const Num MAXS = 100001;
const Num INF = numeric_limits<Num>::max();

int n;			// n: denominations
Num N;			// N: number of bills
Num D;			// D: bill value

// [v] = max value for pack of size v
// This dp array can be seen as dp[i][v] where i is the max item considered
// But this dimension can be omitted by reusing the 1D array
int dp[MAXS];
int cash;

// 0-1 背包必须从dp[cash]开始，因为dp[cash]是最后要读出的值
// 若从dp[0]开始，若背包未满，最大价值dp[cash]将无值可读，需要搜索dp[*]才能确定.
void zeroOnePack(int cost) {
	for (int v = cash; v >= cost; v--)
		dp[v] = max(dp[v], dp[v - cost] + cost);
}

// 对总数为C的某类物体，把C表示为二进制数，记为c7,c6,c5,c4,c3,c2,c1,c0（假定总数<=255)，
// 若某位ci = 1, 则将2^ci个物体看作一个新物体, 这样一类这样的物体便转化为O(log(C))个单一
// 物体，用0-1背包求解。
void multiplePack(int cost, int count) {
	int k = 1;
	while (k < count) {
		zeroOnePack(k * cost);
		count -= k;
		k *= 2; // 二进制思想优化
	}
	zeroOnePack(count * cost);
}

int main() {
#if BENCH
	freopen("files/poj1276_dp_cache_machine.txt","r",stdin);
#endif
	while (~scanf("%d%d", &cash, &n)) {
		CLR(dp);
		REP(i,n) {
			scanf("%d %d", &N, &D);
			multiplePack(D, N);
		}
		printf("%d\n", dp[cash]);
	}
	return 0;
}
