#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size()-1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left+1, right+1};
        }
        else if (sum < target) {
            left++;
        }
        else {
            right--;
        }
    }
    return {};
}

// 2. Hashing
vector<int> Hash_twoSum(vector<int>& numbers, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < numbers.size(); i++) {
        if (mp.count(target - numbers[i])) {
            return {mp[target-numbers[i]]+1, i+1};
        }
        mp[numbers[i]] = i;
    }
    return {};
}