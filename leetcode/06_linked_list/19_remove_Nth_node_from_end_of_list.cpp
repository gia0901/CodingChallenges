#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// Dùng dummy
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* temp = head;
    int totalNodes = 0;
    while (temp) {
        temp = temp->next;
        totalNodes++;
    }

    int steps = totalNodes - n;
    ListNode* prev = &dummy;
    ListNode* cur = head;
    while (steps--) {
        prev = cur;
        cur = cur->next;
    }

    // xóa node, vì ta dùng dummy, nếu có xóa head thì prev vẫn là node bình thường
    prev->next = cur->next;
    delete cur;

    return dummy.next;
}

// Không dummy
ListNode* NoDummyremoveNthFromEnd(ListNode* head, int n) {
    ListNode* temp = head;
    int totalNodes = 0;
    while (temp) {
        temp = temp->next;
        totalNodes++;
    }

    // di chuyển tới node sắp xóa
    int steps = totalNodes - n;
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while (steps--) {
        prev = cur;
        cur = cur->next;
    }

    if (prev) // xóa node ở giữa 
        prev->next = cur->next;
    else // xóa node head
        head = cur->next;

    delete cur;

    return head;
}