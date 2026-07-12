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

bool isSame(TreeNode* root, TreeNode* subRoot) {
    if (root == nullptr && subRoot == nullptr)
        return true;

    if (!root || !subRoot || root->val != subRoot->val) {
        return false;
    }
    return isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
}


//---- Optimized: chỉ cần hàm gốc và isSame() ----//
// Time  O(n * m): isSame (O(m)) bị GỌI LẠI tại tối đa n node của root -> cộng dồn = nhân.
// Space O(n + m): tại 1 thời điểm, stack chỉ có:
//   - chuỗi isSubtree đang lồng: tối đa n khung (cây skewed)
//   - + đúng 1 lời gọi isSame đang chạy: tối đa m khung
//   => chồng lên nhau = n + m. Muốn ra n*m thì phải có n bản isSame sống CÙNG LÚC,
//      nhưng isSame luôn chạy xong (bung hết m khung) rồi isSubtree mới đi tiếp -> cộng, không nhân.
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    // Không tìm được root nào giá trị bằng subRoot nên false
    if (root == nullptr) return false;

    // Tìm thấy root bằng subRoot
    if (root->val == subRoot->val) {
        // Nếu giống nhau thì kết thúc luôn, không thì tiếp tục đệ quy tìm
        if (isSame(root, subRoot)) return true;
    }

    // Chưa tìm thấy, tiếp tục đệ quy tìm root->val == subRoot->val
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

//------ My solution: 3 hàm --------//
void dfs(TreeNode* root, TreeNode* subRoot, vector<TreeNode*>& starts) {
    if (root == nullptr) return;
    if (root->val == subRoot->val) {
        starts.push_back(root);
    }
    dfs(root->left, subRoot, starts);
    dfs(root->right, subRoot, starts);
}


bool MY_isSubtree(TreeNode* root, TreeNode* subRoot) {
    vector<TreeNode*> starts;
    dfs(root, subRoot, starts);

    for (auto start : starts) {
        if (isSame(start,subRoot)) return true;
    }
    
    return false;
}