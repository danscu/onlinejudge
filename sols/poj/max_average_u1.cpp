/**
 *  HDU 2993 MAX Average Problem
 *
 *  分析：这题看可以想到一个简单的DP，就是枚举两个可行的边界，然后取最值就行，
 *  复杂度是O（n^2）的，肯定是超时的，那么有什么好的办法，说实话，我也是没想出来的，
 *  只能去看看周源大神的《浅谈数形结合思想在信息学竞赛中的应用》，里面还是讲得很清楚的
 *  不过寻找切线那块貌似没讲，我一开始想错了，然后一直wa，找不到原因，后来看看别人的代码才明白
 *  方法很简单，直接枚举队列前的几个元素与当前节点构成的斜率，小的直接退队，直到找到最大值
 *  就是当前的最大值了，这样的话，总的均摊时间复杂度是O(n)的，完美的解决了这个问题。。
 *  至于前面斜率小的退队为什么是正确的？简单的反证下，假设后面有个点的切线在那些低的点上，
 *  那么构成的斜率肯定比之前的小。。
 */

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 100005

int sum[MAXN];
int que[MAXN];
int a[MAXN];

int getin()       //getin()函数优化输入，如果有scanf读入，不管用c++还是G++提交都会CE
{
	char c;
	int dd;
	while(c=getchar(),c<'0'||c>'9');
	dd=c-'0';
	while(c=getchar(),c>='0'&&c<='9')
		dd=dd*10+c-'0';
	return dd;
}

double slope(int i,int j) //求斜率
{
	double kk;
	kk=1.0*(sum[i]-sum[j])/(i-j);
	return kk;
}

int main()
{
	int n,k,i,j,head,rear;
	double ans;
#if BENCH
	freopen("max_average.txt", "r", stdin);
#endif
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		sum[0]=0;
		for(i=1;i<=n;i++)
			sum[i]=sum[i-1]+getin();
		que[0] = 0;			    //队列初始化
		head = rear = ans = 0;	//ans存每次更新的最大平均值即最大斜率，head和rear是单调队列的头指针和尾指针
		for(i = k; i <= n; i++)	//从第K个开始检查，因为至少要相隔K个数
		{
			j = i - k + 1;
			while (head < rear && slope(que[head], i) <= slope(que[head+1], i))			//维护单调队列，保证单增队列的头元素必是最大的
				head++;
			ans = max(ans, slope(i, que[head]));									    //更新ans的值
			while (head < rear && slope(j, que[rear]) <= slope(que[rear], que[rear-1]))	//每次遇到上凸点就退队
				rear--;
			que[++rear] = j;														    //把与检查的点相隔k的那个数加入队列
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
