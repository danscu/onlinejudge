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

typedef unsigned Num;
const int maxn = 100005;
typedef map<Num,pair<int,set<Num> > > IPMap;
IPMap ipmap;

Num getnum() {
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
	int n, i, j;
#if BENCH
	freopen("4_ip_addr.txt","r",stdin);
#endif

	T = getnum();
	for (int tc = 0; tc < T; tc++) {
		n = getnum();
		ipmap.clear();
		printf("Case #%d\n", tc + 1);
		bool found = false;
		for (i = 1; i <= n; i++) {
			int id = getnum();
			Num ipd = 0;
			for (j = 0; j < 4; j++)
				ipd = (ipd << 8) | getnum();
			Num ipt = 0;
			for (j = 0; j < 4; j++)
				ipt = (ipt << 8) | getnum();
			if (found) continue;
			IPMap::iterator it = ipmap.find(ipt);
			if (it != ipmap.end() &&
					it->second.second.find(ipd) != it->second.second.end()) {
				printf("%d %d\n", it->second.first, id);
				found = true;
			} else {
				pair<int,set<Num> > &p(ipmap[ipd]);
				p.first = id;
				p.second.insert(ipt);
			}
		}
		if (!found)
			printf("0\n");
	}
	return 0;
}
