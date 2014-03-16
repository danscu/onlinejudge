/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        int i;
        ListNode *prev;
        ListNode *front = head;
        for (i = 0; i < n && front->next; i++)
            front=front->next;
        if (i < n) {
            if (!front->next)
                head = head->next;
            return head; // didn't deleted
        }
        prev = head;
        while (front->next) {
            front = front->next;
            prev = prev->next;
        }
        ListNode *rem = prev->next;
        prev->next = rem->next;
        // delete rem;
        return head;
    }
};
