#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//#define DEBUG

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        //set<int> numSet;
        //vector<int> numUniq;
        set<vector<int> > res;

        sort(nums.begin(), nums.end());
        // convert to set
//        for (auto it = nums.begin(); it != nums.end(); ++it) {
//            numSet.insert(*it);
//        }

//        std::copy(numSet.begin(), numSet.end(), std::back_inserter(numUniq));

        // take subsets
        vector<int> empty;
        res.insert(empty);

        generateSubset(0, empty, nums, res);

        vector<vector<int> > vecRes;
        std::copy(res.begin(), res.end(), std::back_inserter(vecRes));

        return vecRes;
    }

private:
    void generateSubset(int curIndex, vector<int> &curSubset, vector<int> &numUniq, set<vector<int> > &res) {
        if (curIndex == numUniq.size())
            return;

        vector<int> newSubset(curSubset);
        newSubset.push_back(numUniq[curIndex]);

        // skip case
        generateSubset(curIndex + 1, curSubset, numUniq, res);

        // insert case
        res.insert(newSubset);
        generateSubset(curIndex + 1, newSubset, numUniq, res);
    }
};

int main() {
    Solution sn;

    vector<int> input;
    input.push_back(1);
    input.push_back(2);
    input.push_back(3);
    input.push_back(3);
    input.push_back(4);

    set<vector<int> > res = sn.subsetsWithDup(input);

    for (auto it = res.begin(); it != res.end(); ++it) {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2)
            cout << *it2 << " ";
        cout << endl;
    }

    return 0;
}
