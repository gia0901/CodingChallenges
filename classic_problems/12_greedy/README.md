# 12. Greedy ★★☆☆☆

Chọn tối ưu cục bộ ở mỗi bước và kỳ vọng ra tối ưu toàn cục. Khó nhất là **chứng minh lựa chọn tham lam đúng** (exchange argument) — phỏng vấn hay đào chỗ này.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Sort rồi gộp/chọn (interval)
```cpp
sort(iv.begin(), iv.end());        // theo start
vector<vector<int>> res;
for (auto& x : iv) {
    if (res.empty() || res.back()[1] < x[0]) res.push_back(x);      // rời nhau
    else res.back()[1] = max(res.back()[1], x[1]);                  // gộp
}
```

### Pattern B — Trạng thái chạy (reach xa nhất)
```cpp
int reach = 0;
for (int i = 0; i < n; ++i) {
    if (i > reach) return false;          // kẹt, không tới được i
    reach = max(reach, i + a[i]);
}
return true;
```

## Bài cốt lõi (3 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Jump Game | B | Time O(n) |
| 2 | Merge Intervals | A | Time O(n log n) |
| 3 | Non-overlapping Intervals | A (sort theo end) | Time O(n log n) |

### 1. Jump Game
> Có tới được ô cuối không? Giữ `reach` = index xa nhất tới được; nếu `i > reach` thì kẹt.

### 2. Merge Intervals
> Gộp các interval chồng nhau. Sort theo start rồi gộp (skeleton A).

### 3. Non-overlapping Intervals
> Bỏ ít interval nhất để hết chồng lấn. **Sort theo end**, tham lam giữ interval kết thúc sớm nhất, đếm số phải bỏ.
- Đây là chỗ cần lập luận vì sao "kết thúc sớm nhất" là lựa chọn tối ưu.

## Pitfall C++ hay gặp

- **Chọn sai tiêu chí sort** (start vs end) làm hỏng tính đúng — mỗi bài một kiểu.
- **Biên chạm nhau** (`[1,2]` và `[2,3]`): tùy đề coi là chồng hay không → quyết định `<` vs `<=`.
- Greedy **không phải lúc nào cũng đúng** — nếu không chứng minh được, cân nhắc [DP](../09_dp/README.md).
- Overflow khi cộng `i + a[i]` với giá trị lớn → cân nhắc kiểu rộng hơn.

## Liên hệ

- Cùng khai thác việc sort như [Binary Search/Sorting](../04_binary_search/README.md); ranh giới greedy vs DP là điểm quyết định cách tiếp cận.
