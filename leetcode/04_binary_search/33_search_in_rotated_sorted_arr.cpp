#include <bits/stdc++.h>
using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size()-1;

    while (left <= right) {
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            return mid;
        }
        // left portion
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        // right portion
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid+1;
            } else {
                right = mid-1;                
            }
        }
    }
    return -1;
}
int main() {
    vector<int> nums{3,5,1};
    cout << search(nums, 3) << endl;
}