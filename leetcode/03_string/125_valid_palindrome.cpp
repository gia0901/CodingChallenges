#include <bits/stdc++.h>
using namespace std;


// Loại bỏ ký tự ko phải ascii trước
// time O(n), space O(n)
bool isPalindrome(string s) {
    string temp;
    for (char c : s) {
        if (isalpha(c)) temp.push_back(tolower(c));
        else if (isdigit(c)) temp.push_back(c);
    }
    
    int left = 0, right = temp.length()-1;
    while (left < right) {
        if (temp[left] != temp[right]) return false;
        left++,right--;
    }
    return true;
}


// Xử lý string gốc, time O(n), space O(1)

#define IS_ASCII(c) (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
bool MANUAL_isPalindrome(string s) {
    int n = s.length();
    int left = 0, right = n-1;


    while (left < right) {
        while (left < n && !IS_ASCII(s[left])) {
            left++;
        }
        while (right >= 0 && !IS_ASCII(s[right])) {
            right--;
        }

        if (left > right) return true;        
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++, right--;
    }
    return true;
}

int main() {
    bool res = isPalindrome("0P");
    cout << res << endl;
}