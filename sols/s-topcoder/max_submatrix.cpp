#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

#define MAXN 1001

int Answer;
int N, M;
int m[MAXN][MAXN];
int s[MAXN][MAXN];

#define DBG 0

// end is exclusive, areaEnd is inclusive
int maxArea(int m[], int n, int &areaStart, int &areaEnd, int &height) {
	int area[n];
	int areaFrom[n];
	int areaTo[n];
	int i, t;
	stack<int> S;

	for (i = 0; i < n; i++) {
		while (!S.empty())
			if (m[i] <= m[S.top()])
				S.pop();
			else
				break;
		if (S.empty())
			t = -1;
		else
			t = S.top();
		area[i] = i - t - 1;
		areaFrom[i] = t + 1;
		S.push(i);
	}

	while (!S.empty())
		S.pop();

	for (i = n - 1; i >= 0; i--) {
		while (!S.empty())
			if (m[i] <= m[S.top()])
				S.pop();
			else
				break;
		if (S.empty())
			t = n;
		else
			t = S.top();
		area[i] += t - i - 1;
		areaTo[i] = t - 1;
		S.push(i);
	}

	int maxarea = 0;
	for (i = 0; i < n; i++) {
		area[i] = m[i] * (area[i] + 1);
		if (area[i] > maxarea) {
			maxarea = area[i];
			height = m[i];
			areaStart = areaFrom[i];
			areaEnd = areaTo[i];
		}
	}

	return maxarea;
}

int solve(int &x1, int &y1, int &x2, int &y2) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (m[i][j] == 0)
				s[i][j] = 0;
			else
				s[i][j] = i > 0 ? s[i - 1][j] + 1 : 1;
#if DBG
			cout << s[i][j] << " ";
#endif
		}
		cout << endl;
	}

	int maxarea = 0;
	for (i = 0; i < N; i++) {
		int start, end, height;
		int area = maxArea(s[i], M, start, end, height);
		if (area > maxarea) {
			maxarea = area;
			x1 = i - height + 1;
			x2 = i;
			y1 = start;
			y2 = end;
		}
	}

	return maxarea;
}

int main(int argc, char** argv)
{
	int test_case;

#if BENCH
    freopen("max_submatrix.txt", "r", stdin);
#endif

    int T;
    cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> N >> M;

		int i, j;
		for (i = 0; i < N; i++)
			for (j = 0; j < M; j++)
				cin >> m[i][j];

		int x1, y1, x2, y2;
		Answer = solve(x1, y1, x2, y2);

		// Print the answer to standard output(screen).
		cout << "Case# " << test_case + 1 << endl;
		cout << Answer << " " << x1 + 1 << " " << y1 + 1 << " " <<
				x2 + 1 << " " << y2 + 1 << endl;
	}

	return 0;
}
