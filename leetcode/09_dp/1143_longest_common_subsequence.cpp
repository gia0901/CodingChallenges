#include <bits/stdc++.h>
using namespace std;

// LCS - DP 2 chiều. Time O(n*m), Space O(n*m).
// state: dp[i][j] = độ dài LCS của TIỀN TỐ text1[0..i-1] và text2[0..j-1].
// dp lớn (n+1)x(m+1): hàng 0 / cột 0 = chuỗi rỗng -> LCS = 0 (base case tự đúng).
// Lệch index 1: dp[i][j] ứng với ký tự text1[i-1], text2[j-1].
int longestCommonSubsequence(string text1, string text2) {
    int n = text1.length();
    int m = text2.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i-1] == text2[j-1]) {
                // 2 ký tự trùng -> nối vào LCS của phần trước CẢ HAI (bỏ 1 ký tự mỗi bên)
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else {
                // khác nhau → không thể dùng đồng thời cả hai làm ký tự cuối 
                // -> bỏ bớt 1 ký tự ở 1 trong 2 chuỗi, lấy phương án tốt hơn
                dp[i][j] = max(dp[i][j-1],   // bỏ text2[j-1]
                               dp[i-1][j]);  // bỏ text1[i-1]
            }
        }
    }

    return dp[n][m];   // LCS của toàn bộ 2 chuỗi
}

/**
Đang so ký tự cuối của 2 tiền tố (text1[i-1] vs text2[j-1]):

Trùng: 
    → chắc chắn dùng được cặp này, +1 vào LCS của phần trước cả hai (dp[i-1][j-1]).
Khác:  
    → không thể dùng đồng thời cả hai làm ký tự cuối 
    → thử bỏ 1 ký tự ở một trong hai chuỗi (dp[i-1][j] hoặc dp[i][j-1]), lấy cái tốt hơn.
*/