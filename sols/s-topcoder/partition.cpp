// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful.

#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>

using namespace std;

int N;
list<int> data;

#define DEBUG 0

bool compare_descend(const int& a, const int& b)
{
	return a > b;
}

int solve() {
	int ans = 0;

	data.sort(compare_descend);

	while (data.size() >= 2) {
		int min1 = data.back(); data.pop_back();
		int min2 = data.back(); data.pop_back();
		int newsum = min1 + min2;

		// accumulate cost
		ans += newsum;

		// insert newsum back to queue
		list<int>::iterator it;
		for (it = data.begin(); it != data.end(); it++) {
			if (*it <= newsum) {
				data.insert(it, newsum);
				break;
			}
		}

		if (it == data.end())
			data.push_back(newsum);

#if DEBUG
		for (it = data.begin(); it != data.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
#endif

	}

	return ans;
}

int main(int argc, char** argv)
{
	int tc, T, i;

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		int val;
		cin >> N;
		data.clear();

		for(i = 0; i < N; i++) {
			cin >> val;
			data.push_back(val);
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/

		// Print the answer to standard output(screen).
		int ans = solve();

		cout << ans << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


