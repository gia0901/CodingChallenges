# Cheat-sheet: Coding Interview cho Embedded SWE (Codility)

Ôn nhanh trước phỏng vấn. Ưu tiên **low-level + array/number/bit**, tránh tầng cao (graph nặng, DP phức tạp).
Mỗi pattern: skeleton C++ + bài LeetCode mẫu + task Codility tương ứng.

## 0. Chiến thuật phòng thi Codility

- **Chấm cả correctness + performance.** Từ `N` suy ra complexity mục tiêu:
  `N ≤ 10^5` → cần **O(n)** hoặc **O(n log n)**; `O(n^2)` sẽ **timeout** test lớn.
- **Test ẩn hay bắt edge case**: rỗng, 1 phần tử, toàn giống nhau, số âm, N cực đại, **overflow**.
- **Overflow**: tổng/tích `int` dễ tràn → `long long`. `mid = lo + (hi-lo)/2` (không `(lo+hi)/2`).
- Quy trình: đọc constraint → brute force cho chắc đúng → tối ưu về O(n) → **tự test 5 edge case** → submit.

Bảng chốt complexity theo N:

| N tối đa | Complexity chấp nhận |
|---|---|
| ≤ 10 | O(n!), O(2^n) |
| ≤ 20–25 | O(2^n) |
| ≤ 500 | O(n^3) |
| ≤ 5000 | O(n^2) |
| ≤ 10^6 | O(n), O(n log n) |
| > 10^6 | O(n), O(log n), O(1) |

---

## 1. Two pointers

```cpp
int l = 0, r = n - 1;
while (l < r) {
    int s = a[l] + a[r];
    if (s == target) { /* found */ break; }
    else if (s < target) l++;
    else r--;
}
```
- **LeetCode**: 167 Two Sum II, 125 Valid Palindrome, 11 Container With Most Water, 15 3Sum.
- **Codility**: —(thường ẩn trong bài array).

## 2. Prefix sum (cộng dồn trước → query range O(1))

```cpp
vector<long long> pre(n + 1, 0);
for (int i = 0; i < n; i++) pre[i+1] = pre[i] + a[i];
long long sum_lr = pre[r+1] - pre[l];   // tổng a[l..r]
```
- **LeetCode**: 303 Range Sum Query, 560 Subarray Sum Equals K (prefix + hash).
- **Codility**: PassingCars, GenomicRangeQuery, MinAvgTwoSlice, CountDiv.

## 3. Counting / hash (range nhỏ → mảng đếm thay map)

```cpp
// giá trị trong [0, K] -> đếm bằng mảng, O(n) không cần map
vector<int> cnt(K + 1, 0);
for (int x : a) cnt[x]++;
```
- **LeetCode**: 1 Two Sum, 268 Missing Number, 448 Find All Numbers Disappeared, 217 Contains Duplicate.
- **Codility**: FrogRiverOne, MaxCounters, MissingInteger, PermCheck.

## 4. Sliding window / caterpillar (1 lượt O(n))

```cpp
int l = 0; long long sum = 0; int best = INT_MAX;
for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum >= target) {                 // co trái khi thỏa điều kiện
        best = min(best, r - l + 1);
        sum -= a[l++];
    }
}
```
- **LeetCode**: 209 Minimum Size Subarray Sum, 3 Longest Substring Without Repeating, 76 Min Window Substring.
- **Codility**: CountDistinctSlices, MinAbsSumOfTwo.

## 5. Kadane (max subarray sum)

```cpp
long long best = a[0], cur = a[0];
for (int i = 1; i < n; i++) {
    cur = max((long long)a[i], cur + a[i]);   // nối tiếp hay bắt đầu lại?
    best = max(best, cur);
}
```
- **LeetCode**: 53 Maximum Subarray, 121 Best Time to Buy/Sell Stock.
- **Codility**: MaxSliceSum, MaxProfit, MaxDoubleSliceSum.

