#include <bits/stdc++.h>
using namespace std;

// Sliding window cố định:
// Time O(n): mỗi phần tử chỉ duyệt qua 1-2 lần
// Space O(26) = O(1): mảng đếm 26 ký tự
// Ý tưởng: anagram của p luôn có độ dài |p|, nên trượt một cửa sổ CỐ ĐỊNH cỡ |p|
// qua s và so phân bố ký tự với p. Ký tự lạ tự làm freq != targetFreq -> khỏi xử lý riêng.
vector<int> findAnagrams(string s, string p) {
    int len = s.length();
    int targetLen = p.length();
    vector<int> res;
    array<int, 26> freq{}, targetFreq{};   // freq = phân bố cửa sổ hiện tại; {} zero-init

    for (char c : p) targetFreq[c - 'a']++; // phân bố mục tiêu của p

    int left = 0;
    for (int right = 0; right < len; right++) {
        freq[s[right] - 'a']++;             // mở rộng cửa sổ sang phải

        // giữ cửa sổ đúng |p|: nếu vượt thì bỏ ký tự ngoài cùng bên trái
        if (right-left+1 > targetLen) {
            freq[s[left] - 'a']--;
            left++;
        }

        // cửa sổ đã đủ |p| và khớp phân bố -> [left..right] là một anagram của p
        if (freq == targetFreq) {
            res.push_back(left);
        }
    }
    return res;
}


// Sliding window co dãn:
// Time O(n): mỗi phần tử chỉ đi qua đúng 1 lần
// Space O(26) = O(1): mảng đếm 26 ký tự
vector<int> MY_findAnagrams(string s, string p) {
    int len = s.length();
    vector<int> res;
    array<int, 26> freq{}, targetFreq{};

    for (char c : p) targetFreq[c - 'a']++;

    auto isDifferent = [&]() {
        for (int i = 0; i < 26; i++) {
            if (freq[i] > targetFreq[i])
                return true;
        }
        return false;
    };

    int left = 0;
    for (int right = 0; right < len; right++) {
        // điểm tại s[right] ko tồn tại trong p,
        // ta lưu tần suất xuất hiện của nó và đi tới right hợp lệ.
        freq[s[right] - 'a']++;
        if (targetFreq[s[right] - 'a'] == 0) {
            continue;
        }
        
        // nếu đến đây, phía right đã hợp lệ, việc còn lại
        // là co left đến khi cửa sổ hợp lệ
        while (isDifferent() && left < right) {
            freq[s[left] - 'a']--;
            left++;
        }
        // cửa sổ hợp lệ: đã tạo thành p hoàn chỉnh, hoặc chưa đủ để tạo thành p
        if (freq == targetFreq)
            res.push_back(left);
    }

    return res;
}

int main() {
    auto res = findAnagrams("cbaebabacd", "abc");
}