#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// BFS: Time O(n), Space O(w) queue
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        // duyệt từng level (tầng)
        size_t sz = q.size();
        vector<int> nodes;
        for (size_t i = 0; i < sz; i++) {
            TreeNode* cur = q.front();
            q.pop();
            nodes.push_back(cur->val);
            
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        // trong vòng while thì q luôn có phần tử -> luôn có nodes!
        // ko cần kiểm tra empty
        // if (!nodes.empty())
            res.push_back(nodes);
    }

    return res;
}