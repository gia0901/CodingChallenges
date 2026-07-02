# 9. Dynamic Programming ★★★☆☆

Khó nhất trong nhóm phổ biến. Chìa khóa: **định nghĩa state rõ ràng** + **công thức chuyển tiếp** + **base case**. Ba khuôn: 1D, 2D (hai chuỗi/lưới), knapsack.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — 1D DP
```cpp
vector<int> dp(n + 1);
dp[0] = base;
for (int i = 1; i <= n; ++i)
    dp[i] = /* hàm của dp[i-1], dp[i-2], ... */;
return dp[n];
```

### Pattern B — 2D DP (hai chuỗi / lưới)
```cpp
vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
        dp[i][j] = (a[i-1] == b[j-1]) ? dp[i-1][j-1] + 1
                                      : max(dp[i-1][j], dp[i][j-1]);
```

### Pattern C — 0/1 Knapsack (1D tối ưu space)
```cpp
vector<int> dp(W + 1, 0);
for (int i = 0; i < n; ++i)
    for (int w = W; w >= wt[i]; --w)      // duyệt NGƯỢC: mỗi item dùng ≤ 1 lần
        dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
```

## Bài cốt lõi (7 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Climbing Stairs | A | Time O(n), Space O(1) |
| 2 | House Robber | A | Time O(n), Space O(1) |
| 3 | Coin Change | knapsack (unbounded) | Time O(n·amount) |
| 4 | Longest Increasing Subsequence | A | O(n²) hoặc O(n log n) |
| 5 | Longest Common Subsequence | B | Time O(m·n) |
| 6 | Unique Paths | B (lưới) | Time O(m·n) |
| 7 | Partition Equal Subset Sum | C (subset sum) | Time O(n·sum) |

### 1. Climbing Stairs
> `dp[i] = dp[i-1] + dp[i-2]` (Fibonacci). Nền tảng.
- Đã có: [leetcode/dynamic_programming/70_climbing_stairs.cpp](../../leetcode/dynamic_programming/70_climbing_stairs.cpp).

### 2. House Robber
> Không cướp 2 nhà liền kề: `dp[i] = max(dp[i-1], dp[i-2] + a[i])`.

### 3. Coin Change
> Số coin ít nhất tạo `amount`. Unbounded knapsack: `dp[x] = min(dp[x], dp[x-coin] + 1)`, duyệt `x` **tăng**.

### 4. Longest Increasing Subsequence
> O(n²): `dp[i] = max(dp[j]+1)` với `j<i, a[j]<a[i]`. O(n log n): mảng `tails` + `lower_bound`.

### 5. Longest Common Subsequence
> Pattern B (skeleton ở trên). Nền cho edit distance, diff.

### 6. Unique Paths
> Số đường từ góc trên-trái xuống dưới-phải: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`.

### 7. Partition Equal Subset Sum
> Chia mảng thành 2 phần tổng bằng nhau ⇔ subset sum = `total/2` (0/1 knapsack boolean).

## Pitfall C++ hay gặp

- **Thứ tự duyệt**: 0/1 knapsack duyệt trọng số **ngược**; unbounded duyệt **xuôi** — sai chiều là sai kết quả.
- **Base case & khởi tạo**: `INT_MAX` sentinel dễ **overflow** khi `+1` → kiểm tra trước khi cộng.
- **Định nghĩa state mơ hồ** là lỗi gốc — viết rõ `dp[i]` nghĩa là gì trước khi code.
- Có thể ép **O(1)/O(n) space** bằng rolling array khi chỉ phụ thuộc hàng/cột trước.

## Liên hệ

- LIS bản O(n log n) tái dùng binary search ([Binary Search](../04_binary_search/README.md)); nhiều bài DP có thể diễn đạt dạng đệ quy + memo (nối với [Backtracking](../11_backtracking/README.md)).
