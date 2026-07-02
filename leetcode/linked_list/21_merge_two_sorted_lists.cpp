#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* current = &dummy;

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            current->next = new ListNode(list1->val);
            list1 = list1->next;
        }
        else {
            current->next = new ListNode(list2->val);
            list2 = list2->next;
        }
        current = current->next;
    }
    if (list1)
        current->next = list1;
    if (list2)
        current->next = list2;

    return dummy.next;
}

int main() {
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode* res = mergeTwoLists(list1, list2);
    while (res) {
        cout << res->val << "->";
    }
    cout << endl;
}