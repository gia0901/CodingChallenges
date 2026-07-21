# 3. String ★★★★★

Phần lớn bài string quy về: sliding window co giãn, frequency array 26 ký tự, hoặc two pointers từ hai đầu.

> Có bản ghi chú gắn với bài đã giải (kèm ASCII + chứng minh chi tiết) tại
> [leetcode/03_string/README.md](../leetcode/03_string/README.md). File này là phần **pattern tổng quát**.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — Sliding window co giãn
```cpp
unordered_map<char,int> cnt;
int left = 0, best = 0;
for (int right = 0; right < n; ++right) {
    cnt[s[right]]++;
    while (/* cửa sổ vi phạm điều kiện */) {
        if (--cnt[s[left]] == 0) cnt.erase(s[left]);
        ++left;
    }
    best = max(best, right - left + 1);
}
```

Cách chạy — substring dài nhất không lặp ký tự, `s = "abcabcbb"`:

```
 a b c a b c b b
[a]                 "a"    len 1
[a b]               "ab"   len 2
[a b c]             "abc"  len 3  <- max
 a[b c a]           gặp 'a' lặp -> co left qua bản 'a' cũ
   b[c a b]         gặp 'b' lặp -> co left ...
     ...            đáp án = 3
```

### Pattern B — Frequency array 26
```cpp
array<int,26> f{};               // {} BẮT BUỘC: zero-init
for (char c : s) ++f[c - 'a'];   // 'a' cho a-z, 'A' cho A-Z — canh đúng gốc
```

### Pattern C — Two pointers hai đầu (palindrome)
```cpp
int l = 0, r = n - 1;
while (l < r) {
    if (s[l] != s[r]) return false;
    ++l; --r;
}
return true;
```

Cách chạy — palindrome, bỏ qua ký tự không hợp lệ (`"a#ba"`):

```
 a # b a
 L     R    's[L]=a' == 's[R]=a'  -> ok, tiến vào
   L R      L gặp '#' -> skip -> L tới 'b'
     LR     L gặp R  -> palindrome!
```

## Bài cốt lõi (5 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Valid Anagram | B | Time O(n), Space O(1) |
| 2 | Valid Palindrome | C | Time O(n), Space O(1) |
| 3 | Longest Substring Without Repeating Characters | A | Time O(n), Space O(min(n,Σ)) |
| 4 | Longest Repeating Character Replacement | A | Time O(n), Space O(1) |
| 5 | Find All Anagrams in a String | A | Time O(n), Space O(1) |

### 1. Valid Anagram
> Hai chuỗi có phải hoán vị ký tự của nhau không?

- Pattern B: đếm rồi so sánh 2 mảng tần suất (hoặc tăng ở s, giảm ở t, kiểm tra toàn 0).

### 2. Valid Palindrome
> Chỉ xét chữ-số, bỏ hoa/thường và ký tự khác.

- Pattern C + bỏ qua ký tự non-alphanumeric ở hai đầu; so sánh sau `tolower`.

### 3. Longest Substring Without Repeating Characters
> Độ dài substring dài nhất không lặp ký tự.

- Pattern A. Điều kiện vi phạm: `cnt[s[right]] > 1` → co `left` tới khi hết lặp.

### 4. Longest Repeating Character Replacement
> Được thay tối đa `k` ký tự, tìm substring dài nhất toàn 1 loại ký tự sau khi thay.

- Pattern A + biến `maxFreq` của ký tự trội trong cửa sổ. Cửa sổ hợp lệ khi `(size - maxFreq) <= k`.
- Bẫy: không cần giảm `maxFreq` khi co cửa sổ (chỉ cần cận trên) — vẫn cho đáp án đúng.

### 5. Find All Anagrams in a String
> Trả về mọi start index nơi substring là anagram của pattern `p`.

- Cửa sổ **cố định** độ dài `|p|` + so khớp 2 mảng tần suất (hoặc đếm số vị trí khớp).

