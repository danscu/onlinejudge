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
    int threeSumClosest(vector<int> &num, int target) {
        if (num.size() <= 2)
            return 0;

        int n = num.size();

        sort(num.begin(), num.end());

        int i;
        int bestSum, minDiff = INT_MAX;
        for (i = 0; i < n - 2; i++) {
        	int tgt = target - num[i];
        	if (i > 0 && num[i] == num[i-1])
        		continue;
        	vector<int>::iterator left = num.begin() + i + 1;
        	vector<int>::iterator right = num.begin() + n - 1;
        	while (left < right) {
				if (abs(tgt - *left - *right) < minDiff) {
					minDiff = abs(tgt - *left - *right);
					bestSum = *left + *right + num[i];
					if (minDiff == 0)
						return bestSum;
				}

				if (*left + *right < tgt)
					left++;
				else
					right--;
        	}
        }
        return bestSum;
    }
};

int main() {
	int nums[] = {1,2,-1,-4};
	vector<int> num(nums,nums+(sizeof nums/sizeof nums[0]));
	Solution sn;
	int bestSum = sn.threeSumClosest(num,1);
	cout << bestSum << endl;
}
