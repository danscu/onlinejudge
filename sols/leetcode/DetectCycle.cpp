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
    ListNode *detectCycle(ListNode *head) {
        set<ListNode *> old;
        ListNode *cur = head;
        while (cur) {
            if (old.find(cur) != old.end())
                return cur;
            old.insert(cur);
            cur = cur->next;
       }
       return NULL;
    }
};