## Bài luyện thêm (interview hay gặp)

| Bài | Pattern / ý tưởng | Complexity |
|-----|-------------------|------------|
| Longest Common Prefix | quét dọc từng cột ký tự | O(n·m) |
| Longest Palindromic Substring | expand around center (2n-1 tâm) | O(n²), O(1) |
| Palindromic Substrings | expand around center, đếm | O(n²), O(1) |
| Permutation in String | cửa sổ CỐ ĐỊNH `|p|` + so tần suất | O(n) |
| Minimum Window Substring | cửa sổ co giãn + need/have (khó hơn) | O(n) |

- **Longest Common Prefix**: so ký tự cùng cột của mọi chuỗi; dừng khi lệch hoặc hết chuỗi ngắn nhất.
- **Longest Palindromic Substring**: với mỗi trong `2n-1` tâm (n tâm lẻ + n-1 tâm chẵn), **nới hai biên ra** khi còn đối xứng; giữ đoạn dài nhất. Đơn giản, đủ chuẩn interview (khỏi cần Manacher O(n)).
- **Palindromic Substrings**: cùng "expand around center" nhưng **đếm** mỗi lần nới thành công.
- **Permutation in String**: hỏi `s2` có chứa hoán vị của `s1` không → **cửa sổ cố định `|s1|`** trượt qua `s2`, so 2 mảng tần suất (cùng khuôn bài 438).
- **Minimum Window Substring**: cửa sổ **co giãn** tìm đoạn ngắn nhất chứa đủ ký tự của `t`. Giữ `need`/`have` + biến đếm số ký tự đã đủ; mở rộng `right` tới khi đủ, rồi co `left` tối đa. Khó hơn — luyện sau khi chắc 3, 424.

## Vì sao sliding window đúng (không bỏ lỡ cửa sổ tốt hơn khi co `left`)

Đặt `g(cửa sổ)` = mức vi phạm điều kiện. Điều kiện phải **đơn điệu**: mở rộng cửa sổ sang
phải làm `g` **không giảm**. Khi đó:

- **Vứt `left` an toàn**: nếu `[left,right]` đã hỏng, mọi cửa sổ giữ nguyên `left` mà kéo
  `right` xa hơn cũng hỏng (`g` chỉ tăng) → cái `left` đó hết khả năng tạo cửa sổ lớn hơn.
- **Không bỏ lỡ tối ưu**: gọi cửa sổ tối ưu `[i*, j*]`. Vì mọi đoạn đầu `[i*, r]` (`r ≤ j*`)
  cũng hợp lệ, và `left` chỉ tiến + vòng `while` dừng ngay khi hợp lệ → khi `right` chạm `j*`
  thì `left ≤ i*`, nên cửa sổ ghi nhận dài `≥ j* - i* + 1` = tối ưu.

→ Đây chính là **dấu hiệu nhận biết dùng được sliding window**: "hợp lệ đơn điệu".

## Pitfall C++ hay gặp

- **`char` có thể signed**: `s[i] - 'a'` phải chắc chắn ký tự trong `a-z`; ký tự > 127 cho index âm → ép `(unsigned char)` khi dùng `<cctype>`.
- **`array<int,26>` phải có `{}`** để zero-init; canh đúng offset (`'a'` vs `'A'`).
- **`substr` tạo bản sao** O(k) — trong vòng lặp dễ thành O(n·k); ưu tiên so khớp bằng chỉ số.
- **Nối chuỗi bằng `+`** trong vòng lặp là O(n²) — dùng `+=` / `reserve` / `ostringstream`.
- Sliding window: kích thước cửa sổ = `right - left + 1`, dễ off-by-one.

## Liên hệ

- Sliding window ở đây là biến thể co giãn của Pattern C (running) trong [Array](01_array.md); frequency array nối với [Hashing](02_hashing.md).
