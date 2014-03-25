#include <iostream>
#include <set>
#include <cstdio>
#include <algorithm> // std:sort
#include <climits>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

#define MAXN 100005

typedef unsigned long long Num;

int w,h,N;

struct Rect {
        Num l, r, t, b;
};

struct Pt {
        Num x, y;
        Rect *parent;
        char isleft;
};

Pt pt[MAXN*2];
Rect rect[MAXN];

struct AscendX {
        bool operator()(const Pt &a, const Pt &b) {
                return a.x < b.x;
        }
} ascendX;

struct descendByY {
        bool operator()(const Rect* a, const Rect* b) {
                return a->t > b->t;
        }
};

// Optimize
Num darkArea() {
        typedef set<Rect*, descendByY> Box;
        Box box; // set of rectangles under sweep line
        Num area = 0;
        int i;

        sort(pt, pt + N*2, ascendX);

        Num height = 0, lastX = 0;

        // events
        for (i = 0; i < N*2; i++) {
                if (pt[i].isleft)
                        box.insert(pt[i].parent);
                else
                        box.erase(pt[i].parent);

                // merge events at the same x
                if (i < N*2 - 1 && pt[i+1].x == pt[i].x)
                        continue;

                area += height * (pt[i].x - lastX);

                if (box.empty())
                	height = 0;
                else {
                	Rect* top = *box.begin();
                	Rect* bottom = *box.rbegin();
                	height = top->t - bottom->b;
                }

                lastX = pt[i].x;
        }

        return area;
}

int main() {
        int C;
        int i;

#if BENCH
        freopen("warehouse.txt", "r", stdin);
#endif

        cin >> C;
        for (int tc=0;tc<C;tc++) {
                cin >> w >> h >> N;
                // input
                int pti = 0;
                Num inRect = 0;
                for (i=0;i<N;i++) {
                        cin >> rect[i].l >> rect[i].b >> rect[i].r >> rect[i].t;
                        pt[pti].isleft = 1;
                        pt[pti].x = rect[i].l;
                        pt[pti].y = rect[i].b;
                        pt[pti].parent = &rect[i];
                        pti++;
                        pt[pti].isleft = 0;
                        pt[pti].x = rect[i].r;
                        pt[pti].y = rect[i].t;
                        pt[pti].parent = &rect[i];
                        pti++;

                        inRect += (rect[i].r - rect[i].l) * (rect[i].t - rect[i].b);
                }

                Num ans = darkArea() - inRect;
                cout << "Case #" << tc+1 << endl << ans << endl;
        }

        return 0;
}