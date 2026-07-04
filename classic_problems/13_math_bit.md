# 13. Math & Bit Manipulation ★☆☆☆☆

Tần suất thấp nhất nhưng nên biết vài mẹo bit và số học cơ bản — thỉnh thoảng xuất hiện như câu phụ.

## Mẹo bit cốt lõi (C++)
```cpp
x & 1                  // bit thấp nhất: chẵn/lẻ
x >> 1                 // chia 2 (số không âm)
x & (x - 1)            // xóa bit 1 thấp nhất
x & (-x)               // lấy riêng bit 1 thấp nhất
__builtin_popcount(x)  // đếm số bit 1 (popcountll cho long long)
(1 << k)               // bitmask bit thứ k  (dùng 1LL nếu k >= 31)
```

Trực giác `x & (x-1)` xóa bit 1 thấp nhất — trừ 1 lật chuỗi bit thấp:

```
 x     = 1 0 1 1 0 0    (bit 1 thấp nhất ở vị trí 2)
 x - 1 = 1 0 1 0 1 1    (bit đó -> 0, các bit dưới -> 1)
 x&(x-1)=1 0 1 0 0 0    (đã xóa bit 1 thấp nhất)
 -> lặp tới khi x==0 để đếm số bit 1 (Brian Kernighan)
```

## Số học cơ bản (C++)
```cpp
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }   // Euclid
// lcm(a,b) = a / gcd(a,b) * b   (chia trước để tránh overflow)

// Sieve of Eratosthenes: mọi số nguyên tố tới N
vector<bool> is_prime(N + 1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; (long long)i * i <= N; ++i)
    if (is_prime[i])
        for (int j = i * i; j <= N; j += i) is_prime[j] = false;
```

## Bài cốt lõi (3 bài)

| # | Bài | Ý tưởng | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Single Number | XOR toàn mảng | Time O(n), Space O(1) |
| 2 | Counting Bits | DP theo bit | Time O(n) |
| 3 | Count Primes | Sieve | Time O(N log log N) |

### 1. Single Number
> Mỗi phần tử xuất hiện 2 lần trừ một. XOR tất cả → còn lại phần tử lẻ (vì `a^a=0`, `a^0=a`).

### 2. Counting Bits
> Số bit 1 của `0..n`. DP: `dp[i] = dp[i >> 1] + (i & 1)`.

### 3. Count Primes
> Đếm số nguyên tố `< n` bằng sàng Eratosthenes.

## Vì sao XOR giải được Single Number

XOR có tính **giao hoán + kết hợp** và `a ^ a = 0`, `a ^ 0 = a`. Nên khi XOR cả mảng, mọi
phần tử xuất hiện 2 lần triệt tiêu thành 0, chỉ còn phần tử duy nhất. Không cần bộ nhớ phụ
→ O(1) space, thay vì hash đếm tần suất O(n) space.

## Pitfall C++ hay gặp

- **Shift overflow**: `1 << 31` trên `int` là UB → dùng `1LL << k`.
- **Shift không hợp lệ**: dịch âm hoặc ≥ độ rộng kiểu là UB.
- **Số âm**: biểu diễn two's complement; `>>` trên số âm là implementation-defined — cẩn thận.
- **lcm overflow**: `a / gcd * b`, chia trước khi nhân.

## Liên hệ

- Bitmask là nền cho DP trạng thái ([DP](09_dp.md)) khi n nhỏ (≤ ~20); XOR/prefix hay kết hợp với [Hashing](02_hashing.md).
