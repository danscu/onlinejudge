/* THE PROGRAM IS MADE BY PYY */
/*----------------------------------------------------------------------------//
    Copyright (c) 2011 panyanyany All rights reserved.

    URL   :
    Name  : 3264 Balanced Lineup

    Date  : Saturday, October 1, 2011
    Time Stage : more than one hour

    Result:
9381120	panyanyany
3264
Accepted	2208K	1860MS	C++
2677B	2011-10-01 19:56:56

Test Data :

Review :
???AC????????
“”?????
????
???

?


???
 left? right???
//----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#define INF		0x7f7f7f7f

#define MAXSIZE 50010

#define L(n)		((n) << 1)
#define R(n)		(((n) << 1) + 1)
#define MID(a, b)	(((a) + (b)) >> 1)
#define min(a, b)	(((a) < (b)) ? (a) : (b))
#define max(a, b)	(((a) > (b)) ? (a) : (b))

typedef struct {
	int		low, high ;
	int		left, right ;
} NODE ;

int		n, q ;
NODE	tree[MAXSIZE * 10] ;

void swap (int &lhs, int &rhs)
{
	int tmp ;
	tmp = lhs ;
	lhs = rhs ;
	rhs = tmp ;
}

void build (int node, int left, int right)
{
	tree[node].left		= left ;
	tree[node].right	= right ;
	tree[node].low		= INF ;		//
	tree[node].high		= -INF ;	//

	if (left == right)
		return ;

	int mid = MID (left, right) ;
	build (L(node), left, mid) ;
	build (R(node), mid + 1, right) ;
}

void update (int node, int left, int right, int pos, int x)
{
	//
	if (tree[node].left == tree[node].right && tree[node].left == pos)
	{
		tree[node].low = tree[node].high = x ;
		return ;
	}

	int mid = MID (tree[node].left, tree[node].right) ;

	// ???
	tree[node].low = min (tree[node].low, x) ;
	tree[node].high = max (tree[node].high, x) ;

	//
	if (pos <= mid)
		update (L(node), left, mid, pos, x) ;
	//
	else if (mid < pos)
		update (R(node), mid + 1, right, pos, x) ;
}

void query (int node, int left, int right, int *x, int *y)
{
	//
	// *x ?*y
	if (tree[node].left == left && tree[node].right == right)
	{
		*x = tree[node].low ;
		*y = tree[node].high ;
		return ;
	}
	int mid = MID (tree[node].left, tree[node].right) ;
	int x1, y1, x2, y2 ;

	//
	if (right <= mid)
	{
		query (L(node), left, right, &x1, &y1) ;
		*x = x1 ;
		*y = y1 ;
	}
	//
	else if (mid < left)
	{
		query (R(node), left, right, &x2, &y2) ;
		*x = x2 ;
		*y = y2 ;
	}
	//
	else
	{
		query (L(node), left, mid, &x1, &y1) ;
		query (R(node), mid + 1, right, &x2, &y2) ;

		*x = min (x1, x2) ;
		*y = max (y1, y2) ;
	}

	return ;
}

int main ()
{
	// input
#if BENCH
	freopen("files/poj3264_sanity.in", "r", stdin);
#endif
	int	i, j ;
	int x, y, low, high ;
	while (scanf ("%d%d", &n, &q) != EOF)
	{
		build (1, 1, n) ;
		for (i = 1 ; i <= n ; ++i)
		{
			scanf ("%d", &x) ;
			update (1, 1, i, i, x) ;
		}

		for (i = 1 ; i <= q ; ++i)
		{
			scanf ("%d%d", &x, &y) ;
			if (x > y)
				swap (x, y) ;
			query (1, x, y, &low, &high) ;
			printf ("%d\n", high - low) ;
		}
	}
	return 0 ;
}
