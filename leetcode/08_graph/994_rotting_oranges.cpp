#include <bits/stdc++.h>
using namespace std;


static constexpr int dr[4] = {0, 0, -1, +1};
static constexpr int dc[4] = {-1, +1, 0, 0};

// Multi-source BFS.
// - Vì sao BFS (không DFS)? Cần "số phút" = số đợt loang ĐỒNG THỜI từ mọi cam thối.
//   BFS lan theo đợt, mỗi đợt = 1 phút. DFS đi sâu 1 nhánh trước, ko phân biệt đợt này hay đợt tới.
// - Đa nguồn: nạp TẤT CẢ cam thối ban đầu (tầng 0) rồi loang song song.
// - Hết queue mà còn cam tươi => không thể thối hết => -1.
int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int minutes = 0;

    queue<pair<int,int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({i,j});
            }
        }
    }

    while (!q.empty()) {
        size_t rottenInThisTurn = q.size();
        for (size_t i = 0; i < rottenInThisTurn; i++) {
            auto rotten = q.front();
            q.pop();
            int r = rotten.first;
            int c = rotten.second;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if ((0 <= nr && nr < n) &&
                    (0 <= nc && nc < m) &&
                    (grid[nr][nc] == 1))
                {
                    grid[nr][nc] = 2; // bị thối lây từ [r,c]
                    q.push({nr,nc});  // xử lý cho turn sau
                }
            }
        }
        // nếu còn cam thối để xử lý tiếp thì mới tính là hợp lệ
        // tránh trường hợp đã xử lý xong hết (hoặc ko khả thi) thì cộng minutes lần cuối
        if (q.size()) minutes++; 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) return -1;
        }
    }

    return minutes;
}