# 03 — String

Tổng hợp kỹ thuật dùng cho các bài string trong thư mục này. Mỗi phần: *ý tưởng → khi nào dùng → cách chạy (hình) → vì sao đúng*.

| Bài | Kỹ thuật chính |
|-----|----------------|
| 3 — Longest Substring Without Repeating | Sliding window |
| 424 — Longest Repeating Char Replacement | Sliding window + counting array |
| 242 — Valid Anagram | Counting array / Sort canonical |
| 125 — Valid Palindrome | Two pointers |

---

## 1. Sliding window (bài 3, 424)

### Ý tưởng
Duy trì một cửa sổ `[left, right]` trượt qua chuỗi. `right` mở rộng cửa sổ; khi cửa sổ
vi phạm điều kiện thì `left` co lại cho tới khi hợp lệ. Đáp án = cửa sổ hợp lệ dài nhất.

```cpp
int left = 0, res = 0;
for (int right = 0; right < n; right++) {
    add(s[right]);                 // mở rộng
    while (!valid()) {             // co tới khi hợp lệ trở lại
        remove(s[left]);
        left++;
    }
    res = max(res, right - left + 1);
}
```

### Khi nào dùng
Bài hỏi **substring/subarray liên tiếp** thỏa một điều kiện, VÀ điều kiện đó **đơn điệu**:
*một cửa sổ hợp lệ thì mọi đoạn con của nó (cùng biên trái, ngắn hơn) cũng hợp lệ.*
Không có tính đơn điệu này → sliding window sai, phải dùng cách khác.

### Cách chạy — ví dụ bài 3 ("abcabcbb")

Cửa sổ luôn giữ "không có ký tự lặp". Gặp lặp thì co `left` qua bản sao cũ.

```
  a  b  c  a  b  c  b  b
 [a]                        right=0  window "a"      len 1
 [a  b]                     right=1  window "ab"     len 2
 [a  b  c]                  right=2  window "abc"    len 3  <- max
  a [b  c  a]               right=3  gặp 'a' lặp -> co left qua 'a' cũ
     b [c  a  b]            right=4  gặp 'b' lặp -> co left qua 'b' cũ
        c [a  b  c]         right=5  gặp 'c' lặp -> co left qua 'c' cũ
              a [b  c  b]?  right=6  gặp 'b' lặp -> co left tới sau 'b'
                    ...
đáp án = 3
```

`[` `]` là biên cửa sổ; mỗi lần đụng ký tự đã có trong cửa sổ, `left` nhảy tới
*sau* vị trí bản sao để cửa sổ sạch trở lại.

### Vì sao đúng — co `left` không bao giờ bỏ lỡ cửa sổ tốt hơn

Đây là phần dễ dùng mà khó giải thích. Chìa khóa là **tính đơn điệu**.

Đặt `g(cửa sổ)` = "mức vi phạm" (bài 424: `g = độ dài - max_freq` = số ký tự phải thay).
Giữ `left` cố định, kéo `right` sang phải thêm 1:

```
độ dài  : +1
max_freq: +0 hoặc +1   (thêm 1 ký tự chỉ giữ nguyên hoặc tăng max)
------------------------
g       : +0 hoặc +1   ->  g KHÔNG BAO GIỜ GIẢM khi mở rộng phải
```

**Hệ quả 1 (vì sao vứt `left` an toàn):** nếu `[left, right]` đã hỏng (`g > k`), thì mọi
cửa sổ giữ nguyên `left` mà kéo `right` xa hơn cũng hỏng (`g` chỉ tăng). Cái `left` đó
hết khả năng tạo cửa sổ hợp lệ lớn hơn → co đi, không mất gì.

**Hệ quả 2 (vì sao không bỏ lỡ tối ưu):** gọi cửa sổ tối ưu `[i*, j*]`.
Vì `g` không giảm, mọi đoạn đầu `[i*, r]` với `r <= j*` cũng hợp lệ. Do `left` chỉ tiến
và vòng `while` dừng NGAY khi hợp lệ, nên khi `right` chạy tới `j*` thì `left <= i*`.
Lúc đó cửa sổ `[left, j*]` hợp lệ và dài `>= j* - i* + 1` = tối ưu. → `res` chạm tối ưu. ∎

