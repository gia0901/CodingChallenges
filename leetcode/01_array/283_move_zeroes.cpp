#include <bits/stdc++.h>
using namespace std;

// Fast/slow pointers, xử lý in-place, giữ nguyên thứ tự các số khác 0.
// - slow: vị trí sẽ đặt số khác 0 tiếp theo (mọi thứ trước slow đã "gọn").
// - fast: quét cả mảng để tìm số khác 0.
// Ý tưởng: dồn các số khác 0 lên đầu theo đúng thứ tự -> các số 0 tự trôi về cuối.
void moveZeroes(vector<int>& nums) {
    int n = nums.size();
    int slow = 0;

    for (int fast = 0; fast < n; fast++) {
        if (nums[fast]) {                    // gặp số khác 0
            swap(nums[slow], nums[fast]);    // đưa nó về vị trí slow
            slow++;                          // chốt vị trí, chờ số khác 0 kế tiếp
        }
        // nums[fast] == 0 -> bỏ qua, slow đứng yên chờ số khác 0 tới lấp chỗ
    }
}
// Time O(n), Space O(1).


// Tạo mảng mới và gán lại
// Time O(n), Space O(N)
void ARR_moveZeroes(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 0);
    int cur_idx = 0;
    
    for (int x : nums) {
        if (x) res[cur_idx++] = n;
    }
    nums = res;
}