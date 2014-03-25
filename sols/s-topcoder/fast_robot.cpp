#include <cstdio>
#include <cstring>
#include <iostream>
#include <climits>
#include <vector>
#include <list>

using namespace std;

#define PATH		0
#define WALL		1

int N, M;
int maze[201][201];
bool visited[201][201];
int startX, startY, endX, endY;
int bestTurns;

struct Node {
	int x, y;
	int lastDir;
	int turns;

	Node(int x, int y, int lastDir, int turns) {
		this->x = x;
		this->y = y;
		this->lastDir = lastDir;
		this->turns = turns;
	}
};

vector<list<Node*> > open;

void addNode(int x, int y, int dir, int turns) {
	if (visited[x][y])
		return;
	visited[x][y] = true;
	Node *newEl = new Node(x, y, dir, turns);
	open[turns].push_back(newEl);
}

void searchBFS() {
	static int dx[] = {0, 0, 1, -1};
	static int dy[] = {1, -1, 0, 0};
	int i;
	int maxTurns = 0;

	for (int curTurns = 0; curTurns <= maxTurns; curTurns++)
		while (open[curTurns].size()) {
			Node *cur = open[curTurns].front();
			open[curTurns].pop_front();

			// arrival
			if (cur->x == endX && cur->y == endY) {
				bestTurns = cur->turns;
				return;
			}

			for (i = (cur->lastDir != -1 ? -1 : 0); i < 4; i++) {
				if (i == cur->lastDir)
					continue;
				int dir = i == -1 ? cur->lastDir : i;
				int nx = cur->x + dx[dir];
				int ny = cur->y + dy[dir];

				if (nx <= 0 || ny <= 0 || nx > N || ny > N)
					continue;

				int newTurns = i == -1 || cur->lastDir == -1 ? cur->turns : cur->turns + 1;

				if (maze[nx][ny] == PATH) {
					// add to open list
					addNode(nx, ny, dir, newTurns);
					maxTurns = max(maxTurns, newTurns);
				}
			}
		}
}

int solve() {
	open.clear();
	open.resize(N * M, list<Node*>());

	bestTurns = INT_MAX;
	addNode(startX, startY, -1, 0);
	searchBFS();

	return bestTurns == INT_MAX ? -1 : bestTurns;
}

int main(void)
{
	int tc, T, i, j;

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
				visited[i][j] = false;
			}
		}
		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		int minturns = solve();

		// Print the answer to standard output(screen).
		printf("%d\n", minturns);
	}

	return 0;
}
