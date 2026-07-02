#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    int carry = 0;
    
    while (l1 || l2) {
        int total = carry;
        if (l1) {
            total += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            total += l2->val;
            l2 = l2->next;
        }

        carry = total / 10;
        total %= 10;

        current->next = new ListNode(total);
        current = current->next;
    }
    // xử lý carry nếu còn sót
    if (carry) {
        current->next = new ListNode(carry);
    }

    return dummy.next;
}

int main() {

}