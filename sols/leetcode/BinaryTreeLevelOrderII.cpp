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
    void searchDFS(vector<vector<int> > &res, TreeNode *root, int depth) {
        if (root == NULL)
            return;

        if (depth >= res.size())
            res.resize(depth + 1);

        res[depth].push_back(root->val);

        searchDFS(res, root->left, depth + 1);
        searchDFS(res, root->right, depth + 1);
    }

    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > result;
        searchDFS(result, root, 0);
        reverse(result.begin(), result.end());
        return result;
    }
};
