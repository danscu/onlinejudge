#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>

using namespace std;

class Solution {
private:
    typedef unordered_set<string>::iterator Word;
    vector<multimap<int,Word> > dpw;
    vector<bool> dp;

    void recons(vector<string> &res, int i, const string &tail) {
    	// base
    	if (i == 0) {
    		res.push_back(tail);
    		return;
    	}
    	string now;
    	for (multimap<int,Word>::iterator it = dpw[i].begin();
    		it != dpw[i].end(); it++) {
    		now = *it->second;
    		if (tail.length()) now += " " + tail;
    		recons(res, i - it->second->length(), now);
    	}
    }

public:
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        dp.clear();
        dp.resize(s.size() + 1);
        dpw.clear();
        dpw.resize(s.size() + 1);

        // init
        dp[0] = true;

        // iteration
        for (int i = 1; i <= s.size(); i++) {
            for (Word w = dict.begin(); w != dict.end(); w++) {
                int len = w->length();
                int bi = i - len;
                if (len <= i && !s.compare(bi, len, *w) && dp[bi]) {
                    dp[i] = true;
                    dpw[i].insert(pair<int,Word>(bi, w));
                }
            }
        }

        // result
        vector<string> res;
        recons(res, s.size(), string());
        return res;
    }
};

int main() {
	Solution sn;
	unordered_set<string> ws;
	string strs[] = {"cat", "cats", "and", "sand", "dog"};
	ws.insert(strs, strs + 5);
	string w("catsanddog");
	vector<string> res = sn.wordBreak(w, ws);

	struct printfunc {
		void operator()(string& s) { cout << s << endl; }
	};
	for_each(res.begin(), res.end(), printfunc());

	return 0;
}
