#include <bits/stdc++.h>
using namespace std;

// Optimized: canonical keys
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    auto isAnagram = [&](const string& str) {
        array<int,26> freq;
        for (char c : str) {
            freq[c]++;
        }

        
    }

    for (const string& str : strs) {

    }
}

// sort + hashmap: time O(n * mlogm), space O(m * n)
// m: str dài nhất, n: số lượng str
vector<vector<string>> SORT_groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<int>> mp;
    int n =  strs.size();
    for (int i = 0; i < n; i++) {
        string sorted{strs[i]};
        sort(sorted.begin(), sorted.end());

        auto it = mp.find(sorted);
        if (it != mp.end()) {
            it->second.push_back(i);
        }
        else {
            mp[sorted].push_back(i);
        }
    }

    for (auto& kv : mp) {
        vector<string> cur;
        for (int idx : kv.second) {
            cur.push_back(strs[idx]);
        }
        res.push_back(cur);
    }

    return res;
}