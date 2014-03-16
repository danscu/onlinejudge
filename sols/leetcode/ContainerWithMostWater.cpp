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

const int maxn = 10000;

class Solution {
public:
    int maxArea(vector<int> &height) {
       int low = 0, hi = height.size()-1;
       int maxa = 0;
       while (low < hi) {
           maxa = max(maxa, (hi - low) * min(height[low], height[hi]));
           if (height[low] < height[hi])
                low++;
           else
                hi--;
       }
       return maxa;
    }
};

int main(){
	Solution sn;
	int nums[] = {1,2,2};

	vector<int> v(nums, nums+3);

	cout << sn.maxArea(v);
	return 0;
}
