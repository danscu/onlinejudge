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

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 3001;
const int maxx = 100001;

int n;

struct Pt {
	int x, y;
	int index;
};

struct PtSort {
	bool operator()(const Pt &a, const Pt &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}
} ptSort;

Pt P[maxn];
bool g[maxn][maxn];
bool visited[maxn];
int iXforY[maxx*2 + 1];

bool intersect(Pt &a, Pt &b, Pt &c, Pt &d) {
	int hor1 = a.y == b.y;
	int hor2 = c.y == d.y;
	if (hor1 == hor2)
		return false;
	Pt *aa(hor1 ? &a : &c);
	Pt *bb(hor1 ? &b : &d);
	Pt *cc(hor1 ? &c : &a);
	Pt *dd(hor1 ? &d : &b);
	// aa-bb is horizontal, cc-dd is vertical
	if (aa->x > bb->x) swap(aa, bb);
	if (cc->y > dd->y) swap(cc, dd);
	return aa->x < cc->x && cc->x < bb->x && cc->y < aa->y && aa->y < dd->y;
}

bool contain_intersect(int u, int v, int match[]) {
	for (int i = 0; i < n; i++) {
		if (match[i] != -1)
			if (intersect(P[i], P[match[i]], P[u], P[v]))
				return true;
	}
	return false;
}

bool augpath(int u, int match[]) {
	for (int v = 0; v < n; v++) {
		if (g[u][v] && !visited[v] && !contain_intersect(u, v, match)) {
			visited[v] = true;

			if (match[v] == -1 || augpath(match[v], match)) {
				match[v] = u;
				match[u] = v;
				return true;
			}
		}
	}
	return false;
}

int bpm() {
	// find maximum match in graph (subject to intersection constraints)
	int i;
	bool done = false;
	int match[n], cnt;
	while (!done) {
		done = true;
		memset(match, -1, sizeof match);
		cnt=0;
		for (i=0;i<n;i++) {
			if (match[i] != -1) continue;
			memset(visited, 0, n*(sizeof visited[0]));
			visited[i] = true;
			if (augpath(i, match))
				cnt++;
		}
		done = true; // always terminates
	}
	return cnt;
}

/***************************************************************************
 * Generic graph matching (BEGIN)
 ***************************************************************************/

deque<int> p[maxn];	// alternative path
int mate[maxn];			// matched vertex
int odd[maxn];		// -1 unvisited, 0 even vertex, 1 odd vertex
int que[maxn], *qh, *qr;

// 設定好由樹根至花上各個奇點的交錯路徑，並讓奇點變成偶點。
// 只處理花的其中一邊。
// 邊xy是cross edge。bi是花托的索引值。
void label_one_side(int x, int y, int bi)
{
	for (int i = bi+1; i < p[x].size(); ++i)
	{
		int z = p[x][i];
		if (odd[z] == 1)
		{
			// 設定好由樹根至花上奇點的交錯路徑。
			// 會經過cross edge。
			p[z] = p[y];
			p[z].insert(p[z].end(), p[x].rbegin(), p[x].rend()-i);
			odd[z] = 0;   // 花上的奇點變偶點
			*qh++ = z;  // 將來可以延伸出交錯路徑
		}
	}
}

// 給定一個未匹配點r，建立交錯樹。
bool BFS(int r)
{
	for (int i=0; i<n; ++i) p[i].clear();
	p[r].push_back(r);

	memset(odd, -1, sizeof(odd));
	odd[r] = 0;
	qr = qh = que;
	*qh++ = r; // 樹根放入queue

	while (qr < qh)
		for (int x=*qr++, y=0; y<n; ++y)
			if (g[x][y] && mate[y] != y) { // 有鄰點，點存在。

				// CUSTOM CONSTRAINT: INTERSECTION
				if (contain_intersect(x, y, mate))
					continue;

				if (odd[y] == -1)          // 沒遇過的點
					if (mate[y] == -1)     // 發現擴充路徑
					{
						for (int i=0; i+1<p[x].size(); i+=2)
						{
							mate[p[x][i]] = p[x][i+1];
							mate[p[x][i+1]] = p[x][i];
						}
						mate[x] = y; mate[y] = x;
						return true;
					}
					else                // 延伸交錯樹
					{
						int z = mate[y];

						p[z] = p[x];
						p[z].push_back(y);
						p[z].push_back(z);

						odd[y] = 1; odd[z] = 0;
						*qh++ = z;
					}
				else
					if (odd[y] == 0)      // 形成花
					{
						// 從交錯路徑中求得LCA的索引值
						int bi = 0;
						while (bi < p[x].size()
								&& bi < p[y].size()
								&& p[x][bi] == p[y][bi]) bi++;
						bi--;

						// 兩條路徑分開標記
						// 不必擔心x與y在同一朵花上
						label_one_side(x, y, bi);
						label_one_side(y, x, bi);
					}
					else                // 只需留一條路徑
						;
			}
	return false;
}

int match()
{
	memset(mate, -1, sizeof(mate));

	int c = 0;
	for (int i=0; i<n; ++i)
		if (mate[i] == -1)
			if (BFS(i))
				c++;        // 找到擴充路徑，增加匹配數
			else
				mate[i] = i;   // 從圖上刪除此點
	return c;
}

/***************************************************************************
 * Generic graph matching (END)
 ***************************************************************************/

// return 1 if a match is found
int solve() {
	int i;
	if (n & 1) return 0;
	memset(iXforY, -1, sizeof iXforY);
	sort(P, P + n, ptSort);

	// make graph
	int lastx=-1;
	for (i=0;i<n;i++) {
		if (P[i].x == lastx) {
			g[P[i].index][P[i-1].index] = 1;
			g[P[i-1].index][P[i].index] = 1;
		} else
			lastx = P[i].x;

		int ix = iXforY[P[i].y + maxx];
		if (ix >= 0) {
			g[P[i].index][ix] = 1;
			g[ix][P[i].index] = 1;
		}
		iXforY[P[i].y + maxx] = P[i].index;
	}

	return match() * 2 == n;
//	return bpm() * 2 == n;
}

int main() {
	// input
#if BENCH
	freopen("dot_matching.txt", "r", stdin);
#endif

	int T, i;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		for (i = 0; i < n; i++) {
			cin >> P[i].x >> P[i].y;
			P[i].index = i;
			memset(g[i], 0, sizeof(g[i][0])*n);
		}
		cout << "Case #" << tc + 1 << endl;
		cout << (solve() ? "YES" : "NO") << endl;
	}
	return 0;
}
