#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int> > dp(1+word1.size(), vector<int>(1+word2.size()));
        dp[0][0] = 0;
        int i,j;
        for (i = 1; i <= word1.size(); i++)
            dp[i][0] = i;
        for (i = 1; i <= word2.size(); i++)
            dp[0][i] = i;
        for (i = 1; i <= word1.size(); i++)
            for (j = 1; j <= word2.size(); j++)
                dp[i][j] = min(
                    dp[i-1][j-1] + (word1[i-1] != word2[j-1] ? 1 : 0),
                    min(dp[i-1][j] + 1, dp[i][j-1] + 1));
        return dp[word1.size()][word2.size()];
    }
};

int main() {
	Solution s;
	cout<<s.minDistance("plasma","altruism")<<endl;
	return 0;
}
