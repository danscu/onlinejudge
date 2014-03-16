//AC自动机
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std ;

const int maxn = 5555555 ;
class AC_auto
{
private :
    int tot , fail[maxn] , val[maxn] , c[26][maxn] ;
    queue<int> Q ;
    int new_node ()
    {
        int i ;
        fail[tot] = val[tot] = 0 ;
        for ( i = 0 ; i < 26 ; i ++ ) c[i][tot] = 0 ;
        return tot ++ ;
    }
public :
    void init ()
    {
        tot = 0 ; new_node () ;
        while ( !Q.empty () ) Q.pop () ;
    }
    void insert ( char *s )
    {
        int now = 0 ;
        for ( ; *s ; s ++ )
        {
            int k = *s - 'a' ;
            if ( !c[k][now] ) c[k][now] = new_node () ;
            now = c[k][now] ;
        }
        val[now] ++ ;
    }
    void get_fail ()
    {
        int i , u = 0 , j , e ;
        for ( i = 0 ; i < 26 ; i ++ ) if ( c[i][u] ) Q.push ( c[i][u] ) ;
        while ( !Q.empty () )
        {
            u = Q.front () ;
            Q.pop () ;
            for ( i = 0 ; i < 26 ; i ++ )
            {
                if ( !c[i][u] )
                {
                    c[i][u] = c[i][fail[u]] ;
                    continue ;
                }
                e = c[i][u] ;
                j = fail[u] ;
                fail[e] = c[i][j] ;
                Q.push ( e ) ;
            }
        }
    }
    int work ( char *s )
    {
        int u = 0 , i , e , ret = 0 ;
        for ( ; *s ; s ++ )
        {
            int k = *s - 'a' ;
            u = c[k][u] ;
            e = u ;
            while ( e )
            {
                if ( val[e] )
                {
                    ret += val[e] ;
                    val[e] = 0 ;
                }
                e = fail[e] ;
            }
        }
        return ret ;
    }
} ac ;
char s[maxn] ;
int main ()
{
#if BENCH
	freopen("ac_automaton.txt", "r", stdin);
#endif
    int cas , n ;
    scanf ( "%d" , &cas ) ;
    while ( cas -- )
    {
        scanf ( "%d" , &n ) ;
        ac.init () ;
        while ( n -- )
        {
            scanf ( "%s" , s ) ;
            ac.insert ( s ) ;
        }
        ac.get_fail () ;
        scanf ( "%s" , s ) ;
        printf ( "%d\n" , ac.work ( s ) ) ;
    }
}
