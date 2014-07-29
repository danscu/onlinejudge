/** poj 1739
 *  插头 DP
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

const int maxn = 10; // map size
const int maxm = 10;
const int maxhash = 1 << 17;
int n, m;
bool data[maxn][maxm]; // false = blocked

// Hash table for state values
// Each state is 2 bits, each cell has left and up states
// 8 columns * 2 bits * 2 states are packed into one 'int'

// base4 states
//    0: no contour
//    1: open contour
//    2: close contour
//    3: open and close contour (independent branch)

enum CState {
	NOTHING = 0,
	OPEN = 1, // left or open
	CLOSE = 2, // right or close
	IND = 3, // independent
	MASK = 3
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

void dump() {
	printf("-----dump-----\n");
	REP(i,n) {
		REP(j,m)
			printf("%d", data[i][j]);
		printf("\n");
	}
}

int FindMatch(int stat, int from, int delta) {
   int ths, tmp = 0;
   for (int i = from; i <= m * 2 && i >= 0; i += delta) {
       ths = (stat >> i) & MASK;
       if (ths == OPEN) tmp++;
       if (ths == CLOSE) tmp--;
       if (tmp == 0) return i;
   }
   return -1;
}

int work() {
   int now = 0,lst = 1;
   int p; // bit position of 'left' connector count
   int q; // bit position of 'up' connector count
   T[now].clear();
   T[now].update(0,1);
   // scan all the cells
   REP(i,n)
   	   REP(j,m) {
       lst = now;
       now ^= 1;
       T[now].clear();
       p = (m - j) * 2;  // get bit index of 'left' state
       q = p - 2;        // 'up' is one state after 'left' (see the border line)
       REP (k, T[lst].cnt) {
           int pre = T[lst].getsta(k); // state of last cell
           int val = T[lst].getval(k); // value of last cell: number of contours
           if (j == 0) {
        	   // first column
               if (MASK & pre) continue; // 'left' state must be 0, otherwise, skip pre state & cur cell
               pre >>= 2; // shift one state to go to next row: new left is 0, all rest become up states
           }
           // extract states for left and up directions
           int left = (pre >> p) & MASK, up = (pre >> q) & MASK;
           int cur = pre & ~(MASK << p) & ~(MASK << q); // base of current state
           // blocked cell
           if (!data[i][j]) {
        	   // the state is valid if there is no left and no up plugs
               if (left == NOTHING && up == NOTHING)
            	   T[now].update(cur,val);
               continue; // keep T[now][cur] = 0
           }
           // last row and first column (starting point of the contour)
           if (i == n - 1 && j == 0) {
               if (up == NOTHING) T[now].update(cur | (IND << q), val); // add independent up contour
               if (up == OPEN) {
                   int closePos = FindMatch(pre, q, -2); // find CLOSE contour
                   T[now].update(cur | (IND << closePos), val); // add insert independent contour
               }
               continue;
           }
           if (up == NOTHING && left == NOTHING)
               T[now].update(cur | (OPEN << p) | (CLOSE << q), val); // add top-left corner
           else if (up != NOTHING && left != NOTHING) {
               if (up == OPEN && left == CLOSE) T[now].update(cur, val); // close it and leaves no plugs
               else if (left == OPEN && up == OPEN)
            	   T[now].update(cur ^ (IND << FindMatch(pre,q,-2)), val); // IND output from the cell, target state should
               	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   // be CLOSE (2), new state 2 ^ 3 = 1 (OPEN), is
               	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   // updated (close one contour) and open a new one
               else if (left == CLOSE && up == CLOSE)
            	   T[now].update(cur ^ (IND << FindMatch(pre,p,2)), val); // target state should be OPEN (1), 1 ^ 3 = 2 (CLOSE)
               	   	   	   	   	   	   	   	   	   	   	   	   	   	   	  // the CLOSE state is updated, close one contour, and
               	   	   	   	   	   	   	   	   	   	   	   	   	   	   	  // open contour
               else if (left == IND && up == OPEN)
                   T[now].update(cur | (IND << FindMatch(pre,q,-2)), val); // when the OPEN is closed, open the IND again
               else if (up == IND && left == CLOSE)
                   T[now].update(cur | (IND << FindMatch(pre,p,2)), val);  // when the CLOSE is opened, open the IND
           } else {
               if (i == n - 1 && j == m - 1) {T[now].update(cur,val); continue;}
               if (left) {
            	   // something from left
                   if (j < m - 1) T[now].update(cur | (left << q), val); // either go right
                   if (i < n - 1) T[now].update(cur | (left << p), val); // or go down
               } else {
            	   // something from top
                   if (j < m - 1) T[now].update(cur | (up << q), val);   // either go right
                   if (i < n - 1) T[now].update(cur | (up << p), val);   // or go down
               }
           }
       }
   }
   if (T[now].ID[0] != -1) return T[now].getval(T[now].ID[0]);
   return 0;
}

int main() {
#if BENCH
    freopen("files/poj1739_tony_tour.txt","r",stdin);
#endif
	while (scanf("%d%d", &n, &m), n) {
		REP(i,n) {
			char buf[maxm+1];
			scanf("%s", buf);
			REP(j,m)
				data[i][j] = buf[j] == '#' ? false : true;
		}
#if DBG
		dump();
#endif
		printf("%d\n",work());
	}

	return 0;
}
