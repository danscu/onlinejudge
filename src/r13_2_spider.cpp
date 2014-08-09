/* S-TopCoder Round 13 Problem 2
 * DP on connectivity states + Path Reconstruction + 2 paths
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
#include <bitset>
#include <queue>

#define CASE_LIMIT 0
const int MAXCASES = 30;

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
const int conn_mask = (1 << bits) - 1;
const int ctx_bits = (3 + bits * 2);
const int ctx_offset = (m+1)*bits;
const int ctx_mask = ((1 << (ctx_bits+1))-1) << ctx_offset;
const int hashrng = 1 << (ctx_bits + ctx_offset);
const int maxhash = hashrng;

int n;
int s1r, s1c, s2r, s2c, e1r, e1c, e2r, e2c; // start and end coordinates
int hashEntry, idxP, idxQ, i, j;
int cur, pre, totalLines, value, left, up, plugs;
int parentState;
int previ, prevj;
int prevCtx;
int savedCtx, savedLeft, savedUp, savedCur;

// Connectivity States: 3-bit states x 3 lines
//    0: no line
//    1: line_s
//    2: line_e
//    3-7: line type is unknown
enum CState {
	NOTHING = 0,
	LINE_S = 1, // this is a line starting from Start
	LINE_E = 2, // this is a line starting from End
	LINE_UNK_1 = 3, // the start/end of the line is unknown
	LINE_UNK_2 = 4, // the start/end of the line is unknown
	LINE_UNK_3 = 5,
	LINE_UNK_4 = 6,
	LINE_UNK_MAX = LINE_UNK_4 + 1, // exclusive
};

// Context states
enum TState {
#define CTX_LINES_BITS 3
	LINES_0 = 0,
	LINES_1 = 1,
	LINES_2 = 2,
	LINES_3 = 3,
	LINES_4 = 4,
	LINES_MASK = (1 << CTX_LINES_BITS)-1,
#define TOP1_OFFSET CTX_LINES_BITS
#define TOP2_OFFSET (TOP1_OFFSET + bits)
	TOP1_MASK = conn_mask << TOP1_OFFSET,    // Cell (1,1) has an up plug of some line type
	TOP2_MASK = conn_mask << TOP2_OFFSET 	 // Cell (2,1) has an up plug of some line type
};

// Hash table for state values
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

// For simplification
struct Pt {
	int r, c;
	bool start;
	Pt(int r = 0, int c = 0, int start = false) : r(r), c(c), start(start) { }
	bool operator<(const Pt& rhs) const {
		return c < rhs.c;
	}
} P[5];

int realN, Q[5]; // Q is the compacted column values
bool simplified = false;
void printOriginal(int dep);

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
	int st = (newctx << (m + 1) * bits) | cur | (bline << idxP) | (rline << idxQ);
	return st;
}

void encode(int ctx, int bline, int rline, bool setTopRow = false) {
    int st = getcode(ctx, bline, rline, setTopRow);
    D("encode(%x, %d)\n", st, value);
    T[hashEntry].update(st, value);

    std::map<int,PathTracker>::iterator it = tracker[i][j].find(st);
    if (it == tracker[i][j].end()) {
        PathTracker &tr(tracker[i][j][st]);
        tr.fromState = parentState;
        if (previ >= 0)
            tracker[previ][prevj][parentState].hasChild = true;
    }
}

bool isUnk(int line) {
	return line >= LINE_UNK_1 && line < LINE_UNK_MAX;
}

int searchUnk() {
	bool unk[LINE_UNK_MAX - LINE_UNK_1] = {false,};
	int linestat = pre;
	// search lines
	for (int p = 0; p < ctx_offset; p += 3) {
		int st = linestat & conn_mask;
		if (isUnk(st))
			unk[st - LINE_UNK_1] = true;
		linestat >>= 3;
	}
	// search tops
	linestat = prevCtx >> TOP1_OFFSET;
	for (int p = 0; p < 2; p += 3) {
		int st = linestat & conn_mask;
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
	savedCtx = prevCtx, savedLeft = left, savedUp = up, savedCur = cur;
	int mm = conn_mask;
	// replace cur
	for (int p = 0; p < ctx_offset; p += 3) {
		int st = (cur >> p) & conn_mask;
		if (st == unk)
			cur = (cur & ~mm) | line << p;
		mm <<= 3;
	}
	// replace left and up
	if (left == unk) left = line;
	if (up == unk) up = line;
	// replace prevCtx (top)
	for (int p = TOP1_OFFSET; p <= TOP2_OFFSET; p += 3) {
		int st = (prevCtx >> p) & conn_mask;
		if (st == unk)
			prevCtx = (prevCtx & ~(conn_mask << p)) | line << p;
	}
}

void restoreUnk() {
	prevCtx = savedCtx, left = savedLeft, up = savedUp, cur = savedCur;
}

void topRow(int line, int newtot) {
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
}

void addNewLine(int cStart, int cEnd) {
    bool ep = cStart || cEnd;
    if (totalLines == LINES_4)
        return;
    if (left || up)
        return;

    int newtot = totalLines + 1;
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
    	assert(cStart == 1 && cEnd == 1 && plugs == 0);
    	D("addline newtot=%d bottom=0 right=0\n", newtot);
    	    	encode(newtot, 0, 0); // single point
    	return;
    }

    topRow(line, newtot);

    // corner
    if (plugs == 2 && !cStart && !cEnd && j != m - 1) {
        // bottom row
        if (i == n - 1) {
            int open = (prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET)) & conn_mask;
            if (open) {
                line = open; // match open line type
                newtot--;
            }
        }
    	D("addline newtot=%d bottom=%d right=%d\n", newtot, line, line);
    	encode(newtot, line, line); // top-left corner
    }
}

void endLine(int cStart, int cEnd) {
	int endType = cStart ? LINE_S : LINE_E;
	int line = left ? left : up;

	bool unk = false;

	if (isUnk(line)) {
		replaceUnk(line, endType);
		line = endType;
		unk = true;
	}

	if (plugs == 0 && (unk || line != endType)) {
    	D("endline tot=%d\n",totalLines);
    	encode(totalLines, 0, 0); // no output plugs
	}

	if (unk)
		restoreUnk();
}

// must be last (modifies up and left)
void mergeLine() {
    /*
     * |     |
     * |     |
     * +----[+] merge
     */
	bool unk = false;

    // resolve unknown
	assert(left && up);

    if (isUnk(left) && isUnk(up)) {
        if (left == up) return; // can't merge two same unk
        replaceUnk(left, up), unk = true;
    } else if (isUnk(left))
        replaceUnk(left, up), unk = true;
    else if (isUnk(up))
        replaceUnk(up, left), unk = true;

    if (plugs == 0 && (unk || left != up)) {
        D("mergeline tot=%d bottom=0 right=0\n", totalLines - 1);
        encode(totalLines - 1, 0, 0); // reduce total to 1 (represented as 0)
    }
    if (unk) {
        restoreUnk();
        unk = false;
    }
}

