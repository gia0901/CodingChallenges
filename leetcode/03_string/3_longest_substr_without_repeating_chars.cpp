#include <bits/stdc++.h>
using namespace std;

// Sliding window — Time O(n), Space O(min(n, alphabet))
//   Space = số ký tự phân biệt trong map, bị chặn bởi min(n, số ký tự của bảng chữ).
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> freq;
    int n = s.length();
    int left = 0;
    int res = 0;

    for (int right = 0; right < n; right++) {
        freq[s[right]]++;

        // s[right] đã bị lặp lại, vị trí lặp lại có thể ở đâu đó trong [left,right]
        // ta cần loại bỏ dần phía left cho đến khi ký tự lặp bị loại bỏ, khi đó substring mới thỏa mãn.
        while (freq[s[right]] > 1 && left < right) {
            freq[s[left]]--;
            left++;
        }

        // tính độ dài substring vừa tìm thấy
        res = max(res, right-left+1);
    }

    return res;
}