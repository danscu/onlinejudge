#include <cstdio>
#include <iostream>
#include <list>
#include <set>

using namespace std;

#define DBG 1
#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define REP(v,n) for(int v=0;v<n;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;
const int maxn = 100005;
const int mod = 1000000007;
int N;
Num grandSum;

struct Node {
#if DBG
	int idx;
#endif
	int degrees;
	list<pair<Node*,Num> > edges; // target, weight
	Num wts;
	Node() {
		wts = 1;
	}
	void removeEdge(Node *tgt) {
		for (every(it, edges))
			if (it->first == tgt) {
				edges.erase(it);
				break;
			}
	}
	void clear() {
		edges.clear();
		degrees = 0;
		wts = 1;
	}
	Num multiply(Num wt, Node *c) {
		Num nodeSum = wts * wt % mod * c->wts % mod;
#if DBG
		Num oldWts = wts;
#endif
		wts = (wts + c->wts * wt % mod) % mod;
#if DBG
		printf("path sum = %ld (node %d) * %ld (wt) * %ld (node %d) = %ld, ", oldWts, idx+1, wt, c->wts, c->idx+1, nodeSum);
		printf("Node %d new weight = %ld + %ld * %ld = %ld, ", idx + 1, oldWts, c->wts, wt, wts);
#endif
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
#if DBG
			printf("Merge Node %d into Node %d: ", cur->idx + 1, tgt->idx + 1);
			int oldGS = grandSum;
#endif
			Num nodeSum = tgt->multiply(wt, cur);
			grandSum = (grandSum + nodeSum) % mod;
#if DBG
			printf("Grand sum = %ld + %ld = %ld\n", oldGS, nodeSum, grandSum);
#endif
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

int getnum() {
	char cc;
	int dd;
	while (cc = getchar(), (cc<'0'||cc>'9'));
	dd=cc=='-'?0:cc-'0';
	while (cc = getchar(), cc>='0'&&cc<='9')
		dd = dd*10+cc-'0';
	return dd;
}

int main() {
	int T;
#if BENCH
	freopen("tree_weighting.txt","r",stdin);
#endif
	T = getnum();
	for (int tc = 0; tc < T; tc++) {
		N = getnum();
#if DBG
		REP(i,N) nodes[i].idx = i;
#endif
		for (int i = 0; i < N - 1; i++) {
			int a, b, w;
			a = getnum(), b = getnum(), w = getnum();
			a--; b--;
			nodes[a].degrees++; nodes[b].degrees++;
			nodes[a].edges.push_back(make_pair(&nodes[b],w));
			nodes[b].edges.push_back(make_pair(&nodes[a],w));
		}
		printf("%ld\n", solve());
	}
	return 0;
}

/*
Merge Node 1 into Node 6: path sum = 1 (node 6) * 5 (wt) * 1 (node 1) = 5, Node 6 new weight = 1 + 1 * 5 = 6, Grand sum = 0 + 5 = 5
Merge Node 4 into Node 6: path sum = 6 (node 6) * 2 (wt) * 1 (node 4) = 12, Node 6 new weight = 6 + 1 * 2 = 8, Grand sum = 5 + 12 = 17
Merge Node 7 into Node 3: path sum = 1 (node 3) * 4 (wt) * 1 (node 7) = 4, Node 3 new weight = 1 + 1 * 4 = 5, Grand sum = 17 + 4 = 21
Merge Node 8 into Node 6: path sum = 8 (node 6) * 5 (wt) * 1 (node 8) = 40, Node 6 new weight = 8 + 1 * 5 = 13, Grand sum = 21 + 40 = 61
Merge Node 9 into Node 6: path sum = 13 (node 6) * 2 (wt) * 1 (node 9) = 26, Node 6 new weight = 13 + 1 * 2 = 15, Grand sum = 61 + 26 = 87
Merge Node 11 into Node 6: path sum = 15 (node 6) * 3 (wt) * 1 (node 11) = 45, Node 6 new weight = 15 + 1 * 3 = 18, Grand sum = 87 + 45 = 132
Merge Node 12 into Node 10: path sum = 1 (node 10) * 3 (wt) * 1 (node 12) = 3, Node 10 new weight = 1 + 1 * 3 = 4, Grand sum = 132 + 3 = 135
Merge Node 10 into Node 14: path sum = 1 (node 14) * 4 (wt) * 4 (node 10) = 16, Node 14 new weight = 1 + 4 * 4 = 17, Grand sum = 135 + 16 = 151
Merge Node 13 into Node 6: path sum = 18 (node 6) * 5 (wt) * 1 (node 13) = 90, Node 6 new weight = 18 + 1 * 5 = 23, Grand sum = 151 + 90 = 241
Merge Node 6 into Node 3: path sum = 5 (node 3) * 2 (wt) * 23 (node 6) = 230, Node 3 new weight = 5 + 23 * 2 = 51, Grand sum = 241 + 230 = 471
Merge Node 3 into Node 2: path sum = 1 (node 2) * 4 (wt) * 51 (node 3) = 204, Node 2 new weight = 1 + 51 * 4 = 205, Grand sum = 471 + 204 = 675
Merge Node 2 into Node 5: path sum = 1 (node 5) * 4 (wt) * 205 (node 2) = 820, Node 5 new weight = 1 + 205 * 4 = 821, Grand sum = 675 + 820 = 1495
Merge Node 5 into Node 14: path sum = 17 (node 14) * 5 (wt) * 821 (node 5) = 69785, Node 14 new weight = 17 + 821 * 5 = 4122, Grand sum = 1495 + 69785 = 71280
*/

