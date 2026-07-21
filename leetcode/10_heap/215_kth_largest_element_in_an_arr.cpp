#include <bits/stdc++.h>
#include <queue>
using namespace std;

// Pattern: MIN-HEAP kích thước k. Time O(n log k), Space O(k).
// Heap luôn giữ k phần tử LỚN NHẤT đã thấy -> top() (nhỏ nhất trong đó) = phần tử lớn thứ k.
// Ưu điểm: chỉ tốn O(k) bộ nhớ -> hợp streaming / n cực lớn không giữ hết được.
int findKthLargest(vector<int>& nums, int k) {
    // greater<int> -> MIN-heap (top là phần tử nhỏ nhất)
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int num : nums) {
        if ((int)pq.size() < k) {
            pq.push(num);                 // chưa đủ k -> cứ nạp
        }
        else if (pq.top() < num) {        // đủ k rồi: num lớn hơn "kẻ yếu nhất" thì thay
            pq.pop();                     // bỏ phần tử nhỏ nhất hiện tại
            pq.push(num);
        }
    }

    return pq.top();   // phần tử lớn thứ k
}

int main() {
    vector<int> nums{3,2,1,5,6,4};
    cout << findKthLargest(nums, 2) << endl;
}