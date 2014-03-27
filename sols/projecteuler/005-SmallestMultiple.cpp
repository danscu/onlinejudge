/*
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRV(x,v) memset(x, v, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;

void factorize(int n, map<int,int> &factor) {
	FOR(i,2,n) {
		while (n % i == 0) {
			factor[i]++;
			n = n / i;
		}
	}
}

int main() {
	map<int,int> maxfactor;
	FOR(i,1,20) {
		map<int,int> factor;
		factorize(i,factor);
		for (every(it, factor))
			maxfactor[it->first] = max(maxfactor[it->first], it->second);
	}
	Num all = 1;
	for (every(it, maxfactor))
		REP(j,it->second)
			all *= it->first;
	cout << all << endl;
	return 0;
}
