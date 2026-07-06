#include <bits/stdc++.h>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> st;   // các ngày đang CHỜ một ngày ấm hơn (lưu index)
    int n = temperatures.size();
    vector<int> res(n, 0);
    for (int i = 0; i < n; i++) {
        // hôm nay (i) ấm hơn (những) ngày đang chờ ở đỉnh?
        //   -> hôm nay CHÍNH LÀ ngày mà nó chờ. Ghi số ngày phải đợi rồi cho nó rời hàng.
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
            res[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);   // hôm nay cũng xếp vào hàng, chờ ngày ấm hơn của chính nó
    }

    return res;
}