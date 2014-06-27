class Solution {
private:
    vector<int> sel;
    int sum;
public:
    void search(vector<int> &candidates, vector<vector<int> > &res, int dep, int from, int target) {
        int i;

        // corner
        if (sum == target) {
            res.push_back(sel);
            return;
        } else if (sum > target)
            return;

        for (i = from; i < candidates.size(); i++) {
            sel.push_back(candidates[i]);
            sum+=candidates[i];
            search(candidates, res, dep+1, i, target);
            sum-=candidates[i];
            sel.pop_back();
        }
    }

    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > res;
        sort(candidates.begin(), candidates.end());
        sum = 0;
        search(candidates, res, 0, 0, target);
        return res;
    }
};
