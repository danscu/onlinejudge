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

bool isPalindrome(Num n) {
	string s;
	ostringstream os;
	os << n;
	s = os.str();
	int len = s.length();
	int x = 0, y = len - 1;
	while (x < y) {
		if (s[x] != s[y])
			return false;
		x++; y--;
	}
	return true;
}

int main() {
	Num largest = 0;
	FOR(i,100,999)
		FOR(j,100,999) {
			Num prod = i * j;
			if (isPalindrome(prod))
				largest = max(largest, prod);
		}
	cout << largest << endl;
	return 0;
}
