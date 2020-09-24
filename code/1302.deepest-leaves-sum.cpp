class Solution {
 public:
  int deepestLeavesSum(TreeNode* root) {
    const auto D = [&](std::unordered_map<TreeNode*, int> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode *n, int level) {
        if (n == nullptr) {
          return;
        }
        else {
          self[n] = level;
          fold(n->left, level + 1);
          fold(n->right, level + 1);
        }
      };
      return fold(root, 0), self;
    }();

    const auto maxd = [&](int acc = INT_MIN) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          acc = std::max(acc, D.at(n));
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (D.at(n) == maxd) {
            acc += n->val;
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution;
  }
};
