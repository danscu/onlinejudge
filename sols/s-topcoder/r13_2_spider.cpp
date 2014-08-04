/* S-TopCoder Round 13 Problem 2
 * 插头 DP + Path Reconstruction + 2 paths
 */

/* Check all valid output states */

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
#include <bitset>
#include <queue>

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

const int maxn = 100010;
const int m = 2; // two columns
const int bits = 3; // each connectivity state needs 3 bits
const int tbits = (3 + bits * 2);
const int toff = (m+1)*bits;
const int tmask = ((1 << (tbits+1))-1) << toff;
const int mask = (1 << bits) - 1;
const int hashrng = (1 << (tbits + bits * (m + 1)));
const int maxhash = hashrng;

int n;
int s1r, s1c, s2r, s2c, e1r, e1c, e2r, e2c;
int now, p, q, i, j;
int cur, pre, tot, val, left, up, plugs;
int parSt;
int previ, prevj;
int prevCtx;
int svctx, svleft, svup, svcur;

// Hash table for state values

// Connectivity States: base4 states x 2 lines
//    0: no line
//    1: line_s
//    2: line_e
//    4: two lines so far
enum CState {
	NOTHING = 0,
	LINE_S = 1, // this is a line starting from Start
	LINE_E = 2, // this is a line starting from End
	LINE_UNK_1 = 3, // the start/end of the line is unknown
	LINE_UNK_2 = 4, // the start/end of the line is unknown
	LINE_UNK_3 = 5,
	LINE_UNK_4 = 6,
	LINE_UNK_MAX = LINE_UNK_4 + 1, // exclusive
	MASK = 7,
};

// Context states
enum TState {
	LINES_0 = 0,
	LINES_1 = 1,
	LINES_2 = 2,
	LINES_3 = 3,
	LINES_4 = 4,
	LINES_MASK = 7,           // 3 bits
	TOP1_MASK = MASK << 3,    // Cell (1,1) has an up plug of this line type
	TOP2_MASK = MASK << 6 	  // Cell (2,1) has an up plug of this line type
};

#define TOP1_OFFSET 3
#define TOP2_OFFSET 6

template<int HASHSZ, int HASHRNG>
struct Hash {
   int ID[HASHRNG]; // bucket id of the hash key
   int key[HASHSZ], val[HASHSZ]; // key and value of the bucket
   int cnt;
   Hash() : cnt(0) { CLRVN(ID,0xFF,HASHRNG); }
   void clear(){
       REP(i,cnt)
           ID[key[i]] = -1;
       cnt = 0;
   }
   void update(int k, int v) {
       if (ID[k] == -1) {
           ID[k] = cnt++;
           key[ID[k]] = k;
           val[ID[k]] = v;
       }else{
           val[ID[k]] += v; // add to current value in hash table
       }
   }
   int getval(int idx){return val[idx];}
   int getsta(int idx){return key[idx];}
};

Hash<maxhash,hashrng> T[2];
struct PathTracker {
    int fromState;
    bool hasChild;
};
std::map<int,PathTracker> tracker[maxn][m];
int pathState[maxn][m]; // state selected at the cell

int cntStart(int i, int j) {
	return (i + 1 == s1c && j + 1 == s1r) + (i + 1 == s2c && j + 1 == s2r);
}

int cntEnd(int i, int j) {
	return (i + 1 == e1c && j + 1 == e1r) + (i + 1 == e2c && j + 1 == e2r);
}

int getcode(int ctx, int bline, int rline, bool setRow1) {
	int newctx = prevCtx & ~LINES_MASK;
	if (setRow1) newctx &= ~(TOP1_MASK | TOP2_MASK);
	newctx |= ctx;
	int st = (newctx << (m + 1) * bits) | cur | (bline << p) | (rline << q);
	return st;
}

void encode(int ctx, int bline, int rline, bool setRow1 = false) {
    int st = getcode(ctx, bline, rline, setRow1);
    D("encode(%x, %d)\n", st, val);
    T[now].update(st, val);

    std::map<int,PathTracker>::iterator it = tracker[i][j].find(st);
    if (it == tracker[i][j].end()) {
        PathTracker &tr(tracker[i][j][st]);
        tr.fromState = parSt;
        if (previ >= 0)
            tracker[previ][prevj][parSt].hasChild = true;
    }
}

bool isUnk(int line) {
	return line >= LINE_UNK_1 && line < LINE_UNK_MAX;
}

