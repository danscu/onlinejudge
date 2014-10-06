#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
    	generate(n, n, "", res);
    	return res;
    }

    void generate(int left, int right, string str, vector<string>& res)
    {
    	if(left == 0 && right == 0)
    	{
    		res.push_back(str);
    		return;
    	}
    	if(right > left)
    	{
    		generate(left, right - 1, str + ')', res);
    	}
    	if(left > 0)
    	{
    		generate(left - 1, right, str + '(', res);
    	}
    }
};

int main() {
	Solution sn;
	vector<string> res = sn.generateParenthesis(6);

	for (int i = 0; i < res.size(); i++)
		cout << res[i] << endl;

	return 0;
}
