#include <bits/stdc++.h>
using namespace std;

int maxArea(vector<int>& height) {
    int res = 0;
    int left = 0, right = height.size()-1;
    while (left < right) {
        int area = (right-left) * min(height[left],height[right]);
        res = max(res, area);

        // Luôn dời con trỏ ở phía cột THẤP hơn.
        // Vì diện tích bị giới hạn bởi cột thấp: giữ nó lại mà thu hẹp chiều rộng
        // thì chỉ nhỏ đi. Bỏ cột thấp, hy vọng gặp cột cao hơn -> diện tích to hơn.
        if (height[left] < height[right]) {
            left++;
        }
        else {
            right--;
        }
    }

    return res;
}