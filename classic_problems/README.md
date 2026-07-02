# Classic Problems — Lộ trình ôn tập DSA

Đây là **index tổng**: bản đồ các topic kinh điển của DSA cho coding interview, **xếp theo tần suất gặp trong phỏng vấn (cao → thấp)**.

## Cách dùng tài liệu này

- Mỗi topic có 1 folder + `README.md` riêng: liệt kê **core problems**, **pattern/ý tưởng** (mức pseudocode), **complexity mục tiêu**, và **pitfall C++**.
- **Không có code lời giải C++ hoàn chỉnh** — bạn tự viết file `.cpp`, tôi review theo quy trình trong [CLAUDE.md](../CLAUDE.md).
- Danh sách đã **tinh gọn**: chỉ giữ dạng phổ biến hay gặp, tránh bài lạ / quá khó / cần kiến thức hiếm.

## Lộ trình (tần suất cao → thấp)

| # | Topic | Folder | Bài cốt lõi | Tần suất | Ghi chú |
|---|-------|--------|:-----------:|:--------:|---------|
| 1 | Array & Two Pointers | `01_array/` | 5 | ★★★★★ | Nền tảng; index, in-place, sliding window. |
| 2 | Hashing | `02_hashing/` | 4 | ★★★★★ | Đổi space lấy time; xương sống nhiều bài array/string. |
| 3 | String | `03_string/` | 5 | ★★★★★ | Sliding window, anagram, palindrome. |
| 4 | Binary Search (+ Sorting) | `04_binary_search/` | 5 | ★★★★☆ | Search trên answer space; sorting là prerequisite. |
| 5 | Tree & BST | `05_tree/` | 6 | ★★★★☆ | DFS/BFS traversal, tính chất BST, LCA. |
| 6 | Linked List | `06_linked_list/` | 5 | ★★★★☆ | Dummy node, fast/slow, reverse. |
| 7 | Stack & Queue | `07_stack_queue/` | 4 | ★★★☆☆ | Monotonic stack, next greater element. |
| 8 | Graph | `08_graph/` | 6 | ★★★☆☆ | BFS/DFS, topological sort, union-find. |
| 9 | Dynamic Programming | `09_dp/` | 7 | ★★★☆☆ | 1D/2D DP, knapsack, LIS, LCS. |
| 10 | Heap / Priority Queue | `10_heap/` | 3 | ★★☆☆☆ | Top-K, k-way merge, running median. |
| 11 | Backtracking | `11_backtracking/` | 4 | ★★☆☆☆ | Sinh tổ hợp/hoán vị, pruning. |
| 12 | Greedy | `12_greedy/` | 3 | ★★☆☆☆ | Interval scheduling, đổi tiền. |
| 13 | Math & Bit Manipulation | `13_math_bit/` | 3 | ★☆☆☆☆ | GCD, bitmask, xử lý overflow. |

> Tổng ~60 bài cốt lõi. Mục tiêu là nắm **pattern**, không chạy đua số lượng.
>
> **Gợi ý ưu tiên khi ít thời gian:** làm chắc topic 1–6 (chiếm phần lớn câu hỏi phỏng vấn) trước, rồi tới 7–9. Topic 10–13 ôn sau cùng.

## Nguyên tắc học (khớp với CLAUDE.md)

1. Đọc README topic → nhận diện **pattern** trước khi code.
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
