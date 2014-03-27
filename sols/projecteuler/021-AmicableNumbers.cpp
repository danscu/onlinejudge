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

int sumDiv(int n) {
	int s = 0;
	FOR(i,1,n-1) {
		if (n%i==0)
			s += i;
	}
	return s;
}

bool amicable(int n) {
	int b = sumDiv(n);
	return (sumDiv(b) == n && n != b);
}

int main() {
	Num ans = 0;

	FOR(i,1,9999) {
		if (amicable(i)) {
			ans += i;
			cout << "amicable: " << i << endl;
		}
	}

	cout << ans << endl;
	return 0;
}
