#include <cstdio>
#include <cstring>
#include <iostream>
#include <climits>

#define WALL		1
#define VISITED		2
#define PATH		0

int N, M;
int maze[201][201];
int startX, startY, endX, endY;

#define DBG 0

// best
int minTurns;
#if DBG
int bestMaze[201][201];
#endif

void visit(int x, int y, int turns, int lastDir) {
	static int dx[] = {0, 0, -1, 1};
	static int dy[] = {-1, 1, 0, 0};
	int i;

	int saved = maze[x][y];
	maze[x][y] = VISITED;

	// base case
	if (x == endX && y == endY) {
		// save solution
		if (turns < minTurns) {
			minTurns = turns;
#if DBG
			memcpy(bestMaze, maze, sizeof bestMaze);
#endif
			goto exit;
		}
	}

	for (i = -1; i < 4; i++) {
		if (i == lastDir)
			continue;
		int dir = i == -1 ? lastDir : i;
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (nx <= 0 || ny <= 0 || nx > N || ny > N)
			continue;

		int newTurns = i == -1 ? turns : turns + 1;

		if (maze[nx][ny] == PATH)
			visit(nx, ny, newTurns, dir);
	}

exit:
	maze[x][y] = saved;
}

int solve() {
	minTurns = INT_MAX;

	int i;
	for (i = 0; i < 4; i++)
		visit(startX, startY, 0, i);

	return minTurns == INT_MAX ? -1 : minTurns;
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

	freopen("fast_robot.txt", "r", stdin);

	// If you remove the statement below, your program's output may not be rocorded
	// when your program is terminated after the time limit.
	// For safety, please use setbuf(stdout, NULL); statement.

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(tc = 0; tc < T; tc++)
	{
		scanf("%d %d", &M, &N);
		scanf("%d %d %d %d", &startY, &startX, &endY, &endX);
		char line[205];
		for(i = 1; i <= N; i++) {
			scanf("%s", line);
			for(j = 1; j <= M; j++) {
				maze[i][j] = line[j - 1] - '0';
			}
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		int minturns = solve();

		// Print the answer to standard output(screen).
#if DBG
		for(i = 1; i <= N; i++) {
			for(j = 1; j <= M; j++) {
				printf("%d ", bestMaze[i][j]);
			}
			printf("\n");
		}
#endif
		printf("%d\n", minturns);
	}

	return 0;//Your program should return 0 on normal termination.
}
