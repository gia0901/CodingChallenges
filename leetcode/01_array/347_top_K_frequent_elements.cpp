#include <bits/stdc++.h>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    int seen[100005] = {0};
    for (int num : nums) {
        seen[num]++;
    }

    sort(seen, seen + 100005);
    vector<int> res;
    
}