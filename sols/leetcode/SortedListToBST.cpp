/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    class Constructed {
    public:
        TreeNode *node;
        ListNode *next;
        Constructed() : Constructed(NULL, NULL) { }
        Constructed(TreeNode *node, ListNode *next) {
            this->node = node;
            this->next = next;
        }
    };

    Constructed construct(ListNode *head, int len) {
        // Base case
        if (len == 1) {
            return Constructed(new TreeNode(head->val), head->next);
        }

        int leftSize = (len - 1) / 2;
        int rightSize = len - leftSize - 1;

        Constructed left;
        if (leftSize) {
             left = construct(head, leftSize);
             head = left.next;
        }

        TreeNode *node = new TreeNode(head->val);
        head = head->next;
        if (leftSize)
            node->left = left.node;

        Constructed right;
        if (rightSize) {
            right = construct(head, rightSize);
            head = right.next;
            node->right = right.node;
        }

        return Constructed(node, head);
    }

    TreeNode *sortedListToBST(ListNode *head) {
        if (head == NULL)
            return NULL;

        int len = 0;
        ListNode *cur = head;
        while (cur) {
            len++;
            cur = cur->next;
        }

        // convert
        return construct(head, len).node;
    }
};
