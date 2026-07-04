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

Cách chạy — tìm cặp có tổng = `9` trong `[1,2,4,7,11,15]`:

```
 1   2   4   7  11  15      L=0 R=5  sum=1+15=16 > 9 -> R--
 L                   R
 1   2   4   7  11  15      L=0 R=4  sum=1+11=12 > 9 -> R--
 L               R
 1   2   4   7  11  15      L=0 R=3  sum=1+7 =8  < 9 -> L++
 L           R
 1   2   4   7  11  15      L=1 R=3  sum=2+7 =9  == target  ✓
     L       R
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

Cách chạy — lọc bỏ số 0 khỏi `[0,1,0,3,2]` (giữ thứ tự):

```
 idx    0  1  2  3  4
 a  =   0  1  0  3  2
        F                slow=0  a[0]=0 -> bỏ qua
           F             slow=0  a[1]=1 -> ghi a[0]=1, slow=1
              F          slow=1  a[2]=0 -> bỏ qua
                 F       slow=1  a[3]=3 -> ghi a[1]=3, slow=2
                    F    slow=2  a[4]=2 -> ghi a[2]=2, slow=3
 => [1,3,2, .. ]  giữ [0..slow-1]
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

- Pattern A. Luôn **di chuyển con trỏ ở cột thấp hơn**.
- **Vì sao greedy đúng** (câu phỏng vấn hay đào): diện tích bị chặn bởi cột thấp. Nếu ta giữ cột thấp và dời cột cao vào trong, chiều rộng giảm mà chiều cao vẫn ≤ cột thấp → diện tích chỉ nhỏ đi. Vậy cột thấp đã "cạn" tiềm năng → loại nó an toàn, mỗi bước bỏ đúng 1 cột → O(n).

### 5. Maximum Subarray (Kadane)
> Tổng lớn nhất của một đoạn con liên tiếp (ít nhất 1 phần tử).

- Pattern C (skeleton ở trên). Mỗi bước chỉ 2 lựa chọn: **nối dài** (`running + x`) hay **bắt đầu lại** (`x`).
- Bẫy: khởi tạo `best = a[0]` (không phải 0) để xử lý mảng toàn số âm.

## Pitfall C++ hay gặp

- **Signed/unsigned**: `nums.size()` là `size_t` (unsigned). `i < nums.size() - 2` **wrap-around** khi `size() < 2`. Ép `(int)nums.size()` hoặc kiểm tra kích thước trước.
- **Integer overflow**: tổng/tích trên `int` có thể tràn (diện tích, prefix sum lớn) → dùng `long long`.
- **Out-of-bounds**: vòng lặp hai con trỏ luôn giữ `left < right`; cẩn thận khi cả hai cùng nhảy.
- **Iterator invalidation**: tránh `erase` khi đang duyệt — đây cũng là lý do dùng two pointers thay vì xóa trực tiếp.

## Liên hệ

- **3Sum** ([leetcode/two_pointers/15_3Sum.cpp](../leetcode/two_pointers/15_3Sum.cpp)) = sort + Pattern A lồng trong vòng lặp → ôn lại sau khi nắm 5 bài trên.
- Sliding window (Pattern C với cửa sổ co giãn) sẽ đào sâu ở topic [String](03_string.md).
