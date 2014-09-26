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

#define D(...) do { if (DBG) fprintf(stdout, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 151;
const Num maxl = 41;
const Num INF = numeric_limits<Num>::max();

int N,L;
char init[maxn][maxl];
char tgt[maxn][maxl];
char buf[maxl];

list<string> pats[maxn];
typedef list<string>::iterator slIterator;

void solve() {
	// find xor patterns
	REP(i,N) {
		pats[i].clear();
		REP(j,N) {
			REP(k,L)
				buf[k] = init[i][k] == tgt[j][k] ? '0' : '1';
			buf[L] = 0;
			pats[i].push_back(string(buf));
		}
		pats[i].sort();
	}

	// find intersect
	list<string> &is = pats[0];
	FOR(i,1,N-1) {
		D("Checking pat[%d]\n",i);
		slIterator iis = is.begin();
		slIterator ip = pats[i].begin();
		while (iis != is.end() && ip != pats[i].end()) {
			D("%s:%s\n",iis->c_str(),ip->c_str());
			int cmpres = iis->compare(*ip);
			if (cmpres < 0)
				iis = is.erase(iis);
			else if (cmpres > 0)
				ip = pats[i].erase(ip);
			else {
				iis++, ip++;
			}
		}
		while (iis != is.end())
			iis = is.erase(iis);
		while (ip != pats[i].end())
			ip = pats[i].erase(ip);
	}

	// the remaining is intersect, find the one with fewest 1's
	int minOneCnt = L + 1;
	for (every(iis,is)) {
		int oneCnt = 0;
		for (every(ic,*iis))
			if (*ic == '1')
				oneCnt++;
		minOneCnt = min(minOneCnt, oneCnt);
	}

	if (minOneCnt > L)
		cout << "NOT POSSIBLE";
	else
		cout << minOneCnt;
	cout << endl;
}

int main() {
#if BENCH
	freopen("files/gcj141aa_charging_chaos_large.in","r",stdin);
	freopen("files/gcj141aa_charging_chaos_large.out","w",stdout);
#endif
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d%d", &N, &L);
		REP(i,N)
			scanf("%s", init[i]);
		REP(i,N)
			scanf("%s", tgt[i]);
		printf("Case #%d: ", tc + 1);
		solve();
	}
	return 0;
}
