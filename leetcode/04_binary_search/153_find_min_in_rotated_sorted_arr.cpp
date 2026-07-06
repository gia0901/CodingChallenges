#include <bits/stdc++.h>
using namespace std;

// Optimized — Time O(log n), Space O(1)
// So nums[mid] với nums[right] (mốc ổn định) để biết min nằm nửa nào:
//   nums[mid] > nums[right]  -> có "điểm gãy" trong (mid, right] -> min bên phải -> loại mid.
//   nums[mid] <= nums[right] -> (mid, right] không gãy -> min ở mid HOẶC bên trái -> GIỮ mid.
// mid là ứng viên đáp án nên nhánh giữ min phải là right=mid (KHÔNG mid-1, kẻo vứt mất min).
// Cặp bắt buộc: right=mid  +  while(left<right)  (dùng <= sẽ lặp vô hạn vì right=mid không co).
int findMin(vector<int>& nums) {
    int left = 0, right = nums.size()-1;
    while (left < right) {
        int mid = left + (right-left)/2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;        // min chắc chắn bên phải mid
        }
        else {
            right = mid;           // min ở mid hoặc bên trái, giữ mid lại
        }
    }
    return nums[left];             // left == right = vị trí min
}

// MY_findMin — bản đầu, so với nums[left]. Đúng nhưng rối hơn:
// phải thêm nhánh "cả đoạn đã sorted -> return nums[left]", nhiều exit point hơn.
// Giữ lại để đối chiếu; bản Optimized (so với right) gọn và dễ đúng hơn.
int MY_findMin(vector<int>& nums) {
    int left = 0, right = nums.size()-1;
    while (left <= right) {
        int mid = left + (right-left)/2;

        // nửa trái [left, mid] đang sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] < nums[right]) {
                return nums[left];   // cả đoạn [left,right] sorted -> min = nums[left]
            } else {
                left = mid + 1;      // có gãy bên phải -> min ở nửa phải
            }
        }
        // nửa trái không sorted -> min nằm trong [left, mid], giữ mid
        else {
            right = mid;
        }
    }
    return nums[right];
}