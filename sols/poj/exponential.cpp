#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define MAX 10000

void compute(char buf[], int len, int dec, int n) {
	int i;
	cout << '[';
	for (i = 0; i < len; i++)
		cout << (char)(buf[i] + '0');
	cout << ']';
	cout << " " << len << " " << dec << " " << n << endl;
}

int main() {
	int len;
	char buf[MAX];

	// input
	freopen("exponential.txt", "r", stdin);

	string s;
	int n;
	while (cin >> s >> n) {
		// scan float
		int i = 5;
		int decimals = 0;
		len = 0;
		while (i >= 0) {
			char c = s[i];
			if (c == '.') {
				decimals = 5 - i;
			} else if (c >= '0' && c <= '9')
				buf[len++] = c - '0';
			i--;
		}

		while (len >= 1 && (buf[len - 1] == 0))
			len--;

		// postcondition: len = length of the number, decimals = number of decimals
		compute(buf, len, decimals, n);
	}
	return 0;
}
