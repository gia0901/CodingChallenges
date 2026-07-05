#include <bits/stdc++.h>
using namespace std;

// XOR — Time O(n), Space O(1)  (đáp án tối ưu của đề)
// a^a=0, a^0=a, và XOR giao hoán+kết hợp -> mọi cặp trùng triệt tiêu, còn lại số duy nhất.
//   4^1^2^1^2 = 4 ^ (1^1) ^ (2^2) = 4 ^ 0 ^ 0 = 4
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int n : nums) {
        res ^= n;
    }
    return res;
}

// Set toggle — Time O(n), Space O(n)
// Gặp lần đầu: insert; gặp lại: erase -> số trùng biến mất, còn lại đúng 1 số duy nhất.
int SETsingleNumber(vector<int>& nums) {
    unordered_set<int> seenOnce;
    for (int n : nums) {
        if (seenOnce.count(n)) {
            seenOnce.erase(n);
        } else {
            seenOnce.insert(n);
        }
    }
    return *seenOnce.begin();
}