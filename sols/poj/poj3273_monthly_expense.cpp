/*
 * POJ 3273 Monthly Expense
 * Greedy + Binary search
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
const Num maxn = 100010;
const Num INF = numeric_limits<Num>::max();

int n,m;
Num data[maxn];

Num binarySearch(int low, int high) {
	while (low <= high) {
		int mid = (low + high) / 2;
		int count = 1, sum = 0;
		REP(i,n) {
			if (sum + data[i] <= mid)
				sum += data[i];
			else
				sum = data[i], count++;
		}
		if (count > m)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

Num solve() {
	Num maxnum = 0, sum = 0;
	REP(i,n) {
		sum += data[i];
		maxnum = max(maxnum, data[i]);
	}
	return binarySearch(maxnum, sum);
}

int main() {
#if BENCH
	freopen("files/poj3273_monthly_expense.txt","r",stdin);
#endif
	scanf("%d%d", &n, &m);
	REP(i,n) {
		scanf("%d", &data[i]);
	}
	printf("%d\n", solve());
	return 0;
}
