# 10. Heap / Priority Queue ★★☆☆☆

Khi cần **liên tục lấy phần tử lớn/nhỏ nhất**: Top-K, k-way merge, running median.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Top-K bằng min-heap kích thước k
```cpp
priority_queue<int, vector<int>, greater<int>> pq; // min-heap
for (int x : a) {
    pq.push(x);
    if ((int)pq.size() > k) pq.pop();  // loại phần tử nhỏ nhất
}
// pq chứa k phần tử lớn nhất; pq.top() = phần tử lớn thứ k
```

Vì sao giữ **min-heap size k** để tìm k **lớn** nhất: đỉnh là phần tử nhỏ nhất trong nhóm
k ứng viên → gặp số lớn hơn thì đẩy đỉnh ra. Cuối cùng còn đúng k số lớn nhất.

```
 k=3, dòng a = 5 1 8 3 9 ...
 push 5,1,8   -> [1,5,8]           (min-heap, top=1)
 push 3 >top1 -> [3,5,8] (pop 1)
 push 9 >top3 -> [5,8,9] (pop 3)   top=5 = lớn thứ 3
```

### Pattern B — K-way merge
```cpp
// pq chứa (giá trị, nguồn); luôn lấy nhỏ nhất rồi nạp phần tử kế của nguồn đó
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
```

### Pattern C — Two heaps (running median)
```cpp
priority_queue<int> lo;                                   // max-heap: nửa nhỏ
priority_queue<int, vector<int>, greater<int>> hi;        // min-heap: nửa lớn
// giữ |lo| - |hi| ∈ {0,1}; median = lo.top() hoặc trung bình 2 đỉnh
```

Hai heap "quay lưng" vào nhau, median nằm ngay ranh giới:

```
   nửa nhỏ (max-heap)   |   nửa lớn (min-heap)
   ... 1  2  [3]        |        [4]  5  6 ...
              ^top lo             ^top hi
   median = trung bình 2 đỉnh (nếu cân) / đỉnh heap lớn hơn
```

## Bài cốt lõi (3 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Kth Largest Element in an Array | A | Time O(n log k) |
| 2 | K Closest Points to Origin | A (max-heap size k) | Time O(n log k) |
| 3 | Merge k Sorted Lists | B | Time O(N log k) |

### 1. Kth Largest Element
> Min-heap giữ k phần tử lớn nhất; đỉnh là đáp án. (Hoặc quickselect O(n) trung bình.)

### 2. K Closest Points to Origin
> Max-heap kích thước k theo khoảng cách bình phương; đẩy ra điểm xa nhất khi vượt k.
- Bẫy: dùng **khoảng cách bình phương**, khỏi `sqrt` (tránh sai số + tốn kém).

### 3. Merge k Sorted Lists
> Min-heap chứa đầu mỗi list; pop nhỏ nhất, đẩy node kế của nó vào heap.

## Bài luyện thêm (interview hay gặp)

| Bài | Pattern / ý tưởng | Complexity |
|-----|-------------------|------------|
| Top K Frequent Elements | đếm tần suất + heap size k (hoặc bucket sort) | O(n log k) |
| Find Median from Data Stream | two heaps (Pattern C) | O(log n)/add |
| Last Stone Weight | max-heap, lấy 2 lớn nhất đập nhau | O(n log n) |
| Kth Largest Element in a Stream | min-heap size k, `top()` là đáp | O(log k)/add |
| Task Scheduler | đếm tần suất + greedy (heap / công thức) | O(n) |

- **Top K Frequent**: đếm bằng `unordered_map` rồi heap size k. Cùng bài với topic [Hashing](02_hashing.md); bucket sort cho O(n) nếu muốn tối ưu.
- **Find Median from Data Stream**: max-heap giữ nửa nhỏ, min-heap giữ nửa lớn, cân bằng kích thước lệch ≤ 1 (Pattern C ở trên). Median lấy từ đỉnh.
- **Last Stone Weight**: max-heap; mỗi bước pop 2 viên lớn nhất, đập, đẩy phần dư vào lại — mô phỏng thuần.
- **Kth Largest in a Stream**: giữ min-heap đúng `k` phần tử; `add(x)` push rồi pop nếu quá k → `top()` luôn là phần tử lớn thứ k.
- **Task Scheduler**: xếp task cách nhau `n` khe; greedy chọn task còn nhiều nhất trước (max-heap theo tần suất), hoặc công thức từ task tần suất cao nhất.

## Pitfall C++ hay gặp

- **Mặc định `priority_queue` là max-heap**; muốn min-heap dùng `greater<>`.
- **Custom comparator** cho struct/tuple: nhớ chiều so sánh (comparator trả `true` nghĩa là "xuống dưới").
- Top-K: heap kích thước **k** cho O(n log k), tốt hơn sort O(n log n) khi k nhỏ.
- Không có **decrease-key** tiện lợi; nếu cần (vd Dijkstra) thì push bản mới và bỏ qua bản cũ.

## Liên hệ

- Quickselect (thay heap cho Kth Largest) dựa trên partition của [Binary Search/Sorting](04_binary_search.md).
