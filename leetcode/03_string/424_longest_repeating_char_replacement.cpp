#include <bits/stdc++.h>
using namespace std;

// Sliding window — Time O(n*26) = O(n), Space O(1)
// Ý tưởng: một cửa sổ HỢP LỆ khi (độ dài - max_freq) <= k.
//   max_freq = số ký tự xuất hiện nhiều nhất (giữ lại), phần còn lại là số ký tự
//   phải thay. Nếu số phải thay <= k thì biến cả cửa sổ thành 1 ký tự được.
//   Mở rộng right, khi vi phạm thì co left; res = cửa sổ hợp lệ dài nhất.
int characterReplacement(string s, int k) {
    int n = s.length();
    array<int, 26> freq{};
    int res = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        freq[s[right] - 'A']++;
        int max_freq = 0;

        // ký tự có tần suất cao nhất trong cửa sổ (đây là ký tự sẽ được giữ lại)
        for (int f : freq) {
            max_freq = max(max_freq, f);
        }

        // (độ dài cửa sổ - max_freq) = số ký tự phải thay.
        // Vượt quá k -> không đủ lượt thay -> cửa sổ không hợp lệ -> co left.
        while ((right-left+1) - max_freq > k) {
            freq[s[left] - 'A']--;
            left++;
        }

        res = max(res, right-left+1);
    }

    return res;
}

int main() {
    int res = characterReplacement("AABABBA", 2);
    cout << res << endl;
}