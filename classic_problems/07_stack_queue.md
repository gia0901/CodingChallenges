# 7. Stack & Queue ★★★☆☆

- **Stack**: bài "khớp cặp" (ngoặc) và **monotonic stack** (next greater/smaller).
- **Queue**: chủ yếu là nền của **BFS** (xem [Tree](05_tree.md) 102, [Graph](08_graph.md)); bài thiết kế kinh điển là **queue bằng 2 stack** (amortized O(1)).
- **Deque**: **monotonic deque** cho sliding window max — ưu tiên tier-2 (xem ghi chú cuối).

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

**Bất biến (invariant):** stack luôn giữ các index có giá trị **giảm dần từ đáy lên đỉnh**.
Phần tử mới `a[i]` phá vỡ tính đó (lớn hơn đỉnh) chính là tín hiệu để pop.

**Trực giác cốt lõi:** *chính khoảnh khắc pop* là lúc phần tử bị pop tìm thấy đáp án của nó
— `a[i]` là "phần tử lớn hơn đầu tiên nằm bên phải". Phần tử còn nằm lại trong stack nghĩa là
"chưa tìm được ai lớn hơn" → nếu hết mảng mà vẫn kẹt trong stack thì đáp án là giá trị mặc định
(-1 / 0). Đây là lý do chỉ push `i` **sau** khi đã pop hết: `i` chỉ được "xếp hàng chờ" khi đã
đóng vai "người giải cứu" cho mọi phần tử nhỏ hơn phía trước.

### Pattern C — Queue bằng 2 stack (amortized O(1))
```cpp
class MyQueue {
    stack<int> in, out;              // in: nhận push; out: phục vụ pop/peek
    void shift() {                   // dồn in -> out khi out cạn (đảo thứ tự = FIFO)
        while (!in.empty()) { out.push(in.top()); in.pop(); }
    }
public:
    void push(int x) { in.push(x); }
    int  pop()  { if (out.empty()) shift(); int v = out.top(); out.pop(); return v; }
    int  peek() { if (out.empty()) shift(); return out.top(); }
    bool empty(){ return in.empty() && out.empty(); }
};
```
Mỗi phần tử được chuyển từ `in` sang `out` **đúng 1 lần** trong đời → dù `shift()` có vòng lặp,
tổng chi phí n thao tác là O(n) → **amortized O(1)/op**. Cùng kiểu lập luận với monotonic stack.

### Pattern D — Monotonic deque (sliding window maximum)
```cpp
deque<int> dq; // index, a[dq] giảm dần từ front -> back
for (int i = 0; i < n; ++i) {
    if (!dq.empty() && dq.front() <= i - k) dq.pop_front();      // hết hạn ở đầu
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();   // nhỏ hơn a[i] -> vô dụng
    dq.push_back(i);
    if (i >= k - 1) res.push_back(a[dq.front()]);               // front = max cửa sổ
}
```
Là Pattern B "nâng cấp": thêm thao tác **loại phần tử hết hạn ở đầu** (nên cần deque 2 đầu,
không dùng stack được). `dq.front()` luôn là index của max trong cửa sổ hiện tại.

## Bài cốt lõi

| # | Bài | Pattern | Complexity mục tiêu | Ưu tiên |
|---|-----|---------|---------------------|---------|
| 1 | Valid Parentheses | A | Time O(n), Space O(n) | ★ phải nắm |
| 2 | Min Stack | phụ trợ | Time O(1)/op | ★ phải nắm |
| 3 | Daily Temperatures | B | Time O(n), Space O(n) | ★ phải nắm |
| 4 | Implement Queue using Stacks | C | Amortized O(1)/op | ★ phải nắm |
| 5 | Sliding Window Maximum | D | Time O(n), Space O(k) | tier-2 |

### 1. Valid Parentheses
> Chuỗi ngoặc `()[]{}` có hợp lệ không? Pattern A với map ngoặc đóng→mở.

### 2. Min Stack
> Stack hỗ trợ `getMin()` O(1). Lưu kèm min hiện tại tại mỗi phần tử (`pair<val,min>`), hoặc
> stack min phụ. Mấu chốt: min phải cập nhật *đồng thời* với push/pop, không quét lại khi query.

