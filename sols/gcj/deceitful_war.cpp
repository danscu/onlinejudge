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

int N;
const int maxn = 1024;
double naomi_data[maxn];
double ken_data[maxn];

struct Asc {
	bool operator ()(const pair<double,int> &a, const pair<double,int> &b) {
		return a.first < b.first;
	}
};

struct Desc {
	bool operator ()(const pair<double,int> &a, const pair<double,int> &b) {
		return a.first > b.first;
	}
};

typedef set<pair<double,int>,Asc> StoneSetA;
typedef set<pair<double,int>,Desc> StoneSetD;
StoneSetA ken;
StoneSetD naomi, kenDW;

void game_init() {
	REP(i,N) {
		ken.insert(make_pair(ken_data[i], i));
		naomi.insert(make_pair(naomi_data[i], i));
		kenDW.insert(make_pair(ken_data[i], i));
	}
#if DBG
	cout << endl;
	for(every(it,naomi))
		cout << it->first << " ";
	cout << endl;
	for(every(it,ken))
		cout << it->first << " ";
	cout << endl;
#endif
}

StoneSetD::iterator ken_worst(double naomiRef) {
	StoneSetD::iterator it = kenDW.upper_bound(make_pair(naomiRef, 0));
	if (it != kenDW.end())
		return it; // largest waste
	else {
		StoneSetD::iterator fit = kenDW.rbegin().base();
		fit--;
		return fit; // largest
	}
}

StoneSetA::iterator ken_opt(double naomiStone) {
	StoneSetA::iterator it = ken.lower_bound(make_pair(naomiStone, 0));
	if (it != ken.end() && it->first > naomiStone)
		return it; // next weight
	else
		return ken.begin();
}

StoneSetA::iterator ken_opt_dwar(double naomiStone) {
	StoneSetA::iterator it = kenDW.lower_bound(make_pair(naomiStone, 0));
	if (it != kenDW.end() && it->first > naomiStone)
		return it; // next weight
	else
		return kenDW.begin();
}

StoneSetD::iterator naomi_opt_war() {
	return naomi.begin();
}

// prints DW opt, W opt
void solve() {
	game_init();
	int war_naopt = 0;
	int dwar_naopt = 0;
	REP(i,N) {
		StoneSetD::iterator nit = naomi_opt_war();
		StoneSetA::iterator kit = ken_opt(nit->first);

		if (nit->first > kit->first)
			war_naopt++;

		ken.erase(kit);
		naomi.erase(nit);

		StoneSetA::iterator kitDW = ken_worst(nit->first);

		if (nit->first > kitDW->first)
			dwar_naopt++;

		D(cout << "naomi: " << nit->first << ", ken: " << kit->first << ", " << war_naopt << endl);
		kenDW.erase(kitDW);
	}
	cout << dwar_naopt << " " << war_naopt << endl;
}

int main() {
	int T;
#if BENCH
	freopen("deceitful_large.txt","r",stdin);
	freopen("deceitful_large.out","w",stdout);
#endif
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N;
		REP(i,N)
			cin >> naomi_data[i];
		REP(i,N)
			cin >> ken_data[i];
		cout << "Case #" << tc + 1 << ": ";
		solve();
	}
	return 0;
}
