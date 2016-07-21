#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    void rotate(vector<vector<int> >& matrix) {
        int i, j, n = matrix.size();
        for (i = 0; i < n; ++i)
          for (j = 0; j < n - i; ++j) {
              int x = n - j - 1, y = n - i - 1;
              swap(matrix[i][j], matrix[x][y]);
          }
        for (i = 0; i < n/2; ++i)
          for (j = 0; j < n; ++j)
            swap(matrix[i][j], matrix[n-1-i][j]);
    }
};

int main() {
    Solution sn;
    vector<vector<int> >in;
    in.resize(1);
    in[0].resize(1, 1);

    sn.rotate(in);
    for (int i = 0; i < in.size(); ++i) {
        for (int j = 0; j < in[i].size(); ++j)
            cout << in[i][j] << " ";
        cout << endl;
    }

    return 0;
}
