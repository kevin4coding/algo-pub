class Solution {
 public:
  TreeNode* pruneTree(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<bool>> f;
    } mempool;

    std::function<bool(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return true;
          }
          else {
            return n->val == 0 and f(n->left) and f(n->right);
          }
        }());
      }
    };

    std::function<void(TreeNode*)> purge = [&](TreeNode *n) {
      if (n == nullptr) {
        return;
      }
      else {
        purge(n->left);
        purge(n->right);
        delete n;
      }
    };

    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return;
      }
      else if (n == root and f(n)) {
        // should delete the tree, but for some reason it is not passing OJ..
        // the easiest way to avoid is to copy the tree so we have the ownership.
        root = nullptr;
      }
      else {
        if (n->left and f(n->left)) {
          std::exchange(n->left, (purge(n->left), nullptr));

        }
        if (n->right and f(n->right)) {
          std::exchange(n->right, (purge(n->right), nullptr));
        }
        fold(n->left);
        fold(n->right);
      }
    };

    return fold(root), root;
  }
};
