class Solution {
private:
    set<pair<int,int> > dp[2];
public:
    bool isInterleave(string s1, string s2, string s3) {
        int last = 0, cur;
        int ss3 = s3.length();
        if (s3.length() != s1.length() + s2.length()) return false;
        dp[last].insert(pair<int,int>(0,0));
        for (int i = 0; i < ss3; i++) {
            cur =  last ^ 1;
            dp[cur].clear();
            for (set<pair<int,int> >::iterator iPrev = dp[last].begin(); iPrev != dp[last].end(); iPrev++) {
                const pair<int,int> &par(*iPrev);
                if (par.first < s1.length() && s1[par.first] == s3[i])
                    dp[cur].insert(pair<int,int>(par.first + 1, par.second));
                if (par.second < s2.length() && s2[par.second] == s3[i])
                    dp[cur].insert(pair<int,int>(par.first, par.second + 1));
            }
            last = cur;
        }
        return dp[last].size();
    }
};
