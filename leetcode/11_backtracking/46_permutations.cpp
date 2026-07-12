#include <bits/stdc++.h>
using namespace std;

// Big-O:  Time O(n * n!)  |  Space O(n) auxiliary  (O(n * n!) nếu tính output)
//   - n!  = số hoán vị (n lựa chọn cho vị trí 0, n-1 cho vị trí 1, ...).
//   - * n = chi phí copy mỗi hoán vị (n phần tử) vào res.
//   - Space O(n): độ sâu đệ quy = n; swap tại chỗ nên KHÔNG tốn mảng phụ (cur/visited).
//
// Swap-based permutation: hoán vị TẠI CHỖ, không cần mảng cur / visited.
// pos = VỊ TRÍ đang cố định (số vị trí đã chốt);  i = LỰA CHỌN phần tử nào đặt vào vị trí pos.
// Mỗi tầng chốt đúng 1 vị trí -> luôn đệ quy pos+1 (KHÔNG phải i+1: i chỉ là lựa chọn, không phải vị trí).
static void dfs(int pos, vector<vector<int>>& res, vector<int>& nums)
{
    if (pos >= nums.size()) {   // đã chốt hết mọi vị trí -> nums là 1 hoán vị hoàn chỉnh
        res.push_back(nums);
        return;
    }

    // thử đặt lần lượt từng phần tử còn lại (nums[i], i >= pos) vào vị trí pos
    for (int i = pos; i < nums.size(); i++) {
        swap(nums[pos], nums[i]);   // choose: đưa nums[i] về vị trí pos
        dfs(pos + 1, res, nums);    // explore: cố định vị trí kế
        swap(nums[pos], nums[i]);   // un-choose: trả mảng về nguyên trạng trước khi thử i kế
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;

    dfs(0, res, nums);

    return res;
}