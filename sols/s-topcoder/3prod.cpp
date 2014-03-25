#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 100;
const int MAXL = 3;

int mx[MAXN][MAXL];
int mn[MAXN][MAXL];

int prod(int *data, int n, int l) {
	int i, j;
	for (j = 0; j < l; j++) {
		for (i = 0; i < n; i++) {
			mx[i][j] = max(
					i > 0 ? mx[i-1][j] : INT_MIN,
					data[i] >= 0 ?
							(j > 0 ? mx[i-1][j-1] : 1) * data[i] :
							(j > 0 ? mn[i-1][j-1] : 1) * data[i]
			);
			mn[i][j] = min(
					i > 0 ? mn[i-1][j] : INT_MAX,
					data[i] >= 0 ?
							(j > 0 ? mn[i-1][j-1] : 1) * data[i] :
							(j > 0 ? mx[i-1][j-1] : 1) * data[i]
			);
		}
	}
	return mx[n-1][l-1];
}

int main() {
	int data[] = {-7, 4, 1, -8, 3, 2, 6, 9};
	cout << prod(data, 8, 3) << endl;
	return 0;
}
