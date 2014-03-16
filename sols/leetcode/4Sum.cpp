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
private:
    vector<int> path;
    typedef set<int> SetNum;
    SetNum nums;

public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
    	vector<vector<int> > res;

        if (num.size() <= 3)
            return 0;

        int n = num.size();

        sort(num.begin(), num.end());

        int i, j;
        int bestSum, minDiff = INT_MAX;
        for (i = 0; i < n - 3; i++) {
        	if (i > 0 && num[i] == num[i-1])
        		continue;
        	for (j = i + 1; j < n - 2; j++)
        	{
           		if (j > i + 1 && num[j] == num[j-1])
            			continue;
        		int tgt = target - num[i] - num[j];
        		vector<int>::iterator left = num.begin() + j + 1;
        		vector<int>::iterator right = num.begin() + n - 1;
        		while (left < right) {
        			if (tgt - *left - *right == 0) {
        				vector<int> rr;
        				rr.push_back(num[i]);
        				rr.push_back(num[j]);
        				rr.push_back(*left);
        				rr.push_back(*right);
        				res.push_back(rr);

        				left++;
        				right--;

        				while (left < right && *left == *(left-1)) left++;
        				while (left < right && *right == *(right+1)) right--;
        			} else {
						if (*left + *right < tgt)
							left++;
						else
							right--;
        			}
        		}
        	}
        }
        return bestSum;
    }
};

int main() {
	int nums[] = {1,2,-1,-4};
	vector<int> num(nums,nums+(sizeof nums/sizeof nums[0]));
	Solution sn;
	int bestSum = sn.fourSum(num,-2);
	cout << bestSum << endl;
}
