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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
#ifdef BENCH

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define REP(v,n) for(int v=0;v<n;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 100005;
const Num mod = 1000000007;
Num N;
Num grandSum;

struct Node {
#if DBG
	int idx;
#endif
	int degrees;
	list<pair<Node*,Num> > edges; // target, weight
	map<Num,int> pweights;			// path weights
	Node() {
		pweights[1] = 1;
	}
	void removeEdge(Node *tgt) {
		for (every(it, edges))
			if (it->first == tgt) {
				edges.erase(it);
				break;
			}
	}
	void clear() {
		pweights.clear();
		edges.clear();
		degrees = 0;
		pweights[1] = 1;
	}
	Num multiply(Num wt, Node *c) {
		Num nodeSum = 0;
		for (every(pw1, c->pweights)) {
			// updates sums
			for (every(pw2, pweights)) {
				Num part = pw1->first * pw1->second % mod * wt % mod * pw2->first % mod * pw2->second % mod;
				nodeSum = (nodeSum + part) % mod;
			}
		}
		for (every(pw1, c->pweights)) {
			// update weights
			Num partSum = pw1->first * wt % mod;
			pweights[partSum] += pw1->second;
		}
		removeEdge(c);
		return nodeSum;
	}
};

struct NodeComp {
	bool operator()(const Node *lhs, const Node *rhs) {
		return lhs->degrees < rhs->degrees ||
				(lhs->degrees == rhs->degrees && lhs < rhs);
	}
} nodeComp;

multiset<Node*,NodeComp> que;
Node nodes[maxn];

Num solve() {
	// push all to priority_q
	multiset<Node*,NodeComp>::iterator it = que.begin();
	REP(i, N) {
		if (nodes[i].degrees)
			it = que.insert(it, &nodes[i]);
	}
	grandSum = 0;
	while (que.size() > 1) {
		Node *cur = *que.begin();
		que.erase(cur);
		for (every(it, cur->edges)) {
			Node *tgt = it->first;
			Num wt = it->second;
			// cumulate path weights
			Num nodeSum = tgt->multiply(wt, cur);
			grandSum = (grandSum + nodeSum)%mod;
			que.erase(tgt);
			tgt->degrees--;
			que.insert(tgt);
		}
	}
	// clean-up
	que.clear();
	REP(i,N)
		nodes[i].clear();
	return grandSum;
}

int main() {
	int T;
	Num i;
#if BENCH
	freopen("tree_weighting.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N;
#if DBG
		REP(i,N) nodes[i].idx = i;
#endif
		for (i = 0; i < N - 1; i++) {
			Num a, b, w;
			cin >> a >> b >> w;
			a--; b--;
			nodes[a].degrees++; nodes[b].degrees++;
			nodes[a].edges.push_back(make_pair(&nodes[b],w));
			nodes[b].edges.push_back(make_pair(&nodes[a],w));
		}
		cout << solve() << endl;
	}
	return 0;
}
