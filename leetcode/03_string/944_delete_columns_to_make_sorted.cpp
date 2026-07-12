#include <bits/stdc++.h>
using namespace std;

int minDeletionSize(vector<string>& strs) {
    int row = strs.size();
    int col = strs[0].size();

    int res = 0;

    for (int c = 0; c < col; c++) {
        for (int r = 0; r < row; r++) {
            if (r > 0 && strs[r][c] < strs[r-1][c]) {
                res++;
                break;
            }
        }
    }

    return res;
}
int main() {
    vector<string> strs{"cba","daf","ghi"};
    cout << minDeletionSize(strs) << endl;
}