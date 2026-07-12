#include <bits/stdc++.h>
using namespace std;

// Mỗi phần tử dùng tối đa 1 lần (dfs i+1), input CÓ trùng -> phải skip để không sinh tổ hợp lặp.
// Cần sort trước (ở hàm gọi) để các phần tử trùng nằm KỀ nhau thì mới so được candidates[i]==candidates[i-1].
static void dfs(int start, int remaining, vector<int>& cur, vector<vector<int>>& res, vector<int>& candidates) {
    if (remaining == 0) { res.push_back(cur); return; }
    if (remaining < 0) { return; }

    for (int i = start; i < candidates.size(); i++) {
        // skip duplicate = skip ANH EM CÙNG TẦNG (i > start), KHÔNG skip theo chiều sâu.
        // i == start: phần tử đầu của nhóm trùng tại tầng này -> vẫn cho chọn.
        // i  > start & trùng phần tử liền trước -> sibling trùng -> bỏ (tổ hợp đã sinh ở nhánh trước).
        if (i > start && candidates[i] == candidates[i-1])
            continue;
        cur.push_back(candidates[i]);
        dfs(i+1, remaining - candidates[i], cur, res, candidates);  // i+1: không dùng lại phần tử này
        cur.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> cur;

    sort(candidates.begin(), candidates.end());

    dfs(0, target, cur, res, candidates);

    return res;
}