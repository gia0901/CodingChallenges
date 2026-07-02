#include <bits/stdc++.h>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        ListNode* slow = head;
        ListNode* fast = head;

        while (slow && fast) {
            slow = slow->next;
            if (!fast->next)
                return false;
            fast = fast->next->next;
            if (slow == fast) 
                return true;
        }
        return false;
    }
};

int main() {
    
}