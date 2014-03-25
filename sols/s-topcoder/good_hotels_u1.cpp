#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define forr(i,a,b) for(int i = (a); i <= (b); ++i)

typedef long long ll;

struct point
{
    short x,y;

    short dist(const point& p)
    {
        return max(abs(p.x - x), abs(p.y - y));
    }
};

const int MAXP = 1024 * 1024;

point hotels[MAXP];
point offices[MAXP];
int n,m;
int hotelsByX[MAXP];
int hotelsByY[MAXP];
int hotelAtX[1030];
int hotelAtY[1030];

struct mtop
{
    vector<int> best;
    int maxvalue;

    mtop() {
        best.reserve(1024);
        //
    }

    void add(int v, int id)
    {
        if (v > maxvalue)
        {
            maxvalue = v;
            best.clear();
            best.push_back(id);
        } else if (v == maxvalue)
        {
            best.push_back(id);
        }
    }
};

mtop goodOff[8];

struct rect
{
    short x1,x2,y1,y2;

    rect()
        : x1(1), x2(1024), y1(1), y2(1024)
    {}

    rect(const point& p, int d)
    {
        x1 = p.x - d;
        x2 = p.x + d;
        y1 = p.y - d;
        y2 = p.y + d;
    }

    void intersect(const rect& r)
    {
        x1 = max(x1, r.x1);
        x2 = min(x2, r.x2);
        y1 = max(y1, r.y1);
        y2 = min(y2, r.y2);
    }

    bool isEmpty()
    {
        return x1 > x2 || y1 > y2;
    }

    bool inside(const point& p)
    {
        return x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2;
    }
};

struct XcmpHo
{
    bool operator()(int l, int r)
    {
        return hotels[l].x < hotels[r].x;
    }
} xcmp;

struct YcmpHo
{
    bool operator()(int l, int r)
    {
        return hotels[l].y < hotels[r].y;
    }
} ycmp;

void prepare()
{
    rep(i,n)
    {
        hotelsByX[i] = i;
        hotelsByY[i] = i;
    }
    sort(hotelsByX, hotelsByX + n, xcmp);
    sort(hotelsByY, hotelsByY + n, ycmp);
    int hiX = 0,hiY = 0;
    forr(i,1,1025)
    {
        while (hiX < n && hotels[hotelsByX[hiX]].x < i)
            ++hiX;

        hotelAtX[i] = hiX;

        while (hiY < n && hotels[hotelsByY[hiY]].y < i)
            ++hiY;

        hotelAtY[i] = hiY;
    }

    //leftOff.reserve(MAXP);
    //goodOff[0].maxvalue = -10000; // min x -> -x
    //goodOff[1].maxvalue = -1; // max x -> x
    //goodOff[2].maxvalue = -10000; // min y-> -y
    //goodOff[3].maxvalue = -1; // max y -> y
    //goodOff[4].maxvalue = -10000; // min x+y -> -(x+y)
    //goodOff[5].maxvalue = -1; // max x+y -> x+y
    //goodOff[6].maxvalue = -10000; // min x-y -> y-x
    //goodOff[7].maxvalue = -10000; // max x-y -> x-y
    //int minx = 2000;
    //rep(i,m)
    //{
    //    int x = offices[i].x;
    //    int y = offices[i].y;
    //    goodOff[0].add(-x, i);
    //    goodOff[1].add(x, i);
    //    goodOff[2].add(-y, i);
    //    goodOff[3].add(y, i);
    //    goodOff[4].add(-x-y, i);
    //    goodOff[5].add(x+y, i);
    //    goodOff[6].add(y-x, i);
    //    goodOff[7].add(x-y, i);
    //}
}

bool dominated(int hi)
{
    rect r;
    rep(j,m) {
        int d = hotels[hi].dist(offices[j]);
        r.intersect(rect(offices[j], d-1));
        if (r.isEmpty())
            return false;
    }

    if (hotelAtX[r.x2 + 1] - hotelAtX[r.x1] < hotelAtY[r.y2 + 1] - hotelAtY[r.y1])
    {
        for (int i = hotelAtX[r.x1], last = hotelAtX[r.x2 + 1]; i < last; ++i)
        {
            int y = hotels[hotelsByX[i]].y;
            if (r.y1 <= y && y <= r.y2)
                return true;
        }
    } else {
        for (int i = hotelAtY[r.y1], last = hotelAtY[r.y2 + 1]; i < last; ++i)
        {
            int x = hotels[hotelsByY[i]].x;
            if (r.x1 <= x && x <= r.x2)
                return true;
        }
    }

    return false;
}

int main()
{
#if BENCH
	freopen("good_hotels.txt","r",stdin);
#endif
    int C;
    cin >> C;

    rep(c, C)
    {
        cin >> n >> m;
        rep(i,n) {
            cin >> hotels[i].x >> hotels[i].y;
        }
        rep(i,m) {
            cin >> offices[i].x >> offices[i].y;
        }

        prepare();

        cout << "Case #" << c + 1 << "\n";
        bool first = true;
        if (m < 100)
        {
            rep(i,n)
            {
                if (! dominated(i))
                {
                    if (!first)
                        cout << " ";
                    else
                        first = false;

                    cout << i + 1;
                }
            }
        }
        cout << "\n";
    }
    return 0;
}
