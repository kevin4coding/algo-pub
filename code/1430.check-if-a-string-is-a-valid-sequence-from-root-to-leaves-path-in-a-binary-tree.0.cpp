class Solution {
 public:
  bool isValidSequence(TreeNode* root, vector<int>& arr) {
    const auto solution = [&](bool self = false) {
      std::function<void(TreeNode*)> fold = [&, acc = std::vector<int>{}](TreeNode* n) mutable {
        if (n == nullptr or self == true) {
          return;
        }
        else if (n->left == nullptr and n->right == nullptr) {
          acc.emplace_back(n->val);
          if (acc == arr) {
            std::exchange(self, true);
            return;
          }
          acc.pop_back();
        }
        else {
          if (n->left) {
            acc.emplace_back(n->val);
            fold(n->left);
            acc.pop_back();
          }
          if (n->right) {
            acc.emplace_back(n->val);
            fold(n->right);
            acc.pop_back();
          }
        }
      };
      return fold(root), self;
    }();

    return solution;
  }
};
