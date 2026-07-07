# 8. Graph ★★★☆☆

Ba công cụ đủ cho hầu hết bài: **BFS/DFS** (duyệt), **topological sort** (thứ tự phụ thuộc),
**union-find** (nhóm liên thông). Khó không nằm ở thuật toán mà ở chỗ **nhận ra đây là bài graph**
và **dựng đúng cách biểu diễn**.

## 0. Nhận diện & biểu diễn đồ thị

### Khi nào một bài là "graph"?
Bất cứ khi nào có **thực thể** nối với nhau bởi **quan hệ**, và câu hỏi xoay quanh *liên thông /
đường đi / thứ tự phụ thuộc / lan tỏa*. Đồ thị hay bị "giấu":

- **Grid** (ma trận): mỗi ô = 1 node, 2 ô kề (4 hoặc 8 hướng) = 1 cạnh → *implicit graph*.
  Không cần dựng `adj` — suy ra cạnh bằng mảng hướng `dr/dc`.
- **Phụ thuộc** (khóa học, build task): "A cần B trước" = cạnh `B -> A` → topological sort.
- **Quan hệ nhóm** (bạn bè, tỉnh nối nhau): "cùng nhóm" = union-find.

Dấu hiệu grid-là-graph: hỏi về *vùng liền kề / lan tỏa / kết nối*, di chuyển *4-8 hướng*, cần
*đánh dấu visited*.

### Hai cách biểu diễn (graph tường minh)
```cpp
// 1) Adjacency list — MẶC ĐỊNH (đồ thị thưa, E << V^2). Duyệt hàng xóm O(deg).
vector<vector<int>> adj(n);        // adj[u] = danh sách node kề u
for (auto& e : edges) {
    adj[e[0]].push_back(e[1]);
    adj[e[1]].push_back(e[0]);     // BỎ dòng này nếu đồ thị CÓ HƯỚNG
}

// 2) Adjacency matrix — chỉ khi đồ thị dày, hoặc cần tra cạnh (u,v) tức thì O(1).
vector<vector<int>> g(n, vector<int>(n, 0));  // g[u][v] = 1 nếu có cạnh. Tốn O(V^2) bộ nhớ.
```

## Các pattern cốt lõi (skeleton C++)

### Pattern A1 — BFS trên grid (loang theo tầng)
Dùng khi cần **đường đi ngắn nhất** trên lưới không trọng số, hoặc loang "theo thời gian".
```cpp
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};   // 4 hướng: lên/xuống/trái/phải
queue<pair<int,int>> q;
q.push({sr, sc});
vis[sr][sc] = true;                 // (!) đánh dấu ngay khi PUSH, KHÔNG phải khi pop
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];        // ô kề theo hướng d
        // kiểm biên TRƯỚC, rồi mới kiểm visited/hợp lệ (short-circuit tránh out-of-bounds)
        if (nr >= 0 && nr < m && nc >= 0 && nc < n
            && !vis[nr][nc] && valid(nr, nc)) {    // valid = ô đi được (vd grid=='1')
            vis[nr][nc] = true;                    // đánh dấu ngay khi đưa vào queue
            q.push({nr, nc});
        }
    }
}
```

BFS lan theo "tầng" = khoảng cách từ nguồn (số cạnh). Mỗi vòng while mở rộng đúng 1 vành đai:
```
 tầng: 2 1 2      từ nguồn S, BFS phủ dần các vành đai đồng khoảng cách
        1 S 1     -> đây là lý do BFS cho SHORTEST PATH trên đồ thị KHÔNG trọng số
        2 1 2
```

### Pattern A2 — DFS trên grid (flood fill)
Ngắn gọn hơn BFS khi chỉ cần **phủ hết 1 vùng liên thông** (không cần khoảng cách).
```cpp
// Toàn bộ điều kiện dừng gom về ĐẦU hàm -> đệ quy con vô điều kiện, ít lỗi hơn.
void dfs(int r, int c, vector<vector<char>>& grid, vector<vector<int>>& vis) {
    if (r < 0 || r >= m || c < 0 || c >= n) return;   // 1. ra ngoài biên
    if (grid[r][c] != '1' || vis[r][c]) return;        // 2. là nước, hoặc đã thăm
    vis[r][c] = 1;                                      // 3. đánh dấu ô hiện tại
    for (int d = 0; d < 4; ++d)                         // 4. loang 4 hướng
        dfs(r + dr[d], c + dc[d], grid, vis);
}
```
> ⚠️ DFS đệ quy dùng **call stack**: grid rất lớn (toàn '1') có thể **stack overflow**.
> Khi đó chuyển sang BFS (Pattern A1) hoặc DFS iterative bằng `stack` tường minh.

