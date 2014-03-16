class Solution {
public:
    char l[256];

    int lengthOfLongestSubstring(string s) {
        memset(l, -1, sizeof l);
        if (s.empty()) return 0;

        int head = 0; l[s[0]] = 0;
        int maxl = 1;

        for (int i=1; i<s.length(); i++) {
            char c = s[i];
            if (l[c] != -1) {
                for (int j = 0; j < 256; j++)
                    if (l[j] < l[c])
                        l[j] = -1;
                head = l[c] + 1;
            }
            l[c] = i;
            maxl = max(maxl, i - head + 1);
        }

        return maxl;
    }
};
