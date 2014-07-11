#include <cstdio>
#include <iostream>
using namespace std;

#define min(x, y) x<y ? x : y

int price[510];
int weight[510];
int f[10000];
int E, F; // E: empty, F: full, 1 <= E <= F <= 10000
int N; // N: kinds of juice, 1 <= N <= 500
int MAX = 99999999;

int mySolution()
{
	f[0] = 0;
	int Cup = F - E;
	for(int i = 1; i <= Cup; i++)
		f[i] = MAX;
	for(int i = 0; i < N; i++)
		for(int wei = weight[i]; wei <= Cup; wei++)
			f[wei] = min(f[wei], f[wei - weight[i]] + price[i]);
	if(f[Cup] == MAX)
		return -1;
	else
		return f[Cup];
}

int main(int argc, char** argv)
{
	int tc, T; // T <= 20
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> E;
		cin >> F;
		int wCup = F - E;
		cin >> N;
		for(int i = 0; i < N; i++){
			cin >> price[i];
			cin >> weight[i];
		}
		int k = mySolution();
		if(k == -1)
			cout << "impossible";
		else
			cout << k << endl;
	}
	return 0;
}
