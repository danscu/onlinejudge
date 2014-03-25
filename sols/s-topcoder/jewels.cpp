#include <cstdio>
#include <cstring>
#include <iostream>

int N;
int maze[11][11];
int jewels;

// best
int bestMaze[11][11];
int maxJewels;

void visit(int x, int y) {
	static int dx[] = {0, 0, -1, 1};
	static int dy[] = {-1, 1, 0, 0};
	int i;

	int saved = maze[x][y];
	maze[x][y] = 3;

	if (saved == 2)
		jewels++;

	// base case
	if (x == N - 1 && y == N - 1) {
		// save solution
		if (jewels > maxJewels) {
			maxJewels = jewels;
			memcpy(bestMaze, maze, sizeof bestMaze);
			goto exit;
		}
	}

	for (i=0;i<4;i++) {
		int nx = x+dx[i];
		int ny = y+dy[i];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N)
			continue;

		// 0 or 2
		if ((maze[nx][ny] & 1) == 0)
			visit(nx, ny);
	}

exit:
	maze[x][y] = saved;

	if (saved == 2)
		jewels--;
}

int solve() {
	jewels = maxJewels = 0;

	visit(0,0);

	return maxJewels;
}

int main(void)
{
	int tc, T, i, j;

	// The freopen function below opens input.txt file in read only mode, and afterward,
	// the program will read from input.txt file instead of standard(keyboard) input.
	// To test your program, you may save input data in input.txt file,
	// and use freopen function to read from the file when using scanf function.
	// You may remove the comment symbols(//) in the below statement and use it.
	// But before submission, you must remove the freopen function or rewrite comment symbols(//).

	freopen("jewels.txt", "r", stdin);

	// If you remove the statement below, your program's output may not be rocorded
	// when your program is terminated after the time limit.
	// For safety, please use setbuf(stdout, NULL); statement.

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(tc = 0; tc < T; tc++)
	{
		scanf("%d", &N);
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				scanf("%d", &maze[i][j]);
			}
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		int jewels_count = solve();

		// Print the answer to standard output(screen).
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				printf("%d ", bestMaze[i][j]);
			}
			printf("\n");
		}
		printf("%d\n\n", jewels_count);
	}

	return 0;//Your program should return 0 on normal termination.
}
