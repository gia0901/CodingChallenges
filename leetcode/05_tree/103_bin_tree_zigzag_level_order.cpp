#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// Level-order (zigzag): Time O(n), Space O(w)
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    if (root) q.push(root);

    bool leftToRight = true;

    while (!q.empty()) {
        size_t sz = q.size();
        vector<int> nodes;

        for (size_t i = 0; i < sz; i++) {
            TreeNode* cur = q.front();
            q.pop();
            nodes.push_back(cur->val);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        if (leftToRight == false) {
            reverse(nodes.begin(), nodes.end());
        }
        res.push_back(move(nodes));
        leftToRight = !leftToRight;
    }

    return res;
}