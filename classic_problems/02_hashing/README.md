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

### 3. Group Anagrams
> Gom các từ là anagram của nhau vào cùng nhóm.

- Pattern C. Key = **chữ ký tần suất** (`array<int,26>` encode thành string) → O(k); nhanh hơn `sort(word)` là O(k log k).

### 4. Longest Consecutive Sequence
> Độ dài chuỗi số liên tiếp dài nhất (không cần liền kề trong mảng). Yêu cầu O(n).

- Đưa hết vào `unordered_set`. Với mỗi `x` mà `x-1` **không** có trong set (điểm bắt đầu chuỗi), đếm `x, x+1, ...`.
- Bẫy: chỉ đếm từ điểm start → mỗi phần tử được duyệt O(1) lần → tổng O(n).

## Pitfall C++ hay gặp

- **`operator[]` tạo phần tử mặc định** nếu key chưa có → dùng `.find()`/`.count()` khi chỉ muốn kiểm tra tồn tại.
- **Worst-case O(n)** mỗi thao tác do collision (average O(1)); hiếm ảnh hưởng phỏng vấn.
- **Key phức** (pair/vector) cần custom hash → tránh bằng cách encode thành `string` hoặc số.
- **Rehash tốn kém**: `reserve(n)` nếu biết trước số phần tử.

## Liên hệ

- Trade-off kinh điển: **sorted + two pointers (O(1) space)** vs **hashing (O(n) space, không cần sort)** — xem lại topic [Array](../01_array/README.md).
