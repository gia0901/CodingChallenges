#include <bits/stdc++.h>
using namespace std;

// Sort: time O(n log n), space O(n)
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());

    for (int i = 0; i < n; i++) {
        int left = intervals[i][0];
        int right = intervals[i][1];

        while (i < n-1 && right >= intervals[i+1][0]) {
            // lấy đầu mút bên phải rộng hơn
            right = max(right, intervals[i+1][1]);
            i++;
        }

        res.push_back({left, right});
    }

    return res;
}