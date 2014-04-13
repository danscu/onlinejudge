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

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

int R, C, M;
const int maxrc = 50;
char m[maxrc][maxrc];
int s[maxrc][maxrc];
bool added[maxrc][maxrc];
bool visited[maxrc][maxrc];

enum {SOLVED, NO_SOL};

struct Cell {
	int free;
	int x, y;
	Cell(int free, int x, int y)
	: free(free), x(x), y(y)
	{
	}
};

struct ByFree {
	bool operator()(const Cell *a, const Cell *b) {
		return a->free > b->free ||
				(a->free == b->free && (a->x < b->x || a->x == b->x && a->y < b->y));
	}
};

set<Cell*,ByFree> cells;

int countNeighbors(int r, int c) {
	int cnt = 0;
	FOR(x,-1,1)
		FOR(y,-1,1) {
			int nr = r + x, nc = c + y;
			if (nr < 0 || nr >= R || nc < 0 || nc >= C)
				continue;
			if (m[nr][nc] == '*')
				cnt++;
	}
	return cnt;
}

int addNeighbors(int r, int c) {
	int cnt = 0;
	FOR(x,-1,1)
		FOR(y,-1,1) {
			int nr = r + x, nc = c + y;
			if (nr < 0 || nr >= R || nc < 0 || nc >= C)
				continue;
			if (visited[nr][nc])
				continue;
			if (!added[nr][nc]) {
				s[nr][nc] = countNeighbors(nr,nc);
				cells.insert(new Cell(s[nr][nc], nr, nc));
			} else {
				cells.erase(new Cell(s[nr][nc], nr, nc));
				s[nr][nc] = countNeighbors(nr,nc);
				cells.insert(new Cell(s[nr][nc], nr, nc));
			}
			added[nr][nc] = true;
	}
	return cnt;
}

int makezero(Cell *cur, int spaces, bool &succ) {
	set<int> updated;
	succ = true;
	int cnt = 0;
	FOR(x,-1,1)
		FOR(y,-1,1) {
			int nr = cur->x + x, nc = cur->y + y;
			if (nr < 0 || nr >= R || nc < 0 || nc >= C)
				continue;
			if (m[nr][nc] == '*') {
				if (spaces == 0) {
					succ = false;
					goto exit;
				}
				spaces--;
				m[nr][nc] = '.';
				updated.insert(nr << 16 || nc);
				cnt++;
			}
	}
exit:
	for(every(it,updated)) {
		int x = *it >> 16;
		int y = *it & 0xFFFF;
		int newSpace = countNeighbors(x, y);
		cells.erase(cur);
		cells.insert(new Cell(newSpace, x, y));
	}
	return cnt; // spaces used
}

int solve() {
	REP(i,R)
	REP(j,C)
		m[i][j] = '*';

	REP(i,R)
	REP(j,C)
		s[i][j] = countNeighbors(i,j), added[i][j] = visited[i][j] = false;

	int spaces = R*C-M;
	if (spaces == 1) {
		m[0][0] = 'c';
		return SOLVED;
	}

	bool first = true;
	bool madezero = true;

	Cell root(s[0][0], 0, 0);
	m[0][0] = 'c'; spaces--;
	if (spaces == 0)
		return SOLVED;

	cells.clear();
	cells.insert(&root);
	while (spaces && madezero && !cells.empty()) {
		Cell *cur = *cells.begin();
		cells.erase(cur);
		visited[cur->x][cur->y] = true;

		int usedSpaces = makezero(cur, spaces, madezero);
		spaces -= usedSpaces;

		if (!madezero && usedSpaces > 0 && first)
			return NO_SOL;

		first = false;

		if (madezero && usedSpaces > 0)
			addNeighbors(cur->x, cur->y);

#if DBG
		cout << "Inter" << endl;
		REP(r,R) {
			REP(c,C)
				cout << m[r][c];
			cout << endl;
		}
#endif
	}
	return spaces == 0 ? SOLVED : NO_SOL;
}

int main() {
	int T;
#if BENCH
	freopen("minesweeper_master.txt","r",stdin);
//	freopen("minesweeper_master.out","w",stdout);
#endif
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> R >> C >> M;

		cout << "Case #" << tc + 1 << ":" << endl;
		if (solve() == SOLVED) {
			REP(r,R) {
				REP(c,C)
					cout << m[r][c];
				cout << endl;
			}
		} else
			cout << "Impossible" << endl;
	}
	return 0;
}
