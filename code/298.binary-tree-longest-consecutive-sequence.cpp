class Solution {
 public:
  int longestConsecutive(TreeNode* root) {
    const struct {
      mutable std::optional<int> f[12000];
    } mempool;

    const auto ID = [&](std::unordered_map<TreeNode*, int> self = {}) {
      std::function<void(TreeNode*)> fold = [&, ctr = 0](TreeNode* n) mutable {
        if (n == nullptr) {
          return;
        }
        else {
          self[n] = ctr++;
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    std::function<int(TreeNode*)> f = [&, memo = std::ref(mempool.f)](TreeNode* n) {
      if (memo[ID.at(n)].has_value()) {
        return memo[ID.at(n)].value();
      }
      else {
        return memo[ID.at(n)].emplace([&] {
          if (n->left == nullptr and n->right == nullptr) {
            return 1;
          }
          else if (n->left != nullptr and n->right == nullptr) {
            return n->val + 1 == n->left->val ? 1 + f(n->left) : 1;
          }
          else if (n->left == nullptr and n->right != nullptr) {
            return n->val + 1 == n->right->val ? 1 + f(n->right) : 1;
          }
          else {
            return std::max(((n->val + 1) == n->left->val) ? 1 + f(n->left) : 1, ((n->val + 1) == n->right->val) ? 1 + f(n->right) : 1);
          }
        }());
      }
    };

    std::function<int(TreeNode*)> g = [&](TreeNode* n) {
      if (n == nullptr) {
        return 0;
      }
      else {
        return std::max({f(n), n->left != nullptr ? g(n->left) : 0, n->right != nullptr ? g(n->right) :0});;
      }
    };
    
    return g(root);
  }
};
