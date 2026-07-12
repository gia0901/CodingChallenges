#include <bits/stdc++.h>
using namespace std;

// xét dần từ target -> 0
static void dfs(int start, int remaining, vector<int>& cur, vector<vector<int>>& res, vector<int>& candidates) {
    if (remaining <= 0) {
        if (remaining == 0) res.push_back(cur);
        return;
    }

    for (int i = start; i < candidates.size(); i++) {
        cur.push_back(candidates[i]);
        dfs(i, remaining - candidates[i], cur, res, candidates);
        cur.pop_back();
    }
}


// xét dần từ 0 -> target
static void MY_dfs(int start, long long sum, int target, vector<int>& cur, vector<vector<int>>& res, vector<int>& candidates) {
    if (sum >= target) {
        if (sum == target) res.push_back(cur);
        return;
    }
    
    for (int i = start; i < candidates.size(); i++) {
        cur.push_back(candidates[i]); // có thể dùng lại nhiều lần
        MY_dfs(i, sum + candidates[i], target, cur, res, candidates);
        cur.pop_back(); // sum đã >= target, bỏ số i và xét đến tổ hợp tiếp theo
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> cur;

    //MY_dfs(0, 0, target, cur, res, candidates);
    dfs(0, target, cur, res, candidates);

    return res;
}