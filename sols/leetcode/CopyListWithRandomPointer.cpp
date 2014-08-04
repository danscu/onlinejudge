/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *ret;
        
        // duplidate the linked list
        RandomListNode *cur = head;
        RandomListNode *next1;

        if (!cur) return NULL;
        
        while (cur) {
            RandomListNode *el = new RandomListNode(cur->label);
            el->random = cur->random;
            el->next = cur->next;
            cur->next = el;
            cur = el->next;
        }
        
        // move random ptr
        cur = head;
        while (cur) {
            next1 = cur->next;
            if (next1->random) next1->random = next1->random->next;
            cur = cur->next->next;
        }
        
        // split the linked list
        cur = head;
        ret = cur->next;

        while (cur) {
            next1 = cur->next;
            RandomListNode *next2 = next1->next;
            cur->next = next1->next;
            next1->next = next2 ? next2->next : 0;
            cur = next2;
        }
        
        return ret;
    }
};
