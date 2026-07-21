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

Dummy giúp head được xử lý y hệt mọi node khác (không cần `if (head == null)` riêng):

```
 dummy -> [ ] -> [ ] -> [ ]     tail luôn trỏ node cuối đã nối
   ^tail đầu tiên             trả về dummy.next = head thật
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

Fast đi gấp đôi → khi fast hết list, slow ở giữa:

```
 1 -> 2 -> 3 -> 4 -> 5 -> null
 S    S         S            slow: 1,2,3
 F         F         F(null) fast: 1,3,5 -> dừng, slow=3 (giữa)
```

### Pattern C — Reverse in-place
```cpp
ListNode* prev = nullptr;
ListNode* cur = head;
while (cur) {
    ListNode* nxt = cur->next; // lưu TRƯỚC khi ghi đè
    cur->next = prev;
    prev = cur;
    cur = nxt;
}
return prev; // head mới
```

Đảo từng cạnh, luôn giữ `nxt` để không mất phần còn lại:

```
 null <- 1    2 -> 3 -> null      prev=1, cur=2, nxt=3
 prev    cur  ...
 null <- 1 <- 2    3 -> null      prev=2, cur=3
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
- Đã có bản của bạn: [leetcode/linked_list/21_merge_two_sorted_lists.cpp](../leetcode/linked_list/21_merge_two_sorted_lists.cpp) — ôn lại.

### 3. Linked List Cycle
> Phát hiện chu trình. Fast/slow gặp nhau → có cycle (Floyd).
- Đã có: [leetcode/linked_list/141_linked_list_cycle.cpp](../leetcode/linked_list/141_linked_list_cycle.cpp).
- **Vì sao gặp nhau nếu có cycle**: khi cả hai đã vào vòng, mỗi bước khoảng cách fast→slow **giảm đúng 1** → chắc chắn về 0 (không thể nhảy qua). Không có cycle thì fast chạm `null` trước.

### 4. Middle of the Linked List
> Fast đi 2 bước, slow đi 1 → khi fast hết, slow ở giữa.
- Bẫy chẵn/lẻ: điều kiện `fast && fast->next` quyết định trả node giữa nào.

### 5. Remove Nth Node From End
> Hai con trỏ cách nhau `n` bước; khi con trước ra khỏi list, con sau ở ngay trước node cần xóa. Dùng dummy để xử lý xóa head.

## Bài luyện thêm (interview hay gặp)

| Bài | Pattern / ý tưởng | Complexity |
|-----|-------------------|------------|
| Add Two Numbers | duyệt song song + carry, dummy head | O(n) |
| Palindrome Linked List | tìm mid + reverse nửa sau + so | O(n), O(1) |
| Intersection of Two Linked Lists | hai con trỏ đổi làn khi hết | O(n+m), O(1) |
| Reorder List | mid + reverse nửa sau + trộn xen kẽ | O(n), O(1) |
| Copy List with Random Pointer | hash map cũ→mới (hoặc chèn xen kẽ) | O(n) |
| Merge k Sorted Lists | min-heap các đầu list | O(N log k) |

- **Add Two Numbers**: cộng từng chữ số + `carry`, dùng dummy head. Đã có: [leetcode/linked_list/2_add_two_numbers.cpp](../leetcode/linked_list/2_add_two_numbers.cpp).
- **Palindrome Linked List**: fast/slow tìm mid → reverse nửa sau → so hai nửa. Đạt O(1) space (khác cách đổ ra vector O(n)).
- **Intersection**: hai con trỏ đi, hết list này thì nhảy sang đầu list kia → sau ≤ 2 lượt chúng gặp nhau ở giao điểm (hoặc cùng `null`).
- **Reorder List**: kết hợp 3 kỹ thuật nền — tìm mid (fast/slow) + reverse nửa sau + merge xen kẽ. Bài "tổng hợp" hay gặp.
- **Copy List with Random Pointer**: `unordered_map<old,new>` để nối `random` đúng bản sao; hoặc mẹo chèn node sao xen kẽ để O(1) space.
- **Merge k Sorted Lists**: min-heap chứa đầu mỗi list, pop nhỏ nhất rồi đẩy node kế. Nối với [Heap](10_heap.md).

## Pitfall C++ hay gặp

- **Null dereference**: luôn kiểm tra `node && node->next` trước khi đi tiếp.
- **Mất con trỏ khi reverse**: lưu `next` trước khi ghi đè `cur->next`.
- **Dummy node** giúp xử lý đồng nhất trường hợp thao tác trên head.
- Nếu tự cấp phát: cẩn thận **memory leak / double free** (thường phỏng vấn bỏ qua, nhưng nên biết).

## Liên hệ

- Fast/slow ở đây trùng ý tưởng với con trỏ cách nhau `k` trong [Array](01_array.md).
