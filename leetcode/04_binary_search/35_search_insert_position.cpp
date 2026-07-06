#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// lower_bound: tìm phần tử đầu tiên >= target
int searchInsert(vector<int>& nums, int target) {
    return *lower_bound(nums.begin(),nums.end(), target);
}

// manually
int BS_searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size()-1;

    while (left <= right) {
        int mid = left + (right-left)/2;
        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}