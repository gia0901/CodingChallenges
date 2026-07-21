#include <bits/stdc++.h>
using namespace std;

int maxProduct(vector<int>& nums) {
    int n = nums.size();
    vector<pair<int,int>> dp(n);

    dp[0] = {nums[0], nums[0]};
    int res = 0;
    for (int i = 1; i < n; i++) {
        int val1 = nums[i] * dp[i-1].first;
        int val2 = nums[i] * dp[i-1].second;

        dp[i].first = min({dp[i-1].first * val1})
        
    }
}