#include <bits/stdc++.h>
using namespace std;

static constexpr int dr[4] = {-1, +1, 0, 0};
static constexpr int dc[4] = {0, 0, -1, +1};

int dfs(int r, int c, vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();

    if ((r < 0 || r >= n) ||
        (c < 0 || c >= m) ||
        (grid[r][c] == 0)) {
        return 0;
    }

    grid[r][c] = 0;

    /* Dùng for hoặc return trực tiếp
    int maxArea = 1;
    for (int i = 0; i < 4; i++) {
        maxArea += dfs(r + dr[i], c + dc[i], grid);
    }
    return maxArea;
    */

    return 1 + (dfs(r + dr[0], c + dc[0], grid) +
                dfs(r + dr[1], c + dc[1], grid) +
                dfs(r + dr[2], c + dc[2], grid) +
                dfs(r + dr[3], c + dc[3], grid));
}

int bfs(int r, int c, vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> q;
    q.push({r,c});
    grid[r][c] = 0;
    int area = 1;
    
    while (!q.empty()) {
        auto pos = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = pos.first + dr[i];
            int nc = pos.second + dc[i];

            if ((0 <= nr && nr < n) &&
                (0 <= nc && nc < m) &&
                (grid[nr][nc] == 1)) {
                q.push({nr,nc});
                grid[nr][nc] = 0; // visited
                area++;
            }
        }
    }
    return area;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = 0;
    int n = grid.size(), m = grid[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                //maxArea = max(maxArea, bfs(i, j, grid));
                maxArea = max(maxArea, dfs(i,j,grid));
            }
        }
    }

    return maxArea;
}