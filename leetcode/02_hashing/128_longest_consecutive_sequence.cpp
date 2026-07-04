#include <bits/stdc++.h>
using namespace std;

// Time O(n), Space O(n)  (dựa trên unordered_set: count/insert O(1) trung bình).
//   - Vòng for ngoài lướt n phần tử -> O(n).
//   - Các vòng while cộng lại chạy đúng n bước (mỗi số được đếm 1 lần) -> O(n).
//   Tổng 2n -> O(n). Lưu ý: n là SỐ PHẦN TỬ, không phụ thuộc số chuỗi.
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> seen;
    int res = 0;

    for (int n : nums) {
        seen.insert(n);
    }

    for (int x : seen) {
        // Chỉ bắt đầu đếm từ ĐẦU chuỗi: x là đầu chuỗi khi x-1 không có trong set.
        // Bỏ qua các x không phải đầu chuỗi -> mỗi số chỉ được đếm 1 lần -> O(n).
        if (seen.count(x-1)) {
            continue;
        }

        int count = 0;
        while (seen.count(x)) {
            count++;
            x++;
        }
        res = max(res, count);
    }


    return res;
}

int main() {
    vector<int>nums{100,4,200,1,3,2};
    int res = longestConsecutive(nums);

    cout << res << endl;
}