void processInputs(int cStart, int cEnd) {
    // two inputs, have to merge
    if (left && up) {
        if (plugs == 0)
            mergeLine();
        return;
    }

    // one input
    int line = left ? left : up;

    int remplugs = plugs;
    int open = (prevCtx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET)) & conn_mask;
    if (i == n - 1 && open) {
        // bottom that connects with top cells
        remplugs -= !!open; // one plug must be bottom
        if (!remplugs) {
            D("extendline tot=%d bottom=%d right=0\n", totalLines-1, open);
            encode(totalLines - 1, open, 0); // dup top, no more plugs
        } else if (remplugs == 1 && j != m - 1) {
            // no left or up input, just output to the right
            D("extendline tot=%d bottom=%d right=%d\n", totalLines-1, open, open);
            encode(totalLines - 1, open, open); // connects with top and right
        }
    }
    else {
        if (i == 0)
            topRow(line, totalLines);

        // other cases: not bottom or no top connections
        if (plugs == 1) {
            D("extendline tot=%d bottom=%d right=0\n", totalLines, line);
            encode(totalLines, line, 0); // down
            if (j != m - 1) {
                D("extendline tot=%d bottom=0 right=%d\n", totalLines, line);
                encode(totalLines, 0, line); // right
            }
        } else if (plugs == 0) {
            endLine(cStart, cEnd);
            return;
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
        pre = pathState[c][r] & ~ctx_mask;
        idxP = (m - r) * bits, idxQ = idxP - bits;
        bottom = (pre >> idxP) & conn_mask, right = (pre >> idxQ) & conn_mask;
        if (bottom) {
            x = c + 1, y = r; if (x == n) x = 0;
            if (!visited[x][y])
                continue;
        }
        if (right) {
            x = c, y = r + 1;
            if (!visited[x][y])
                continue;
        }
        // wrap to top row
        int ctx = pathState[0][r] >> ctx_offset;
        int open = (ctx >> (j == 0 ? TOP1_OFFSET : TOP2_OFFSET)) & conn_mask;
        if (c == 0)
            if (open && calcxy(x, y, c - 1, r) && !visited[x][y])
                continue;
        if (c == n - 1)
            if (open && calcxy(x, y, 0, r) && !visited[x][y])
                continue;
        // go up
        if (calcxy(x, y, c - 1, r)) {
            pre = pathState[x][y] & ~ctx_mask;
            idxP = (m - y) * bits, idxQ = idxP - bits;
            bottom = (pre >> idxP) & conn_mask, right = (pre >> idxQ) & conn_mask;
            if (bottom && !visited[x][y])
                continue;
        }
        // go left
        if (calcxy(x, y, c, r - 1)) {
            pre = pathState[x][y] & ~ctx_mask;
            idxP = (m - y) * bits, idxQ = idxP - bits;
            bottom = (pre >> idxP) & conn_mask, right = (pre >> idxQ) & conn_mask;
            if (right && !visited[x][y])
                continue;
        }
        assert(false);
    }

    if (!simplified) {
		printf("%d\n", dep + 1);
		REP(i, dep + 1)
			printf("%d %d\n", path[i][0] + 1, path[i][1] + 1);
    } else
    	printOriginal(dep);
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
	int lastEntry = 1;
	hashEntry = 0;
	previ = -1;
	T[hashEntry].clear();
	// Initial state(s)
	T[hashEntry].update(0, 1);
	for (i = 0; i < n; i++) for (j = 0; j < m; j++) {
	    tracker[i][j].clear();
		lastEntry = hashEntry;
		hashEntry ^= 1;
		T[hashEntry].clear();
		idxP = (m - j) * bits, idxQ = idxP - bits;

		for (int k = 0; k < T[lastEntry].cnt; k++) {
			value = T[lastEntry].getval(k);
			pre = T[lastEntry].getsta(k);
			parentState = pre;
			prevCtx = pre >> ctx_offset;
			pre &= ~ctx_mask; // pre does not contain context

			if (j == 0) {
				if (conn_mask & pre) {
				    assert(false && "shouldn't have left conns on leftmost columns");
				    continue; // right border should be clear
				}
				pre >>= bits;
			}

			left = (pre >> idxP) & conn_mask, up = (pre >> idxQ) & conn_mask;
			cur = pre & ~(conn_mask << idxP) & ~(conn_mask << idxQ);

			// Total is separated from context
			totalLines = prevCtx & LINES_MASK;
			prevCtx &= ~LINES_MASK;

			D("(%d,%d) st=%x ctx=%x left=%d up=%d tot=%d val=%d top1=%d top2=%d\n", i, j,
			        parentState, prevCtx, left, up, totalLines, value,
			        (prevCtx >> TOP1_OFFSET) & conn_mask,
			        (prevCtx >> TOP2_OFFSET) & conn_mask);

			// Compute input and output connections
			int cStart = cntStart(i,j);
			int cEnd = cntEnd(i,j);
			int cDiff = abs(cStart - cEnd);

			// contains plugs
			assert(!(cStart == cEnd && cStart == 2));
			plugs = 2 - cDiff;
			// Special case: one pair of start-end overlaps, treat plugs == 0
			if (cStart == cEnd && cStart == 1)
			    plugs = 0;

			plugs -= !!left + !!up;

			if (left || up)
			    processInputs(cStart, cEnd);
			else
			    addNewLine(cStart, cEnd);
		}
		previ = i, prevj = j;
	}
	cur = 0; // for getcode below
	idxP = bits, idxQ = 0;
	REP(top,9) {
		int st1 = top % 3;
		int st2 = top / 3;
		int topst = st2 << bits | st1;
		int bottomst = st1 << bits | st2;
		int st = getcode(topst << TOP1_OFFSET | LINES_2, bottomst, 0, true);
		D("checking state %x\n", st);
		if (T[hashEntry].ID[st] != -1) {
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

// Simplifier
bool findAnchor(int r, int c, int &cOrg) {
	REP(i,4)
		if (Q[i] == c && P[i].r == r) {
			cOrg = P[i].c;
			return true;
		}
	return false;
}

int truePath[maxn][2];
void printOriginal(int dep) {
	int trueLen = 0;
	int cOrg;
	int pr, pc;

	// 1. analyze the simplified solution; 
	// record starting positions of left (LL or LULD or LDLU ) and right units (RR or RURD or RDRU), and when they end, repeated can be thrown away
        // 2. Find next alignment col (some columne with S or E cells)
	// 3. copy the lines until the starting of the recurring part
	// 3. extend the simplified solution to near the next anchor column
	// 4. copy the rest of the lines until the next anchor point
	// If not done, repeat from  3

	REP(i, dep + 1) {
		bool anchor = findAnchor(path[i][0] + 1, path[i][1] + 1, cOrg);
		if (anchor) {
			// extend past 4 until hitting next anchor
			if (i == 0) {
				pr = path[i][0] + 1, pc = cOrg;
			} else {
				// TODO: search for period cycle and extrapolate it
				// extrapolate path to reach anchor
				while (pr != path[i][0] + 1 || pc != cOrg) {
					pr += (path[i - 1][0] - path[i - 3][0]);
					pc += (path[i - 1][1] - path[i - 3][1]);

					truePath[trueLen][0] = pr, truePath[trueLen][1] = pc, trueLen++;

					pr += (path[i][0] - path[i - 2][0]);
					pc += (path[i][1] - path[i - 2][1]);
				}
			}
		} else
			pr += path[i][0] - path[i-1][0], pc += path[i][1] - path[i-1][1];

		truePath[trueLen][0] = pr, truePath[trueLen][1] = pc, trueLen++;
	}

	printf("%d\n", trueLen);
	REP(i, trueLen)
		printf("%d %d\n", truePath[i][0], truePath[i][1]);
}

void simplifier() {
	realN = n;
	P[0] = Pt(s1r, s1c, true);
	P[1] = Pt(s2r, s2c, true);
	P[2] = Pt(e1r, e1c, false);
	P[3] = Pt(e2r, e2c, false);
	std::sort(P, P + 4);
	P[4] = Pt(0, n, false); // boundary

	int lastC = 0, lastQ = 0;
	int startId = 0, endId = 0;

	// Simplify the problem
	REP(i,5) {
		Q[i] = lastQ + (P[i].c - lastC);

		if (P[i].c - lastC >= 5) {
			int reduce = ((P[i].c - lastC) - 5) / 2 * 2;
			Q[i] -= reduce;
		}
		lastC = P[i].c;
		lastQ = Q[i];

		if (i == 4) {
			n = Q[i];
			D("new n = %d, old n = %d\n", n, realN);
		} else {
			D("%d %d %s\n", P[i].r, Q[i], P[i].start ? "s" : "e");
			if (P[i].start)
				if (++startId == 1)
					s1r = P[i].r, s1c = Q[i];
				else
					s2r = P[i].r, s2c = Q[i];
			else
				if (++endId == 1)
					e1r = P[i].r, e1c = Q[i];
				else
					e2r = P[i].r, e2c = Q[i];
		}
	}
	simplified = true;
	solve();
}

int main() {
#if BENCH
    freopen("files/r13_2_rand.txt","r",stdin);
#endif
	int T;

	scanf("%d", &T);
#if CASE_LIMIT
	T = MAXCASES;
#endif
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		scanf("%d%d%d%d", &s1r, &s1c, &s2r, &s2c);
		scanf("%d%d%d%d", &e1r, &e1c, &e2r, &e2c);
		printf("Case #%d\n", tc+1);
		if (invalid())
			printf("-1\n");
		else // simplifier();
			solve();
	}
	return 0;
}
