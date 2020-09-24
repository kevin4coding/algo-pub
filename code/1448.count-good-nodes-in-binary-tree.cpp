class Solution {
 public:
  int goodNodes(TreeNode* root) {
    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int subacc_max) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->val >= subacc_max) {
            ++acc;
          }
          fold(n->left, std::max(subacc_max, n->val));
          fold(n->right, std::max(subacc_max, n->val));
        }
      };
      return fold(root, INT_MIN), acc;
    }();
    return solution;
  }
};