### Pattern A3 — BFS đa nguồn (multi-source)
Nạp **nhiều nguồn cùng lúc** vào queue ban đầu → loang song song. Nền của "Rotting Oranges".
```cpp
queue<pair<int,int>> q;
for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
        if (isSource(i, j)) { q.push({i, j}); vis[i][j] = true; }  // nạp MỌI nguồn trước

int steps = 0;
while (!q.empty()) {
    int sz = q.size();                 // chốt số node của tầng hiện tại (như level-order tree)
    for (int k = 0; k < sz; ++k) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (inBounds(nr, nc) && !vis[nr][nc] && valid(nr, nc)) {
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    ++steps;                           // xong 1 tầng = 1 đơn vị thời gian/khoảng cách
}
```

### Pattern B — Topological sort (Kahn, dùng BFS trên indegree)
Xếp thứ tự các node sao cho mọi cạnh `u -> v` thì `u` đứng trước `v`. Chỉ áp dụng cho **DAG**
(đồ thị có hướng, không chu trình). Đồng thời **phát hiện chu trình**.
```cpp
vector<int> indeg(n, 0);
for (auto& [u, v] : edges) indeg[v]++;          // cạnh u -> v: v phụ thuộc u
queue<int> q;
for (int i = 0; i < n; ++i)
    if (indeg[i] == 0) q.push(i);               // node không phụ thuộc ai -> làm được ngay
vector<int> order;
while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);                         // "hoàn thành" u
    for (int v : adj[u])
        if (--indeg[v] == 0) q.push(v);         // gỡ cạnh u->v; v hết phụ thuộc thì tới lượt
}
// order.size() < n  =>  còn node kẹt trong chu trình (không bao giờ về indegree 0)
```

Trực giác — cứ lấy node **indegree 0** (không còn phụ thuộc), gỡ cạnh của nó, lặp lại:
```
 A -> B -> D        indeg khởi tạo: A0  B1  C1  D2
 A -> C -> D        lấy A -> giảm B,C về 0 -> lấy B,C -> giảm D về 0 -> lấy D
                    order = A B C D   (đủ 4 node => KHÔNG có chu trình)
```

### Pattern C — Union-Find (DSU: path compression + union by rank)
Gộp/hỏi "hai node có cùng nhóm không" gần như O(1). Mạnh cho **liên thông động** (thêm cạnh dần).
```cpp
vector<int> parent(n), rnk(n, 0);
iota(parent.begin(), parent.end(), 0);          // ban đầu mỗi node là root của chính nó

function<int(int)> find = [&](int x) {
    // path compression: nối thẳng x lên root để lần sau tra nhanh
    return parent[x] == x ? x : parent[x] = find(parent[x]);
};
auto unite = [&](int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return;                        // đã cùng nhóm
    if (rnk[ra] < rnk[rb]) swap(ra, rb);         // union by rank: gắn cây thấp vào cây cao
    parent[rb] = ra;
    if (rnk[ra] == rnk[rb]) rnk[ra]++;           // hai cây cùng cao -> cây mới cao thêm 1
};
```

## Bài cốt lõi (6 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Number of Islands | A1 / A2 | Time O(m·n), Space O(m·n) |
| 2 | Rotting Oranges | A3 (multi-source) | Time O(m·n) |
| 3 | Clone Graph | A1/DFS + hash map | Time O(V+E) |
| 4 | Course Schedule | B (topo sort) | Time O(V+E) |
| 5 | Surrounded Regions | A2 (DFS từ biên) | Time O(m·n) |
| 6 | Number of Connected Components | C (union-find) | Time O(V·α + E) |

### 1. Number of Islands
> Đếm cụm ô `'1'` liền kề. Quét grid; gặp `'1'` **chưa thăm** → `count++` rồi BFS/DFS làm chìm
> cả cụm (đánh dấu visited). **Phải** check visited *trước* khi `count++`, nếu không sẽ đếm lại
> ô đã thuộc đảo cũ.

