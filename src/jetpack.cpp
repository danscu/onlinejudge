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
const int maxn = 510;
const Num INF = 100000000;
const Num NO_PATH = INF + 1;
const Num SYMX = -10;

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

	// min path
	WtFunc operator*(const WtFunc rhs) {
		if (noPath() && !rhs.noPath())
			return rhs;
		if (rhs.noPath() && !noPath())
			return *this;

		WtFunc res; res.clear();
		WtFunc::const_iterator lhsIt = begin();
		WtFunc::const_iterator rhsIt = rhs.begin();
		Num lastBound = 0; // exclusive
		while (lhsIt != end() && rhsIt != rhs.end()) {
			Num bound = min(lhsIt->bound, rhsIt->bound);
			Num v1 = lhsIt->eval(lastBound);
			Num v2 = lhsIt->eval(bound);
			Num w1 = rhsIt->eval(lastBound);
			Num w2 = rhsIt->eval(bound);

			if (v1 <= w1 && v2 <= w2)
				res.push_back(PieceFunc(bound, lhsIt->b, lhsIt->a));
			else if (w1 <= v1 && w2 <= v2)
				res.push_back(PieceFunc(bound, rhsIt->b, rhsIt->a));
			else {
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
			}
			if (bound == lhsIt->bound)
				lhsIt++;
			if (bound == rhsIt->bound)
				rhsIt++;
			lastBound = bound;
		}
		assert(lhsIt == end() && rhsIt == rhs.end());
		return res;
	}
};

vector<Edge> g[maxn];
WtFunc w[maxn][maxn];

int N, M;

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
	if (wt != SYMX)
		found->weight = min(found->weight, wt);
	else
		found->hasX = true;
}

void floydMarshall() {
	REP(i, N)
		w[i][i].setSimpleWeight(0);

	REP(i, N) {
		for (every(it, g[i]))
			w[i][it->dst] = WtFunc(*it);
	}

	REP(i,N)
	REP(j,N)
	REP(k,N) {
		WtFunc newPath = w[i][k] + w[k][j];
		w[i][j] = w[i][j] * newPath;
	}
}

string queryPath(int src, int dst) {
	WtFunc &wf = w[src][dst];
	int count;
	Num res = wf.getVal(count);
	ostringstream os;
	return res == NO_PATH ? "0 0" :
			(res == INF ? "inf" : (os << count << " " << res, os.str()));
}

list<int> open;

string bfs(int src, int dst) {
	bool *visited = new bool[N];
	CLR(visited);
	open.clear();
	open.push_back(src);
	while (!open.empty()) {
		int u = open.front(); open.pop_front();
		// TODO
	}
	return "";
}

int main() {
	int T;
	Num i;
#if BENCH
	freopen("jetpack.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N >> M;
		REP(i, N) {
			g[i].clear();
			REP(j,N) w[i][j].reset();
		}
		for (i = 0; i < M ; i++) {
			Num a, b, l;
			string w;
			cin >> a >> b >> w;
			a--; b--;
			if (!w.compare("x"))
				l = SYMX;
			else {
				istringstream is(w);
				is >> l;
			}
			addEdge(a, b, l);
		}
		int Q;
		cin >> Q;
		if (Q > 0) {
			// floyd
			floydMarshall();
			REP(i,Q) {
				Num a, b;
				cin >> a >> b; a--; b--;
				cout << queryPath(a, b) << endl;
			}
		} else {
			// dijkstra
			REP(i,Q) {
				Num a, b;
				cin >> a >> b; a--; b--;
				cout << bfs(a, b) << endl;
			}
		}
		cout << endl;
		cout.flush();
	}
	return 0;
}
