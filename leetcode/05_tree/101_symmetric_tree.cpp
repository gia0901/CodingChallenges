#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool isSame(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr)
        return true;

    if (p && q && p->val == q->val) {
        return isSame(p->right, q->left) &&
               isSame(p->left, q->right);
    }
    return false;
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true; // tree rỗng vẫn là đối xứng!
    return isSame(root->left, root->right);
}