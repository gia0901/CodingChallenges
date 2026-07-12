#include <bits/stdc++.h>
using namespace std;

/**
 * @brief   Bubble sort | O(n) best / O(n^2) avg-worst | Space O(1) | STABLE
 * @details Mỗi lượt "nổi" phần tử lớn nhất về cuối, thu hẹp biên phải đã sort dần.
 */
void bubble_sort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n-1; i > 0; i--) {
        bool swapped = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {   // dấu '>' nghiêm ngặt: phần tử bằng nhau KHÔNG swap -> stable
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) return;   // 1 lượt không swap = đã sorted -> dừng sớm (đây là best case O(n))
    }
}

/**
 * @brief   Selection sort | O(n^2) mọi trường hợp (không early-exit) | Space O(1) | KHÔNG stable
 * @details Mỗi bước chọn min của đoạn phải chưa sort, đưa về vị trí i.
 * @note    Ưu: swap <= n-1 lần -> lợi khi swap object nặng.
 *          Nhược: KHÔNG stable (xem swap dưới); không tối ưu về O(n) dù mảng đã sort.
 */
void selection_sort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // swap có thể nhảy 1 phần tử qua phần tử bằng khóa -> KHÔNG stable. VD [4a,4b,3] -> [3,4b,4a]
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

int main() {
    vector<int> arr{2,5,1,6,4,3,3,2};
    //bubble_sort(arr);
    selection_sort(arr);


    for (int n : arr) cout << n << ' '; cout << endl;
}