## 6. Stack (khớp cặp + monotonic)

```cpp
// Khớp ngoặc
stack<char> st;
for (char c : s) {
    if (isOpen(c)) st.push(c);
    else { if (st.empty() || !match(st.top(), c)) return 0; st.pop(); }
}
return st.empty();

// Monotonic (next greater): stack giữ index, giá trị giảm dần
stack<int> mst;
for (int i = 0; i < n; i++) {
    while (!mst.empty() && a[i] > a[mst.top()]) { ans[mst.top()] = i; mst.pop(); }
    mst.push(i);
}
```
- **LeetCode**: 20 Valid Parentheses, 739 Daily Temperatures, 155 Min Stack, 496 Next Greater Element.
- **Codility**: Brackets, Nesting, Fish, StoneWall.

## 7. Binary search (mảng sorted + on answer)

```cpp
// tìm trên mảng sorted
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;           // tránh overflow
    if (a[mid] == t) return mid;
    else if (a[mid] < t) lo = mid + 1;
    else hi = mid - 1;
}

// BINARY SEARCH ON ANSWER: tìm giá trị nhỏ nhất thỏa feasible()
long long lo = 1, hi = HIGH;
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (feasible(mid)) hi = mid;            // đủ tốt -> thử nhỏ hơn
    else lo = mid + 1;
}
return lo;
```
- **LeetCode**: 704 Binary Search, 35 Search Insert, 875 Koko Eating Bananas (on answer), 410 Split Array Largest Sum.
- **Codility**: MinMaxDivision, NailingPlanks.

## 8. Boyer–Moore (leader / phần tử đa số) — O(n)/O(1)

```cpp
int cand = a[0], cnt = 0;
for (int x : a) {
    if (cnt == 0) cand = x;
    cnt += (x == cand) ? 1 : -1;
}
// verify lại cand nếu đề không đảm bảo tồn tại leader
```
- **LeetCode**: 169 Majority Element, 229 Majority Element II.
- **Codility**: Dominator, EquiLeader.

## 9. Sorting + greedy (sort rồi quét 1 lượt)

```cpp
sort(v.begin(), v.end());
int count = 0, last_end = INT_MIN;
for (auto& iv : v) {                         // vd: chọn nhiều interval không đè
    if (iv.start > last_end) { count++; last_end = iv.end; }
}
```
- **LeetCode**: 55 Jump Game, 45 Jump Game II, 435 Non-overlapping Intervals, 56 Merge Intervals.
- **Codility**: MaxNonoverlappingSegments, TieRopes, Flags.

## 10. Number theory (gcd, sieve, đếm ước)

```cpp
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long lcm(long long a, long long b) { return a / gcd(a,b) * b; }   // chia trước tránh tràn

// Sieve of Eratosthenes: đánh dấu hợp số tới N
vector<char> is_p(N+1, 1); is_p[0] = is_p[1] = 0;
for (int i = 2; (long long)i*i <= N; i++)
    if (is_p[i]) for (int j = i*i; j <= N; j += i) is_p[j] = 0;

// đếm ước của n: O(sqrt n)
int factors = 0;
for (int i = 1; (long long)i*i <= n; i++)
    if (n % i == 0) factors += (i == n/i) ? 1 : 2;
```
- **LeetCode**: 204 Count Primes, 279 Perfect Squares, 1071 GCD of Strings.
- **Codility**: CountFactors, Peaks, ChocolatesByNumbers, CommonPrimeDivisors.

---

# PHẦN EMBEDDED — ôn kỹ, dễ được hỏi

## 11. Bit manipulation (gần như chắc gặp)

