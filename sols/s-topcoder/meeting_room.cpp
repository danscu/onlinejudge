#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define MAXN 10001

#define DBG 1

int N, K;

typedef pair<int,int> Time;
struct Interval {
	pair<Time,Time> times;
	int index;
};

Interval I[MAXN];
vector<list<int> > colors;
Time color_end[MAXN];

bool earlier(const Time &a, const Time &b) {
	return a.first * 128 + a.second < b.first * 128 + b.second;
}

bool earliestStartTime(const Interval &a, const Interval &b) {
	return earlier(a.times.first, b.times.first);
}

void solve() {
	sort(I, I + N, earliestStartTime);

	int i, j;

	for (i = 0; i < N; i++) {
		Time &startTime = I[i].times.first;
		// color
		for (j = 0; j < K; j++) {
			if (earlier(color_end[j], startTime)) {
				// found an available color j
				colors[j].push_back(i);
				color_end[j] = I[i].times.second; // end time
				break;
			}
		}
	}
	for (i = 0; i < K; i++) {
		if (colors[i].empty())
			break;
		for (list<int>::iterator it = colors[i].begin(); it != colors[i].end(); it++) {
			cout << I[*it].index << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include<stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */

#if BENCH
	freopen("meeting_room.txt", "r", stdin);
#endif

	/*
	   Program is given to the problem, test cases should be handled.
                 If a test case is given to 10   ex) test_case < 10
	 */

	int T;
	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		/*
			Read each test case from standard input.
			The number of node is N[0], N[1], ..., N[9]
		 */

		cin >> N >> K;

		int i;
		for (i = 0; i < N; i++) {
			cin >> I[i].times.first.first >> I[i].times.first.second >>
				I[i].times.second.first >> I[i].times.second.second;
			color_end[i].first = color_end[i].second = -1;
			I[i].index = i + 1;
		}

#if DBG
	for (i = 0; i < N; i++) {
		cout << I[i].times.first.first << " " << I[i].times.first.second << " "
			<< I[i].times.second.first << " " << I[i].times.second.second << " " << endl;
	}
#endif

		colors.clear();
		colors.resize(K);

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen).
		cout << "Case# " << test_case+1 << endl;
		solve();
	}

	return 0;//Your program should return 0 on normal termination.
}
