/**
 * Wythoff's game POJ 1067
 *
 * NOI
 *
 * Solution: DP (not gonna meet timing criteria)
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdio>

using namespace std;

#define DBG 0

#define MAXN 100

char t[MAXN][MAXN];

#define EMPTY	0
#define WIN		1
#define LOSE	2

void extendLose(int x, int y, int a, int b) {
	int i;
	for (i = x + 1; i <= a; i++)
		t[i][y] = WIN;
	for (i = y + 1; i <= b; i++)
		t[x][i] = WIN;
	for (i = 1; x + i <= a && y + i <= b; i++)
		t[x + i][y + i] = WIN;
}

void print(int a, int b) {
	int i, j;
#if DBG
	for (i = 0; i <= a; i++) {
		for (j = 0; j <= b; j++)
			cout << (char)('0' + t[i][j]);
		cout << endl;
	}
#endif
}

/**
 * Theorem 1: if (a, b) is LOSE, then for x \neq a and y \neq b,
 * (x, b) and (a, y) are WIN.
 */

int wythoff(int a, int b) {
	// base
	t[0][0] = LOSE;
	extendLose(0, 0, a, b);

	print(a,b);

	// iterate over column i and row i
	int i, j;
	for (i = 1; i <= a || i <= b; i++) {
		if (i <= a) {
			// scan row i, the first empty should be L, other should W
			bool hasL = false;
			for (j = 0; j <= b; j++) {
				if (t[i][j] == EMPTY) {
					if (!hasL) {
						t[i][j] = LOSE;
						extendLose(i, j, a, b);
						hasL = true;
					} else {
						t[i][j] = WIN;
					}
				}
			}
		}

		if (i <= b) {
			// scan column i
			bool hasL = false;
			for (j = 0; j <= a; j++) {
				if (t[j][i] == EMPTY) {
					if (!hasL) {
						t[j][i] = LOSE;
						extendLose(j, i, a, b);
						hasL = true;
					} else {
						t[j][i] = WIN;
					}
				}
			}
		}
	}

	print(a, b);

	return t[a][b] == WIN;
}

int main() {
	freopen("wythoff_poj_1067.txt", "r", stdin);

	string line;
	while (getline(cin, line)) {
		int a, b;
		istringstream is(line);
		if (!(is >> a >> b))
			break;
		memset(t, 0, sizeof t);
		int ans = wythoff(a, b);
		cout << ans << endl;
	}
	return 0;
}
