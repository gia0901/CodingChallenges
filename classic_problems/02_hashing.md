# 2. Hashing ★★★★★

Đổi space lấy time — xương sống của rất nhiều bài array/string. 3 pattern chính: đếm tần suất, kiểm tra tồn tại, gom nhóm theo key.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Complement lookup (tìm phần bù)
```cpp
unordered_map<int,int> seen; // value -> index
for (int i = 0; i < n; ++i) {
    int need = target - a[i];
    auto it = seen.find(need);
    if (it != seen.end()) { /* found (it->second, i) */ }
    seen[a[i]] = i; // insert SAU khi tra để không dùng lại chính nó
}
```

### Pattern B — Set kiểm tra tồn tại / khử trùng lặp
```cpp
unordered_set<int> s;
for (int x : a) {
    if (!s.insert(x).second) { /* x đã tồn tại */ }
}
```

### Pattern C — Gom nhóm theo canonical key
```cpp
unordered_map<string, vector<string>> groups;
for (auto& w : words) {
    string key = canonical(w); // vd chữ ký tần suất 26 ký tự
    groups[key].push_back(w);
}
```

Ý tưởng canonical key — mọi anagram quy về **cùng một dạng chuẩn**:

```
"eat"  --count-->  a1 e1 t1  --key-->  "#1#0..#1..#1.."  ┐
"tea"  --count-->  a1 e1 t1  --key-->  "#1#0..#1..#1.."  ├─> cùng key -> 1 nhóm
"ate"  --count-->  a1 e1 t1  --key-->  "#1#0..#1..#1.."  ┘
"tan"  --count-->  a1 n1 t1  --key-->  "#1#..#1..#1.."   -> key khác -> nhóm khác
```

## Bài cốt lõi (4 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Two Sum (unsorted) | A | Time O(n), Space O(n) |
| 2 | Contains Duplicate | B | Time O(n), Space O(n) |
| 3 | Group Anagrams | C | Time O(n·k), Space O(n·k) |
| 4 | Longest Consecutive Sequence | B | Time O(n), Space O(n) |

### 1. Two Sum (unsorted)
> Mảng **chưa sort**, trả về index của hai phần tử cộng bằng `target`.

- Pattern A. Bẫy: kiểm tra complement **trước** khi insert phần tử hiện tại.
- So sánh: bản sorted (Two Sum II) dùng two pointers O(1) space; bản này chưa sort nên hash cho O(n) time.

### 2. Contains Duplicate
> Có phần tử nào xuất hiện ≥ 2 lần không?

- Pattern B. `insert().second == false` nghĩa là đã tồn tại. Hoặc so sánh `set.size()` với `a.size()`.
- Trade-off thực tế: `sort + quét` (O(n log n), O(1) space, cache-friendly) đôi khi **chạy nhanh hơn** `unordered_set` (O(n) nhưng hashing + pointer-chasing tốn cache). Big-O không phải tất cả.

### 3. Group Anagrams
> Gom các từ là anagram của nhau vào cùng nhóm.

- Pattern C. Key = **chữ ký tần suất** (`array<int,26>` encode thành string) → O(k); nhanh hơn `sort(word)` là O(k log k).
- Bẫy khi ghép key từ count: chèn **dấu phân cách** (`#`) để `[1,1]` và `[11]` không cho cùng chuỗi.

### 4. Longest Consecutive Sequence
> Độ dài chuỗi số liên tiếp dài nhất (không cần liền kề trong mảng). Yêu cầu O(n).

- Đưa hết vào `unordered_set`. Với mỗi `x` mà `x-1` **không** có trong set (điểm bắt đầu chuỗi), đếm `x, x+1, ...`.
- **Vì sao O(n)** (không phải O(n²) dù có vòng lặp lồng): chỉ đếm từ điểm start, và các chuỗi rời nhau phân hoạch cả set → tổng số bước của mọi vòng đếm cộng lại = n. Cộng vòng `for` ngoài = n → 2n = O(n).

```
set = {1,2,3, 100,101}          x-1 có trong set? -> KHÔNG đếm (không phải start)
 1  -> 0 không có  => START, đếm 1,2,3         (len 3)
 2  -> 1 có        => bỏ qua
 3  -> 2 có        => bỏ qua
100 -> 99 không có => START, đếm 100,101       (len 2)
101 -> 100 có      => bỏ qua
mỗi số bị "đếm" đúng 1 lần across tất cả các start.
```

## Bài luyện thêm (interview hay gặp)

| Bài | Pattern / ý tưởng | Complexity |
|-----|-------------------|------------|
| Top K Frequent Elements | đếm tần suất + bucket sort (hoặc heap) | O(n) |
| Subarray Sum Equals K | prefix sum + hash map đếm | O(n), O(n) |
| Valid Sudoku | hash set cho hàng/cột/ô 3×3 | O(1) (81 ô) |
| First Unique Character | đếm tần suất, lấy vị trí đầu có count 1 | O(n) |
| LRU Cache | hash map + doubly linked list | O(1)/op |

- **Top K Frequent**: `unordered_map` đếm tần suất, rồi **bucket sort** theo tần suất (index = số lần xuất hiện, ≤ n) → O(n), nhanh hơn heap O(n log k). Heap size k là phương án lùi dễ nhớ.
- **Subarray Sum Equals K**: giữ `prefixSum` chạy + map `{prefix: số lần gặp}`. Tại mỗi bước cộng `cnt[prefix - k]` (số đoạn con kết thúc ở đây có tổng `k`). Bẫy: khởi tạo `map[0] = 1`.
- **Valid Sudoku**: một lượt duyệt 81 ô, dùng set (hoặc bitmask) cho 9 hàng, 9 cột, 9 ô 3×3; ô box index = `(r/3)*3 + c/3`.
- **First Unique Character**: đếm tần suất trước, rồi duyệt lại tìm ký tự đầu tiên có `count == 1`.
- **LRU Cache** (design, rất hay hỏi): `unordered_map<key, node*>` để tra O(1) + **doubly linked list** để biết thứ tự dùng gần đây (đầu = mới dùng, cuối = cũ nhất, evict cuối). Kết hợp 2 cấu trúc là mấu chốt.

## Pitfall C++ hay gặp

- **`operator[]` tạo phần tử mặc định** nếu key chưa có → dùng `.find()`/`.count()` khi chỉ muốn kiểm tra tồn tại.
- **Worst-case O(n)** mỗi thao tác do collision (average O(1)); hiếm ảnh hưởng phỏng vấn.
- **Key phức** (pair/vector) cần custom hash → tránh bằng cách encode thành `string` hoặc số.
- **Rehash tốn kém**: `reserve(n)` nếu biết trước số phần tử.
- **Ordered vs unordered**: cần O(1) tra cứu dùng `unordered_*`; cần giữ thứ tự (như Longest Consecutive nếu đổi cách) thì `set`/`map` là O(log n)/op.

## Liên hệ

- Trade-off kinh điển: **sorted + two pointers (O(1) space)** vs **hashing (O(n) space, không cần sort)** — xem lại topic [Array](01_array.md).
