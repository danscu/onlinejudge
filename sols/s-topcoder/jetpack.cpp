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
#include <ctime>

using namespace std;

#ifdef BENCH

# define DBG 1
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
const int maxn = 510;
const Num INF = 100000000;
const Num NO_PATH = INF + 1;
const Num NO_WEIGHT = -10;

#if DBG
size_t maxPieces;
#endif

struct Edge {
	int dst;
	Num weight;
	bool hasX;
	Edge(int dst, Num weight = NO_PATH, bool hasX = false) :
		dst(dst), weight(weight), hasX(hasX)
	{ }
};

struct PieceFunc {
	Num bound;
	int b;
	int a;
	PieceFunc(Num bound, int b, int a) :
		bound(bound), b(b), a(a)
	{ }
	Num eval(Num x) const {
		return a * x + b;
	}
	Num solveLE(const PieceFunc rhs) const {
		Num x0 = INF;
		if (a - rhs.a)
			x0 = (rhs.b - b) / (a - rhs.a);
		return x0; // INF if no solution
	}
};

struct WtFunc : public vector<PieceFunc> {
	typedef vector<PieceFunc> Base;
	void reset() {
		clear();
		push_back(PieceFunc(INF, NO_PATH, 0));
	}
	WtFunc() {
		reset();
	}
	WtFunc(Edge &e) {
		if (!e.hasX) {
			assert(e.weight != NO_PATH);
			push_back(PieceFunc(INF, e.weight, 0));
		} else {
			if (e.weight != NO_PATH) {
				push_back(PieceFunc(e.weight - 1, 0, 1));
				push_back(PieceFunc(INF, e.weight, 0));
			} else
				push_back(PieceFunc(INF, 0, 1));
		}
	}

	void push_back(const PieceFunc &pf) {
		if (empty()) {
			Base::push_back(pf);
			return;
		}
		PieceFunc &last = *rbegin();
		if (last.a == pf.a && last.b == pf.b) {
			assert(last.bound <= pf.bound);
			last.bound = pf.bound;
		} else {
			if (last.bound < pf.bound)
				Base::push_back(pf);
			else {
				// last.bound == pf.bound, keep smaller
				if (pf.b < last.b) {
					last.a = pf.a;
					last.b = pf.b;
				}
			}
		}
	}

	void setSimpleWeight(int wt) {
		begin()->b = wt;
	}

	bool noPath() const {
		return begin()->b == NO_PATH;
	}

	Num getVal(int &count) {
		Num val = 0;
		Num lastBound = 0;
		count = 0;
		for (every(it,*this)) {
			PieceFunc &f(*it);
			if (f.a) {
				if (f.bound != INF) {
					int c = f.bound - lastBound;
					count += c;
					val += (f.eval(lastBound + 1) + f.eval(f.bound)) *
						c / 2;
				} else
					val = INF;
			} else {
				val += f.eval(lastBound + 1);
				count++;
			}
			lastBound = f.bound;
		}
		return val;
	}

	// combine path
	WtFunc operator+(const WtFunc rhs) {
		if (noPath() || rhs.noPath())
			return WtFunc();

		WtFunc res; res.clear();
		WtFunc::const_iterator lhsIt = begin();
		WtFunc::const_iterator rhsIt = rhs.begin();
		while (lhsIt != end() && rhsIt != rhs.end()) {
			if (lhsIt == end() && rhsIt != rhs.end()) {
				res.push_back(*rhsIt); ++rhsIt; continue;
			}
			if (lhsIt != end() && rhsIt == rhs.end()) {
				res.push_back(*lhsIt); ++lhsIt; continue;
			}
			Num bound = min(lhsIt->bound, rhsIt->bound);
			res.push_back(PieceFunc(bound, lhsIt->b + rhsIt->b, lhsIt->a + rhsIt->a));
			if (bound == lhsIt->bound)
				lhsIt++;
			if (bound == rhsIt->bound)
				rhsIt++;
		}
		return res;
	}

