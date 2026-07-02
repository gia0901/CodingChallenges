# 11. Backtracking ★★☆☆☆

Sinh mọi cấu hình (tập con / hoán vị / tổ hợp) bằng đệ quy: **chọn → đệ quy → hoàn tác (undo)**, kèm **pruning** để cắt nhánh vô vọng.

## Khuôn chung (skeleton C++)
```cpp
void backtrack(int start, vector<int>& path) {
    // ghi nhận nghiệm (tùy bài: khi đủ độ dài / mọi thời điểm)
    result.push_back(path);
    for (int i = start; i < n; ++i) {
        if (/* i không hợp lệ */) continue;   // pruning
        path.push_back(nums[i]);
        backtrack(i + 1, path);   // i+1: không dùng lại; i: cho phép lặp phần tử
        path.pop_back();          // UNDO — bắt buộc
    }
}
```

## Các biến thể

- **Tập con (Subsets)**: mỗi node đều là một nghiệm; nhánh `start = i+1`.
- **Hoán vị (Permutations)**: dùng mảng `used[]` thay `start`.
- **Cho phép lặp (Combination Sum)**: gọi lại với `i` (không phải `i+1`).
- **Grid (Word Search)**: đánh dấu ô đang dùng, DFS 4 hướng, bỏ dấu khi quay lui.

## Bài cốt lõi (4 bài)

| # | Bài | Biến thể | Complexity |
|---|-----|----------|-----------|
| 1 | Subsets | chọn/bỏ | O(2ⁿ · n) |
| 2 | Permutations | used[] | O(n! · n) |
| 3 | Combination Sum | cho phép lặp | ~O(2^target) |
| 4 | Word Search | DFS grid + undo | O(m·n·4^L) |

### 1. Subsets
> Sinh mọi tập con. Mỗi node của cây đệ quy là một tập con hợp lệ.

### 2. Permutations
> Mọi hoán vị. Bẫy trùng lặp (nếu có phần tử trùng): sort + skip `i>start && nums[i]==nums[i-1]`.

### 3. Combination Sum
> Chọn (có lặp) các số cộng bằng `target`. Truyền `i` để dùng lại phần tử; pruning khi `remain < 0`.

### 4. Word Search
> Tìm từ trong lưới ký tự theo 4 hướng, mỗi ô dùng 1 lần. Đánh dấu `visited`/đổi tạm ký tự rồi **khôi phục** khi quay lui.

## Pitfall C++ hay gặp

- **Quên undo** (`pop_back` / bỏ dấu visited) → trạng thái rò rỉ sang nhánh khác.
- **Trùng nghiệm**: sort trước + skip duplicate ở cùng cấp.
- Độ phức tạp **hàm mũ** — pruning sớm là bắt buộc với ràng buộc lớn.
- Truyền `path` **by reference** (không copy mỗi lần gọi) để tránh O(n) mỗi node.

## Liên hệ

- Là DFS đệ quy ([Tree](../05_tree/README.md)) có thêm bước undo; nhiều bài backtracking + memo trở thành [DP](../09_dp/README.md).
