# 6. Linked List ★★★★☆

Ba kỹ thuật gỡ được hầu hết bài: **dummy head**, **fast/slow**, **reverse in-place**.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Dummy head (đơn giản hóa chèn/xóa đầu)
```cpp
ListNode dummy(0);
ListNode* tail = &dummy;
while (/* còn phần tử */) {
    tail->next = node;
    tail = tail->next;
}
return dummy.next;
```

### Pattern B — Fast/slow (middle, cycle)
```cpp
ListNode* slow = head; ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    // if (slow == fast) -> có cycle
}
// slow = node giữa
```

### Pattern C — Reverse in-place
```cpp
ListNode* prev = nullptr;
ListNode* cur = head;
while (cur) {
    ListNode* nxt = cur->next; // lưu trước khi ghi đè
    cur->next = prev;
    prev = cur;
    cur = nxt;
}
return prev; // head mới
```

## Bài cốt lõi (5 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Reverse Linked List | C | Time O(n), Space O(1) |
| 2 | Merge Two Sorted Lists | A | Time O(n+m), Space O(1) |
| 3 | Linked List Cycle | B | Time O(n), Space O(1) |
| 4 | Middle of the Linked List | B | Time O(n), Space O(1) |
| 5 | Remove Nth Node From End | A + B | Time O(n), Space O(1) |

### 1. Reverse Linked List
> Đảo chiều toàn bộ list. Pattern C — nắm chắc, tái dùng ở nhiều bài.

### 2. Merge Two Sorted Lists
> Trộn hai list sort thành một. Pattern A + so đầu hai list.
- Đã có bản của bạn: [leetcode/linked_list/21_merge_two_sorted_lists.cpp](../../leetcode/linked_list/21_merge_two_sorted_lists.cpp) — ôn lại.

### 3. Linked List Cycle
> Phát hiện chu trình. Fast/slow gặp nhau → có cycle (Floyd).
- Đã có: [leetcode/linked_list/141_linked_list_cycle.cpp](../../leetcode/linked_list/141_linked_list_cycle.cpp).

### 4. Middle of the Linked List
> Fast đi 2 bước, slow đi 1 → khi fast hết, slow ở giữa.
- Bẫy chẵn/lẻ: điều kiện `fast && fast->next` quyết định trả node giữa nào.

### 5. Remove Nth Node From End
> Hai con trỏ cách nhau `n` bước; khi con trước ra khỏi list, con sau ở ngay trước node cần xóa. Dùng dummy để xử lý xóa head.

## Pitfall C++ hay gặp

- **Null dereference**: luôn kiểm tra `node && node->next` trước khi đi tiếp.
- **Mất con trỏ khi reverse**: lưu `next` trước khi ghi đè `cur->next`.
- **Dummy node** giúp xử lý đồng nhất trường hợp thao tác trên head.
- Nếu tự cấp phát: cẩn thận **memory leak / double free** (thường phỏng vấn bỏ qua, nhưng nên biết).

## Liên hệ

- Fast/slow ở đây trùng ý tưởng với con trỏ cách nhau `k` trong [Array](../01_array/README.md).
