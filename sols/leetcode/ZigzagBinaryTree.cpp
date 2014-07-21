/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void addRes(vector<vector<int> > &res, vector<int> data, int level) {
        if (level%2)
            reverse(data.begin(), data.end());
        res.push_back(data);
    }

    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > res;
        vector<int> line;
        queue<pair<int,TreeNode*> > que;
        int lastLine = -1;
        if (!root) return res;
        // even levels: left to right
        que.push(make_pair(0,root));
        while (!que.empty()) {
            pair<int,TreeNode*> cur = que.front();
            que.pop();
            if (cur.first != lastLine) {
                if (lastLine != -1) addRes(res, line, lastLine);
                lastLine = cur.first;
                line.clear();
            }
            line.push_back(cur.second->val);
            if (cur.second->left) que.push(make_pair(cur.first+1, cur.second->left));
            if (cur.second->right) que.push(make_pair(cur.first+1, cur.second->right));
        }
        if (!line.empty())
            addRes(res, line, lastLine);
        return res;
    }
};
