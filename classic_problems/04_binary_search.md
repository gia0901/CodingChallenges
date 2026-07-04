# 4. Binary Search (+ Sorting) ★★★★☆

Bất cứ khi nào có **tính đơn điệu** (mảng sort, hoặc predicate monotonic) → nghĩ tới binary search để cắt còn O(log n).

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Binary search chuẩn (tìm target)
```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;   // tránh overflow
    if (a[mid] == target) return mid;
    else if (a[mid] < target) lo = mid + 1;
    else                      hi = mid - 1;
}
return -1;
```

Cách chạy — tìm `7` trong `[1,3,5,7,9,11]`:

```
 1  3  5  7  9 11     lo=0 hi=5 mid=2 a[2]=5 <7 -> lo=mid+1
 L     M     H
 1  3  5  7  9 11     lo=3 hi=5 mid=4 a[4]=9 >7 -> hi=mid-1
          L  M  H
 1  3  5  7  9 11     lo=3 hi=3 mid=3 a[3]=7 == target ✓
          LMH
```

### Pattern B — Lower/upper bound (tìm biên)
```cpp
int idx  = lower_bound(a.begin(), a.end(), target) - a.begin(); // first >= target
int idx2 = upper_bound(a.begin(), a.end(), target) - a.begin(); // first > target
// số lần xuất hiện target = idx2 - idx
```

### Pattern C — Binary search trên answer space
```cpp
int lo = minVal, hi = maxVal;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (feasible(mid)) hi = mid;      // mid khả thi -> thử nhỏ hơn
    else               lo = mid + 1;  // chưa khả thi -> cần lớn hơn
}
return lo; // giá trị nhỏ nhất khả thi
```

Ý tưởng "search trên answer space" — predicate `feasible` đơn điệu theo giá trị:

```
value :  1   2   3   4   5   6   7   8
feasible: F   F   F   F   T   T   T   T
                      ^
                      binary search tìm biên F->T (đáp = 5)
```

## Bài cốt lõi (5 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Binary Search (basic) | A | Time O(log n) |
| 2 | Search Insert Position | B | Time O(log n) |
| 3 | Find First and Last Position | B | Time O(log n) |
| 4 | Search in Rotated Sorted Array | A biến thể | Time O(log n) |
| 5 | Koko Eating Bananas | C | Time O(n log maxVal) |

### 1. Binary Search
> Tìm target trong mảng sort, trả index hoặc -1. Nắm chắc skeleton A trước tiên.

### 2. Search Insert Position
> Vị trí chèn để mảng vẫn sort = `lower_bound`.

### 3. Find First and Last Position
> Vị trí đầu và cuối của target trong mảng sort có lặp.

- Dùng `lower_bound` (first ≥ target) và `upper_bound - 1` (last).

### 4. Search in Rotated Sorted Array
> Mảng sort bị xoay tại một pivot chưa biết; tìm target O(log n).

- Mỗi bước, **một nửa luôn sort** — xác định nửa đó (`a[lo] <= a[mid]`?), kiểm tra target có nằm trong nửa sort không để chọn hướng.

```
 [4 5 6 7 0 1 2]   mid=7  a[lo]=4<=a[mid]=7 -> nửa TRÁI [4..7] sort
  L     M     H     target=0 không thuộc [4,7] -> đi nửa phải
```

### 5. Koko Eating Bananas
> Tìm tốc độ ăn nhỏ nhất để ăn hết trong `h` giờ.

- Pattern C: `feasible(speed)` = tổng `ceil(pile/speed)` ≤ h. Không gian nghiệm `[1, max(pile)]` đơn điệu theo speed (ăn nhanh hơn thì không thể tốn nhiều giờ hơn).

## Vì sao đúng & không lặp vô hạn

- **Tính đúng**: mỗi bước loại bỏ nửa **chắc chắn không chứa** đáp án nhờ tính đơn điệu → không gian co một nửa mỗi vòng → O(log n).
- **Không vô hạn**: khoảng `[lo, hi]` phải **co lại thật sự** mỗi vòng. Với `lo < hi` + `hi = mid`, phải có `lo = mid + 1` ở nhánh kia (vì `mid` làm tròn xuống, `mid` có thể = `lo` → nếu gán `lo = mid` sẽ kẹt).

## Pitfall C++ hay gặp

- **Overflow `mid`**: luôn `lo + (hi - lo) / 2`, không `(lo + hi) / 2`.
- **Vòng lặp vô hạn**: chọn nhất quán `lo <= hi` (Pattern A) hoặc `lo < hi` (Pattern C); cập nhật biên sao cho khoảng luôn co lại.
- **Predicate phải monotonic** trong Pattern C — nếu không, binary search sai.
- **Sorting**: `std::sort` là O(n log n); comparator phải là **strict weak ordering** (dùng `<`, không `<=`) nếu không UB.

## Liên hệ

- Two pointers trên sorted ([Array](01_array.md)) và binary search đều khai thác tính sort — chọn theo dạng bài.
