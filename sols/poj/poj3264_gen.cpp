#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
#ifdef BENCH

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 50000;
const Num maxq = 180000;

ofstream input("files/poj3264_test.in");

Num n,m;

int main() {
	int T;
	Num i, j;

	n = maxn - 10;
	m = maxq - 10;

	input << n << " " << m << endl;

	REP(i,n)
	input << rand() % 100000 << endl;

	REP(i,m)
	input << 1+(rand() % n) << " " << 1+(rand() % n) << endl;

	input.close();

	return 0;
}
