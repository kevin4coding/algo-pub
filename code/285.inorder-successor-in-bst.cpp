class Solution {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    const auto solution = [&]() {
      const struct {
        mutable int time_stamp = 0;
        mutable std::optional<int> target_time_stamp = {};
      } state;

      auto result = std::optional<TreeNode*>{};
      
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr or result.has_value()) {
          return;
        }
        else {
          fold(n->left);
          ++state.time_stamp;
          if (n == p) {
            state.target_time_stamp = state.time_stamp + 1;
          }
          else if (state.time_stamp == state.target_time_stamp) {
            result.emplace(n);
          }
          fold(n->right);
        }
      };

      return fold(root), result;
    }();


    return solution.value_or(nullptr);
    
  }
};
