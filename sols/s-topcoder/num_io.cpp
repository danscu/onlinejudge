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

#ifdef BENCH
# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)

#endif // BENCH
typedef int Num;
const Num maxn = 1000006;
const Num INF = 10000000;

Num data[maxn];
#if BENCH
Num getnum() {
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
#endif // BENCH

int main() {
	int T;
	Num n, k, i, v;
	Num h,r;

#if BENCH
	freopen("template.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;

		Num ans = 0;

		cout << "Case #" << tc + 1 << endl;
		cout << ans;
	}

	return 0;
}
