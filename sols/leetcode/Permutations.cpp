#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<bool> used;
    vector<int> permu;
    vector<int> *nums;

    int n;

    void perm(int pos, vector<vector<int> >& res) {
        if (pos == n) {
            vector<int> permnum;
            for (int i = 0; i < n; i++) {
                permnum.push_back((*nums)[permu[i]]);
            }
            res.push_back(permnum);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = true;
                permu[pos] = i;
                perm(pos+1, res);
                used[i] = false;
            }
        }
    }

public:
    vector<vector<int> > permute(vector<int>& nums) {
        vector<vector<int> > res;

        n = nums.size();
        used.resize(n, false);
        permu.resize(n, 0);

        this->nums = &nums;
        perm(0, res);

        return res;
    }
};

int main() {
    Solution sn;
    vector<int> in;
    in.push_back(1);
    in.push_back(2);
    in.push_back(3);

    vector<vector<int> > r = sn.permute(in);
    for (int i = 0; i < r.size(); ++i) {
        for (int j = 0; j < r[i].size(); ++j)
            cout << r[i][j] << " ";
        cout << endl;
    }

    return 0;
}
