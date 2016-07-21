#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        int N = 1 << n;
        bool used[N];
        memset(used, 0, sizeof(used));

        int c = 0; res.push_back(c); used[c] = true;
        for (int i = 0; i < N-1; i++) {
            int j, nc;
            for (j = 0; j < n; j++) {
                nc = c ^ (1 << j);
                if (!used[nc]) break;
            }
            if (j != n) {
                res.push_back(nc);
                c = nc;
                used[c] = true;
            } else {
                cout << "fail!" << endl;
            }
        }

        return res;
    }
};

int main() {
    Solution sn;

    auto r = sn.grayCode(5);

    for (int i = 0; i < r.size(); ++i) {
        cout << r[i] << " ";
    }

    cout << endl;

    return 0;
}
