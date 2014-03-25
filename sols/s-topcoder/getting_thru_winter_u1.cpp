#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int trees1[1024], trees2[1024];
static int tree1_cnt, tree2_cnt;


inline int min( int a, int b )
{
    return (a > b) ? b : a;
}


int cmp_less( const void *a, const void *b )
{
    return *(const int*)a - *(const int*)b;
}


int find_min_s( int k )
{
    int buffer[4096];
    int *min_dbl, *min_sep, *tmp;
    int *next_min_dbl, *next_min_sep;
    int last1, last2, lastD;
    int i1, i2;
    int p1, p2;
    int i, cur_x, cur_s;

    memset( buffer, 0, 2048*sizeof(int) );
    last1 = last2 = lastD = 0;
    min_dbl = buffer;
    min_sep = min_dbl + 1024;
    next_min_dbl = min_sep + 1024;
    next_min_sep = next_min_dbl + 1024;

    for( i1 = i2 = 0; i1 < tree1_cnt || i2 < tree2_cnt; i1 += p1, i2 += p2 )
    {
        p1 = p2 = 0;

        if(trees1[i1] <= trees2[i2])
        {
            p1 = 1;
            cur_x = trees1[i1];
        }

        if(trees1[i1] >= trees2[i2])
        {
            p2 = 1;
            cur_x = trees2[i2];
        }

        for( i = 0; i <= k; ++i )
            next_min_dbl[i] = next_min_sep[i] = 1000000000;

        for( i = 0; i <= k; ++i )
        {
            if( lastD != 0 )
            {
                cur_s = (cur_x - lastD)*2 + min_dbl[i];
                next_min_dbl[i] = min( next_min_dbl[i], cur_s );
            }

            cur_s = min( min_dbl[i], min_sep[i] ) + 2;
            next_min_dbl[i+1] = min( next_min_dbl[i+1], cur_s );

            if( last1 != 0 && p1 )
            {
                if( last2 != 0 && p2 )
                {
                    cur_s = (cur_x - last1) + (cur_x - last2) + min_sep[i];
                    next_min_sep[i] = min( next_min_sep[i], cur_s );
                }

                cur_s = cur_x - last1 + min_sep[i] + p2;
                next_min_sep[i+p2] = min( next_min_sep[i+p2], cur_s );
            }

            if( last2 != 0 && p2 )
            {
                cur_s = cur_x - last2 + min_sep[i] + p1;
                next_min_sep[i+p1] = min( next_min_sep[i+p1], cur_s );
            }

            cur_s = min( min_dbl[i], min_sep[i] ) + p1 + p2;
            next_min_sep[i+p1+p2] = min( next_min_sep[i+p1+p2], cur_s );
        }

        tmp = min_dbl;
        min_dbl = next_min_dbl;
        next_min_dbl = tmp;
        tmp = min_sep;
        min_sep = next_min_sep;
        next_min_sep = tmp;

        lastD = cur_x;
        if( p1 ) last1 = cur_x;
        if( p2 ) last2 = cur_x;
    }

    return min( min_dbl[k], min_sep[k] );
}


int main()
{
    int T, t, N, K, B;
    int i, x, y;
#if BENCH
	freopen("getting_thru_winter.txt","r",stdin);
#endif
    scanf( "%d", &T );
    for( t = 1; t <= T; ++t )
    {
        tree1_cnt = tree2_cnt = 0;

        scanf( "%d %d %d", &N, &K, &B );
        for( i = 0; i < N; ++i )
        {
            scanf( "%d %d", &y, &x );
            if( y == 1 )
                trees1[tree1_cnt++] = x;
            else
                trees2[tree2_cnt++] = x;
        }

        if( N <= K )
        {
            printf( "%d\n", K );
            continue;
        }

        qsort( trees1, tree1_cnt, sizeof(int), cmp_less );
        qsort( trees2, tree2_cnt, sizeof(int), cmp_less );
        trees1[tree1_cnt] = trees2[tree2_cnt] = 1000000000;

        printf( "%d\n", find_min_s(K) );
    }

    return 0;
}
