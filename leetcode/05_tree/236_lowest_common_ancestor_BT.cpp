#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) 
        return nullptr;

    if (root == p || root == q)
        return root;

    TreeNode* findLeft = lowestCommonAncestor(root->left, p, q);
    TreeNode* findRight = lowestCommonAncestor(root->right, p, q);

    if (findLeft && findRight) {
        return root;
    }
    // chỉ bên trái trả về non-null => mọi thứ tìm được đều nằm bên trái.
    // KHÔNG tự kết luận đây có phải LCA hay không (có thể findLeft chỉ là
    // 1 mục lẻ, đứa kia nằm ở nhánh khác) — cứ đẩy nguyên findLeft lên,
    // để node cha phía trên tổng hợp tiếp.
    else if (findLeft) {
        return findLeft;
    }
    // đối xứng: chỉ bên phải trả về non-null => đẩy nguyên findRight lên
    // cho cha xử lý, không tự kết luận LCA tại đây.
    else if (findRight) {
        return findRight;
    }
    // tại subtree này ko có đứa nào được tìm thấy, trả về nullptr
    // cho cha kiểm tra tiếp.
    else {
        return nullptr;
    }

}