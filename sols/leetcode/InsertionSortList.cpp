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
    ListNode *insertionSortList(ListNode *head) {
        if (!head) return NULL;

        ListNode *sorted = head;
        ListNode *rem = head->next, *next;

        sorted->next = NULL;

        while (rem) {
            next = rem->next;

            // insert rem into list 'head'
            if (rem->val < sorted->val) {
                // insert before head
                rem->next = sorted;
                sorted = rem;
            } else {
                ListNode *last = sorted, *cur = sorted->next;
                while (cur) {
                    if (rem->val <= cur->val) {
                        // insert before cur
                        break;
                    }
                    last = cur;
                    cur = cur->next;
                }
                rem->next = last->next;
                last->next = rem;
            }

            rem = next;
        }

        return sorted;
    }
};

