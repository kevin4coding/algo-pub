class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    using int64 = long long;
    std::function<bool(TreeNode*, int64, int64)> f = [&](TreeNode* n, int64 lo, int64 hi) {
      if (n == nullptr) {
        return true;
      }
      else if (not (lo < n->val and n->val < hi)) {
        return false;
      }
      else {
        return f(n->left, lo, int64(n->val)) and f(n->right, int64(n->val), hi);
      }
    };
    return f(root, LONG_MIN, LONG_MAX);
  }
};
