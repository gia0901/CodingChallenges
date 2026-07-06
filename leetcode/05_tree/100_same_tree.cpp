#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    // cả p và q đều đến được nullptr
    // => nhánh này giống nhau nên, return true
    if (p == nullptr && q == nullptr) {
        return true;
    }

    // p và q đều chưa đến tận cùng (== nullptr)
    // cần kiểm tra giống nhau:
    // - cả 2 đều phải khác nullptr
    // - cả 2 phải cùng val
    // Chỉ sai 1 điều kiện thì nhánh này bỏ, return false
    // (node parent gọi xuống đây cũng kết thúc luôn vì 1 trong 2 nhánh con đã sai)
    if (p && q && p->val == q->val) {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
    return false;
}