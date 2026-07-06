#include <bits/stdc++.h>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x) , left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

static bool isValid(TreeNode* root, long long lo, long long hi) {
    if (root == nullptr) return true;

    if (root->val <= lo || root->val >= hi) {
        return false;
    }
    return isValid(root->left, lo, root->val) &&
           isValid(root->right, root->val, hi);
}

bool isValidBST(TreeNode* root) {
    if (root == nullptr) return true;
    return isValid(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    cout << isValidBST(root) << endl;
}