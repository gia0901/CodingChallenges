#include <bits/stdc++.h>
using namespace std;

// Optimized
// Time O(n log M), M = max_pile: log M bước binary search trên dải tốc độ [1, M],
//   mỗi bước quét n đống để tính số giờ. (Lưu ý: log theo M, không phải theo n.)
// Space O(1): không dùng gì để chứa
int minEatingSpeed(vector<int>& piles, int h) {
    int min_k = 1, max_k = *max_element(piles.begin(),piles.end());

    auto countHours = [&](int k) {
        long long total = 0;
        for (int p : piles) {
            if (k >= p) total++;
            else if (p % k == 0) total += p/k;
            else total += p/k + 1;
        }
        return total;
    };
    int res = max_k;
    while (min_k <= max_k) {
        int mid_k = min_k + (max_k - min_k)/2;
        // k hiện tại ăn kịp trong h giờ
        // khoan kết luận vội, binary search tìm tiếp xem có k nào bé hơn vẫn thỏa điều kiện không 
        if (countHours(mid_k) <= h) {
            res = min(res, mid_k);
            max_k = mid_k - 1;
        }
        else {
            min_k = mid_k + 1;
        }
    }

    return res;
}

// Chậm: vì vòng while trong lặp đơn điệu
int SLOW_minEatingSpeed(vector<int>& piles, int h) {
    int min_k = 1, max_k = piles[0];
    for (int p : piles) {
        if (p > max_k) max_k = p;
        if (p < min_k) min_k = p;
    }

    auto countHours = [&](int k) {
        long long total = 0;
        for (int p : piles) {
            if (k >= p)
                total++;
            else if (p % k == 0)
                total += p/k;
            else
                total += p/k + 1;
        }
        return total;
    };

    int res = max_k;

    while (min_k <= max_k) {
        int mid = min_k + (max_k - min_k)/2;
        long long hoursNeeded = countHours(mid);
        
        // ăn kịp trong h giờ, cố gắng ăn chậm từng chút mà vẫn thỏa
        if (hoursNeeded == h) {
            while (mid && countHours(mid) == h) {
                res = min(res, mid);
                mid--;
            }
            return res;
        }
        // ăn nhanh hơn trong h giờ, cố gắng thử ăn ít lại xem vẫn kịp h giờ hay không
        else if (hoursNeeded < h) {
            res = min(res, mid);
            max_k = mid-1;
        }
        // ăn ko kịp trong h giờ, cần ăn nhanh hơn
        else { 
            min_k = mid+1;
        }
    }

    return res;
}

int main() {
    vector<int> piles{2,2};
    int res = minEatingSpeed(piles, 4);
}