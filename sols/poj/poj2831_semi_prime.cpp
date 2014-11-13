/*
 * POJ 2831 H semi primes
 * Find h semi primes (easy)
 */
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifdef BENCH
#define DBG 1 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;

const Num maxn = 1000010;
const Num nlim = 1000001;
Num h_semi_prime[maxn];

void findHSemiPrimes()
{
    Num i, j;
    memset(h_semi_prime, 0, sizeof(h_semi_prime));
    for (i = 5; i <= nlim; i += 4)
        for (j = 5; j <= nlim; j += 4)
        {
        	Num product = i * j;
            if (product > maxn)
                break;

            // If they are h-primes (not a product)
            if (h_semi_prime[i] == 0 && h_semi_prime[j] == 0)
                h_semi_prime[product] = 1;	// h-semi-prime
            else
                h_semi_prime[product] = -1;	// not h-semi-prime
        }
    int cnt = 0;
    for(i = 0; i <= nlim; i++) {
    	cnt += (h_semi_prime[i] == 1);
    	h_semi_prime[i] = cnt;
    }
}

int main()
{
#if BENCH
	freopen("files/poj2831_semi_prime.txt","r",stdin);
#endif
    int n;
    findHSemiPrimes();
    while (~scanf("%d",&n) && n)
    {
         printf("%d %d\n", n, h_semi_prime[n]);
    }
    return 0;
}
