#include <bits/stdc++.h>
using namespace std;

int climbStairs(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = dp[1] = 1; // luôn có 1 cách tại 0 (trước khi bước) và 1 (chỉ có cách đi từ 0 lên)

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

int main() {

}