```cpp
x |=  (1u << k);          // set bit k
x &= ~(1u << k);          // clear bit k
x ^=  (1u << k);          // toggle bit k
bool b = (x >> k) & 1;    // test bit k

// đếm bit 1 — Brian Kernighan: O(số bit 1)
int cnt = 0; while (x) { x &= (x - 1); cnt++; }

bool isPow2 = (n > 0) && ((n & (n - 1)) == 0);   // power of 2
int lowest  = x & (-x);                          // bit 1 thấp nhất (isolate)
a ^= b; b ^= a; a ^= b;                          // swap không temp

// reverse bits 32-bit
uint32_t rev = 0;
for (int i = 0; i < 32; i++) { rev = (rev << 1) | (x & 1); x >>= 1; }
```
- **LeetCode**: 191 Number of 1 Bits, 231 Power of Two, 136 Single Number (XOR), 190 Reverse Bits, 338 Counting Bits, 268 Missing Number (XOR).
- Nhớ: **XOR** hủy cặp trùng → tìm phần tử lẻ; `a^a=0`, `a^0=a`.

## 12. Overflow & kiểu cố định (bẫy embedded)

```cpp
// tổng dễ tràn int -> long long
long long sum = 0; for (int x : a) sum += x;

// signed/unsigned: KHÔNG so int với size() trực tiếp
for (int i = 0; i < (int)v.size(); i++) { ... }

// trung điểm an toàn
int mid = lo + (hi - lo) / 2;
```
- Chú ý: `int8_t/uint16_t/uint32_t` (`<cstdint>`), wrap-around của unsigned, truncation khi chia số nguyên, endianness khi ghép byte.

## 13. Linked list (con trỏ)

```cpp
// reverse (3 con trỏ) — O(n), O(1)
Node *prev = nullptr, *cur = head;
while (cur) { Node* nx = cur->next; cur->next = prev; prev = cur; cur = nx; }
return prev;

// Floyd cycle detection (fast/slow)
Node *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next; fast = fast->next->next;
    if (slow == fast) return true;   // có vòng
}
return false;
```
- **LeetCode**: 206 Reverse Linked List, 141/142 Linked List Cycle, 876 Middle of the List, 19 Remove Nth From End.

## 14. Ring / circular buffer (rất embedded)

```cpp
struct Ring {
    vector<int> buf; int head = 0, tail = 0, count = 0, cap;
    Ring(int c) : buf(c), cap(c) {}
    bool full()  { return count == cap; }
    bool empty() { return count == 0; }
    bool push(int x) { if (full()) return false; buf[tail] = x; tail = (tail+1)%cap; count++; return true; }
    bool pop(int& x) { if (empty()) return false; x = buf[head]; head = (head+1)%cap; count--; return true; }
};
```
- **LeetCode**: 622 Design Circular Queue, 641 Design Circular Deque.

## 15. Iterative thay recursive (embedded lo stack overflow)

- Ưu tiên vòng lặp; nếu cần DFS → dùng `stack<>` tường minh thay đệ quy.
- Đệ quy sâu = risk tràn stack; đổi sang iterative để đẩy "stack" ra heap.

---

## 16. Checklist edge case trước khi submit

- [ ] Mảng **rỗng** (n = 0) / **1 phần tử**.
- [ ] **Toàn giống nhau** / đã sorted / sorted ngược.
- [ ] **Số âm**, số 0, giá trị **biên** (INT_MIN/MAX).
- [ ] **N cực đại** → đúng complexity, không timeout.
- [ ] **Overflow** tổng/tích → long long.
- [ ] **Off-by-one** ở index/range (insert range [0,n], erase [0,n-1]).

## 17. Ít gặp cho vòng embedded cơ bản (đừng dồn sức)

Graph nặng (Dijkstra/topo/union-find), DP 2 chiều phức tạp, tree cân bằng, backtracking sinh tổ hợp lớn.
Nếu có graph/DP thì thường chỉ mức: BFS/DFS đơn giản, DP 1 chiều (Fibonacci/climbing stairs/house robber).
- **LeetCode nếu muốn thủ**: 70 Climbing Stairs, 198 House Robber, 200 Number of Islands, 733 Flood Fill.
