class Solution {
 public:
  vector<vector<int>> verticalOrder(TreeNode* root) {
    struct node_t {
      TreeNode* node;
      int r;
      int c;
    };

    struct state_t {
      mutable std::deque<node_t> Q;
      mutable int col_boundary_min;
      mutable int col_boundary_max;
    };

    const auto ST = state_t {
      .Q = root == nullptr ? std::deque<node_t>{} : std::deque<node_t>{node_t{root, 0, 0}},
      .col_boundary_min = root == nullptr ? INT_MAX : 0,
      .col_boundary_max = root == nullptr ? INT_MIN : 0
    };

    const auto candidate = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      std::function<void(void)> bfs = [&]() {
        if (std::empty(ST.Q)) {
          return;
        }
        else {
          const auto [curr_n, curr_r, curr_c] = ST.Q.front();
          ST.Q.pop_front();
          self[curr_c].emplace_back(curr_n->val);
          if (curr_n->left != nullptr) {
            ST.col_boundary_min = std::min(ST.col_boundary_min, curr_c - 1);
            ST.Q.emplace_back(node_t{curr_n->left, curr_r - 1, curr_c - 1});
          }
          if (curr_n->right != nullptr) {
            ST.col_boundary_max = std::max(ST.col_boundary_max, curr_c + 1);
            ST.Q.emplace_back(node_t{curr_n->right, curr_r - 1, curr_c + 1});
          }
          bfs();
        }
      };

      return bfs(), self;
    }();

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      for (int c = ST.col_boundary_min; c <= ST.col_boundary_max; ++c) {
        self.emplace_back(candidate.at(c));
      }
      return self;
    }();

    return solution;
  }
};
