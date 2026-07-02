# 8. Graph ★★★☆☆

Ba công cụ đủ cho hầu hết bài: **BFS/DFS** (duyệt), **topological sort** (thứ tự phụ thuộc), **union-find** (nhóm liên thông).

## Các pattern cốt lõi (skeleton C++)

### Pattern A — BFS trên grid
```cpp
int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
queue<pair<int,int>> q;
q.push({sr, sc});
vis[sr][sc] = true;                 // đánh dấu khi PUSH, không phải khi pop
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr>=0 && nr<m && nc>=0 && nc<n && !vis[nr][nc] && valid(nr,nc)) {
            vis[nr][nc] = true;
            q.push({nr, nc});
        }
    }
}
```

### Pattern B — Topological sort (Kahn)
```cpp
vector<int> indeg(n, 0);
for (auto& [u, v] : edges) indeg[v]++;      // cạnh u -> v
queue<int> q;
for (int i = 0; i < n; ++i) if (!indeg[i]) q.push(i);
vector<int> order;
while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);
    for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
}
// order.size() < n  =>  có chu trình
```

### Pattern C — Union-Find (DSU, path compression)
```cpp
vector<int> parent(n);
iota(parent.begin(), parent.end(), 0);
function<int(int)> find = [&](int x){
    return parent[x] == x ? x : parent[x] = find(parent[x]);
};
auto unite = [&](int a, int b){ parent[find(a)] = find(b); };
```

## Bài cốt lõi (6 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Number of Islands | A | Time O(m·n) |
| 2 | Rotting Oranges | A (multi-source) | Time O(m·n) |
| 3 | Clone Graph | A/DFS + map | Time O(V+E) |
| 4 | Course Schedule | B | Time O(V+E) |
| 5 | Surrounded Regions | DFS từ biên | Time O(m·n) |
| 6 | Number of Connected Components | C | Time O(V·α + E) |

### 1. Number of Islands
> Đếm cụm ô `'1'` liền kề. Mỗi lần gặp `'1'` chưa thăm → +1 và BFS/DFS làm chìm cả cụm.

### 2. Rotting Oranges
> BFS **đa nguồn**: nạp mọi cam thối vào queue ban đầu, lan theo tầng = số phút.

### 3. Clone Graph
> DFS/BFS + `unordered_map<Node*,Node*>` ánh xạ gốc→bản sao để tránh clone lại.

### 4. Course Schedule
> Có thể học hết môn (đồ thị không chu trình)? Topo sort — nếu xếp đủ `n` node thì được.

### 5. Surrounded Regions
> Vùng `'O'` chạm biên thì an toàn; DFS từ **biên** đánh dấu an toàn, phần còn lại bị lật.

### 6. Number of Connected Components
> Union mọi cạnh; đếm số root phân biệt = số thành phần.

## Pitfall C++ hay gặp

- **Đánh dấu `visited` khi PUSH** (không phải khi pop) → tránh cùng một node vào queue nhiều lần.
- **DFS đệ quy trên grid lớn** dễ stack overflow → ưu tiên BFS.
- Mảng hướng `dr/dc` gọn hơn viết tay 4 nhánh; nhớ kiểm tra biên trước khi truy cập.
- Union-Find: **path compression** (+ union by rank nếu cần) để gần O(α(n)).

## Liên hệ

- BFS theo tầng dùng lại từ [Tree](../05_tree/README.md); DFS đệ quy nối với [Backtracking](../11_backtracking/README.md).
