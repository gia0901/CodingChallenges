#include <bits/stdc++.h>
using namespace std;

// Stack (LIFO): ngoặc đóng phải khớp ngoặc mở GẦN NHẤT chưa đóng.
// Time O(n), Space O(n) - worst case toàn ngoặc mở, vd "(((("
bool isValid(string s) {
    vector<char> st;                     // stack các ngoặc mở đang chờ đóng
    unordered_map<char,char> pair = {{')','('}, {']','['}, {'}','{'}};  // đóng -> mở

    for (char c : s) {
        if (c=='(' || c=='[' || c=='{') {
            st.push_back(c);             // ngoặc mở: đẩy vào chờ
        }
        else {
            // ngoặc đóng: stack rỗng (không có gì để khớp) HOẶC đỉnh sai loại -> invalid
            if (!st.empty() && st.back() == pair[c]) {
                st.pop_back();           // khớp -> bỏ ngoặc mở tương ứng, đi tiếp
            }
            else {
                return false;
            }
        }
    }
    return st.empty();                   // còn ngoặc mở dư -> invalid; rỗng -> hợp lệ
}