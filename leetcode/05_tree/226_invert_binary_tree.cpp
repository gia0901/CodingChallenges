#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// BFS: Time O(n), 
// Space O(w) queue: dùng khi tree quá sâu, tránh stack-overflow
TreeNode* invertTree(TreeNode* root) {
    queue<TreeNode*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        //chỉ swap tại nội bộ từng node nên ko cần chia theo tầng
        //size_t sz = q.size();
        //for (size_t i = 0; i < sz; i++) {
            TreeNode* cur = q.front();
            q.pop();
            swap(cur->left, cur->right);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        //}
    }
    
    return root;
}

// DFS: Time O(n), Space O(h) stack
void dfs(TreeNode* root) {
    if (root == nullptr) return;

    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    dfs(root->left);
    dfs(root->right);
}

TreeNode* DFSinvertTree(TreeNode* root) {
    dfs(root);
    return root;
}