//Shortest Path Faster Algorithm
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#define maxint 200000;
using namespace std;

const int juzhen=101;
int a[juzhen][juzhen];//邻接矩阵
int dist[juzhen];//源点到每个点的最短距离
int n;//n为图中的节点数

void spfa(int s)
{
    int q[juzhen]; //队列
    int v[juzhen]; //v为Boolean,true->已经入队,false->未入队
    int h=0,t=1; //h为头指针，t为尾指针
    int x,i;
    memset(q,0,sizeof(q));
    memset(v,0,sizeof(v));
    for (i=1;i<=n;i++)
        dist[i]=maxint;//初始化dist数组
    dist[s]=0;  //源点到自己的路径长度为0
    q[t]=s;  //把源点入队
    v[s]=1; //将v[s]置为true
    while(h!=t) //本来这应该是h<t,但这是循环队列
    {
        h=(h+1)%(n+1); //不能用%n，否则队满和对空一样
        x=q[h]; //从队头拿出一个元素
        v[x]=0;
        for (i=1;i<=n;i++)
        {
            if (dist[i]-a[x][i]>dist[x])
            {   //本来是dist[i]>dist[x]+a[x][i]
                dist[i]=dist[x]+a[x][i];
                if (!v[i])
                {
                    t=(t+1)%(n+1);
                    q[t]=i;//入队操作
                    v[i]=1;
                }
            }
        }
    }
}

int main()
{
#if BENCH
	freopen("spfa.txt","r",stdin);
#endif
    int m;//图中边数
    int s;//源点的编号
    int tt;//目标顶点
    int i,x,y,z;
    cin>>n>>m>>s;
    memset(a,127,sizeof(a));
    for (i=1;i<=m;i++)
    {
    	cin>>x>>y>>z;
        a[x][y]=z;
        a[y][x]=z;
    }
    spfa(s);
    for (i=1;i<=n;i++)
    	cout<<dist[i]<<endl;
    return 0;
}
