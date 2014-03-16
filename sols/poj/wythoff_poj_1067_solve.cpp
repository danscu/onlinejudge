/**
 * Wythoff's game POJ 1067
 *
 * NOI
 *
 * Solution: DP (not gonna meet timing criteria)
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int wythoff_math(int a, int b) {
	int t;
	if (a > b) {
		t = a; a = b; b = t;
	}
	// a <= b
	int d = b - a;
	t = floor( d * (sqrt(5.0)+1) / 2 );
	return t == a ? 0 : 1;
}

int main() {
	// freopen("wythoff_poj_1067.txt", "r", stdin);

	string line;
	while (getline(cin, line)) {
		int a, b;
		istringstream is(line);
		if (!(is >> a >> b))
			break;
		int ans = wythoff_math(a, b);
		cout << ans << endl;
	}
	return 0;
}
