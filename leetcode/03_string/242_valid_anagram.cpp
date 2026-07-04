#include <algorithm>
#include <string>
#include <array>
using namespace std;

// Array: Time O(n), Space O(1) - 2 mảng cố định 26 phần tử
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    int n = s.length();
    array<int, 26> cnt1{}, cnt2{};

    for (int i = 0; i < n; i++) {
        cnt1[s[i] - 'a']++;
        cnt2[t[i] - 'a']++;
    }

    return cnt1 == cnt2;
}

// Sort: Time O(n logn), Space O(log n) - stack đệ quy của sort (s, t là bản copy do nhận by-value)
bool SORT_isAnagram(string s, string t) {
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}
