# 1. Array & Two Pointers ★★★★★

Topic nền tảng, tần suất cao nhất. Hầu hết bài array phỏng vấn là biến thể của 3 pattern dưới đây. Mỗi pattern kèm **skeleton C++** để nhận diện nhanh; phần bài tập chỉ gợi hint để bạn tự code.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Two pointers hai đầu (opposite ends)
Mảng **đã sort** (hoặc thứ tự không quan trọng), tìm cặp thỏa điều kiện. Mỗi bước loại 1 khả năng → O(n).

```cpp
int left = 0, right = n - 1;
while (left < right) {
    int sum = a[left] + a[right];
    if (sum == target) { /* ghi nhận / trả về */ break; }
    else if (sum < target) ++left;   // cần lớn hơn
    else                   --right;  // cần nhỏ hơn
}
```

### Pattern B — Fast/slow (read-write, in-place)
Sửa mảng tại chỗ với O(1) extra space. `slow` = vị trí ghi tiếp theo, `fast` = con trỏ đọc.

```cpp
int slow = 0;
for (int fast = 0; fast < n; ++fast) {
    if (/* a[fast] cần giữ */) {
        a[slow++] = a[fast];
    }
}
// slow = độ dài kết quả; a[0..slow-1] là mảng đã lọc
```

### Pattern C — Prefix sum / running value
Cần tổng đoạn con hoặc trạng thái tích lũy — giữ giá trị chạy thay vì tính lại. Ví dụ Kadane:

```cpp
long long running = 0, best = LLONG_MIN;
for (int x : a) {
    running = max((long long)x, running + x); // nối tiếp hay bắt đầu lại
    best = max(best, running);
}
```

## Bài cốt lõi (5 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Two Sum II – Input Array Is Sorted | A | Time O(n), Space O(1) |
| 2 | Remove Duplicates from Sorted Array | B | Time O(n), Space O(1) |
| 3 | Move Zeroes | B | Time O(n), Space O(1) |
| 4 | Container With Most Water | A | Time O(n), Space O(1) |
| 5 | Maximum Subarray (Kadane) | C | Time O(n), Space O(1) |

### 1. Two Sum II (sorted)
> Mảng **sort tăng dần** và `target`. Trả về **index (1-based)** của hai phần tử cộng lại bằng `target`. Có đúng 1 nghiệm.

- Pattern A. `sum < target` → `++left`; `sum > target` → `--right`.
- Vì sao không cần hash map: mảng đã sort nên two pointers cho O(1) space.

### 2. Remove Duplicates from Sorted Array
> Mảng **sort tăng dần**, xóa phần tử trùng **tại chỗ** để mỗi giá trị xuất hiện 1 lần. Trả về độ dài mới `k`.

- Pattern B. Chỉ ghi `a[fast]` khi nó **khác `a[slow-1]`**.
- Edge case: mảng rỗng → trả 0.

### 3. Move Zeroes
> Dồn tất cả số 0 về cuối, **giữ thứ tự tương đối** các phần tử khác 0. Làm tại chỗ.

- Pattern B: gặp phần tử ≠ 0 thì `swap(a[slow++], a[fast])`.
- Bẫy: swap giữ đúng thứ tự và tránh phải điền 0 thủ công ở cuối.

### 4. Container With Most Water
> Mỗi phần tử là chiều cao một cột. Chọn 2 cột cho thùng chứa lớn nhất: `area = min(h[l], h[r]) * (r - l)`.

- Pattern A. Luôn **di chuyển con trỏ ở cột thấp hơn** (di cột cao không thể cải thiện: chiều rộng giảm, chiều cao vẫn bị chặn bởi cột thấp).
- Cần **giải thích được vì sao greedy đúng** — câu hỏi phỏng vấn hay đào chỗ này.

### 5. Maximum Subarray (Kadane)
> Tổng lớn nhất của một đoạn con liên tiếp (ít nhất 1 phần tử).

- Pattern C (skeleton ở trên).
- Bẫy: khởi tạo `best = a[0]` (không phải 0) để xử lý mảng toàn số âm.

## Pitfall C++ hay gặp

- **Signed/unsigned**: `nums.size()` là `size_t` (unsigned). `i < nums.size() - 2` **wrap-around** khi `size() < 2`. Ép `(int)nums.size()` hoặc kiểm tra kích thước trước.
- **Integer overflow**: tổng/tích trên `int` có thể tràn (diện tích, prefix sum lớn) → dùng `long long`.
- **Out-of-bounds**: vòng lặp hai con trỏ luôn giữ `left < right`; cẩn thận khi cả hai cùng nhảy.
- **Iterator invalidation**: tránh `erase` khi đang duyệt — đây cũng là lý do dùng two pointers thay vì xóa trực tiếp.

## Liên hệ

- **3Sum** ([leetcode/two_pointers/15_3Sum.cpp](../../leetcode/two_pointers/15_3Sum.cpp)) = sort + Pattern A lồng trong vòng lặp → ôn lại sau khi nắm 5 bài trên.
- Sliding window (Pattern C với cửa sổ co giãn) sẽ đào sâu ở topic **String**.
