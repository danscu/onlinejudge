#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>

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

int coin[] = {1,2,5,10,20,50,100,200,-1};
int cnt;

void solve(int n, int k) {
	if (coin[k] == -1) {
		if (!n) cnt++;
		return;
	}
	for (int i = 0; i * coin[k] <= n; i++)
		solve(n - coin[k] * i, k + 1);
}

int main() {
	solve(200, 0);
	cout << cnt << endl;
	return 0;
}
