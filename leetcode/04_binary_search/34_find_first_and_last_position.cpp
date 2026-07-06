#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<int> searchRange(vector<int>& nums, int target) {
    // Shortest: lower_bound + upper_bound
    auto lo = lower_bound(nums.begin(), nums.end(), target);
    
    // phần tử đầu tiên >= target không tồn tại hoặc > target
    // ko có nghĩa lý gì khi kiểm tra tiếp
    if (lo == nums.end() || *lo != target)
        return {-1, -1};

    // phía trên lo đã chạm target thỏa, upper_bound thì > target nên trước target 1 bước
    // nên lùi 1 bước luôn luôn đúng, return thẳng
    auto hi = upper_bound(nums.begin(), nums.end(), target);
    return {int(lo - nums.begin()), (int)(hi - nums.begin())-1};



    // Manual
    // int x = findBound(nums, target, true);
    // int y = findBound(nums, target, false);
    // return {x,y};
}

// MANUAL
static int findBound(vector<int>& nums, int target, bool leftMost) {
    int left = 0, right = nums.size()-1;
    int x = -1;
    while (left <= right) {
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            x = mid;
            // hiện tại nums[mid] đã thỏa
            if (leftMost) right = mid-1; // cố gắng tìm thêm nums thỏa phía bên trái
            else left = mid+1; // cố gắng tìm thêm nums thỏa phía bên phải
        }
        else if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return x;
}
int main() {

}