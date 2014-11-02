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

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (m == n) return head;

        int i = 1;
        ListNode *listHead = head;
        ListNode *prev = NULL;
        ListNode *cur = head;
        while (i < m) {
            i++;
            prev = cur;
            cur = cur->next;
        }
        
        // cur points to first to be reversed
        ListNode *preChain = prev;
        ListNode *firstChain = cur, *lastChain = NULL;
        prev = cur; cur = cur->next;
        
        for (i++; i <= n; i++) {
        	if (i == n) lastChain = cur;
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        
        if (preChain)
            preChain->next = lastChain;
        else
            listHead = lastChain;
        
        firstChain->next = cur;
        
        return listHead;
    }
};

int main() {
	ListNode *u1 = new ListNode(3);
	ListNode *u2 = new ListNode(5);
	u1->next = u2;
	u2->next = NULL;

	Solution sn;
	ListNode *pNode = sn.reverseBetween(u1, 1, 2);
	while (pNode) {
		cout << pNode->val << endl;
		pNode = pNode->next;
	}

	return 0;
}
