#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

int main() {
	srand(time(NULL));

	ofstream fo;

	fo.open("rect_container_large.in");

	int TC = 5, N = 1000;
	int tc, i;

	fo << TC << endl;
	for (tc = 0; tc < TC; tc++) {
		fo << N << endl;

		for (i=0; i < N; i++)
			fo << rand() % 999 + 1 << " ";

		fo << endl;
	}

	fo.close();

	return 0;
}
