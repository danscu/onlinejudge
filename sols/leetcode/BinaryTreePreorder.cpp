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
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        list<TreeNode*> open;

        if (!root) return res;

        open.push_back(root);

        while (!open.empty()) {
            TreeNode *node = open.front(); open.pop_front();
            res.push_back(node->val);
            if (node->right)
                open.push_front(node->right);
            if (node->left)
                open.push_front(node->left);
        }

        return res;
    }
};
