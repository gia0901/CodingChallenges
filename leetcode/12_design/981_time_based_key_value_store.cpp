#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// Optimized
class TimeMap {
    // {key, vector< timestamp, value >}
    unordered_map<string, vector<pair<int,string>>> mp;
public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        auto it = mp.find(key);
        if (it == mp.end()) return "";

        const auto& vec = it->second;
        // dùng upper_bound thay vì binary search bằng tay
        auto best = upper_bound(vec.begin(), vec.end(), timestamp,
                                [](int t, const pair<int, string>& p) {
                                    return t < p.first;
                                });

        // mọi timestamp đều > target      
        if (best == vec.begin())
            return "";

        // phần tử ngay trước = lớn nhất <= target
        return prev(best)->second;
    }
};


// My solution
class MyTimeMap {
    // {key, vector< timestamp, value >}
    unordered_map<string, vector<pair<int,string>>> mp;
public:
    MyTimeMap() {}
    
    void set(string key, string value, int timestamp) {
        // theo đề timestamp strictly increasing, nên ta ko cần check duplicate
        mp[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        vector<pair<int,string>>& vec = mp[key];
        // binary search tìm timestamp_prev <= timestamp
        int left = 0, right = vec.size()-1;
        int best = -1;

        while (left <= right) {
            int mid = left + (right - left)/2;
            if (vec[mid].first == timestamp) {
                return vec[mid].second;
            }
            else if (vec[mid].first < timestamp) {
                best = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        if (best != -1) return vec[best].second;
        return "";
    }
};