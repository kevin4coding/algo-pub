class Solution {
 public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    // returns the successor node of target in the subtree rooted at target
    auto successor = [&](TreeNode* target) {
      auto result = std::optional<int>{};
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->val > target->val) {
            result.emplace(n->val);
            fold(n->left);
          }
          else {
            fold(n->right);
          }
        }
      };
      return fold(target), result;
    };

    // returns the predecessor node of target in the subtree rooted at target
    auto predecessor = [&](TreeNode* target) {
      auto result = std::optional<int>{};
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->val < target->val) {
            result.emplace(n->val);
            fold(n->right);
          }
          else {
            fold(n->left);
          }
        }
      };
      return fold(target), result;
    };

    std::function<TreeNode*(TreeNode*, int)> fold = [&](TreeNode* n, int k) {
      if (n == nullptr) {
        return static_cast<TreeNode*>(nullptr);
      }
      else {
        if (n->val < k) {
          n->right = fold(n->right, k);
        }
        else if (n->val > k) {
          n->left = fold(n->left, k);
        }
        else {
          if (n->left == nullptr and n->right == nullptr) {
            n = nullptr;
          }
          else {
            const auto [pred, succ] = std::pair{predecessor(n), successor(n)};
            if (succ.has_value()) {
              std::exchange(n->val, succ.value());
              n->right = fold(n->right,succ.value());
            }
            else if (pred.has_value()) {
              std::exchange(n->val, pred.value());
              n->left = fold(n->left, pred.value());
            }
            else throw std::domain_error("");
          }
        }
        return n;
      }
    };

    return fold(root, key);
  }
};
