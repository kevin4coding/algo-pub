/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
 public:
  bool checkEqualTree(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;

    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return n->val + f(n->left) + f(n->right);
          }
        }());
      }
    };

    const auto solution = [&](bool acc = false) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n != root) {
            acc |= (f(n) == f(root) - f(n));
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
