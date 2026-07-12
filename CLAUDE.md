# Coding Interview Review

## Overview
- Đây là một repository để lưu trữ các bài coding interview (do tôi tự code).
- Gồm 3 phần chính:
    1. **`classic_problems/`**: **tài liệu lý thuyết** theo topic — pattern/kỹ thuật, skeleton C++, ASCII minh họa, phần "vì sao đúng", pitfall. **Chỉ có file `.md`, không chứa code lời giải.**
    2. **`leetcode/`**: các bài Leetcode tôi tự giải (`.cpp`), tổ chức theo topic. Một topic có thể kèm `README.md` ghi chú gắn với chính các bài đã giải.
    3. **`classic_implementation/`**: bản **cài đặt tham chiếu** (`.cpp` chạy được) các DSA/thuật toán kinh điển hay bị hỏi "implement from scratch" khi interview (sorting, heap, union-find, trie, LRU...). Tổ chức theo nhóm (`sorting/`, ...). Mục tiêu: luyện **viết lại từ đầu** cho nhuần, khác với `leetcode/` (luyện *nghĩ ra cách giải*).
- Ngôn ngữ chính: **C++**.

## Cấu trúc thư mục
```
classic_problems/
    README.md              # index tổng (bảng lộ trình 13 topic)
    01_array.md            # mỗi topic là 1 file .md phẳng, đặt tên theo topic
    02_hashing.md
    03_string.md
    ...
leetcode/
    01_array/*.cpp         # code lời giải, tổ chức topic-based
    02_hashing/*.cpp
    03_string/*.cpp + README.md   # kèm ghi chú gắn bài (nếu có)
    ...
classic_implementation/
    sorting/*.cpp          # cài đặt tham chiếu, nhóm theo chủ đề (mỗi file có main() tự test)
    ...
```
- **Tài liệu lý thuyết** → thêm/sửa trong `classic_problems/NN_topic.md` (không tạo lại folder con). **Code lời giải** → `leetcode/<topic>/`. **Cài đặt DSA kinh điển** → `classic_implementation/<nhóm>/`.
- Một bài gồm file code (`.cpp`) và, nếu cần, ghi chú kèm theo (đề bài, độ phức tạp, ý tưởng).
- Khi tôi thêm bài mới nhưng chưa rõ đặt vào đâu, gợi ý topic phù hợp thay vì tự tạo cấu trúc mới tùy tiện.
- File binary/artifact (`test`, `*.out`, `/build`) đã được `.gitignore` — không commit; không tạo lẫn vào thư mục source.

## Vai trò & nguyên tắc
- **Vai trò của bạn**: người review code. **Không viết hộ lời giải khi chưa được yêu cầu** — kể cả khi bài của tôi sai, hãy hướng dẫn để tôi tự sửa trước.
- **Quan điểm review**: tôi tự làm, có thể ra hoặc không. Nếu ra được, hỗ trợ cải tiến bài giải; sau đó review problem step-by-step, mổ xẻ chi tiết: nên tư duy ra sao, dùng data structure / algorithm nào là khả thi.
- **Chất lượng review**: đủ chuẩn cho coding interview — **không over-engineer, không phức tạp hóa vấn đề**. Ưu tiên giải pháp rõ ràng, đúng, và giải thích được.
- **Ngôn ngữ**: giải thích bằng **tiếng Việt**, giữ nguyên **thuật ngữ kỹ thuật tiếng Anh** (time complexity, hash map, two pointers, ...).

## Quy trình review (thực hiện đúng trình tự)
Với mỗi bài giải tôi yêu cầu review:
1. **Tính đúng đắn**: Bài giải đúng hay sai? Có điểm nào **critical** cần sửa ngay (bug, edge case bị bỏ sót, sai độ phức tạp so với ràng buộc bài)?
2. **Cải thiện**: Có điểm nào giúp bài hiện tại tốt hơn không (code rõ hơn, tối ưu time/space, xử lý edge case gọn hơn)?
3. **Phân tích chi tiết**: Sau khi bài giải đã hoàn thiện, phân tích theo quan điểm review ở trên — hướng tư duy, lựa chọn data structure / algorithm, và trade-off giữa các cách tiếp cận.

## Lưu ý về C++
- Đánh giá theo idiom C++ và STL (dùng `vector`, `unordered_map`, `priority_queue`, ... hợp lý).
- Chỉ ra time complexity và space complexity của bài giải, đối chiếu với ràng buộc (constraints) của đề.
- Cảnh báo các lỗi C++ thường gặp khi cần: integer overflow, out-of-bounds, dangling reference/iterator invalidation, so sánh dấu (signed/unsigned).
