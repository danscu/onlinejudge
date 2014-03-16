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
    string convert(string s, int nRows) {
    	if (nRows==1) return s;
        int R = 2*nRows-2, n = s.length();
        char buf[n+1]; int bi=0;
        for (int i=0;i<nRows;i++) {
            if (i==0) {
                for (int k=0;R*k<n;k++)
                    buf[bi++]=s[R*k];
            } else if (i==nRows-1) {
                for (int k=0;R*k+nRows-1<n;k++)
                    buf[bi++]=s[R*k+nRows-1];
            } else for (int k=0;R*k+i<n;k++) {
                    buf[bi++]=s[R*k+i];
                    if (R*(k+1)-i<n)
                        buf[bi++]=s[R*(k+1)-i];
            }
        }
        buf[bi]=0;
        return string(buf);
    }
};

int main() {
	Solution sn;
	cout << sn.convert(string("PAYPALISHIRING"),1)<<endl;
	return 0;
}
