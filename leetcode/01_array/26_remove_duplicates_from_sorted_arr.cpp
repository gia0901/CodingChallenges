#include <bits/stdc++.h>
using namespace std;

// Optimized: Time O(N), Space O(1)
    int TP_removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int slow = 0;

        for (int fast = 1; fast < n; fast++) {
            if (nums[fast] != nums[slow]) {
                nums[slow+1] = nums[fast];
                slow++;
            }
        }

        return slow+1;
    }

// Set: Time O(n log n), Space O(n)
    int removeDuplicates(vector<int>& nums) {
        set<int> se;
        for (int n : nums) {
            se.insert(n);
        }

        int curIdx = 0;
        for (int n : se) {
            nums[curIdx++] = n;
        }

        return se.size();
    }