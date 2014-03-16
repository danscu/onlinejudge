/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 #include <cmath>

class Solution {
public:
    int visit(TreeNode *root, int depth) {
        if (!root)
            return depth;

        int left = visit(root->left, depth + 1);
        int right = visit(root->right, depth + 1);

        if (left == -1 || right == -1)
            return -1;

        if (abs(left - right) >= 2)
            return -1;

        return left > right ? left : right;
    }

    bool isBalanced(TreeNode *root) {
        if (root == 0)
            return true;
        return -1 != visit(root, 1);
    }
};
