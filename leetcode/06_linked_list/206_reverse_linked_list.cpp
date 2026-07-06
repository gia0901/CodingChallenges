#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;

    while (cur) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur; // prev làm điểm kết nối giữa node hiện tại và node cur tương lai
        cur = next; // cur dịch lên next để chuẩn bị nối cho lần lặp tiếp
    }

    return prev;
}