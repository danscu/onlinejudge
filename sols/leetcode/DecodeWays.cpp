#include <iostream>
#include <string>

using namespace std;

//#define DEBUG

class Solution {
public:
    int numDecodings(string s) {
        const int len(s.length());
        if (!len)
            return 0;

        int w[len + 1][2];

        w[0][0] = 1;
        w[0][1] = 0;

        for (int i = 1; i <= len; ++i) {
            char ch = s[i - 1];
            bool canBeNew = ch != '0';
            bool canContinue = i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && ch <= '6'));

            w[i][0] = (canBeNew ? w[i - 1][0] : 0) + (canContinue ? w[i - 1][1] : 0);
            w[i][1] = (canBeNew ? w[i - 1][0] : 0);
        }

#ifdef DEBUG
        for (int i = 0; i <= len; ++i) {
            cout << w[i][0] << " " << w[i][1] << endl;
        }
#endif

        return w[len][0];
    }
};

int main() {
    Solution sn;

    cout << "Enter s: ";
    string line;
    cin >> line;
    cout << "decode ways: " << sn.numDecodings(line) << endl;
    return 0;
}
