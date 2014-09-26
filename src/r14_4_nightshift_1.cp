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

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 100006;
int m,r,n; // m: number of cols, r: number of rows, n = m*r

struct Data {
    Num id;
    int index;
    bool operator<(const Data& rhs) const {
        return id < rhs.id;
    }
};

Num data[maxn];
Data targ[maxn];
bool done[maxn];
bool seen[maxn];
int newLoc[maxn][2];
int moves;
int rootIdx;
int printbuf[maxn][2];
int printlen;

void getXY(int u, int &x, int &y) {
    x = u / m, y = u % m;
}

int fromXY(int x, int y) {
    return x * m + y;
}

Data &getTarget(int i, int j) {
    if (j == m - 1)
        return targ[i];                    // X element
    else
        return targ[r + i * (m - 1) + j];  // id element
}

bool inFinal(int u) {
    int row, col; getXY(u, row, col);
    int num;
    if ((num = data[u]))
        return newLoc[num][0] == row && newLoc[num][1] == col;
    else
        return col == m - 1;
}

void print(int origDay, int newDay) {
    if (origDay > newDay)
        swap(origDay, newDay);
    printbuf[printlen][0] = origDay;
    printbuf[printlen][1] = newDay;
    printlen++;
}

void putnum(int v) {
    char buf[64];
    int i=0;
    do {
        buf[i]=v%10;
        v/=10;
        i++;
    } while (v);
    while(i>0)
        putchar(buf[--i]+'0');
    putchar(' ');
}

void dumpPrint() {
    REP(i,printlen) {
        putnum(printbuf[i][0]+1);
        putchar(' ');
        putnum(printbuf[i][1]+1);
        putchar('\n');
    }
}

int dfs(int dep, int u) {
    int cycle;
    D("dep=%d u=%d num=%d\n", dep, u, data[u]);
    // base cases
    if (u == rootIdx && dep > 0)
        return dep;

    if (done[u] || seen[u]) return -1;
    seen[u] = true;

    if (inFinal(u)) {
        done[u] = true;
        return -1;
    }

    // find chain
    int row, col; getXY(u, row, col);
    int num = data[u];
    if (num) {
        // number
        int loc = fromXY(newLoc[num][0], newLoc[num][1]);
        D(" treat number (%d,%d)\n", newLoc[num][0], newLoc[num][1]);
        cycle = dfs(dep+1, loc);
        if (cycle >= 0) {
            Data &tgt = getTarget(newLoc[num][0], newLoc[num][1]);
            done[u] = true;
            if (dep) print(u, loc);
            return cycle;
        }
    } else {
        // space
        REP(s,r) {
            int loc = s*m + (m-1);
            if (data[loc]) {
                // space occupied by number
                D(" treat space at (%d,%d)\n", s, m - 1);
                cycle = dfs(dep+1, loc);
                if (cycle >= 0) {
                    done[u] = true;
                    if (dep) print(u, loc);
                    return cycle;
                }
            }
        }
    }
    return -1;
}

bool verify() {
    Num buf[maxn];
    memcpy(buf, data, n * sizeof(Num));
    REP(i,printlen) {
        int from = printbuf[i][0];
        int to = printbuf[i][1];
        swap(buf[from], buf[to]);
    }
    int ii = 0;
    REP(i,r) {
        REP(j,m-1)
            if (buf[i * m + j] != ++ii)
                return false;
        if (buf[i * m + m - 1])
            return false;
    }
    return true;
}

Num solve() {
    // Find new location of moved element
    REP(i,r) {
        REP(j,m) {
            Data &tgt = getTarget(i,j);
            if (tgt.id) {
                newLoc[tgt.id][0] = i;
                newLoc[tgt.id][1] = j;
            }
            D("%d(%d) ", tgt.id, tgt.index);
        }
        D("\n");
    }

    // search for moves
    moves = printlen = 0;
    CLRN(done,n);

    // start from all numbers
    REP(i,n) {
        rootIdx = i;
        CLRN(seen,n);
        if (!done[i]) {
            int ncycle = dfs(0, i);
            if (ncycle >= 0)
                moves += ncycle - 1;
        }
    }

	return moves;
}

int getnum() {
    char cc;
    int dd;
    while (cc = getchar(), cc<'0'||cc>'9');
    dd=cc-'0';
    while (cc = getchar(), cc>='0'&&cc<='9')
        dd = dd*10+cc-'0';
    return dd;
}

int main() {
#if BENCH
	freopen("files/r14_4_sample.txt","r",stdin);
#endif
	int T, ii;
	T = getnum();
	for (int tc = 0; tc < T; tc++) {
	    m = getnum(), r = getnum(), n = m * r;
		ii = 0;
		REP(i,r)
		    REP(j,m) {
			    data[ii] = getnum();
			    targ[ii].id = data[ii];
			    targ[ii].index = ii;
			    ii++;
		    }
		sort(targ, targ + n);
		printf("Case #%d\n", tc + 1);
		printf("%d\n", solve());
		dumpPrint();
#if DBG
		if (!verify())
		    printf("VERIFY FAIL!!!\n");
#endif
	}
	return 0;
}
