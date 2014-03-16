/*
 * sliding_window.cpp
 *
 * POJ 2823
 * TLE: due to STL
 *
 *  Created on: Feb 18, 2014
 *      Author: danke
 */

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

const int maxn = 1000006;
int data[maxn];
list<pair<int,int> > mqueue; // monotonic queue (index,val)

int getnum() {
	char cc,s;
	int dd;
	while (cc = getchar(), (cc<'0'||cc>'9')&&cc!='-');
	s=cc=='-'?-1:1;
	dd=cc=='-'?0:cc-'0';
	while (cc = getchar(), cc>='0'&&cc<='9')
		dd = dd*10+cc-'0';
	return dd*s;
}

void putnum(int v) {
	char buf[64];
	int i=0;
	char s;
	if (v<0) {v=-v;s=-1;} else s=1;
	do {
		buf[i]=v%10;
		v/=10;
		i++;
	} while (v);

	if (s==-1)
		putchar('-');
	while(i>0)
		putchar(buf[--i]+'0');
	putchar(' ');
}

int main() {
	int n, k, i, v;

#if BENCH
	freopen("sliding_window.txt","r",stdin);
#endif

	scanf("%d%d",&n,&k);

	for (i=0;i<n;i++) {
		data[i]=v=getnum();
		// pop all elems whose index < i-k
		while (!mqueue.empty() && mqueue.front().first <= i-k)
			mqueue.pop_front();

		while (!mqueue.empty() && v <= mqueue.back().second)
				mqueue.pop_back();

		mqueue.push_back(make_pair(i,v));

		if (i>=k-1)
			putnum(mqueue.front().second); // min
	}
	cout<<endl;

	mqueue.clear();
	for (i=0;i<n;i++) {
		v=data[i];
		// pop all elems whose index < i-k
		while (!mqueue.empty() && mqueue.front().first <= i-k)
			mqueue.pop_front();

		while (!mqueue.empty() && v >= mqueue.back().second)
			mqueue.pop_back();

		mqueue.push_back(make_pair(i,v));

		if (i>=k-1)
			putnum(mqueue.front().second); // max
	}
	cout<<endl;

	return 0;
}
