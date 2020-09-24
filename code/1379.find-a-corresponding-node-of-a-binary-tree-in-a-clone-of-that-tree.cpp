class Solution {
 public:
  TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
    const auto solution = [&](TreeNode* self = nullptr) {
      std::function<void(TreeNode*, TreeNode*)> fold = [&](TreeNode* n, TreeNode* m) {
        if (n == nullptr or self != nullptr) {
          return;
        }
        else {
          if (n == target) {
            std::exchange(self, m);
          }
          fold(n->left, m->left);
          fold(n->right, m->right);
        }
      };
      return fold(original, cloned), self;
    }();

    return solution;
  }
};
