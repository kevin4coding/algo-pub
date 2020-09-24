class Solution {
 public:
  int countUnivalSubtrees(TreeNode* root) {
    const struct {
      mutable std::optional<bool> f[2000];
    } mempool;
    
    const auto ID = [&](std::unordered_map<TreeNode*, int> self = {}) {
      std::function<void(TreeNode*)> fold = [&, ctr = 0](TreeNode* node) mutable {
        if (node == nullptr) {
          return;
        }
        else {
          self[node] = ctr++;
          fold(node->left);
          fold(node->right);
        }
      };
      return fold(root), self;
    }();


    std::function<bool(TreeNode*)> f = [&, memo = std::ref(mempool.f)](TreeNode* n) {
      if (memo[ID.at(n)].has_value()) {
        return memo[ID.at(n)].value();
      }
      else {
        return memo[ID.at(n)].emplace([&] {
          if (n->left == nullptr and n->right == nullptr) {
            return true;
          }
          else {
            return (n->left ? n->val == n->left->val and f(n->left) : true) and (n->right ? n->val == n->right->val and f(n->right) : true);
          }
        }());
      }
    };

    std::function<int(TreeNode*)> g = [&](TreeNode* n) {
      if (n == nullptr) {
        return 0;
      }
      else {
        return (f(n) ? 1 : 0) + (n->left ? g(n->left) : 0) + (n->right ? g(n->right) : 0);
      }
    };
    return g(root);
  }
};