int searchUnk() {
	bool unk[LINE_UNK_MAX - LINE_UNK_1] = {false,};
	int linestat = pre;
	// search lines
	for (int p = 0; p < toff; p += 3) {
		int st = linestat & mask;
		if (isUnk(st))
			unk[st - LINE_UNK_1] = true;
		linestat >>= 3;
	}
	// search tops
	linestat = prevCtx >> TOP1_OFFSET;
	for (int p = 0; p < 2; p += 3) {
		int st = linestat & mask;
		if (isUnk(st))
			unk[st - LINE_UNK_1] = true;
		linestat >>= 3;
	}
	REP(i, sizeof(unk)/sizeof(unk[0])) {
		if (!unk[i])
			return i + LINE_UNK_1;
	}
	assert(false && "Not enough unknown?");
	return -1;
}

void replaceUnk(int unk, int line) {
	// save states
	svctx = prevCtx, svleft = left, svup = up, svcur = cur;
	int mm = mask;
	// replace cur
	for (int p = 0; p < toff; p += 3) {
		int st = (cur >> p) & mask;
		if (st == unk)
			cur = (cur & ~mm) | line << p;
		mm <<= 3;
	}
	// replace left and up
	if (left == unk) left = line;
	if (up == unk) up = line;
	// replace prevCtx (top)
	for (int p = toff + TOP1_OFFSET; p < tbits + toff; p += 3) {
		int st = (prevCtx >> p) & mask;
		if (st == unk)
			prevCtx = (prevCtx & ~mm) | line << p;
		mm <<= 3;
	}
}

void restoreUnk() {
	prevCtx = svctx, left = svleft, up = svup, cur = svcur;
}

void addNewLine(bool first, int cStart, int cEnd) {
    bool ep = cStart || cEnd;
    if (tot == LINES_4)
        return;
    if (left || up)
        return;

    int newtot = tot + 1;
    int line = ep ? (cStart ? LINE_S : LINE_E) : searchUnk();
    if (plugs == 1 && !left && j != 1) {
        D("addline newtot=%d bottom=0 right=%d\n", newtot, line);
        encode(newtot, 0, line); // horizontal
    }
    if (ep && plugs == 1) {
    	D("addline newtot=%d bottom=%d right=0\n", newtot, line);
    	encode(newtot, line, 0); // vertical
    }

    // start == end
    if (cStart && cEnd) {
    	assert(cStart == 1 && cEnd == 1 && plugs == 2);
    	D("addline newtot=%d bottom=0 right=0\n", newtot);
    	    	encode(newtot, 0, 0); // single point
    	return;
    }

    // top row
    if (i == 0) {
        int open = prevCtx | line << (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);

        if (plugs == 1) {
            D("addline newtot=%d bottom=0 right=0 open=%d\n", newtot, open);
            encode(open | newtot, 0, 0, true); // vertical up
        }

        if (plugs == 2) {
            D("addline newtot=%d bottom=%d right=0 open=%d\n", newtot, line, open);
            encode(open | newtot, line, 0, true); // vertical up and down
        }

        if (plugs == 2 && j != m - 1) {
            D("addline newtot=%d bottom=0 right=%d open=%d\n", newtot, line, open);
            encode(open | newtot, 0, line, true); // up and right
        }
    }

    // corner
    if (plugs == 2 && !cStart && !cEnd) {
    	D("addline newtot=%d bottom=%d right=%d\n", newtot, line, line);
    	encode(newtot, line, line); // top-left corner
    }

    // double starts / ends
    if (ep && plugs == 2) {
        if (i != n - 1) {
            D("addline newtot=%d bottom=%d right=%d\n", newtot, line, line);
            encode(newtot + 1, line, line); // top-left corner
        } else {
            // bottom
            int open = prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);
            open &= MASK;
            int myplugs = plugs;
            myplugs -= !!open;
            if (open && open != line && tot > 0) {
                if (!myplugs) {
                    D("addline tot=%d bottom=%d right=0\n", tot, line);
                    encode(tot, line, 0); // connects with top, no more plugs
                } else if (myplugs == 1) {
                    D("addline tot=%d bottom=0 right=%d\n", tot, line);
                    encode(tot, 0, line); // connects with top and right
                }
            }
        }
    }
}

void endLine(int cStart, int cEnd) {
	if (cStart && cEnd) return;

	int endType = cStart ? LINE_S : LINE_E;
	int line = left ? left : up;

	bool unk = false;

	if (isUnk(line)) {
		replaceUnk(line, endType);
		line = endType;
		unk = true;
	}

	if (plugs == 0 && left && up && left == up && (cStart == 2 || cEnd == 2) && tot > 2) {
	    D("endline (double) tot=%d\n",tot-2);
	    encode(tot-2, 0, 0); // no output plugs
	    return;
	}

	if (plugs == 0 && (unk || line != endType)) {
    	D("endline tot=%d\n",tot);
    	encode(tot, 0, 0); // no output plugs
	}

	if (unk)
		restoreUnk();
}

