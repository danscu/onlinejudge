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
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > res;
        if (num.size() <= 2)
            return res;

        int n = num.size();

        sort(num.begin(), num.end());

        int i;
        for (i = 0; i < n - 2; i++) {
        	int tgt = -num[i];
        	if (i > 0 && num[i] == num[i-1])
        		continue;
        	vector<int>::iterator left = num.begin() + i + 1;
        	vector<int>::iterator right = num.begin() + n - 1;
        	while (left < right) {
				if (*left + *right == tgt) {
					vector<int> sl;
					sl.push_back(num[i]);
					sl.push_back(*left);
					sl.push_back(*right);
					res.push_back(sl);
					left++; right--;

					while (left < right && *(left-1) == *left)
						left++;
					while (left < right && *(right+1) == *right)
						right--;
				} else
					if (*left + *right < tgt)
						left++;
					else
						right--;
        	}
        }
        return res;
    }
};

ostream & operator<<(ostream& os, vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;
	return os;
}

int main() {
	int nums[] = {-1,0,1,2,-1,-4};
	vector<int> num(nums,nums+(sizeof nums/sizeof nums[0]));
	Solution sn;
	vector<vector<int> > r = sn.threeSum(num);
	for (int i = 0; i < r.size(); i++)
		cout << r[i] << endl;
}
