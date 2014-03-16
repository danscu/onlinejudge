#include <iostream>
#include <algorithm> // std::min

using namespace std;

typedef unsigned long Number;

int cycle(Number n) {
	int c = 1;
	while (n != 1) {
		if ((n & 1) == 1)
			n = n * 3 + 1;
		else
			n /= 2;
		c++;
	}
	return c;
}

int maxCycle(Number from, Number to) {
	int mx = 0;
	Number i;
	if (from > to) {
		Number tmp = from; from = to; to = tmp;
	}
	for (i = from; i <= to; i++)
		mx = max(mx, cycle(i));
	return mx;
}

int main() {
	Number from, to;
	while (cin >> from >> to) {
		cout << from << " " << to << " " << maxCycle(from, to) << "\n";
	}
	return 0;
}
