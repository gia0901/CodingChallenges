#include <bits/stdc++.h>
using namespace std;

// Thuật toán euclid tìm ước chung lớn nhất
int GCD(int a, int b) {
    if (a == 0)
        return b;

    return GCD(b % a, a); // b % a sẽ luôn < a, lần đệ quy tiếp sẽ tự xếp (a,b) với a < b
}

int findGCD(vector<int>& nums) {
    int max = nums[0], min = nums[0];
    for (int num : nums) {
        max = num > max ? num : max;
        min = num < min ? num : min; 
    }

    return GCD(max, min);
}