### 2. Rotting Oranges
> Cam thối lan sang cam tươi kề mỗi phút; hỏi số phút để thối hết. BFS **đa nguồn** (Pattern A3):
> nạp mọi cam thối vào queue trước, mỗi tầng = 1 phút. Cuối cùng nếu còn cam tươi chưa thăm → -1.

### 3. Clone Graph
> Sao chép sâu đồ thị. DFS/BFS + `unordered_map<Node*, Node*>` ánh xạ gốc→bản sao. Map vừa
> tránh clone lại node đã sao, vừa đóng vai **visited** (đã có trong map = đã thăm).

### 4. Course Schedule
> Học hết môn được không (đồ thị phụ thuộc không chu trình)? Topo sort (Pattern B) — nếu xếp đủ
> `n` node thì được; thiếu node = có chu trình = không thể.

### 5. Surrounded Regions
> Vùng `'O'` **chạm biên** thì an toàn, còn lại bị lật thành `'X'`. Mẹo **đảo ngược**: DFS/BFS từ
> các ô `'O'` *trên biên* đánh dấu "an toàn"; sau đó mọi `'O'` chưa được đánh dấu đều bị lật.

### 6. Number of Connected Components
> Đếm số thành phần liên thông. `unite` mọi cạnh; đáp = số **root phân biệt** (`find(i) == i`).
> Hoặc: bắt đầu `count = n`, mỗi lần `unite` thành công (hai nhóm khác nhau) thì `count--`.

## Khái niệm cốt lõi cần nắm chắc

### Vì sao đánh dấu visited khi PUSH, không phải khi POP
Nếu chỉ đánh dấu lúc pop, một node có thể được **push nhiều lần** (từ nhiều hàng xóm) trước khi
được pop lần đầu → queue phình to, xử lý trùng, **sai đếm tầng**. Đánh dấu ngay khi push đảm bảo
**mỗi node vào queue đúng 1 lần** → tổng chi phí O(V + E).

### DFS hay BFS?
| Cần gì | Chọn |
|--------|------|
| Chỉ phủ hết 1 vùng / đếm component / có tồn tại đường đi | **DFS** (ngắn gọn) hoặc BFS đều được |
| **Đường đi ngắn nhất** (đồ thị không trọng số) | **BFS** (loang theo tầng = khoảng cách) |
| Loang "theo thời gian" từ nhiều nguồn | **BFS đa nguồn** |
| Grid rất lớn (lo stack overflow) | **BFS** (heap) thay vì DFS đệ quy |

### Vì sao BFS/DFS là O(V + E)
Mỗi node thăm đúng 1 lần (nhờ visited) = O(V); tại mỗi node duyệt hết các cạnh kề, tổng số cạnh
xét qua toàn bộ = O(E). Cộng lại O(V + E) — với grid, `V = m·n` và `E ≈ 4·m·n` nên là O(m·n).

## Pitfall C++ hay gặp

- **Đánh dấu `visited` khi PUSH** (không phải khi pop) → tránh cùng node vào queue nhiều lần.
- **DFS đệ quy trên grid lớn** dễ stack overflow → ưu tiên BFS hoặc stack tường minh.
- **Kiểm biên TRƯỚC khi truy cập** `grid[nr][nc]`; đặt điều kiện biên trước trong `&&` để
  short-circuit chặn out-of-bounds.
- Mảng hướng `dr/dc` gọn hơn viết tay 4 nhánh; muốn 8 hướng thì mở rộng mảng thành 8 phần tử.
- Đồ thị **có hướng**: chỉ thêm cạnh 1 chiều vào `adj` (đừng thêm cạnh ngược).
- Union-Find: nhớ **path compression** (bắt buộc) + **union by rank** (nên có) để gần O(α(n)).
- `auto [r, c] = q.front();` (structured binding) cần C++17.

## Liên hệ

- **BFS theo tầng** dùng lại từ [Tree](05_tree.md) level-order (102/103); grid A3 = level-order đa nguồn.
- **DFS đệ quy** nối với [Backtracking](11_backtracking.md) — khác biệt: flood-fill đánh dấu
  visited **vĩnh viễn** (mỗi ô 1 lần), backtracking **hoàn tác** (`vis=false` khi quay lui) để thử
  đường khác.
- **Union-Find** tái dùng ở bài nhóm/đảo động, và Kruskal (MST) khi học đồ thị có trọng số.
- **Topological sort** liên quan [DP](09_dp.md) trên DAG (thứ tự tính subproblem).
