class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty())
            return "";
        int i = 0, j, done = false;
        while (i < strs[0].length() && !done) {
            for (j = 1; j < strs.size(); j++) {
                if (i >= strs[j].length() || strs[j][i] != strs[0][i])
                    { done = true; break; }
            }
            if (!done) i++;
        }
        return strs[0].substr(0,i);
    }
};
