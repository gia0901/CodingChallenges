#include <bits/stdc++.h>
using namespace std;



bool isHappy(int n) {
    unordered_set<int> seen;
    auto calSquare = [](int n) {
        long long res = 0;
        while (n) {
            int d = n % 10;
            res += d*d;
            n /= 10;
        }
        return res;
    }; 
    
    while (seen.count(n) == 0) {
        seen.insert(n);
        n = calSquare(n);
        if (n == 1) return true;
    }
    return false;
}