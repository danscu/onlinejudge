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
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        list<TreeNode*> open;

        if (!root) return res;

        open.push_back(root);

        while (!open.empty()) {
            TreeNode *node = open.front(); open.pop_front();
            res.push_back(node->val);
            if (node->left)
                open.push_front(node->left);
            if (node->right)
                open.push_front(node->right);
        }

        reverse(res.begin(), res.end());

        return res;
    }
};
