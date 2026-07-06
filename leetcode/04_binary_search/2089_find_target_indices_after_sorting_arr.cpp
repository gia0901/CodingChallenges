#include <bits/stdc++.h>
using namespace std;

// Optimized - counting: Time O(n), Space O(1)
vector<int> targetIndices(vector<int>& nums, int target) {
    int lessThanTarget = 0;
    int countTarget = 0;

    for (int n : nums) {
        if (n < target) lessThanTarget++;
        if (n == target) countTarget++;
    }

    vector<int> res;
    for (int i = 0; i < countTarget; i++)
        res.push_back(lessThanTarget + i);

    return res;
}


// Sorting: Time O(n log n), Space O(1)
// Nhánh nào cũng co (mid±1) → <=. Có nhánh giữ mid (right=mid) → <.
static int findBound(vector<int>& nums, int target, bool leftMost) {
    int bound = -1;
    int left = 0, right = nums.size()-1;

    while (left <= right) {
        int mid = left + (right-left)/2;
        if (nums[mid] == target) {
            bound = mid;
            if (leftMost) right = mid - 1;
            else          left = mid + 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return bound;
}

vector<int> SORT_targetIndices(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int lo = findBound(nums, target, true);
    int hi = findBound(nums, target, false);

    if (lo == -1) // nếu bound dưới đã ko tồn tại, thì trên cũng sẽ ko tồn tại 
        return {};
    vector<int>res;
    for (int i = lo; i <= hi; i++) res.push_back(i);
    return res;
}

int main() {
    vector<int> nums{};
    auto res = targetIndices(nums, 1);

    for (int n : res) cout << n << ' ';
}