### 3. Daily Temperatures
> Với mỗi ngày, còn bao nhiêu ngày tới ngày ấm hơn. Pattern B, lưu index, đáp = `i - st.top()`.
> Ngày còn kẹt trong stack đến hết mảng = không có ngày ấm hơn → giữ 0 (nhờ khởi tạo `res(n,0)`).
> **Pitfall:** chỉ pop trong vòng `while`; push `i` đúng **một lần sau** while. Nếu push `i`
> ngay trong lúc pop, đỉnh stack thành `i`, điều kiện `temp[i] > temp[i]` false → thoát sớm,
> mỗi ngày chỉ pop được 1 phần tử → các ngày lạnh hơn còn lại bị bỏ sót đáp án.

### 4. Implement Queue using Stacks
> Cài queue (FIFO) chỉ bằng 2 stack (LIFO). Pattern C. Mấu chốt: **chỉ `shift()` khi `out` rỗng**
> (lazy), đừng dồn qua dồn lại mỗi lần pop → nhờ vậy mới đạt amortized O(1). Bài 225 (stack bằng
> queue) là bản đối xứng, biết để so sánh.

### 5. Sliding Window Maximum
> Max của mỗi cửa sổ độ dài `k`. Pattern D — mỗi index vào/ra deque đúng 1 lần → O(n).
> Nếu bí, giải tạm bằng **max-heap `pair<val,idx>`** O(n log k) rồi tối ưu xuống deque.

## Vì sao amortized O(n)/O(1) (monotonic stack & queue-2-stack)

Cả hai nhìn có vòng `while` lồng nhưng **không phải O(n²)**: mỗi phần tử được **đưa vào đúng 1
lần và lấy ra tối đa 1 lần** trong cả thuật toán (pop khỏi monotonic stack, hoặc chuyển in→out).
Tổng thao tác ≤ n → cộng lại O(n) → chia đều là amortized O(1)/op. Cùng tư duy với sliding window:
đếm theo "mỗi phần tử vào/ra một lần", không nhân số vòng lặp trong × ngoài.

## Ghi chú ưu tiên luyện

- **Stack (A, B) + Min Stack + Queue-2-stack (C)**: nền tảng, **phải nắm chắc** — hay ra, độ khó vừa.
- **Monotonic deque (D)**: 239 là **Medium** nhưng kỹ thuật khó nhằn. Vì tái dùng đúng invariant
  của Pattern B nên chi phí học thêm thấp → **nên biết**, nhưng luyện *sau* khi chắc stack. Trong
  interview có heap O(n log k) làm phương án lùi.
- **Queue thực chiến = BFS**: ứng dụng queue quan trọng nhất không nằm ở đây mà ở duyệt theo tầng
  ([Tree](05_tree.md) 102/103) và [Graph](08_graph.md) BFS. Bài queue thuần (346 moving average,
  933 recent calls) quá dễ, chỉ cần biết `std::queue` là xong.

## Pitfall C++ hay gặp

- **Luôn `empty()` trước `top()`/`front()`** — gọi trên container rỗng là UB.
- Monotonic stack: quyết định **lưu index hay value** (thường index để tính khoảng cách).
- `std::queue` không random-access; sliding window max cần `std::deque`.
- Dấu so sánh `<` vs `<=` trong monotonic quyết định xử lý phần tử bằng nhau — chọn theo đề.
- Queue-2-stack: `shift()` **chỉ khi `out` rỗng**; dồn sớm khi `out` còn phần tử sẽ đảo lộn thứ tự FIFO.

## Liên hệ

- **Queue ↔ BFS**: [Tree](05_tree.md) level-order, [Graph](08_graph.md) shortest path không trọng số.
- **Monotonic deque** là biến thể tối ưu của [sliding window](03_string.md) khi cần max/min cửa sổ.
- **Amortized analysis** (mỗi phần tử vào/ra 1 lần) dùng lại ở [two pointers / sliding window](01_array.md).