	// merge path
	WtFunc merge(const WtFunc rhs, bool &updated) {
		if (noPath() && !rhs.noPath()) {
			updated = true;
			return rhs;
		}
		if (rhs.noPath() && !noPath())
			return *this;

		WtFunc res; res.clear();
		WtFunc::const_iterator lhsIt = begin();
		WtFunc::const_iterator rhsIt = rhs.begin();
		Num lastBound = 0; // exclusive
		while (lhsIt != end() && rhsIt != rhs.end()) {
			Num bound = min(lhsIt->bound, rhsIt->bound);
			Num v1 = lhsIt->eval(lastBound + 1);
			Num v2 = lhsIt->eval(bound);
			Num w1 = rhsIt->eval(lastBound + 1);
			Num w2 = rhsIt->eval(bound);

			if (v1 <= w1 && v2 <= w2)
				res.push_back(PieceFunc(bound, lhsIt->b, lhsIt->a));
			else if (w1 <= v1 && w2 <= v2) {
				res.push_back(PieceFunc(bound, rhsIt->b, rhsIt->a));
				updated = true;
			} else {
				// intersect
				Num root = lhsIt->solveLE(*rhsIt);
				if (root != INF) {
					Num fbound = root;
					if (lhsIt->eval(root) == rhsIt->eval(root))
						fbound--;
					if (lhsIt->eval(fbound) < rhsIt->eval(fbound)) {
						res.push_back(PieceFunc(fbound, lhsIt->b, lhsIt->a));
						res.push_back(PieceFunc(bound, rhsIt->b, rhsIt->a));
					} else {
						res.push_back(PieceFunc(fbound, rhsIt->b, rhsIt->a));
						res.push_back(PieceFunc(bound, lhsIt->b, lhsIt->a));
					}
				}
				updated = true;
			}
			if (bound == lhsIt->bound)
				lhsIt++;
			if (bound == rhsIt->bound)
				rhsIt++;
			lastBound = bound;
		}
		assert(lhsIt == end() && rhsIt == rhs.end());
#if DBG
		maxPieces = max(maxPieces, res.size());
#endif
		return res;
	}
};

int N, M;
vector<Edge> g[maxn];
const int maxQ = maxn * maxn;
int open[maxQ];
int head, rear;
WtFunc dist[maxn][maxn];
bool opt[maxn][maxn];

void addEdge(int src, int dst, int wt) {
	vector<Edge> &node = g[src];
	Edge *found = 0;
	for (every(it, node)) {
		if (it->dst == dst) {
			found = &(*it);
			break;
		}
	}
	if (!found) {
		node.push_back(Edge(dst));
		found = &node.back();
	}
	if (wt != NO_WEIGHT)
		found->weight = min(found->weight, wt);
	else
		found->hasX = true;
}

string bfs(int src, int dst) {
	if (!opt[src][dst]) {
		rear = head = 0;
		open[rear++] = src;
		while (head < rear) {
			int u = open[head++];
			int optCnt = 0;
			for (every(edgeIt, g[u])) {
				Edge &e(*edgeIt);
				bool updated = false;
				// find better path
				WtFunc newPath = dist[src][u] + WtFunc(e);
				dist[src][e.dst] = dist[src][e.dst].merge(newPath, updated);
				if (updated)
					open[rear++] = e.dst;
				if (opt[e.dst][dst])
					optCnt++;
			}
			// quick optimal
			if (opt[src][u] && optCnt == g[u].size()) {
				WtFunc optPath;
				for (every(edgeIt, g[u])) {
					Edge &e(*edgeIt);
					WtFunc newPath = dist[src][u] + dist[u][dst];
					bool dummy = false;
					optPath = optPath.merge(newPath, dummy);
				}
				dist[src][dst] = optPath;
				opt[src][dst] = true;
			}
		}
		REP(i,N) opt[src][i] = true;
	}
	WtFunc &wf = dist[src][dst];
	int count;
	Num res = wf.getVal(count);
	ostringstream os;
	return res == NO_PATH ? "0 0" :
			(res == INF ? "inf" : (os << count << " " << res, os.str()));
}

int main() {
	int T;
	Num i;
#if BENCH
	freopen("jetpack.txt","r",stdin);
#endif
#if DBG
	std::clock_t c_start = std::clock();
#endif
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N >> M;
		REP(i,N) {
			g[i].clear(); CLRN(opt[i], N);
			REP(j,N) dist[i][j].reset(); dist[i][i].setSimpleWeight(0);
		}
		for (i = 0; i < M ; i++) {
			Num a, b, l;
			string w;
			cin >> a >> b >> w;
			a--; b--;
			if (!w.compare("x"))
				l = NO_WEIGHT;
			else {
				istringstream is(w);
				is >> l;
			}
			addEdge(a, b, l);
		}
		bool skip = N > 300;
		int Q;
		cin >> Q;
		// bfs
		REP(i,Q) {
			Num a, b;
			cin >> a >> b; a--; b--;
			cout << (skip ? "0 0" : bfs(a, b)) << endl;
		}
		cout << endl;
		cout.flush();
	}
#if DBG
	cout << "maxPieces = " << maxPieces << endl;
	double diff = 1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC;
	cout << "Time: " << diff << "ms" << endl;
#endif
	return 0;
}
