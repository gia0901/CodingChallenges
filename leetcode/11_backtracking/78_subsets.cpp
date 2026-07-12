#include <bits/stdc++.h>
using namespace std;

// ===== Template B: vòng for "chọn phần tử tiếp theo" (template mẹ của cả cụm backtracking) =====
// Hợp đồng mỗi node: (1) in ra chính mình, (2) sinh mọi subset mở rộng thêm 1 phần tử index LỚN HƠN.
// Câu hỏi mỗi tầng: "nối thêm phần tử nào tiếp theo?" -> thu kết quả ở MỌI node.
static void dfs(int start, vector<int>& cur, vector<int>& nums, vector<vector<int>>& res) {
    res.push_back(cur);   // cur luôn là 1 subset hoàn chỉnh -> thu ngay (kể cả [] rỗng)

    // thử lần lượt từng phần tử khả dụng làm "phần tử kế tiếp" của prefix cur
    for (int i = start; i < nums.size(); i++) {
        cur.push_back(nums[i]);          // choose: gắn tạm nums[i]
        dfs(i+1, cur, nums, res);        // explore: i+1 => chỉ chọn index LỚN HƠN -> không trùng/hoán vị
        cur.pop_back();                  // un-choose: gỡ ra để prefix sạch trước khi thử nums[i+1]
    }
}


// ===== Template A: take / not-take (quyết định nhị phân cho TỪNG phần tử) =====
// Câu hỏi mỗi tầng: "phần tử nums[idx] này - LẤY hay KHÔNG?" -> cây nhị phân, sâu đúng n.
// Chỉ thu kết quả ở LÁ (idx == n), khi đã quyết định xong mọi phần tử. Có 2^n lá = 2^n subset.
static void TN_dfs(int idx, vector<int>& cur, vector<int>& nums, vector<vector<int>>& res) {
    if (idx >= nums.size()) {
        res.push_back(cur);   // đã quyết định hết -> cur là 1 subset hoàn chỉnh
        return;
    }

    // Nhánh 1: LẤY nums[idx]
    cur.push_back(nums[idx]);
    TN_dfs(idx+1, cur, nums, res);
    cur.pop_back();               // hoàn tác trước khi sang nhánh "không lấy"
    // Nhánh 2: KHÔNG lấy nums[idx]
    TN_dfs(idx+1, cur, nums, res);
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    dfs(0, cur, nums, res);

    return res;
}