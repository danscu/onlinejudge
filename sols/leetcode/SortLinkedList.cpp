#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        ListNode *head1 = 0, *last1 = 0;
        ListNode *head2 = 0, *last2 = 0;

        // base case (single element)
        if (!head || !head->next)
            return head;

        // split
        while (head) {
            if (!head1)
                head1 = last1 = head;
            else {
                last1->next = head;
                last1 = head;
            }

            head = head->next;
            if (!head)
                break;

            if (!head2)
                head2 = last2 = head;
            else {
                last2->next = head;
                last2 = head;
            }

            head = head->next;
       }

       last1->next = NULL;
       if (last2)
            last2->next = NULL;

       ListNode *sorted1 = sortList(head1);
       ListNode *sorted2 = sortList(head2);

       // merge
       ListNode *sorted = NULL, *lastSorted;
       while (sorted1 || sorted2) {
           ListNode *next;
           if (!sorted1 || (sorted2 && sorted2->val < sorted1->val)) {
               next = sorted2;
               sorted2 = sorted2->next;
           } else {
               next = sorted1;
               sorted1 = sorted1->next;
           }

           if (!sorted) {
                sorted = lastSorted = next;
           } else {
               lastSorted->next = next;
               lastSorted = next;
           }
       }

       lastSorted->next = NULL;

       return sorted;
    }
};

int main() {
	int i, n = 10;

	ListNode *head = NULL, *last;

	for (i = 0; i < n; i++) {
		int num;
		ListNode *el = new ListNode(num = rand() % 100);
		cout << num << " ";

		if (!head) {
			head = last = el;
		} else {
			last->next = el;
			last = el;
		}
	}

	cout << endl;

	Solution sn;
	ListNode *sorted = sn.sortList(head);

	while (sorted) {
		cout << sorted->val << " ";
		sorted = sorted->next;
	}

	cout << endl;
}
