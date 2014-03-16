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
    private void visit(ArrayList<ArrayList<Integer>> res, ArrayList<Integer> path, TreeNode root, int sum) {
        if (root == null)
            return;
            
        path.add(root.val);
        if (root.left == null && root.right == null) {
            if (sum == root.val) {
                res.add(new ArrayList<Integer>(path));
            }
            path.remove(path.size()-1);
            return;
        }
        
        visit(res, path, root.left, sum - root.val);
        visit(res, path, root.right, sum - root.val);
        
        path.remove(path.size()-1);
    }
    
    public ArrayList<ArrayList<Integer>> pathSum(TreeNode root, int sum) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
        ArrayList<Integer> path = new ArrayList<Integer>();
        visit(result, path, root, sum);
        return result;
    }
}
