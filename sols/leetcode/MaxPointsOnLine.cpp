#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <climits>
#include <cfloat>
#include <cmath>
#include <sstream>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

struct Point {
      int x;
      int y;
      Point() : x(0), y(0) {}
      Point(int a, int b) : x(a), y(b) {}
};

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

//////////////////////////////////////////////////////////////////

const double EPS = 10e-8;
const double INF = 10e10;

struct PointComp {
    bool operator()(const Point &a, const Point &b) {
        return a.x <= b.x || (a.x == b.x && a.y < b.y);
    }
} pointComp;

void printPoint(const Point &p) {
	cout << "(" << p.x << "," << p.y << ") ";
}

class Solution {
public:
    int maxPoints(vector<Point> &points) {
    	if (points.size() <= 1)
    		return points.size();

    	sort(points.begin(), points.end(), pointComp);

        int i,j,n=points.size(),maxP=0;
        for (i=0;i<n-1;i++) {
        	int maxI = 0;
        	int dupCnt = 1;
            map<double,int> c;
        	for (j=i+1;j<n;j++) {
        		if (points[i].x == points[j].x && points[i].y == points[j].y) {
        			dupCnt++;
        			maxP = max(maxP, dupCnt);
        			continue;
        		}

        		double k;
        		if (points[i].x == points[j].x) {
        			// vertical
        			k = INF;
        		} else {
            		k = (double)(points[i].y - points[j].y) / (points[i].x - points[j].x);
        		}
        		int &cnt = c[k];
        		cnt++;
        		maxI = max(maxI, cnt);
        	}
        	maxP = max(maxP, maxI + dupCnt);
        }
        return maxP;
    }
};

//////////////////////////////////////////////////////////////////

/**
 * Working on [(-230,324),(-291,141),(34,-2),(80,22),(-28,-134),(40,-23),(-72,-149),(0,-17),(32,-32),(-207,288),(7,32),(-5,0),(-161,216),(-48,-122),(-3,39),(-40,-113),(115,-216),(-112,-464),(-72,-149),(-32,-104),(12,42),(-22,19),(-6,-21),(-48,-122),(161,-288),(16,11),(39,23),(39,30),(873,-111)]
 */

int ston(string &s) {
	istringstream is(s);
	int n;
	is >> n;
	return n;
}

int main() {
	vector<Point> pts;

	string input = "(-230,324),(-291,141),(34,-2),(80,22),(-28,-134),(40,-23),(-72,-149),(0,-17),(32,-32),(-207,288),(7,32),(-5,0),(-161,216),(-48,-122),(-3,39),(-40,-113),(115,-216),(-112,-464),(-72,-149),(-32,-104),(12,42),(-22,19),(-6,-21),(-48,-122),(161,-288),(16,11),(39,23),(39,30),(873,-111)";
	string num;
	stringstream ss(input);
	int id = 0;
	int x,y;
	while (getline(ss, num, ',')) {
		if (num[0]=='(') num = num.substr(1);
		if (num[num.length()-1]==')') num = num.substr(0, num.length()-1);
		if (id & 1) {
			y = ston(num);
			pts.push_back(Point(x,y));
		} else
			x = ston(num);
		id++;
	}
/*
	pts.push_back(Point(3,1));
	pts.push_back(Point(12,3));
	pts.push_back(Point(3,1));
	pts.push_back(Point(-6,-1));
*/
	Solution sn;
	cout << sn.maxPoints(pts) << endl;

	return 0;
}
