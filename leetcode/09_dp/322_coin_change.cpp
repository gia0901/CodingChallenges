#include <bits/stdc++.h>
using namespace std;

int coinChange(vector<int>& coins, int amount) {
    vector<long long> dp(amount+1, INT_MAX);
    dp[0] = 0;

    for (int cur = 1; cur <= amount; cur++) {
        for (int coin : coins) {
            // chọn đồng coin hiện tại, và 
            // tìm xem phần còn lại (cur-coin) có thể được tạo từ bao nhiêu đồng
            if (cur >= coin) {
                dp[cur] = min(dp[cur], 1 + dp[cur-coin]);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}