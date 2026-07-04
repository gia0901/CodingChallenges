#include <bits/stdc++.h>
using namespace std;

// set: Time O(n), Space O(n)
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> se;
    for (int n : nums) {
        if (se.count(n)) {
            return true;
        }
        se.insert(n);
    }
    return false;
}

// sort + iteration: O(n log n), Space O(log n) -stack cho quicksort của std::sort
bool SORT_containsDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i-1]) return true;
    }
    return false;
}