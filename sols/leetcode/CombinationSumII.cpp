#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> sel;
    int sum;
public:
    void search(vector<pair<int,int> > &candidates, vector<vector<int> > &res, int dep, int from, int target) {
        int i,j,j2,oldsum,oldsize;

        // corner
        if (sum == target) {
        	res.push_back(sel);
            return;
        }

        oldsum = sum;
        oldsize = sel.size();

        for (i = from; i < candidates.size(); i++) {
        	for (j=1; j<=candidates[i].second;j++) {
        		sel.push_back(candidates[i].first);
        		sum+=candidates[i].first;
        	    if (sum > target)
        	        break;
            	search(candidates, res, dep+1, i+1, target);
        	}
            sum=oldsum;
            sel.resize(oldsize);
        }
    }

    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
    	vector<pair<int,int> > num;
        sort(candidates.begin(), candidates.end());

        num.reserve(candidates.size());
        sel.reserve(candidates.size());

    	for (int i = 0; i < candidates.size(); i++) {
    		if (i==0 || candidates[i] != num[num.size()-1].first)
    			num.push_back(make_pair(candidates[i], 1));
    		else
    			num[num.size()-1].second++;
    	}

        vector<vector<int> > res;
        sum = 0;
        search(num, res, 0, 0, target);
        return res;
    }
};


int main() {
	Solution s;

	int a[] = {14,6,25,9,30,20,33,34,28,30,16,12,31,9,9,12,34,16,25,32,8,7,30,12,33,20,21,29,24,17,27,34,11,17,30,6,32,21,27,17,16,8,24,12,12,28,11,33,10,32,22,13,34,18,12};
	vector<int> num;
	int n = sizeof(a) / sizeof(a[0]);
	num.reserve(n);
	num.insert(num.begin(), a, a + n);

	s.combinationSum2(num, 27);
	return 0;
}
