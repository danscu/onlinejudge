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

const int maxn=1004;
int n;

int main() {
	// input
#if BENCH
	freopen("A-large-practice.in", "r", stdin);
#endif

	int TC,tc,i;
	cin>>TC;
	for(tc=0;tc<TC;tc++) {
		int C; cin>>C;
		int I; cin>>I;
		multimap<int,int>ss;
		vector<int>data(I);
		for(i=0;i<I;i++) {
			int val; cin>>val;
			ss.insert(make_pair(val,i));
			data[i]=val;
		}
		int j=0;
		for(i=0;i<I-1;i++) {
			pair<multimap<int,int>::iterator,multimap<int,int>::iterator> rit = ss.equal_range(C-data[i]);
			bool done = false;
			for (multimap<int,int>::iterator it = rit.first; it!=rit.second; ++it) {
				if (it->second!=i) {
					j=it->second; done = true; break;
				}
			}
			if (done) break;
		}
		cout<<"Case #"<<(tc+1)<<": "<<i+1<<" "<<j+1<<endl;
	}
	return 0;
}
