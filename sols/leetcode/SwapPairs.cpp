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
    ListNode *swapPairs(ListNode *head) {
        ListNode *newHead = head, *cur = head;
        ListNode *prev = head;
        while (cur && cur->next) {
            ListNode *first = cur;
            ListNode *second = cur->next;
            if (newHead == head)
                newHead = second;

            prev->next = second;
            first->next = second->next;
            second->next = first;
            cur = first->next;
            prev = first;
        }
        return newHead;
    }
};
