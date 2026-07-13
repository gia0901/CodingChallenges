#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void dfs(TreeNode* root, int& res) {
    if (root == nullptr) return;

    
}

int diameterOfBinaryTree(TreeNode* root) {
    if (root == nullptr) return 0;
    int res = 0;
    dfs(root, res);


}