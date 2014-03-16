class Solution {
private:
    char *path;

    void search(int k, int n, int open, vector<string> &res) {
        if (k >= n * 2) {
            if (open == 0) {
                path[k] = 0;
                res.push_back(string(path));
            }
            return;
        }

        if (open < n) {
            path[k] = '(';
            search(k + 1, n, open + 1, res);
        }

        if (open > 0) {
            path[k] = ')';
            search(k + 1, n, open - 1, res);
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        path = new char[n*2+1];
        search(0, n, 0, res);
        delete [] path;
        return res;
    }
};
