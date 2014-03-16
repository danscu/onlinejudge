class Solution {
public:
    bool isValid(string s) {
        int pc = 0, bc = 0, cc = 0;
        stack<char> t;
        for (string::iterator it = s.begin(); it != s.end(); ++it) {
            switch (*it) {
                case '{':
                case '[':
                case '(':
                    t.push(*it);
                    break;
                case '}':
                    if (t.empty() || t.top() != '{')
                        return false;
                    t.pop();
                    break;
                case ']':
                    if (t.empty() || t.top() != '[')
                        return false;
                    t.pop();
                    break;
                case ')':
                    if (t.empty() || t.top() != '(')
                        return false;
                    t.pop();
                    break;
            }
        }
        return t.empty();
    }
};
