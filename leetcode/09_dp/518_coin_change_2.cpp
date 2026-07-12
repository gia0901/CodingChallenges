#include <bits/stdc++.h>
using namespace std;

// Counting DP (unbounded knapsack - đếm số TỔ HỢP). Time O(amount * #coins), Space O(amount).
// state: dp[i] = số cách tạo ra số tiền i bằng các coin đã xét.
//
// unsigned long long (KHÔNG dùng int): đáp án cuối dp[amount] vừa int, NHƯNG dp[i] trung gian
// có thể bùng nổ tổ hợp -> tràn int (signed overflow = UB). unsigned: tràn là wrap-around
// định nghĩa rõ, không UB; và các giá trị trung gian dù wrap cũng không sai đáp án cuối.
int change(int amount, vector<int>& coins) {
    vector<unsigned long long> dp(amount+1, 0);

    dp[0] = 1; // base: đúng 1 cách tạo ra 0 (không lấy coin nào) -> nền để cộng dồn

    // coin ở vòng NGOÀI => đếm TỔ HỢP: {1,2} và {2,1} tính là 1 cách.
    // (đảo lại - amount ngoài, coin trong - sẽ đếm HOÁN VỊ, sai đề. Đó là bài 377.)
    for (int coin : coins) {
        // i TĂNG dần + cập nhật in-place => 1 coin dùng lại vô hạn lần (unbounded).
        // (0/1 knapsack - mỗi món 1 lần - thì i phải chạy GIẢM dần.)
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];   // thêm coin này vào mọi cách tạo (i - coin)
        }
    }

    return (int)dp[amount];   // đáp án cuối vừa int theo bảo đảm của đề
}