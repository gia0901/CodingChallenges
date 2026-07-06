#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// quy tắc quan trọng nhất: nếu p, q tách làm 2 phía khỏi root, root chính là LCA
// nếu cố đi tiếp qua left/right sẽ mất p hoặc q -> vô nghĩa

// Iteration: p,q có thể dễ dàng tìm bằng cách check val và lặp về phía trái/phải
// Time O(h): độ sâu nhất của p,q
// Space O(1): không cần stack hay chứa gì
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) {
            root = root->left;
        }
        else if (p->val > root->val && q->val > root->val) {
            root = root->right;
        }
        else {
            break;
        }
    }
    return root;
}

// DFS chuẩn
// Time O(h): độ sâu nhất của p,q
// Space O(h): stack cho độ sâu sâu nhất
TreeNode* DFSlowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return root;
    if ((p->val < root->val) && (q->val < root->val)) {
        return DFSlowestCommonAncestor(root->left, p, q);
    }
    else if ((p->val > root->val) && (q->val > root->val)) {
        return DFSlowestCommonAncestor(root->right, p, q);
    }
    else {
        return root; // p và q phân tán ra 2 bên left, right, root chính là LCA
    }
}

// DFS tôi viết
TreeNode* My_DFSlowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return root;

    if ((q->val <= root->val && root->val <= p->val) ||
        (p->val <= root->val && root->val <= q->val)) {
        return root; // root chính là LCA
    }

    if ((p->val < root->val) && (q->val < root->val)) {
        return My_DFSlowestCommonAncestor(root->left, p, q);
    }
    return My_DFSlowestCommonAncestor(root->right, p, q);
}