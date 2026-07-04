# 5. Tree & BST ★★★★☆

Gần như mọi bài cây quy về **DFS đệ quy** hoặc **BFS theo tầng**; BST thêm bất biến inorder tăng dần.

## Các pattern cốt lõi (skeleton C++)

### Pattern A — DFS đệ quy (pre/in/post-order)
```cpp
void dfs(TreeNode* node) {
    if (!node) return;
    // preorder:  xử lý node ở đây
    dfs(node->left);
    // inorder:   xử lý node ở đây (với BST -> tăng dần)
    dfs(node->right);
    // postorder: xử lý node ở đây
}
```

Thứ tự thăm trên cây mẫu:

```
        4
       / \
      2   6
     / \ / \
    1  3 5  7

preorder  (node,L,R): 4 2 1 3 6 5 7
inorder   (L,node,R): 1 2 3 4 5 6 7   <- BST -> TĂNG DẦN (bất biến hay dùng)
postorder (L,R,node): 1 3 2 5 7 6 4
```

### Pattern B — BFS theo tầng (queue)
```cpp
queue<TreeNode*> q;
if (root) q.push(root);
while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; ++i) {
        TreeNode* n = q.front(); q.pop();
        // xử lý n
        if (n->left)  q.push(n->left);
        if (n->right) q.push(n->right);
    }
    // kết thúc một tầng
}
```

Chốt `sz = q.size()` đầu mỗi tầng để tách tầng — đây là mấu chốt:

```
tầng 0: [4]           sz=1  -> pop 4, push 2,6
tầng 1: [2,6]         sz=2  -> pop 2,6, push 1,3,5,7
tầng 2: [1,3,5,7]     sz=4
```

### Pattern C — BST bounds (kiểm tra bất biến)
```cpp
bool valid(TreeNode* n, long lo, long hi) {
    if (!n) return true;
    if (n->val <= lo || n->val >= hi) return false;
    return valid(n->left, lo, n->val) && valid(n->right, n->val, hi);
}
```

## Bài cốt lõi (6 bài)

| # | Bài | Pattern | Complexity mục tiêu |
|---|-----|---------|---------------------|
| 1 | Maximum Depth of Binary Tree | A | Time O(n), Space O(h) |
| 2 | Invert Binary Tree | A | Time O(n), Space O(h) |
| 3 | Symmetric Tree | A (đôi) | Time O(n), Space O(h) |
| 4 | Level Order Traversal | B | Time O(n), Space O(n) |
| 5 | Validate BST | C | Time O(n), Space O(h) |
| 6 | Lowest Common Ancestor | A | Time O(n) (O(h) với BST) |

### 1. Maximum Depth
> Độ sâu lớn nhất = `1 + max(depth(left), depth(right))`.

### 2. Invert Binary Tree
> Đổi chỗ left/right ở mọi node (đệ quy).

### 3. Symmetric Tree
> Cây có đối xứng gương không? So `left.left` với `right.right` và `left.right` với `right.left`.

### 4. Level Order Traversal
> Trả về các giá trị theo từng tầng. Pattern B, gom mỗi `sz` node thành 1 tầng.

### 5. Validate BST
> Pattern C với bound `(lo, hi)`.
- **Bẫy quan trọng**: **không** chỉ so `node` với con trực tiếp — một node cháu vẫn có thể vi phạm dù cha-con hợp lệ. Phải truyền bound `(lo, hi)` lan xuống. Dùng `long` để tránh biên `INT_MIN/MAX`.

### 6. Lowest Common Ancestor
> Với **BST**: đi trái/phải theo so sánh giá trị → O(h). Với **binary tree thường**: đệ quy, node là LCA nếu hai phía chứa hai target.

## Vì sao Space là O(h)

DFS đệ quy tốn stack theo **chiều sâu** đường đang đi, không phải toàn bộ node. Cây cân bằng
`h ≈ log n` → O(log n); cây lệch (skewed) `h ≈ n` → O(n), và đây là ca dễ **stack overflow**.

## Pitfall C++ hay gặp

- **Null check** đầu mỗi hàm đệ quy — nguồn segfault số một.
- **Stack overflow** với cây lệch (skewed, h ≈ n); nếu lo ngại độ sâu, chuyển sang lời giải iterative + stack/queue.
- **Validate BST**: biên `INT_MIN/INT_MAX` cần `long`/`long long` hoặc dùng con trỏ nullable.
- Truyền node **by pointer**, không copy cả subtree.

## Liên hệ

- BFS ở đây dùng lại cho [Graph](08_graph.md); đệ quy DFS là nền cho [Backtracking](11_backtracking.md).
