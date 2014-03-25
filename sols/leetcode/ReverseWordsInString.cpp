class Solution {
public:
    void reverseWords(string &s) {
        istringstream is(s);
        vector<string> buf;
        string t;
        while (is >> t)
            buf.push_back(t);
        ostringstream os;
        for (vector<string>::reverse_iterator it = buf.rbegin(); it!=buf.rend(); ++it) {
            if (it != buf.rbegin()) os << " ";
            os << *it;
        }
        s = os.str();
    }
};