// must be last (modifies up and left)
void mergeLine(int cStart, int cEnd) {
	if (cStart && cEnd) return;

    /*
     * |     |
     * |     |
     * +----[+] merge
     */

	bool unk = false;

    // resolve unknown
	if (left && up) {
		if (isUnk(left) && isUnk(up))
			replaceUnk(left, up), unk = true;
		else if (isUnk(left))
			replaceUnk(left, up), unk = true;
		else if (isUnk(up))
			replaceUnk(up, left), unk = true;

		if (plugs == 0 && (unk || left != up)) {
			D("mergeline tot=%d bottom=0 right=0\n", tot - 1);
			encode(tot - 1, 0, 0); // reduce total to 1 (represented as 0)
		}
		if (unk) {
			restoreUnk();
			unk = false;
		}
	}

    if (i == n - 1) {
        // bottom
        int open = prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);
        open &= MASK;
        int myplugs = plugs;
        myplugs -= !!open;
        if (!myplugs && open) {
        	if (isUnk(left) && isUnk(open))
        		replaceUnk(left, open), unk = true;
        	else if (isUnk(left))
        		replaceUnk(left, open == LINE_S ? LINE_E : LINE_S), unk = true;
        	else if (isUnk(open))
        		replaceUnk(open, left == LINE_S ? LINE_E : LINE_S), unk = true;

        	open = prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET); // refresh
        	open &= MASK;
        	if (open != left && tot > 0) {
        		D("mergeline tot=%d bottom=%d right=0\n", tot, open);
        		encode(tot, open, 0); // connects with top, no more plugs
        	}
        }
        if (unk)
        	restoreUnk();
    }
}

void extendLine(int j, bool bottom, int cStart, int cEnd) {
    if (left && up) return;
    if (cStart && cEnd) return;

    int line = left ? left : up;

    int myplugs = plugs;
    int open;
    if (bottom) {
        open = prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);
        open &= MASK;
        myplugs -= !!open;
        if (open && open != line && tot > 0) {
            if (!myplugs) {
                D("extendline tot=%d bottom=%d right=0\n", tot-1, line);
                encode(tot - 1, line, 0); // connects with top, no more plugs
            } else if (myplugs == 1) {
                D("extendline tot=%d bottom=0 right=%d\n", tot-1, line);
                encode(tot - 1, 0, line); // connects with top and right
            }
        }
    }

    if ((left || up) && myplugs == 1) {
        D("extendline tot=%d bottom=%d right=0\n", tot, line);
        encode(tot, line, 0); // down
        if (j != m - 1) {
            D("extendline tot=%d bottom=0 right=%d\n", tot, line);
            encode(tot, 0, line); // right
        }
    }
}

int path[maxn*2][2];

bool calcxy(int &rx, int &ry, int x, int y) {
	rx = x;
	if (rx < 0) rx = n - 1;
	else if (rx == n) rx = 0;
	ry = y;
	return (ry >= 0 && ry < m);
}

bool visited[maxn][m];

void genPath(int r, int c, int er1, int ec1, int er2, int ec2) {
    int dep = 0;
    for (int x = c, y = r;
         c = x, r = y,
         path[dep][0] = r, path[dep][1] = c,
         visited[c][r] = true,
         !(r == er1 && c == ec1) & !(r == er2 && c == ec2);) {
        D("genPath dep=%d x=%d y=%d\n", dep, c, r);
        dep++;
        // search 4 directions and find next cell
        int pre, bottom, right;
        // below and right
        pre = pathState[c][r] & ~tmask;
        p = (m - r) * bits, q = p - bits;
        bottom = (pre >> p) & mask, right = (pre >> q) & mask;
        if (bottom) {
            x = c + 1, y = r;
            if (!visited[x][y])
                continue;
        }
        if (right) {
            x = c, y = r + 1;
            if (!visited[x][y])
                continue;
        }
        // wrap
        if (c == 0) {
            int ctx = pathState[c][r] >> ((m + 1) * bits);
            int open = ctx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);
            open &= MASK;
            if (open && calcxy(x, y, c - 1, r) && !visited[x][y])
                continue;
        }
        if (c == n - 1) {
            int ctx = pathState[c][r] >> ((m + 1) * bits);
            int open = ctx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET);
            open &= MASK;
            if (open && calcxy(x, y, 0, r) && !visited[x][y])
                continue;
        }
        // up
        if (calcxy(x, y, c - 1, r)) {
            pre = pathState[x][y] & ~tmask;
            p = (m - y) * bits, q = p - bits;
            bottom = (pre >> p) & mask, right = (pre >> q) & mask;
            if (bottom && !visited[x][y])
                continue;
        }
        // left
        if (calcxy(x, y, c, r - 1)) {
            pre = pathState[x][y] & ~tmask;
            p = (m - y) * bits, q = p - bits;
            bottom = (pre >> p) & mask, right = (pre >> q) & mask;
            if (right && !visited[x][y])
                continue;
        }
        assert(false);
    }

    printf("%d\n", dep + 1);
    REP(i, dep + 1)
        printf("%d %d\n", path[i][0] + 1, path[i][1] + 1);
    if (cntEnd(path[dep][1], path[dep][0]) == 2)
        visited[path[dep][1]][path[dep][0]] = false;
}

