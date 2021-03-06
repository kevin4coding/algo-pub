class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    struct state_t {
      mutable std::deque<TreeNode*> Q;
    };

    const auto state = state_t { .Q = (root == nullptr) ? std::deque<TreeNode*>{} : std::deque<TreeNode*>{root} };
    
    auto value_getter = [&](TreeNode* n) {
      return n->val;
    };
    
    const auto level_order = [&](std::vector<std::vector<int>> self = {}) {
      for (auto & Q = state.Q; not std::empty(Q); ) {
        const int level_size = std::size(Q);
        for (int i = 0; i < level_size; ++i) {
          if (Q[i]->left != nullptr) {
            Q.emplace_back(Q[i]->left);
          }
          if (Q[i]->right != nullptr) {
            Q.emplace_back(Q[i]->right);
          }
        }
        self.emplace_back([&](std::vector<int> x = {}) {
          std::transform(std::begin(Q), std::begin(Q) + level_size, std::back_inserter(x), value_getter);
          return (Q.erase(std::begin(Q), std::begin(Q) + level_size), std::move(x));
        }());
      }
      return self;
    }();

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      std::copy(std::begin(level_order), std::end(level_order), std::back_inserter(self));
      for (int i = 0; i < std::size(self); ++i) {
        if (i % 2 == 1) {
          std::reverse(std::begin(self[i]), std::end(self[i]));
        }
      }
      return self;
    }();

    return solution;
  }
};
