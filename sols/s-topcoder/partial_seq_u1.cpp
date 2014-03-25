#define _BSD_SOURCE

#include <ctype.h>
#include <limits.h>
#include <math.h>
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
#define DBGFMT printf
#else
#define DBGFMT(...) do { } while(0)
#endif

#define NMAX 260

int S[NMAX][NMAX][NMAX];
int M[NMAX][NMAX];

void dump(int N)
{
#ifdef DEBUG
	int x, y, z;
	for (z = 0; z <= N; ++z) {
		printf("layer z = %d\n", z);
		for (y = 0; y <= N; ++y) {
			for (x = 0; x <= N; ++x)
				if (S[y][x][z] == INT_MAX)
					printf(" P");
				else if (S[y][x][z] == INT_MIN)
					printf(" N");
				else
					printf(" %d", S[y][x][z]);
			puts("");
		}
	}
#endif
}

int main()
{
	freopen("/home/danke/workspace/skymap/src/partial_seq.txt", "r", stdin);

	int x, y, z, T, N;
	scanf("%d", &T);
	for (z = 0; z <= NMAX - 1; ++z)
		for (x = 0; x <= NMAX - 1; ++x)
			//for (y = 0; y <= NMAX - 1; ++y)
				S[x][0][z] = S[0][x][z] = z ? INT_MAX : INT_MIN;
	dump(4);
	while (T--) {
		scanf("%d", &N);
		for (y = 1; y <= N; ++y)
			for (x = 1; x <= N; ++x)
				scanf("%d", &M[y][x]);
		for (y = 1; y <= N; ++y)
			for (x = 1; x <= N; ++x)
				for (z = 1; z <= N; ++z) {
					S[y][x][z] = MIN(S[y][x - 1][z], S[y - 1][x][z]);
					if (M[y][x] >= S[y - 1][x - 1][z - 1])// || M[y][x] >= S[y][x - 1][z - 1])
						S[y][x][z] = MIN(S[y][x][z], M[y][x]);
				}
		dump(N);
		for (z = N; S[N][N][z] == INT_MAX; --z);
		printf("%d\n", z);
	}

	return 0;
}

