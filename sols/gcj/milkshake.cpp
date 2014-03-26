#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>
#include <queue>
#include <sstream>

using namespace std;
#ifdef BENCH
#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;
const int maxn=2001;
const int maxm=2001;
int N, M;

set<int> unmaltPrefs[maxm];			// the sets of unmalted flavors preferred by customer [i]
int maltPrefs[maxm];				// the malted flavor customer [i] prefers, -1 if none
bool flavorMalted[maxn];			// the flavor [i] is malted

bool custSatisfied(int i) {
	set<int> &pref( unmaltPrefs[i] );
	for (every(p, pref))
		if (!flavorMalted[*p])
			return true;
	int custMaltPref = maltPrefs[i];
	if (custMaltPref >= 0 && flavorMalted[custMaltPref])
		return true;
	return false;
}

string solve() {
	bool recheck = true;
	while (recheck) {
		recheck = false;
		REP(i,M) {
			if (custSatisfied(i))
				continue;
			else {
				int custMaltedPref = maltPrefs[i];
				if (custMaltedPref >= 0) {
					if (!flavorMalted[custMaltedPref]) {
						flavorMalted[custMaltedPref] = true;
						recheck = true;
					}
				}
			}
		}
	}

	bool allSatis = true;
	REP(i,M) {
		if (!custSatisfied(i)) {
			allSatis = false;
			break;
		}
	}

	if (allSatis) {
		ostringstream os;
		REP(i,N)
			os << (flavorMalted[i] ? '1' : '0') << " ";
		return os.str();
	} else
		return "IMPOSSIBLE";
}

int main() {
	// input
	string basename("milkshake-large");
	string in(basename + ".in");
	string out(basename + ".out");
#if BENCH
	freopen(in.c_str(), "r", stdin);
	if (1) // write to file
		freopen(out.c_str(), "w", stdout);
#endif
	int TC, tc;
	cin >> TC;
	for (tc = 0; tc < TC; tc++) {
		cin >> N >> M;

		REP(i,M) unmaltPrefs[i].clear();
		CLRVN(maltPrefs, -1, M);
		CLRN(flavorMalted, N);

		REP(i,M) { // customers
			set<int> &pref = unmaltPrefs[i];
			int T;
			cin >> T;
			REP(t,T) {
				int flav, malt;
				cin >> flav >> malt;
				flav--;
				if (malt)
					maltPrefs[i] = flav;
				else
					pref.insert(flav);
			}
		}

		cout << "Case #" << (tc + 1) << ": " << solve() << endl;
	}
	return 0;
}
