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

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef unsigned long long Num;
const int maxn = 4010;
const int maxk = 4010;
const int maxm = 2010;
const Num INF = numeric_limits<Num>::max();
const Num MOD = 1000000007ll;

int n, k, m;

// Trie stuff
int que[maxn];
int head, tail;
int next[maxn][maxk], fail[maxn], cnt[maxn], nodes;
#define root 0

void clear(int x) {
    CLRVN(next[x], -1, k + 1);
    fail[x] = -1; cnt[x] = 0;
}

void init() {
    clear(root);
    nodes = 1;
}

void insert(const int *sym, int len) {
    int p = root, idx;
    REP(i,len) {
        idx = *sym;
        if (next[p][idx] == -1) {
            clear(nodes);
            next[p][idx] = nodes++;
        }
        p = next[p][idx];
        sym++;
    }
    cnt[p]++;
}

void buildGraph() {
    int cur, inext, fptr1, fptr2;
    head = tail = 0;
    que[tail++] = root;
    while (head < tail) {
        cur = que[head++];
        for (int i = 0; i < k; i++)
            if ((inext = next[cur][i]) != -1) {
                for (fptr1 = fail[cur]; fptr1 != -1; fptr1 = fail[fptr1])
                    if ((fptr2 = next[fptr1][i]) != -1) {
                        fail[inext] = fptr2;
                        break;
                    }
                if (fptr1 == -1)
                    fail[inext] = 0;
                que[tail++] = inext;
            } else
                if (!cur)
                    next[cur][i] = 0;
                else
                    next[cur][i] = next[fail[cur]][i];
    }
}

// Matrix stuff
struct Mat {
    int sz;
    Num **a;
    inline void swap(Mat &rhs) {
        Num **t = a;
        a = rhs.a;
        rhs.a = t;
    }
    inline void clear() {
        REP(i,sz)
            CLRN(a[i], sz);
    }
    Mat(int n) : sz(n) {
        a = new Num*[n];
        REP(i,n)
                a[i] = new Num[n];
    }
    ~Mat() {
        REP(i,sz)
                delete[] a[i];
        delete[] a;
    }
} *am, *ampow;

void multiply(Mat &res, const Mat &l, const Mat &r) {
    res.clear();
    REP(i, res.sz)
    REP(k, res.sz) {
        if (l.a[i][k])
            REP(j, res.sz) {
                res.a[i][j] += l.a[i][k] * r.a[k][j];
                res.a[i][j] %= MOD;
            }
    }
}

void getPow(Mat &ans, Mat &base, int x){
    Mat *tmp = new Mat(nodes);
    REP(i,ans.sz)
        REP(j,ans.sz)
            ans.a[i][j] = i==j ? 1 : 0;
    while (x) {
        if (x & 1) {
            multiply(*tmp, ans, base);
            ans.swap(*tmp);
        }
        multiply(*tmp, base, base);
        base.swap(*tmp);
        x >>= 1;
    }
    delete tmp;
}

int main() {
#if BENCH
    freopen("files/1_rand.txt","r",stdin);
#endif
	int T;
	int sym[maxk];

	scanf("%d", &T); // T = 19;
	for (int tc = 0; tc < T; tc++) {
		scanf("%d%d%d", &n, &k, &m);
		init();
		REP(i,m) {
		    int l;
			scanf("%d", &l);
			REP(j,l)
			    scanf("%d", &sym[j]);
			insert(sym, l);
		}
		buildGraph();

		(am = new Mat(nodes))->clear();
		REP(i,nodes)
		    REP(j, k) {
		        int son = next[i][j];
		        if (!cnt[son] && !cnt[i])
		            am->a[i][son]++;
		}
#if DBG
		printf("----mat----\n");
		REP(i,nodes) {
		    REP(j,nodes)
		        printf("%llu ", am->a[i][j]);
		    printf("\n");
		}
#endif

		ampow = new Mat(nodes);
		getPow(*ampow, *am, n);
#if DBG
        printf("----pow----\n");
        REP(i,nodes) {
            REP(j,nodes)
                printf("%llu ", ampow->a[i][j]);
            printf("\n");
        }
#endif

        Num ans = 0;
		REP(i,nodes) {
		    ans += ampow->a[0][i];
		    if (ans >= MOD) ans -= MOD;
		}

		delete am;
		delete ampow;

		printf("Case #%d\n", tc + 1);
		printf("%llu\n", ans);
	}
	return 0;
}
