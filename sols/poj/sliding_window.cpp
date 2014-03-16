/*
 * sliding_window.cpp
 *
 * POJ 2823
 *
 *  Created on: Feb 18, 2014
 *      Author: danke
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
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

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 1000006;
int data[maxn];
int que[maxn];
int ind[maxn];

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
	int h,r;
#if BENCH
	freopen("sliding_window.txt","r",stdin);
#endif

	n=getnum(); k=getnum();

	h=r=0; // empty queue

	for (i=0;i<n;i++) {
		v=data[i]=getnum();
		// pop all elems whose index < i-k
		while (h<r && ind[h] <= i-k)
			h++;

		while (h<r && v <= que[r-1])
			r--;

		ind[r]=i; que[r++]=v;

		if (i>=k-1)
			putnum(que[h]); // min
	}
	printf("\n");

	h=r=0; // clear
	for (i=0;i<n;i++) {
		v=data[i];
		// pop all elems whose index < i-k
		while (h<r && ind[h] <= i-k)
			h++;

		while (h<r && v >= que[r-1])
			r--;

		ind[r]=i; que[r++]=v;

		if (i>=k-1)
			putnum(que[h]); // max
	}
	printf("\n");

	return 0;
}
