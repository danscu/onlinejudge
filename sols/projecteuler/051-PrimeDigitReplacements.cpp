#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>
#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRV(x,v) memset(x, v, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int N = 999999;
bitset<N> sv;

// 1 values are positions to search
// This pattern includes 5 and 6 digit numbers
// 0 values are locations to fill in the same number
char pat[][6] = {
	{1, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 1},
	{0, 1, 1, 0, 0, 1},
	{0, 1, 0, 1, 0, 1},
	{0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1},
	{0, 0, 0, 1, 1, 1},
	{-1},
};

void sieve(int limit) {
	int fac = 3, faclim = sqrt(limit);
	for (int i = 4; i <= limit; i+=2)
		sv[i] = true;
	while (fac <= faclim) {
		while (sv[fac] && fac <= faclim)
			fac++;
		if (fac > faclim) break;
		int visit = fac * 2;
		while (visit <= limit) {
			sv[visit] = true;
			visit += fac;
		}
		fac+=2;
	}
}

inline bool isprime(int n) {
	return !sv[n];
}

int main() {
	sieve(N);
	cout << "sieve done" << endl;

	for (int n = 100000; n < 999999; n++)
		if (isprime(n)) {
			char num[6];
			int nc = n;
			for (int j = 0; j < 6; j++) {
				num[j] = nc % 10;
				nc /= 10;
			}
			// test patterns
			for (int t = 0; pat[t][0] >= 0; t++) {
				// fill in 1 locations with num[] and 0 locations
				// with fill
				int cnt = 0;
				vector<int> news;
				REP(fill,10) {
					int val = 0;
					bool valid = true;
					REP(j,6) {
						char dig;
						if (pat[t][j])
							dig = num[5-j];
						else {
							dig = fill;
							if (val == 0 && fill == 0)
								valid = false;
						}
						val = val*10 + dig;
					}
					if (isprime(val) && valid) {
						cnt++;
						news.push_back(val);
					}
				}
				if (cnt == 8) {
					cout << "The variants (1st is answer):" << endl;
					for (every(it,news))
						cout << *it << endl;
					return 0;
				}
			}
	}
	return 0;
}
