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
    TreeNode *construct(vector<int> &num, int index, int n) {
        // base case
        if (n == 1)
            return new TreeNode(num[index]);
        
        int leftNum = (n - 1) / 2;
        int rightNum = n - 1 - leftNum;
        
        TreeNode *node = new TreeNode(num[index + leftNum]);
        if (leftNum)
            node->left = construct(num, index, leftNum);
        if (rightNum)
            node->right = construct(num, index + leftNum + 1, rightNum);
    }

    TreeNode *sortedArrayToBST(vector<int> &num) {
        if (num.empty())
            return 0;
        return construct(num, 0, num.size());
    }
};