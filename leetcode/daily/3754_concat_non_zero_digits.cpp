#include <bits/stdc++.h>
using namespace std;

long long sumAndMultiply(int n) {
    int sum = 0;
    string numStr;

    while (n) {
        if (n % 10 > 0) {
            numStr.push_back((n % 10) + '0');
            sum += n % 10;
        }
        n /= 10;
    }
    long long num = 0;
    for (auto it = numStr.rbegin(); it != numStr.rend(); it++) {
        num = num*10 + (*it - '0');
    }

    return num * sum;
}

int main() {
    long long res = sumAndMultiply(10203004);
    cout << res << endl;
}