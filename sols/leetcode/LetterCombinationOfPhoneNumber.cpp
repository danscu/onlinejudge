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

static char *letters[] = {
    " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

class Solution {
private:
    char *path;

    void search(vector<string> &res, string &digits, int k) {
        if (k >= digits.length()) {
            path[k] = 0;
            res.push_back(string(path));
            return;
        }

        char c = digits[k];
        char *let = letters[c-'0'];
        while (*let) {
            path[k] = *let;
            search(res, digits, k + 1);
            ++let;
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        path = new char[digits.length()+1];

        search(res, digits, 0);

        delete[] path;

        return res;
    }
};

int main() {
	Solution sn;
	vector<string> res = sn.letterCombinations("4");
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << endl;
}
