class Solution {
public:
    ListNode *newDigitNode(int &carry, int num1, int num2, ListNode* &list, ListNode* &prev) {
        int digitSum = num1 + num2 + carry;
        ListNode *newNode = new ListNode(digitSum % 10);
        carry = digitSum / 10;
        if (prev) {
            prev->next = newNode;
        } else
            list = newNode;
        prev = newNode;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *res = 0, *prev = 0;
        int carry = 0;
        while (l1 && l2) {
            newDigitNode(carry, l1->val, l2->val, res, prev);
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1) {
            newDigitNode(carry, l1->val, 0, res, prev);
            l1 = l1->next;
        }

        while (l2) {
            newDigitNode(carry, l2->val, 0, res, prev);
            l2 = l2->next;
        }

        if (carry)
            newDigitNode(carry, 0, 0, res, prev);

        prev->next = 0;

        return res;
    }
};
