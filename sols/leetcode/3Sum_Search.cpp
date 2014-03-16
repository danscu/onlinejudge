class Solution {
private:
    vector<int> path;

public:
    void search(vector<int> &num, int k, int from, int partial, vector<vector<int> > res) {
        // base
        if (k == 3) {
            if (partial == 0) {
                vector<int> newRes(path.begin(), path.begin()+3);
                res.push_back(newRes);
            }
            return;
        }

        int i;
        for (i = from; i < num.size() - (2-k); i++) {
            int nn = num[i];

            if (k == 0 && nn > 0)
                continue;
            else if (k == 1 && !(-partial - 2 * nn >= 0))
                continue;

            path.push_back(nn);
            search(num, k + 1, i + 1, partial + nn, res);
            path.pop_back();
        }
    }

    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > res;
        if (num.size() <= 2)
            return res;
        sort(num.begin(), num.end());
        path.resize(4);
        search(num, 0, 0, 0, res);
        return res;
    }
};
