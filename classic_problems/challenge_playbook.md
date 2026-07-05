# Coding Challenge Playbook (Codility / Coderbyte)

Sổ tay liếc nhanh **trước & trong** khi thi. Bối cảnh: **3 bài / 90 phút**, chấm tự động, có thể chấm điểm từng phần.

---

## Quy trình 90 phút

1. **Phân bổ ~25–30 phút/bài**, chừa ~5 phút cuối rà lại. Làm **bài dễ trước** để chốt điểm sớm.
2. Mỗi bài, theo đúng thứ tự:
   1. Đọc đề + **constraints** → **suy bậc complexity mục tiêu** (bảng dưới) TRƯỚC khi code.
   2. Phác thuật toán khớp bậc đó.
   3. Code trong **editor của platform**.
   4. **Verify** với example + **tự thêm 3–5 edge case**.
   5. Rà **checklist** (overflow / edge / complexity).
   6. Chỉ **Submit/Finish khi chắc**.
3. **Kẹt** → nộp bản **brute đúng** để ăn correctness score, sang bài khác, quay lại nếu còn giờ.

---

## Bước 1 luôn làm: constraints → bậc mục tiêu

```
N ≤ 10^3            -> O(N²) OK
N ≤ 10^5 .. 10^6    -> phải O(N log N) hoặc O(N)
N ≤ 10^18 / value lớn -> O(log) hoặc toán; binary-search-on-answer
value ≤ 10^9        -> KHÔNG brute theo giá trị; cẩn thận overflow
```
> Chọn thuật toán theo bậc cho phép, đừng code xong mới phát hiện quá chậm (bẫy Koko).

---

## Cơ chế nền tảng — nhớ để không hoảng

- **Không có step-debugger** (breakpoint). Thay bằng: in `cerr`/`cout` + **chạy custom input**.
- **Verify/Run** (thử example): dùng **bao nhiêu lần cũng được, không trừ điểm**. Verify thả ga.
- **Submit/Finish = chốt**. Phân biệt rõ nút "Run/Verify" vs "Submit". Một số bài **khóa sau khi Submit** → chỉ bấm khi xong.
- Trong 90 phút được **sửa & chạy lại tự do**; "hết cơ hội" chỉ khi hết giờ / finish cả bài test.
- **Proctoring** có thể phát hiện chuyển tab / paste → ưu tiên code thẳng trong editor platform.
- **Codility** chấm **correctness + performance TÁCH RIÊNG**, và hiện **"detected time complexity"** sau verify → đối chiếu với bậc mục tiêu.

---

## Reflex overflow (Codility rất thích bẫy)

> Có **cộng dồn / nhân** không? → dùng `long long` NGAY.

`N ~ 10^5` × `value ~ 10^9` → tổng tới `~10^14` → tràn `int` (32-bit). Đừng chờ tràn mới sửa.

---

## Checklist trước mỗi Submit (30 giây)

| Rà | Bug kinh điển tương ứng |
|---|---|
| mảng rỗng / size 1 | Remove Duplicates trả 1 sai |
| phần tử cuối / phần dư sau vòng lặp | Valid Parentheses thiếu `st.empty()` |
| toàn giống nhau / toàn số âm | Kadane cần `best = a[0]` |
| **overflow** tổng/tích | Container, prefix sum → `long long` |
| `array<int,K>{}` zero-init + đúng offset ký tự | 242, 424 (`'a'` vs `'A'`) |
| signed/unsigned khi so với `.size()` | 167, 26, 438 |
| **complexity vòng lặp lồng** (amortized?) | Longest Consecutive O(n²), Koko O(range) |
| **re-test sau khi refactor** | Valid Parentheses tạo bug mới lúc gom nhánh |

---

## Mini-oracle (khi không chắc đúng)

Bản thu nhỏ của fuzz test — làm ngay trong editor:
1. Viết nhanh **brute force** hiển nhiên đúng.
2. So với lời giải chính trên **5–10 input nhỏ / edge** tự thêm.

Bắt bug logic trước khi submit "mù". (Đã dùng cho 438, 424, 875.)

---

## Chiến thuật điểm số

- Chấm **từng phần** → **brute đúng trước** (ăn correctness), **tối ưu sau** (ăn performance).
- Đừng "all-or-nothing" đuổi lời giải hoàn hảo mà bỏ trắng bài.
- Bài dễ chốt điểm chắc trước, bài khó để sau.

---

## Trước ngày thi

- Làm **1–2 bài thật trên chính platform** để quen editor, nút Verify/Submit, format signature.
- **Codility**: luyện bộ **Lessons công khai** — cùng style/scoring với đề thi thật.
- **Coderbyte**: luyện thêm **string parsing / simulation** (hay ra hơn thuần algo).
- Ôn gap so với repo hiện tại: **prefix sum**, **Kadane biến thể**, **greedy interval**, **số học nặng overflow**.
- Hỏi recruiter: số bài / thời lượng / ngôn ngữ (bản C++) / chủ đề / có trắc nghiệm không.
