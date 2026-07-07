#include <bits/stdc++.h>
using namespace std;

// DP 1D: Time O(n), Space O(1) - sử dụng 2 biến duy trì
int rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];

    int twoStepAway = nums[0];
    int oneStepAway = max(nums[0], nums[1]);

    for (size_t i = 2; i < nums.size(); i++) {
        int total = max(nums[i] + twoStepAway, oneStepAway);
        twoStepAway = oneStepAway;
        oneStepAway = total;
    }

    return oneStepAway;
}

// DP 1D: Time O(n), Space O(n)
int DP_rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    
    vector<int> dp(nums.size(), 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (size_t i = 2; i < nums.size(); i++) {
        dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
    }

    return dp[nums.size()-1];
}