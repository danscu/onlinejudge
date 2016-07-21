/*
 * merge_two_sorted.cpp
 *
 *  Created on: Jul 20, 2016
 *      Author: danke
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* res = NULL;
        ListNode* cur = NULL;

        while (l1 || l2) {
            ListNode* next;
            if (l1 != NULL && (!l2 || l1->val < l2->val)) {
                next = l1; l1 = l1->next;
            } else {
                next = l2; l2 = l2->next;
            }

            if (res == NULL)
                res = cur = next;
            else {
                cur->next = next;
                cur = next;
            }
        }

        if (cur) cur->next = NULL;
        return res;
    }
};

int main() {
    Solution sn;
    ListNode *l2 = NULL, *l1 = new ListNode(1);
    ListNode *res = sn.mergeTwoLists(l1, l2);
    while (res) {
        std::cout << res->val << std::endl;
        res = res->next;
    }
    return 0;
}
