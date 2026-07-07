#include <bits/stdc++.h>
using namespace std;

class BFS_Solution {
private:
    static constexpr int dr[4] = {-1, +1, 0 , 0};
    static constexpr int dc[4] = {0, 0, -1, +1};
    int n;
    int m;

    // time: O(m*n), space O(m*n) - toàn bộ grid đều là đất liền
    void bfs(int r, int c, vector<vector<char>>& grid, vector<vector<int>>& visited) {
        queue<pair<int,int>> q;
        q.push({r,c});  // tọa độ đầu tiên là đất liền
        visited[r][c] = 1;

        // bfs rộng ra 4 phía, nếu tọa độ là đất liền
        // thì đẩy vào queue => xử lý đến khi empty 
        // (= toàn bộ tọa độ liền kề tạo thành đảo)
        while (!q.empty()) {
            auto pos = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = pos.first + dr[i];
                int nc = pos.second + dc[i];

                if ((0 <= nr && nr < n) &&
                    (0 <= nc && nc < m) &&
                    (grid[nr][nc] == '1') &&
                    (visited[nr][nc] == 0)) {
                    q.push({nr,nc});
                    visited[nr][nc] = 1;
                }
            }
        }
    }


public:
    int numIslands(vector<vector<char>>& grid) {
        int islands = 0;
        n = grid.size();
        m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == '1' && visited[r][c] == 0) {
                    bfs(r, c, grid, visited);
                    islands++;
                }
            }
        }

        return islands;
    }

};


class DFS_Solution {
public:

static constexpr int dx[4] = {-1, +1, 0, 0};
static constexpr int dy[4] = {0, 0, -1, +1};
int n;
int m;

void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<int>>& vis) {
    if (vis[i][j]) {
        return;
    }
    vis[i][j] = 1;

    for (int dir = 0; dir < 4; dir++) {
        int new_x = i + dx[dir];
        int new_y = j + dy[dir];

        if ((0 <= new_x && new_x < n) &&
            (0 <= new_y && new_y < m) &&
            (grid[new_x][new_y] == '1')) {
            dfs(new_x, new_y, grid, vis);
        }
    }
};

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    n = grid.size();
    m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m,0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1' && vis[i][j] == 0) {
                count++;
                dfs(i, j, grid, vis);
            }
        }
    }

    return count;
}
};

int main() {
    BFS_Solution solution;

}