#include <bits/stdc++.h>
#include <string>
using namespace std;

// Optimized: canonical keys
// time O(n*m), space: O(n*m)
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        array<int, 26> count = {0};
        for (char c : s) {
            count[c - 'a']++;
        }
        string key;
        for (int n : count) {
            key += to_string(n) + '#'; // tránh trường hợp đếm: ab = aaaaaaaaaaa
        }

        groups[key].push_back(s);
    }

    vector<vector<string>> res;
    for (auto& kv : groups) {
        res.push_back(move(kv.second));
    }
    return res;
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

        // auto it = mp.find(sorted);
        // if (it != mp.end()) {
        //     it->second.push_back(i);
        // }
        // else {
        //     mp[sorted].push_back(i);
        // }
        // có thể rút còn 1 dòng
        mp[sorted].push_back(i);
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