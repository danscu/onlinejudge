#include <iostream>
#include <cstdio>
using namespace std;
const int maxInt=999999;
const int maxNum=100;

struct edge{
	int u;
	int v;
	int weight;
};

int n,m,source;
int dist[maxNum];
struct edge e[maxNum];

void init()
{
	cin>>n>>m>>source;
	for(int i=1;i<=n;i++)
	{
		dist[i]=maxInt;
	}
	dist[source]=0;
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].u;cin>>e[i].v;cin>>e[i].weight;
		if(e[i].u==source)
		{
			dist[e[i].v]=e[i].weight+dist[e[i].u];
		}

	}

}

void songchi(int u,int weight,int v)
{
	if(dist[u]+weight<dist[v])
		dist[v]=dist[u]+weight;
}

bool bellman_ford(){
	bool flag=1;
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			songchi(e[j].u,e[j].weight,e[j].v);
		}
	}
	//检查是否有负回路
	for(int i=1;i<=m;i++)
		if(dist[e[i].v]>dist[e[i].u]+e[i].weight)
		{
			flag=false;break;
		}

	return flag;
}

int main()
{
#if BENCH
	freopen("bellman-ford.txt","r",stdin);
#endif
	init();
	bool fail = bellman_ford();
	if (fail)
		for(int i=1;i<=n;i++)
			cout<<dist[i]<<endl;
	else cout<<"Negative cycles found."<<endl;
	return 0;
}
