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
#include <fstream>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

typedef long long Num;
const int maxn=801;
int N;

Num x[maxn];
Num y[maxn];

bool asc(int a, int b) {
	return a > b;
}

Num solve() {
	sort(x,x+N);
	sort(y,y+N,asc);
	Num sum = 0;
	for(int i=0;i<N;i++)
		sum += x[i] * y[i];
	return sum;
}

int main() {
	// input
	string in("min-scalar-product-large.in");
	string out("min-scalar-product-large.out");
#if BENCH
	freopen(in.c_str(), "r", stdin);
//	freopen(out.c_str(), "w", stdout);
#endif
	int TC,tc,i;
	cin>>TC;
	for(tc=0;tc<TC;tc++) {
		cin>>N;
		for(i=0;i<N;i++)
			cin>>x[i];
		for(i=0;i<N;i++)
			cin>>y[i];
		cout<<"Case #"<<(tc+1)<<": "<<solve()<<endl;
	}
	return 0;
}
