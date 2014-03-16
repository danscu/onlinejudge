class Solution {
public:
    int stoi(string &s) {
        istringstream is(s);
        int r;
        is >> r;
        return r;
    }

    string itos(int i) {
        ostringstream os;
        os << i;
        return os.str();
    }

    int evalRPN(vector<string> &tokens) {
        stack<string> s;

        for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
            string &tok(*it);
            if (isdigit(tok[0]) || (tok[0] == '-' && tok.length() > 1))
                s.push(tok);
            else {
                string op2 = s.top(); s.pop();
                string op1 = s.top(); s.pop();
                int op2n = stoi(op2);
                int op1n = stoi(op1);
                char op = tok[0];
                int res;

                switch (op) {
                    case '+':
                        res = op1n + op2n;
                        break;
                    case '-':
                        res = op1n - op2n;
                        break;
                    case '*':
                        res = op1n * op2n;
                        break;
                    case '/':
                        res = op1n / op2n;
                        break;
                }

                s.push(itos(res));
            }
        }

        return stoi(s.top());
    }
};
