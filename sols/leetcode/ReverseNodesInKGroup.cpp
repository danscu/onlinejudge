#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x=0) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (k <= 1 || !head || !head->next)
            return head;
        ListNode *ret = NULL, *last = NULL;
        vector<ListNode*> buf;
        buf.reserve(k);
        int c = 0;
        ListNode *cur = head;
        while (cur) {
        	ListNode *next = cur->next;
            buf.push_back(cur);
            if (++c == k) {
                vector<ListNode*>::reverse_iterator it = buf.rbegin();
                if (last)
                    last->next = *it;
                if (!ret)
                    ret = *it;
                last = *it;
                ++it;
                while (it != buf.rend()) {
                    last->next = *it;
                    last = last->next;
                    ++it;
                }
                buf.clear();
                c = 0;
            }
            cur = next;
        }
        for (vector<ListNode*>::iterator it = buf.begin(); it!=buf.end(); ++it) {
            if (last)
            	last->next = *it;
            if (!ret)
            	ret = *it;
            last = *it;
        }
        last->next = NULL;
        return ret;
    }
};

int main()
{
	ListNode nodes[5];
	int i;
	for (i = 0; i < 2; i++) {
		nodes[i].val = i + 1;
		nodes[i].next = &nodes[i + 1];
	}

	nodes[i - 1].next = 0;

	Solution sn;
	ListNode *head = sn.reverseKGroup(&nodes[0], 3);

	while (head) {
		cout << head->val << " ";
		head = head->next;
	}

	return 0;
}
