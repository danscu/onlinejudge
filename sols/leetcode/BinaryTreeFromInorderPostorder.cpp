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
    TreeNode *build(vector<int> &inorder, int ifrom, int ito, vector<int> &postorder, int pfrom, int pto) {
        // base case (empty tree)
        if (ito - ifrom == 0)
            return NULL;

        int rootVal = postorder[pto-1];
        vector<int>::iterator it = find(inorder.begin() + ifrom, inorder.begin() + ito, rootVal);

        TreeNode *node = new TreeNode(rootVal);

        int leftSize = it - inorder.begin() - ifrom;
        node->left = build(inorder, ifrom, ifrom + leftSize, postorder, pfrom, pfrom + leftSize);

        int rightSize = (ito - ifrom) - 1 - leftSize;
        node->right = build(inorder, ifrom + 1 + leftSize, ito, postorder, pfrom + leftSize, pto - 1);

        return node;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.empty())
            return 0;
        return build(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
};
