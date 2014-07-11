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

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
        typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 200006;
const Num maxd = 2000;

struct Node {
        int ne;
        int parent;
        int e[maxd];
        int idx;
        int exitIdx;
        int depth;
        vector<Node*> children;
};

Node g[maxn];
Num p[maxn];

Num n,m;
Num next;

int getnum() {
        char cc;
        int dd;
        while (cc = getchar(), cc<'0'||cc>'9');
        dd=cc-'0';
        while (cc = getchar(), cc>='0'&&cc<='9')
                dd = dd*10+cc-'0';
        return dd;
}

void findParents(int parent, int d) {
    g[parent].idx = next++;
    g[parent].depth = d;
    g[parent].children.clear();
    REP(i, g[parent].ne) {
        int child = g[parent].e[i];
        if (g[child].parent < 0) {
            g[child].parent = parent;
            g[parent].children.push_back(&g[child]);
            findParents(child, d+1);
        }
    }
    g[parent].exitIdx = next;
}

// 1 if common path, 0 if not
Num solve(Num x, Num y) {
    if (g[x].depth > g[y].depth)
        swap(x,y);

    return g[x].idx < g[y].idx && g[y].idx < g[x].exitIdx;
}

void addEdge(int x, int y) {
    if (g[x].ne == maxd)
        return; // skip the edge (OOM)
    g[x].e[g[x].ne++] = y;
}

int main() {
        int T;
        Num i, j;
#if BENCH
        freopen("files/2_sample_input.txt","r",stdin);
//        freopen("files/ant.in","r",stdin);
//        freopen("files/ant.my.out","w",stdout);
#endif

        T = getnum();
        for (int tc = 0; tc < T; tc++) {
                n = getnum(); m = getnum();
                REP(i,n+1)
                    g[i].ne = 0, g[i].parent = -1;
                for (i = 0; i < n - 1; i++) {
                    Num x,y;
                    x = getnum(); y = getnum();
                    addEdge(x, y);
                    addEdge(y, x);
                }
                next=1;
                g[1].parent = 0;
                findParents(1, 1);
                printf("Case #%d\n", tc + 1);
                REP(i,m) {
                    Num x,y;
                    x = getnum(); y = getnum();
                    putchar(solve(x,y) ? '1' : '0');
                    putchar('\n');
                }
        }
        return 0;
}
