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

#define OP0 0
#define OPX 'X'
#define OPY 'Y'
#define OPZ 'Z'

typedef long long Num;
const int nlimit = 21*100000000;
const int maxn = 1010;

Num A, B, K;
char lastOp;
int opCnt, lineCnt;
bool OOB; // out of bound
vector<string> lineBuf(maxn);

void execute(char op, int cnt) {
	ostringstream os; os << op << " " << cnt;
	lineBuf[lineCnt++] = os.str();
	assert(lineCnt <= maxn);
}

void addOp(char op, int cnt = 1) {
	if (op != lastOp) {
		if (lastOp != OP0)
			execute(lastOp, opCnt);
		opCnt = cnt;
		lastOp = op;
	} else
		opCnt+=cnt;
}

inline pair<Num,Num> checkedPair(Num a, Num b) {
	if (abs(a) > nlimit || abs(b) > nlimit) {
		OOB = true;
		assert(!OOB);
	}
	return make_pair(a, b);
}

pair<Num,Num> gcd(Num a, Num b, bool codegen) {
	assert(a != 0 || b != 0);
	if (b == 0) {
		if (codegen)
			addOp(OPZ);
		b = a;
	}
	Num q;
	while (a) {
		bool sameSign = (a >= 0) ^ (b < 0);
		if (abs(a) < abs(b)) {
			if (codegen) {
				if (abs(a + b) < nlimit) {
					addOp(OPX);
					addOp(OPZ);
					addOp(OPY);
					checkedPair(a + b, b);
				} else {
					if (a + b >= nlimit) {
						checkedPair(b - a, a);
						return gcd(b - a, a, codegen);
					} else {
						checkedPair(a - b, b);
						return gcd(a - b, b, codegen);
					}
				}
			}
			return gcd(b, a, codegen);
		}
		q = abs(a) / abs(b);
		if (a > 0)
			a -= abs(b) * q;
		else
			a += abs(b) * q;
		if (codegen)
			addOp(sameSign ? OPY : OPX, q);
	}
	return checkedPair(a, b);
}

void solve() {
	if (A == 0 && B == 0) {
		cout << (K == 0 ? "YES" : "NO") << endl;
		return;
	}
	Num d = abs(gcd(A, B, false).second);
	bool sol = (K % d == 0);
	if (sol) {
		OOB = false;
		Num a = A, b = B;
		lastOp = OP0; opCnt = lineCnt = 0;
		pair<Num,Num> pr = gcd(a, b, true);
		a = pr.first, b = pr.second;
		Num z = K / b;
		if (z > 0)
			addOp(OPX, z);
		else
			addOp(OPY, -z);

		if (lastOp != OP0)
			addOp(-1); // flush

		if (!OOB) {
			cout << "YES" << endl;
			for (int i = 0; i < lineCnt; i++)
				cout << lineBuf[i] << endl;
			return;
		}
	}
	assert(!sol);
	cout << "NO" << endl;
}

int main() {
	int T;
	ios_base::sync_with_stdio(false);
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> A >> B >> K;
		cout << "Case #" << tc + 1 << endl;
		solve();
	}
	return 0;
}
