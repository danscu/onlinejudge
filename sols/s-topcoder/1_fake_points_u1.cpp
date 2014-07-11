#define _BSD_SOURCE

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

typedef long long int ll;
typedef unsigned long long int ull;
typedef unsigned int ui;

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x)   ((x) >= 0 ? (x) : -(x))
#define SWAP(type,x,y) do { type __tmp = x; x = y; y = __tmp; } while (0)
#define CLR(a) memset(&(a), 0, sizeof(a))
#define CLRA(a,n) memset(a, 0, (n) * sizeof(a[0]))

#ifdef DEBUG
#define DBG printf
#else
#define DBG(...) do { } while(0)
#endif

#define NMAX 100005

int N, K;
int X[NMAX], Y[NMAX];
int SX[NMAX], ISX[NMAX], SY[NMAX];

int stree[1 << 18], nStree, lStree;
int stLow[1 << 18], stHigh[1 << 18], stExtra[1 << 18];

void stree_init(int N)
{
	for (nStree = 1; nStree < N; nStree *= 2)
		;
	DBG("stree_init(N=%d) nStree=%d\n", N, nStree);
	CLRA(stree, 2 * nStree);
	CLRA(stExtra, 2 * nStree);
	//printf("nStree=%d\n", nStree);
	int v, step, p;
	for (v = 1, step = nStree; v < 2 * nStree; step /= 2) {
		//printf("+nStree=%d v=%d\n", nStree, v);
		for (p = 0; p < nStree; p += step, ++v) {
			stLow[v] = p;
			stHigh[v] = p + step - 1;
		}
		//printf("-nStree=%d v=%d\n", nStree, v);
	}
#ifdef DEBUG
	//printf("nStree=%d\n", nStree);
	printf("stLH=");
	for (v = 0; v < 2 * nStree; ++v) {
		if ((v & (v - 1)) == 0)
			putchar('|');
		printf(" (%d-%d)", stLow[v], stHigh[v]);
	}
	puts("");
#endif
		
	/*int step = nStree;
	for (b = 1; b <= nStree; b *= 2, step /= 2) {
		for (k = 0; k < b; ++k) {
			stree_low
		}
	}*/
}

#define stree_max() stree[1]

void __stree_add(int v, int a, int b)
{
	/*int low = (v - (1 << level)) << (lStree - level);
	int high = low + (1 << (lStree - level));*/
	DBG("  __stree_add(v=%d,a=%d,b=%d)   low=%d   high=%d\n",
		v, a, b, stLow[v], stHigh[v]);
	if (a <= stLow[v] && b >= stHigh[v]) {
		++stExtra[v];
		++stree[v];
		return;
	}
	if (v < nStree && a <= stHigh[2 * v])
		__stree_add(2 * v, a, b);
	if (v < nStree && b >= stLow[2 * v + 1])
		__stree_add(2 * v + 1, a, b);
	stree[v] = stExtra[v] + MAX(stree[2 * v], stree[2 * v + 1]);
}
#define stree_add(a,b) __stree_add(1, a, b)

void __stree_del(int v, int a, int b)
{
	/* int low = (v - (1 << level)) << (lStree - level);
	int high = low + (1 << (lStree - level)); */
	if (a <= stLow[v] && b >= stHigh[v]) {
		--stree[v];
		--stExtra[v];
		return;
	}
	if (v < nStree && a <= stHigh[2 * v])
		__stree_del(2 * v, a, b);
	if (v < nStree && b >= stLow[2 * v + 1])
		__stree_del(2 * v + 1, a, b);
	//FIXME: missing extra nodes
	stree[v] = stExtra[v] + MAX(stree[2 * v], stree[2 * v + 1]);
}
#define stree_del(a,b) __stree_del(1, a, b)

void stree_dump()
{
#ifdef DEBUG
	int v;
	//printf("nStree=%d\n", nStree);
	printf("stree=");
	for (v = 0; v < 2 * nStree; ++v) {
		if ((v & (v - 1)) == 0)
			putchar('|');
		printf(" %d:%d", stExtra[v], stree[v]);
	}
	puts("");
#endif
}

