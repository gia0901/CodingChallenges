#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// BFS: Time O(n), Space O(w) queue: tầng có nhiều node nhất
int maxDepth(TreeNode* root) {
    queue<TreeNode*> q;
    if (root)
        q.push(root);
    int depth = 0;
    while (!q.empty()) {
        // số node của tầng hiện tại
        // xác định đủ node của tầng, các node dôi ra sẽ là của tầng tiếp theo
        size_t sz = q.size();
        for (size_t i = 0; i < sz; i++) {
            TreeNode* cur = q.front();
            q.pop();
            // push node con nếu có, chúng sẽ được xét trong tầng tiếp theo
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        // xong 1 tầng, độ sâu +1
        depth++;
    }

    return depth;
}

// DFS: Time O(n), Space O(h) stack
int DFSmaxDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;
    // tại mỗi tầng, độ sâu tăng thêm 1
    // và cộng tiếp độ sâu sâu nhất của nhánh con (left hoặc right)
    return 1 + max(DFSmaxDepth(root->left), DFSmaxDepth(root->right));
}