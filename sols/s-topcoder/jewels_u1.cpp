// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful.

#include <stdio.h>
#include <string.h>


#define SIZE 11
int N;
int maze[11][11];
int copy[11][11];
int jewels_count;
int dx[4] = {0,-1,0,1};
int dy[4] = {-1,0,1,0};

void countJewel(int x, int y,int count){
	int u,v,i;
	int temp = maze[x][y];
	if(maze[x][y] == 1 || maze[x][y] == 3)
		return;

	if(maze[x][y] == 2) {
		count++;
	}
	maze[x][y] = 3;
	if(x == N-1 && y == N-1){
		if(count >= jewels_count){
			jewels_count = count;
			memcpy(copy,maze,sizeof(maze));
					}
		maze[x][y] = temp;
		return;
	}


	for( i = 0; i<4; i++){
		u = x + dx[i];
		v = y + dy[i];

		if( u >= 0 && u <= N-1 && v >= 0 && v <= N-1){
			countJewel(u,v,count);
		}
	}
	maze[x][y] = temp;
	return;
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
		jewels_count = 0;

	  countJewel(0,0,0);

	for(i = 0; i < N; i++){
	    for( j = 0; j < N; j++){
			printf("%d ",copy[i][j]);
		}
		printf("\n");
	}
		// Print the answer to standard output(screen).

		printf("%d\n\n", jewels_count);
	}

	return 0;//Your program should return 0 on normal termination.
}