int verify(int R)
{
	DBG("----- solve(R = %d) ---- \n", R);
	stree_init(N);
	stree_dump();
	static int LOW[NMAX];
	int i = 0, j = 0;
	// compute ranges
	for (i = j = 0; j < N; ++j) {
		while (X[SX[i]] + R < X[SX[j]])
			++i;
		LOW[SX[j]] = SX[i];
	}

#ifdef DEBUG
	for (i = 0; i < N; ++i)
		printf("  low[%d] = %d:%d (%d - %d)\n", i, LOW[i], SX[LOW[i]],
			X[SX[LOW[i]]], X[i]);
#endif

	for (i = j = 0; j < N; ) {
		int a = SY[i], b = SY[j];
		DBG("i=%d  j=%d  a=%d  b=%d\n", i, j, a, b);
		if (Y[b] - Y[a] <= R) {
			DBG("add %d   (%d,%d)\n", b, X[b], Y[b]);
			DBG("stree_add(%d,%d)  %d-%d\n",
				LOW[b], b,
				ISX[LOW[b]], ISX[b]);
			stree_add(ISX[LOW[b]], ISX[b]);
			stree_dump();
			++j;
		} else {
			DBG("del %d   (%d,%d)\n", a, X[a], Y[a]);
			DBG("stree_del(%d,%d)\n", ISX[LOW[a]], ISX[a]);
			stree_del(ISX[LOW[a]], ISX[a]);
			stree_dump();
			++i;
		}
		DBG("max = %d\n", stree_max());
		if (stree_max() >= N - K) {
			DBG(" !! accepted R=%d\n", R);
			return 1;
		}
	}
	DBG(" !! rejected R=%d\n", R);
	return 0;
}

static int ycmp(const void *va, const void *vb)
{
	int a = *(const int *)va;
	int b = *(const int *)vb;
	return Y[a] - Y[b];
}

static int xcmp(const void *va, const void *vb)
{
	int a = *(const int *)va;
	int b = *(const int *)vb;
	return X[a] - X[b];
}

int solveR(void)
{
	int i;
#ifdef DEBUG
	printf("--------- N = %d    K = %d  -----------\n", N, K);
	for (i = 0; i < N; ++i)
		printf("point[%d] = (%d,%d)\n", i, X[i], Y[i]);
#endif
	for (i = 0; i < N; ++i)
		SX[i] = SY[i] = i;
	qsort(SX, N, sizeof(SX[0]), xcmp);
	qsort(SY, N, sizeof(SY[0]), ycmp);
	for (i = 0; i < N; ++i)
		ISX[SX[i]] = i;

#ifdef DEBUG
	printf("by-x:");
	for (i = 0; i < N; ++i)
		printf(" (%d,%d)", X[SX[i]], Y[SX[i]]);
	puts("");
	printf("by-inv x:");
	for (i = 0; i < N; ++i)
		printf(" %d", ISX[i]);
	puts("");
	printf("by-y:");
	for (i = 0; i < N; ++i)
		printf(" (%d,%d)", X[SY[i]], Y[SY[i]]);
	puts("");
#endif

	int dx = X[SX[N - 1]] - X[SX[0]];
	int dy = Y[SY[N - 1]] - Y[SY[0]];

	int h = MAX(dx, dy);
	int l = -1;

	while (l + 1 < h) {
		int m = (l + h) / 2;
		DBG("l=%d  m=%d  h=%d\n", l, m, h);
		if (verify(m))
			h = m;
		else
			l = m;
	}
	return h;
}
int main()
{
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) {
		printf("Case #%d\n", t);
		int i;
		scanf("%d %d", &N, &K);
		for (i = 0; i < N; ++i)
			scanf("%d %d", &X[i], &Y[i]);

		int R = solveR();
		printf("%d\n", R);
	}
	return 0;
}