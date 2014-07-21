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
    void reorderList(ListNode *head) {
        int c, i;
        ListNode *cur, *prev;
        ListNode *next, *cur2;
        for (cur = head, c = 0; cur; cur = cur->next)
            c++;
        for (cur = head, prev = 0, i = 0; i < (c+1)/2; prev = cur, cur = cur->next)
            i++;
        if (!prev)
            return; // empty or single item

        // reverse second half list
        prev->next = 0; // terminuate first half
        for (prev = 0; cur; prev = cur, cur = next) {
            next = cur->next;
            cur->next = prev;
        }

        // prev points to second half now
        for (cur = head, cur2 = prev; cur;)  {
            ListNode *curnext = cur->next;
            ListNode *cur2next = cur2 ? cur2->next : 0;
            cur->next = cur2;
            if (cur2) {
                cur2->next = curnext;
                cur2 = cur2next;
            }
            cur = curnext;
        }
    }
};
