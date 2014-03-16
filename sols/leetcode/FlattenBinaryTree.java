/**
 * Definition for binary tree
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    private TreeNode list;
    
    // returns the last node in the list
    private TreeNode visit(TreeNode root) {
        if (root == null)
            return null;
        
        TreeNode left = root.left;
        TreeNode right = root.right;
        
        // base case
        if (left == null && right == null)
            return root;
        
        TreeNode listTail = root;
        
        if (left != null) {
            listTail.right = root.left;
            listTail = visit(root.left);
        }

        if (right != null) {
            listTail.right = right;
            listTail = visit(root.right);
        }

        root.left = null;

        return listTail;
    }
    
    public void flatten(TreeNode root) {
        visit(root);
    }
}