# Classic Problems — Lộ trình ôn tập DSA

Đây là **index tổng**: bản đồ các topic kinh điển của DSA cho coding interview, **xếp theo tần suất gặp trong phỏng vấn (cao → thấp)**.

> 🎯 Sắp thi coding challenge (Codility/Coderbyte)? Xem [challenge_playbook.md](challenge_playbook.md) — quy trình 90 phút, checklist edge case, reflex overflow, cơ chế nền tảng.

## Cách dùng tài liệu này

- Mỗi topic là **1 file `.md` riêng** (vd `01_array.md`): liệt kê **core problems**, **pattern/ý tưởng** (kèm skeleton C++ + ASCII minh họa + phần "vì sao đúng"), **complexity mục tiêu**, và **pitfall C++**.
- **Không có code lời giải C++ hoàn chỉnh** — bạn tự viết file `.cpp` trong [leetcode/](../leetcode/), tôi review theo quy trình trong [CLAUDE.md](../CLAUDE.md).
- Danh sách đã **tinh gọn**: chỉ giữ dạng phổ biến hay gặp, tránh bài lạ / quá khó / cần kiến thức hiếm.

## Lộ trình (tần suất cao → thấp)

| # | Topic | File | Bài cốt lõi | Tần suất | Ghi chú |
|---|-------|------|:-----------:|:--------:|---------|
| 1 | Array & Two Pointers | [01_array.md](01_array.md) | 5 | ★★★★★ | Nền tảng; index, in-place, sliding window. |
| 2 | Hashing | [02_hashing.md](02_hashing.md) | 4 | ★★★★★ | Đổi space lấy time; xương sống nhiều bài array/string. |
| 3 | String | [03_string.md](03_string.md) | 5 | ★★★★★ | Sliding window, anagram, palindrome. |
| 4 | Binary Search (+ Sorting) | [04_binary_search.md](04_binary_search.md) | 5 | ★★★★☆ | Search trên answer space; sorting là prerequisite. |
| 5 | Tree & BST | [05_tree.md](05_tree.md) | 6 | ★★★★☆ | DFS/BFS traversal, tính chất BST, LCA. |
| 6 | Linked List | [06_linked_list.md](06_linked_list.md) | 5 | ★★★★☆ | Dummy node, fast/slow, reverse. |
| 7 | Stack & Queue | [07_stack_queue.md](07_stack_queue.md) | 4 | ★★★☆☆ | Monotonic stack, next greater element. |
| 8 | Graph | [08_graph.md](08_graph.md) | 6 | ★★★☆☆ | BFS/DFS, topological sort, union-find. |
| 9 | Dynamic Programming | [09_dp.md](09_dp.md) | 7 | ★★★☆☆ | 1D/2D DP, knapsack, LIS, LCS. |
| 10 | Heap / Priority Queue | [10_heap.md](10_heap.md) | 3 | ★★☆☆☆ | Top-K, k-way merge, running median. |
| 11 | Backtracking | [11_backtracking.md](11_backtracking.md) | 4 | ★★☆☆☆ | Sinh tổ hợp/hoán vị, pruning. |
| 12 | Greedy | [12_greedy.md](12_greedy.md) | 3 | ★★☆☆☆ | Interval scheduling, đổi tiền. |
| 13 | Math & Bit Manipulation | [13_math_bit.md](13_math_bit.md) | 3 | ★☆☆☆☆ | GCD, bitmask, xử lý overflow. |

> Tổng ~60 bài cốt lõi. Mục tiêu là nắm **pattern**, không chạy đua số lượng.
>
> **Gợi ý ưu tiên khi ít thời gian:** làm chắc topic 1–6 (chiếm phần lớn câu hỏi phỏng vấn) trước, rồi tới 7–9. Topic 10–13 ôn sau cùng.

## Nguyên tắc học (khớp với CLAUDE.md)

1. Đọc file topic (vd `01_array.md`) → nhận diện **pattern** trước khi code.
2. Tự viết `.cpp`, tự test edge case.
3. Yêu cầu tôi review: (1) tính đúng đắn → (2) cải thiện → (3) phân tích tư duy & trade-off.
4. Ghi lại complexity đạt được, so với complexity mục tiêu trong README.

## Trạng thái

- [ ] 1. Array & Two Pointers
- [ ] 2. Hashing
- [ ] 3. String
- [ ] 4. Binary Search (+ Sorting)
- [ ] 5. Tree & BST
- [ ] 6. Linked List
- [ ] 7. Stack & Queue
- [ ] 8. Graph
- [ ] 9. Dynamic Programming
- [ ] 10. Heap / Priority Queue
- [ ] 11. Backtracking
- [ ] 12. Greedy
- [ ] 13. Math & Bit Manipulation