```
tại thời điểm right = j* (biên phải của cửa sổ tối ưu):

   ... [ left ....... i* ....... j* ] ...
        ^^^^          ^^          ^^
        left <= i*    biên trái   right
                      tối ưu
   => cửa sổ ghi nhận [left, j*] có độ dài >= [i*, j*]
```

### Độ phức tạp
`left` và `right` mỗi con trỏ chỉ đi một chiều, mỗi phần tử vào/ra cửa sổ đúng 1 lần
→ **Time O(n)** (dù có vòng `while` lồng, đây là amortized). **Space O(alphabet)**.

---

## 2. Counting array (bài 242, 424)

### Ý tưởng
Với chuỗi chỉ gồm alphabet nhỏ cố định (a–z / A–Z), dùng `array<int, 26>` đếm tần suất
thay cho `unordered_map`. Nhanh hơn hẳn: không hashing, bộ nhớ liên tục, cache-friendly.

```cpp
array<int, 26> cnt{};        // {} BẮT BUỘC: zero-init, quên là đọc giá trị rác
cnt[c - 'a']++;              // canh đúng gốc: 'a' cho chữ thường, 'A' cho chữ hoa
```

### Hai cạm bẫy khi đổi map -> array
1. **Quên `{}`** → mảng local mang giá trị rác → kết quả sai ngẫu nhiên.
2. **Sai offset ký tự** → `'A' - 'a' = -32` → truy cập ngoài mảng (out-of-bounds).

> Mẹo: build với `-fsanitize=address,undefined` để bắt ngay 2 lỗi này lúc chạy.

### Trade-off
`array<int,26>` nhanh nhưng chỉ hợp alphabet cố định. Nếu ký tự đa dạng (Unicode,
hoa lẫn thường, số...) → quay lại `unordered_map<char,int>` cho linh hoạt.

---

## 3. Sort làm canonical form (bài 242)

### Ý tưởng
Hai chuỗi là anagram ⟺ sắp xếp xong thì bằng nhau. Sort đưa mọi anagram về **một dạng
chuẩn** duy nhất để so sánh trực tiếp.

```cpp
sort(s.begin(), s.end());
sort(t.begin(), t.end());
return s == t;               // O(n log n)
```

### Trade-off so với counting
- Counting: **O(n)**, nhưng giả định alphabet cố định.
- Sort: **O(n log n)**, chậm hơn nhưng không phụ thuộc alphabet, code ngắn.

---

## 4. Two pointers (bài 125)

### Ý tưởng
Hai con trỏ từ hai đầu tiến vào giữa, so sánh từng cặp. Với palindrome: skip ký tự
không hợp lệ tại chỗ để đạt **Space O(1)** (không tạo chuỗi phụ).

### Cách chạy — ví dụ "a#ba" (kiểm palindrome, bỏ qua '#')

```
  a  #  b  a
  L        R     so 'a' == 'a'  -> ok, tiến vào
     L  R        L gặp '#' -> skip -> L tới 'b'
        LR       L == R  -> gặp nhau -> palindrome!
```

`L` bỏ qua ký tự không hợp lệ rồi mới so với `R`. Dừng khi `L >= R`.

### Khi nào dùng
Chuỗi/mảng cần đối chiếu **từ hai đầu** (palindrome), hoặc mảng **đã sort** cần tìm cặp
(two-sum sorted). Đạt O(1) space vì không cần cấu trúc phụ.

---

## Nhắc nhanh: chọn kỹ thuật nào?

```
substring liên tiếp + điều kiện đơn điệu   -> sliding window
alphabet nhỏ cố định, cần đếm tần suất     -> counting array (array<int,26>{})
so khớp không quan tâm thứ tự (anagram)    -> sort canonical / counting
đối chiếu hai đầu / mảng đã sort           -> two pointers
```
