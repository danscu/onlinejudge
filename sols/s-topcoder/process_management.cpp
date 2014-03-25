/*

In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful.

*/

#include <stdio.h>

int N;
int Li[5001];
int Wi[5001];
int Answer;

int solve(int N, int Li[5001], int Wi[5001])
{
	int i, j;

	// Sort by Li & Wi
	for (i = 0; i < N - 1; i++) {
		for (j=i+1;j<N;j++) {
			if (Li[i]>Li[j] || (Li[i]==Li[j] && Wi[i]>Wi[j])) {
				int tmp;
				tmp=Li[i];Li[i]=Li[j];Li[j]=tmp;
				tmp=Wi[i];Wi[i]=Wi[j];Wi[j]=tmp;
			}
		}
	}

	// Output the sequence
	int ans = 0;
	bool done = true;
	int lastLi = 0, lastWi;

	do {
		lastLi = 0;
		done = true;
		for (i=0;i<N;i++) {
			// mark outputted as 0
			if (Li[i]) {
				if (!lastLi) {
					ans++;
					lastLi=Li[i]; lastWi=Wi[i];
					Li[i]=0;
				} else if (Li[i]>=lastLi && Wi[i]>=lastWi) {
					lastLi=Li[i]; lastWi=Wi[i];
					Li[i]=0;
				}
				done=false;
			}
		}
	} while (!done);

	return ans;
}

int main(void)
{
	int test_case;
	int T;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using scanf function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */
	freopen("process_management.txt", "r", stdin);

	/*
	   If you remove the statement below, your program's output may not be rocorded
	   when your program is terminated after the time limit.
	   For safety, please use setbuf(stdout, NULL); statement.
	 */
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		int i;
		scanf("%d", &N);
		for(i=0;i<N;i++)
		{
			scanf("%d %d", &Li[i], &Wi[i]);
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		Answer = solve(N, Li, Wi);

		// Print the answer to standard output(screen).
		printf("%d\n", Answer);
	}

	return 0;//Your program should return 0 on normal termination.
}


