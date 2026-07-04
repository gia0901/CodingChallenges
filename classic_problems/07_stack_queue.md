# 7. Stack & Queue ★★★☆☆

Stack cho bài "khớp cặp" và **monotonic stack** (next greater/smaller); **monotonic deque** cho sliding window max.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Stack khớp cặp (ngoặc)
```cpp
stack<char> st;
for (char c : s) {
    if (isOpen(c)) st.push(c);
    else {
        if (st.empty() || !match(st.top(), c)) return false;
        st.pop();
    }
}
return st.empty();
```

### Pattern B — Monotonic stack (next greater to the right)
```cpp
stack<int> st;            // lưu index, giá trị giảm dần từ đáy
vector<int> ans(n, -1);
for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) {
        ans[st.top()] = i;   // hoặc a[i], tùy bài
        st.pop();
    }
    st.push(i);
}
```

Cách chạy — next greater của `[2,1,3]`:

```
 i=0 a=2  st rỗng -> push        st=[2]
 i=1 a=1  1<2 không pop -> push  st=[2,1]
 i=2 a=3  a[top]=1<3 pop, ans[1]=3
          a[top]=2<3 pop, ans[0]=3
          push                   st=[3]
 => ans = [3, 3, -1]   (chỉ số/giá trị tùy bài)
```

### Pattern C — Monotonic deque (sliding window maximum)
```cpp
deque<int> dq; // index, a[dq] giảm dần
for (int i = 0; i < n; ++i) {
    if (!dq.empty() && dq.front() <= i - k) dq.pop_front(); // hết hạn
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) res.push_back(a[dq.front()]);
}
```

## Bài cốt lõi (4 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Valid Parentheses | A | Time O(n), Space O(n) |
| 2 | Min Stack | phụ trợ | Time O(1)/op |
| 3 | Daily Temperatures | B | Time O(n), Space O(n) |
| 4 | Sliding Window Maximum | C | Time O(n), Space O(k) |

### 1. Valid Parentheses
> Chuỗi ngoặc `()[]{}` có hợp lệ không? Pattern A với map ngoặc đóng→mở.

### 2. Min Stack
> Stack hỗ trợ `getMin()` O(1). Lưu kèm min hiện tại tại mỗi phần tử (hoặc stack min phụ).

### 3. Daily Temperatures
> Với mỗi ngày, còn bao nhiêu ngày tới ngày ấm hơn. Pattern B, lưu index, đáp = `i - st.top()`.

### 4. Sliding Window Maximum
> Max của mỗi cửa sổ độ dài `k`. Pattern C — mỗi index vào/ra deque đúng 1 lần → O(n).

## Vì sao monotonic stack là O(n)

Nhìn có vòng `while` lồng trong `for` nhưng **không phải O(n²)**: mỗi index được **push đúng 1
lần và pop tối đa 1 lần** trong cả thuật toán. Tổng số thao tác pop ≤ n → cộng lại O(n)
(amortized). Đây là cùng kiểu lập luận với sliding window: đếm theo "mỗi phần tử vào/ra 1 lần".

## Pitfall C++ hay gặp

- **Luôn `empty()` trước `top()`/`front()`** — gọi trên container rỗng là UB.
- Monotonic stack: quyết định **lưu index hay value** (thường index để tính khoảng cách).
- `std::queue` không random-access; sliding window max cần `std::deque`.
- Dấu so sánh `<` vs `<=` trong monotonic quyết định xử lý phần tử bằng nhau — chọn theo đề.

## Liên hệ

- Monotonic deque là biến thể tối ưu của sliding window ([String](03_string.md)) khi cần max/min cửa sổ.
