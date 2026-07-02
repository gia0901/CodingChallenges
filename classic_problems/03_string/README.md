# 3. String ★★★★★

Phần lớn bài string quy về: sliding window co giãn, frequency array 26 ký tự, hoặc two pointers từ hai đầu.

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

### Pattern B — Frequency array 26
```cpp
array<int,26> f{};
for (char c : s) ++f[c - 'a'];   // giả định chữ thường a-z
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

## Pitfall C++ hay gặp

- **`char` có thể signed**: `s[i] - 'a'` phải chắc chắn ký tự trong `a-z`; ký tự > 127 cho index âm.
- **`substr` tạo bản sao** O(k) — trong vòng lặp dễ thành O(n·k); ưu tiên so khớp bằng chỉ số.
- **Nối chuỗi bằng `+`** trong vòng lặp là O(n²) — dùng `+=` / `reserve` / `ostringstream`.
- Sliding window: kích thước cửa sổ = `right - left + 1`, dễ off-by-one.

## Liên hệ

- Sliding window ở đây là biến thể co giãn của Pattern C (running) trong [Array](../01_array/README.md); frequency array nối với [Hashing](../02_hashing/README.md).
