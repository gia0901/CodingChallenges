#include <bits/stdc++.h>
using namespace std;

// LIS pattern
// Time O(n^2)
// Space O(n)
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 0);

    int res = 1;
    dp[0] = 1;

    for (int i = 1; i < n; i++) {
        int lis = 1;
        for (int k = i-1; k >= 0; k--) {
            if (nums[i] > nums[k]) {
                lis = max(lis, dp[k] + 1);
            }
        }
        dp[i] = lis;
        res = max(res, dp[i]);
    }

    return res;
}