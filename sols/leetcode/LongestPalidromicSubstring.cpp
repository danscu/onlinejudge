class Solution {
public:
    string longestPalindrome(string s) {
        int i, j, maxl = 0, maxi = -1;
        for (i = 0; i < s.length(); i++) {
            for (j = 0; i - j >= 0 && i + j < s.length(); j++) {
                if (s[i-j] != s[i+j])
                    break;
                if (j*2+1 > maxl) {
                    maxl = j*2+1;
                    maxi = i - j;
                }
            }
            if (i < s.length() - 1 && s[i+1] == s[i]) {
                for (j = 0; i - j >= 0 && i + 1 + j < s.length(); j++) {
                    if (s[i-j] != s[i+1+j])
                        break;
                    if (j*2+2 > maxl) {
                        maxl = j*2+2;
                        maxi = i - j;
                    }
                }
            }
        }
        return s.substr(maxi, maxl);
    }
};
