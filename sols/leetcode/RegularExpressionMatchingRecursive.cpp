#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

class Solution {
public:
    bool isMatchHelper(const char *s, int si, const char *p, int pi) {
        if (!s[si] || !p[pi])
            return s[si] == p[pi];
        switch (p[pi]) {
            case '.':
                return isMatchHelper(s, si+1, p, pi+1);
            default:
            	if (s[si] == p[pi] && isMatchHelper(s, si+1, p, pi+1))
            		return true;
            	if (p[pi + 1] == '*') {
            		if (isMatchHelper(s, si, p, pi+2)) // match 0
            			return true;
            		if (s[si] == p[pi]) {
            			if (isMatchHelper(s, si+1, p, pi))
            				return true;
            			if (isMatchHelper(s, si+1, p, pi+2))
            				return true;
            		}
            		break;
            	}
        }
        return false;
    }

    bool isMatch(const char *s, const char *p) {
    	return isMatchHelper(s, 0, p, 0);
    }
};

int main() {
	Solution sn;
	cout << sn.isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c") << endl;
	return 0;
}
