/*
Work out the first ten digits of the sum of the following
one-hundred 50-digit numbers.
*/

#include <cstdio>
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

const int maxn = 60;

class Number {
public:
	char dig[maxn];
	int nDigits;

	Number() {
		nDigits = 1;
		dig[0] = 0;
	}
	Number(string &s) {
		nDigits = s.length();
		int len = s.length();
		FOR(i,0,len-1)
			dig[i] = s[len-1-i]-'0';
	}
	void add(const Number b) {
		int maxLen = max(b.nDigits, nDigits);
		char carry = 0;
		FOR(i,0,maxLen-1) {
			char dig1 = i < nDigits ? dig[i] : 0;
			char dig2 = i < b.nDigits ? b.dig[i] : 0;
			char newDig = dig1 + dig2 + carry;
			dig[i] = newDig % 10;
			carry = newDig / 10;
		}
		if (carry)
			dig[maxLen++] = carry;
		nDigits = maxLen;
	}
};

ostream& operator<<(ostream& os, const Number &n) {
	FOR(i,0,n.nDigits-1) {
		os << (char)(n.dig[n.nDigits-1-i] + '0');
	}
	return os;
}

int main() {
	freopen("013-LargeSum.txt","r",stdin);
	string s;
	Number sum;
	while (cin >> s) {
		cout << "Num=" << s << endl;
		Number term(s);
		sum.add(term);
		cout << "Sum=" << sum << endl;
	}

	FOR(i,0,9)
		cout << (char)(sum.dig[sum.nDigits-1-i] + '0');
	cout << endl;

	return 0;
}
