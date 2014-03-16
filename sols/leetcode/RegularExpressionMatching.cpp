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
#include <cassert>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

class Solution {
public:
    bool isMatchHelper(const char *s, int si, int sz, const char *p, int pi, int pz, int forward) {
    	if (pi > pz)
    		return si > sz;

    	if (si > sz) {
    		if (pi > pz)
    			return true;
    		if (pi + 1 <= pz && p[pi+1] == '*')
    			return isMatchHelper(s, si, sz, p, pi+2, pz, forward);
    		else
    			return false;
    	}

    	if (forward) {
			switch (p[pi]) {
				case '.':
					if (isMatchHelper(s, si+1, sz, p, pi+1, pz, !forward))
						return true;
					// fall
				default:
					if (s[si] == p[pi] && isMatchHelper(s, si+1, sz, p, pi+1, pz, !forward))
						return true;
					if (p[pi + 1] == '*') {
						if (isMatchHelper(s, si, sz, p, pi+2, pz, !forward)) // match 0
							return true;
						if (s[si] == p[pi]  || p[pi] == '.') {
							if (isMatchHelper(s, si+1, sz, p, pi, pz, !forward)) // match more
								return true;
							if (isMatchHelper(s, si+1, sz, p, pi+2, pz, !forward)) // match done
								return true;
						}
						break;
					}
			}
			return false;
    	} else {
    		switch (p[pz]) {
    		case '.':
    			if (isMatchHelper(s, si, sz-1, p, pi, pz-1, !forward))
    				return true;
    			// fall
    		default:
    			if (s[sz] == p[pz] && isMatchHelper(s, si, sz-1, p, pi, pz-1, !forward))
    				return true;
    			if (p[pz] == '*') {
    				if (isMatchHelper(s, si, sz, p, pi, pz-2, !forward)) // match 0
    					return true;
    				if (s[sz] == p[pz-1] || p[pz-1] == '.') {
    					if (isMatchHelper(s, si, sz-1, p, pi, pz, !forward)) // match more
    						return true;
    					if (isMatchHelper(s, si, sz-1, p, pi, pz-2, !forward)) // match done
    						return true;
    				}
    				break;
    			}
    		}
    		return false;
    	}
    }

    bool myIsMatch(const char *s, const char *p) {
    	int sl = strlen(s), pl = strlen(p);
    	return isMatchHelper(s, 0, sl-1, p, 0, pl-1, 1);
    }

    bool isMatch(const char *s, const char *p) {
    	assert(s && p);
    	if (*p == '\0') return *s == '\0';

    	// next char is not '*': must match current character
    	if (*(p+1) != '*') {
    		assert(*p != '*');
    		return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
    	}
    	// next char is '*'
    	while ((*p == *s) || (*p == '.' && *s != '\0')) {
    		if (isMatch(s, p+2)) return true;
    		s++;
    	}
    	return isMatch(s, p+2);
    }
};

int main() {
	Solution sn;
//	cout << sn.isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c") << endl;
	cout << sn.isMatch("bb", ".bab") << endl;
	return 0;
}
