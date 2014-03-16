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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > res;
        if (!root) return res;

        list<pair<int,TreeNode*> > open;
        open.push_back(make_pair(0,root));

        while (open.size()) {
            pair<int,TreeNode*> node = open.front(); open.pop_front();
            res[node.first].push_back(node.second->val);
            if (node.second->left)
                open.push_back(make_pair(node.first+1, node.second->left));
            if (node.second->right)
                open.push_back(make_pair(node.first+1, node.second->right));
        }

        return res;
    }
};
