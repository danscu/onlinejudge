#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <queue>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)

const int maxn = 70;

int n;
int rank[maxn];

struct ByRank {
	bool operator()(int i, int j) {
		return rank[i] < rank[j]; // dec
	}
} byRank;

int solve(int &ncases) {
	ncases = 0;

	priority_queue<int,vector<int>,ByRank> q, qn;
	REP(i, n)
		q.push(i);

	// huffman
	int cost = 0;
	do {
		while (q.size() > 1) {
			int ia = q.top(); q.pop();
			int ib = q.top(); q.pop();
			cost += abs(rank[ia] - rank[ib]);
			D(cout<<rank[ia]<<" "<<rank[ib]<<" "<<cost<<endl);
			qn.push( rank[ia] < rank[ib] ? ia : ib );
		}
		if (q.size()) {
			qn.push( q.top() );
			q.pop();
		}
		swap(q, qn);
	} while (q.size() > 1);

	return cost;
}

int main() {
	int T;
	int i;

#if BENCH
	freopen("company_track_meet.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		for (i=0;i<n;i++) {
			cin >> rank[i];
		}

		int ncases;
		int ans = solve(ncases);
		cout << ans << endl;
		cout << ncases << endl;
		cout << endl;
	}

	return 0;
}
