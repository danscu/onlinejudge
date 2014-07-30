/* S-TopCoder Round 13 Problem 2
 * 插头 DP + Path Reconstruction
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

const int maxn = 100010;
const int bits = 3; // each state needs 3 bits (may set to 4 bits to make it faster)
const int mask = (1 << bits) - 1;
const int maxhash = 3 * (1 << bits); // three states on two columns
#define params cur, left, up, lnum, unum, val

int n;
const int m = 2; // two columns
int s1r, s1c, s2r, s2c, e1r, e1c, e2r, e2c;
int now, p, q;

// Hash table for state values

// base4 states x 2 lines
//    0: no contour
//    1: open contour
//    2: close contour
//    3: open and close contour (independent branch)
//    0 - 3: one line, 4 - 7: two lines

enum CState {
	NOTHING = 0,
	OPEN = 1, // left or open
	CLOSE = 2, // right or close
	IND = 3, // independent
	TWO_LINES = 4, // two lines
};

template<int HASHSZ>
struct Hash {
   int ID[HASHSZ]; // bucket id of the hash key
   int key[HASHSZ], val[HASHSZ]; // key and value of the bucket
   int cnt;
   Hash() : cnt(0) { CLRVN(ID,-1,HASHSZ); }
   void clear(){
       REP(i,cnt)
           ID[key[i]] = -1;
       cnt = 0;
   }
   void update(int k, int v){
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

Hash<maxhash> T[2];

bool isStart(int i, int j) {
	return (i + 1 == s1c && j + 1 == s1r) || (i + 1 == s2c && j + 1 == s2r);
}

bool isEnd(int i, int j) {
	return (i + 1 == e1c && j + 1 == e1r) || (i + 1 == e2c && j + 1 == e2r);
}

void addNewLine(int cur, int left, int up, int lnum, int unum, int val) {
}

void endLine(int cur, int left, int up, int lnum, int unum, int val) {
}

void mergeLine(int cur, int left, int up, int lnum, int unum, int val) {
}

void processSameLine(int cur, int left, int up, int lnum, int unum, int val) {
}

void solve() {
	int lst = 1;
	now = 0;
	T[now].clear();
	// Initial state(s)
	T[now].update(0, 1);
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		lst = now;
		now ^= 1;
		T[now].clear();
		p = (m - j) * bits, q = p - bits;

		for (int k = 0;k < T[lst].cnt;k ++) {
			int val = T[lst].getval(k);
			int pre = T[lst].getsta(k);

			if (j == 0) {
				if (mask & pre) continue; // right border should be clear
				pre >>= bits;
			}

			int left = (pre >> p) & mask, up = (pre >> q) & mask;
			int cur = pre & ~(mask << p) & ~(mask << q);

			int lnum = left >= TWO_LINES ? TWO_LINES : 0;
			int unum = up >= TWO_LINES ? TWO_LINES : 0;
			left -= lnum;
			up -= unum;

			// TODO check bottom row here

			// Add line
			bool canAddNewLine = (i == 0);
			if (max(lnum, unum) == 0 && (isStart(i,j) || isEnd(i,j)))
				canAddNewLine = true;

			if (canAddNewLine)
				addNewLine(params);

			// End line
			bool canEndLine = false; /* (i == n - 1)  && top row state allows */;
			canEndLine = isStart(i,j) || isEnd(i,j);
			if (canEndLine)
				endLine(params);

			// Merge line
			bool canMergeLine = false;
			if (canMergeLine)
				mergeLine(params);

			// Same line
			if (lnum == unum) {
				processSameLine(params);
			} else if (lnum < unum) {
				// todo
			} else if (lnum > unum) {
				// todo
			}
		}
	}
}

int main() {
#if BENCH
    freopen("files/r13_2_sample.txt","r",stdin);
#endif
	int T;

	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &n);
		scanf("%d%d%d%d", &s1r, &s1c, &s2r, &s2c);
		scanf("%d%d%d%d", &e1r, &e1c, &e2r, &e2c);
		solve();
	}
	return 0;
}