void printPaths(int st) {
    for (i = n - 1; i >= 0; i--)
        for (j = m - 1; j >= 0; j--) {
            D("path state: (%d,%d) %x\n", i,j,st);
            // child state
            pathState[i][j] = st;
            // parent state
            st = tracker[i][j][st].fromState;
        }
    CLR(visited);
    D("path1--\n");
    genPath(s1r-1, s1c-1, e1r-1, e1c-1, e2r-1, e2c-1);
    D("path2--\n");
    genPath(s2r-1, s2c-1, e1r-1, e1c-1, e2r-1, e2c-1);
}

void solve() {
	int lst = 1;
	now = 0;
	previ = -1;
	T[now].clear();
	// Initial state(s)
	T[now].update(0, 1);
	for (i = 0; i < n; i++) for (j = 0; j < m; j++) {
	    tracker[i][j].clear();
		lst = now;
		now ^= 1;
		T[now].clear();
		p = (m - j) * bits, q = p - bits;

		for (int k = 0; k < T[lst].cnt; k++) {
			val = T[lst].getval(k);
			pre = T[lst].getsta(k);
			parSt = pre;
			prevCtx = pre >> toff;
			pre &= ~tmask;

			if (j == 0) {
				if (mask & pre) continue; // right border should be clear
				pre >>= bits;
			}

			left = (pre >> p) & mask, up = (pre >> q) & mask;
			cur = pre & ~(mask << p) & ~(mask << q);

			tot = prevCtx & LINES_MASK;
			prevCtx &= ~LINES_MASK;

			D("(%d,%d) st=%x ctx=%x left=%d up=%d tot=%d val=%d top1=%d top2=%d\n", i, j,
			        parSt, prevCtx, left, up, tot, val,
			        (prevCtx > TOP1_OFFSET) & mask,
			        (prevCtx > TOP2_OFFSET) & mask);

			// Add line
			int cStart = cntStart(i,j);
			int cEnd = cntEnd(i,j);
			plugs = (cStart || cEnd) ? cStart + cEnd : 2; // Assume start != end
			plugs -= !!left + !!up;

			addNewLine(i == 0 && j == 0, cStart, cEnd);

			// End line
			if (cStart || cEnd)
			    endLine(cStart, cEnd);

			// Extend line
			if (i == n - 1) {
			    // Bottom row
			    extendLine(j, true, cStart, cEnd);
			} else
			    extendLine(j, false, cStart, cEnd);

            // Merge line
            bool canMergeLine = (j == 1) && left;
            if (canMergeLine)
                mergeLine(cStart, cEnd);
		}
		previ = i, prevj = j;
	}
	cur = 0; // for getcode below
	p = bits, q = 0;
	REP(top,(1<<(bits*2))) {
		int st1 = (top >> bits) & mask;
		int st2 = top & mask;
		int stb1 = st1, stb2 = st2;
		if (st1 == LINE_E) stb1 = LINE_S;
		else if (st1 == LINE_S) stb1 = LINE_E;
		if (st2 == LINE_E) stb2 = LINE_S;
		else if (st2 == LINE_S) stb2 = LINE_E;
		int stb = stb1 << bits | stb2;
		int st = getcode(top << TOP1_OFFSET | LINES_2, stb, 0, true);
		D("checking state %x\n", st);
		if (T[now].ID[st] != -1) {
			printPaths(st);
			return;
		}
	}

	printf("-1\n");
}

bool invalid() {
	if ((s1r == s2r && s1c == s2c) || (e1r == e2r && e1c == e2c))
		return true;
	return false;
}

int main() {
#if BENCH
//    freopen("files/r13_2_rand.txt","r",stdin);
	freopen("files/r13_2_test.txt","r",stdin);
#endif
	int T;

	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		scanf("%d%d%d%d", &s1r, &s1c, &s2r, &s2c);
		scanf("%d%d%d%d", &e1r, &e1c, &e2r, &e2c);
		printf("Case #%d\n", tc+1);
		if (invalid())
			printf("-1\n");
		else solve();
	}
	return 0;
}
