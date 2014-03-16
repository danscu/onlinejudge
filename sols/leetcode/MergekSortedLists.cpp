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
    ListNode *mergeKLists(vector<ListNode *> &plists) {
        ListNode *head = NULL;
        ListNode *tail = NULL;

        bool done = false;
        int i;
        int bestI;
        do {
            bestI = -1;
            for (i = 0; i < plists.size(); i++)
                if (plists[i] && (bestI < 0 || plists[i]->val < plists[bestI]->val))
                    bestI = i;
            if (bestI >= 0) {
                if (!head) {
                    head = plists[bestI];
                    tail = head;
                } else {
                    tail->next = plists[bestI];
                    tail = tail->next;
                }
                plists[bestI] = plists[bestI]->next;
            }
        } while (bestI >= 0);
        if (tail) tail->next = NULL;
        return head;
    }
};
