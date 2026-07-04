#include <bits/stdc++.h>
using namespace std;

// Kadane — Time O(n), Space O(1)
// Ý tưởng: duyệt 1 lượt, tại mỗi i chỉ giữ "tổng lớn nhất của subarray KẾT THÚC tại i".
// Mỗi bước chỉ có 2 lựa chọn: bắt đầu subarray mới, hoặc nối dài subarray trước đó.
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int cur = nums[0];   // tổng lớn nhất của subarray kết thúc tại vị trí hiện tại
    int res = cur;       // đáp án toàn cục (khởi tạo = nums[0] để xử lý đúng mảng toàn số âm)

    for (int i = 1; i < n; i++) {
        // Nối dài (cur + nums[i]) hay bỏ hết bắt đầu lại từ nums[i]?
        // Nếu cur < 0 thì phần trước chỉ kéo xuống -> vứt, chọn nums[i].
        cur = max(nums[i], nums[i] + cur);
        res = max(res, cur);   // cập nhật đáp án toàn cục sau mỗi bước
    }

    return res;
}

// normal dp
    int DP_maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int dp[100005] = {0};
        dp[0] = nums[0];

        int res = dp[0];

        for (int i = 1; i < n; i++) {
            // nếu nums[i] hiện tại lớn hơn cả subarray tốt nhất phía trước + nums[i], ta chọn nums[i] luôn
            if (nums[i] > nums[i] + dp[i-1]) { 
                dp[i] = nums[i];
            }
            // subarray + nums[i] sẽ tạo thành subarray mới có sum tốt hơn nữa, nên ta lấy
            else {
                dp[i] = nums[i] + dp[i-1];
            }
            res = max(res, dp[i]);
        }

        return res;
    }