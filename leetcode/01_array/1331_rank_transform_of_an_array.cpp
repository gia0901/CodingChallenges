#include <bits/stdc++.h>
using namespace std;

// map
vector<int> arrayRankTransform(vector<int>& arr) {
    map<int,vector<int>> mp;
    for (int i = 0; i < arr.size(); i++) {
        mp[arr[i]].push_back(i);
    }

    vector<int> res(arr.size());
    int rank = 1;
    for (auto& kv : mp) {
        for (int idx : kv.second) {
            res[idx] = rank;
        }
        rank++;
    }

    return res;
}