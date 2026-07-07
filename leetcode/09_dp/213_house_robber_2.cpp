#include <bits/stdc++.h>
using namespace std;

// DP-1D: Time O(2n) -> O(n)
// Space O(1)
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);

    for (int i = 2; i < n-1; i++) {
        int total = max(nums[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = total;
    }
    int max1 = prev1;
    
    prev2 = 0;
    prev1 = nums[1];
    for (int i = 2; i < n; i++) {
        int total = max(nums[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = total;
    }
    int max2 = prev1;

    return max(max1, max2);
}

// DP-1D: Time O(2n) -> O(n)
// Space O(2n) -> O(n)
int DP_rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    vector<int> dp1(n, 0),
                dp2(n, 0);

    dp1[0] = nums[0];
    dp1[1] = max(nums[0],nums[1]);

    for (int i = 2; i < n-1; i++) {
        dp1[i] = max(nums[i] + dp1[i-2], dp1[i-1]);   
    }

    dp2[0] = 0; // từ bỏ căn nhà 0, để tính căn nhà n-1
    dp2[1] = nums[1];

    for (int i = 2; i < n; i++) {
        dp2[i] = max(nums[i] + dp2[i-2], dp2[i-1]);
    }

    return max(dp1[n-2], dp2[n-1]); 
}