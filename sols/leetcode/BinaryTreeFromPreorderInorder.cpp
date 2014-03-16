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
    TreeNode *build(vector<int> &inorder, int ifrom, int ito, vector<int> &preorder, int pfrom, int pto) {
        // base case (empty tree)
        if (ito - ifrom == 0)
            return NULL;

        int rootVal = preorder[pfrom];
        vector<int>::iterator it = find(inorder.begin() + ifrom, inorder.begin() + ito, rootVal);

        TreeNode *node = new TreeNode(rootVal);

        int leftSize = it - inorder.begin() - ifrom;
        node->left = build(inorder, ifrom, ifrom + leftSize, preorder, pfrom + 1, pfrom + 1 + leftSize);

        int rightSize = (ito - ifrom) - 1 - leftSize;
        node->right = build(inorder, ifrom + 1 + leftSize, ito, preorder, pfrom + 1 + leftSize, pto);

        return node;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (inorder.empty())
            return 0;
        return build(inorder, 0, inorder.size(), preorder, 0, preorder.size());
    }
};
