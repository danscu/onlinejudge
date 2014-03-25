#include <iostream>

using namespace std;

bool study_solve(int a, int b, int c, int *xx, int *yy) {
	int x, y;

	for (x = 0; x <= 100; x++) {
		if ((c - a * x) % b == 0) {
			y = (c - a * x) / b;
			*xx = x;
			*yy = y;
			cout << x << " " << y << endl;
		}
		if ((c + a * x) % b == 0) {
			y = (c + a * x) / b;
			*xx = -x;
			*yy = y;
			cout << -x << " " << y << endl;
		}
	}

	return false;
}

int find_k1(int x, int y, int u, int v, int *kk)
{
	int k;
	for (int k1 = 0; k1 <= 1000; k1++) {
		if ((k1*x - x - y + 1) % (-k1*u + u - v) == 0) {
			k = (k1*x - x - y + 1) / (-k1*u + u - v);
			*kk = k;
			return k1;
		}
	}
	return -1;
}

unsigned GCD(unsigned u, unsigned v) {
    while ( v != 0) {
        unsigned r = u % v;
        u = v;
        v = r;
    }
    return u;
}

int main() {
	int a = 19, b = 7, c = 27;
	int x, y;
	study_solve(a, b, c, &x, &y);
	int d = GCD(a,b);
	int u = a / d, v = b / d;
	int k;
	int k1 = find_k1(x, y, u, v, &k);
	cout << "K = " << k << " K1 = " << k1 << endl;
	return 0;
}
