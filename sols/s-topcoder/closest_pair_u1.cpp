#include <stdio.h>
#include "stdlib.h"
#include "math.h"

typedef struct node
{
	int x,y;
	int index;
}NODE;

NODE data[100005];
int start, end;
int min;
double distance (NODE a, NODE b)
{
	return (pow((double)(a.x-b.x),2)+pow((double)(a.y-b.y),2));
}
int compare(const void *a, const void *b)
{
	NODE *c =(NODE *)a;
	NODE *d =(NODE *)b;
	if(c->x!=d->x)
		return c->x-d->x;
	else
		return c->y!=d->y;
}
int main(void)
{
	int tc, T,N,i,j;
	freopen("closest-pair.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(tc = 0; tc < T; tc++)
	{
		//memset(length, 1, sizeof(length));
		scanf("%d", &N);
		for(i=0;i<N;i++)
		{
			scanf("%d%d", &data[i].x,&data[i].y);
			data[i].index=i+1;
		}
		if(N==1)
			printf("%d %d\n", 1, 1);
		else
		{
			qsort(data,N,sizeof(data[0]),compare);

			start=data[0].index>data[1].index?1:0;
			end=data[0].index<data[1].index?1:0;
			double dis2=distance(data[start],data[end]);
			//min=0;
			for(i=0;i<N-1;i++)
			{
				for(j=i+1;j<N&&dis2>=abs(data[j].x-data[i].x);j++)
				{
					double dis1=distance(data[i],data[j]);
					if(dis1<dis2)
					{
						int a=data[i].index>data[j].index?j:i;
						int b=data[i].index<data[j].index?j:i;
						start=a;
						end=b;
						dis2=distance(data[start],data[end]);
					}
					else if(dis1==dis2)
					{
						int a=data[i].index>data[j].index?j:i;
						int b=data[i].index<data[j].index?j:i;
						if(data[a].index<data[start].index||(data[a].index==data[start].index&&data[b].index<data[end].index))
						{
							start=a;
							end=b;
						}
					}
				}
			}

			printf("%d %d\n", data[start].index, data[end].index);
			printf("%f\n", sqrt(distance(data[start], data[end])));
		}
	}

	return 0;//Your program should return 0 on normal termination.
}
