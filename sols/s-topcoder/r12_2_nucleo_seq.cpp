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
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);

typedef int Num;
const Num maxn = 1000006;

string r;
int n;
char s[maxn*2];
int p[maxn*2];

void solve() {
	int mx = 0, id = 0, i, m = 0;
	s[m++] = '^'; s[m++] = '.';
	for (i = 0; i < (int)r.length(); i++) {
		s[m++] = r[i];
		s[m++] = '.';
	}
	s[m] = '\0';

	CLRN(p, m);
	for (i = 1; s[i] != '\0'; i++) {
	    p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
	    while (s[i + p[i]] == s[i - p[i]])
	    	p[i]++;
	    if (i + p[i] > mx) {
	        mx = i + p[i];
	        id = i;
	    }
	}
	int imaxp = distance(p, max_element(p, p + m));
	int len = p[imaxp] - 1;
	int start = (imaxp - 1) / 2 - len / 2 + 1;

	cout << start << " " << len << endl;
}

int main() {
	int T;
#if BENCH
	freopen("2_nucleo_seq.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		cin >> r;
		cout << "Case #" << tc + 1 << endl;
		solve();
	}
	return 0;
}
