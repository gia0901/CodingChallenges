#include <bits/stdc++.h>
using namespace std;

bool isValid(string s) {
    vector<char> st;
    for (char c : s) {
        if (c == '(' || c=='[' || c=='{') {
            st.push_back(c);
        }
        else if (c == ')') {
            if (!st.empty() && st.back() == '(') {
                st.pop_back();
            } else {
                return false;
            }
        }
        else if (c == '}') {
            if (!st.empty() && st.back() == '{') {
                st.pop_back();
            } else {
                return false;
            }
        }
        else {
            if (!st.empty() && st.back() == '[') {
                st.pop_back();
            } else {
                return false;
            }
        }
    }
    return true;
}