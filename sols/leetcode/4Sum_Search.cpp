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

class Solution {
private:
    vector<int> path;

public:
    void search(vector<int> &num, int k, int from, int partial, int target, vector<vector<int> > res) {
        // base
        if (k == 4) {
            if (partial == target) {
                vector<int> newRes(path.begin(), path.begin()+4);
                res.push_back(newRes);
            }
            return;
        }

        int i;
        for (i = from; i < num.size() - (3-k); i++) {
            int nn = num[i];

            if (partial + nn * (3 - k) > target)
            	continue;

            path.push_back(nn);
            search(num, k + 1, i + 1, partial + nn, target, res);
            path.pop_back();
        }
    }

    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector<vector<int> > res;
        if (num.size() <= 3)
            return res;
        sort(num.begin(), num.end());
        path.resize(5);
        search(num, 0, 0, 0, target, res);
        return res;
    }
};
