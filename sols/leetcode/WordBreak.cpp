#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;
class Solution {
private:
    static const int maxn = 10000;
    bool good[maxn];
public:
    bool dfs(string &s, unordered_set<string> &dict, int pos, int slen) {
        if (pos >= s.length())
            return true;
        for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
            const string &lex(*it);
            int len(lex.length());

            if (slen < len) continue;

            if (!s.compare(pos, len, lex)) {
                bool ret = dfs(s, dict, pos + len, slen - len);
                if (ret) return ret;
            }
        }
        return false;
    }

    bool dynam(string &s, unordered_set<string> &dict, int slen) {
        good[0] = true;
        for (int i = 1; i <= slen; i++) {
            for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
                const string &lex(*it);
                int len(lex.length());
                if (i >= len)
                    good[i] |= good[i - len] && !s.compare(i - len, len, lex);
            }
        }
        return good[slen];
    }

    bool wordBreak(string s, unordered_set<string> &dict) {
        // return dfs(s, dict, 0, s.length());
        return dynam(s, dict, s.length());
    }
};

int main() {
	unordered_set<string> dict;
	dict.insert("leet"); dict.insert("code");
	cout << (new Solution())->wordBreak("leetcode", dict) << endl;
	return 0;
}
