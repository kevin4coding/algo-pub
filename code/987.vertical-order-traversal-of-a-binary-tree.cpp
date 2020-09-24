class Solution {
 public:
  vector<vector<int>> verticalTraversal(TreeNode* root) {
    struct coord_t {
      int x;
      int y;
    };

    const auto coord_map = [&](std::unordered_map<TreeNode*, coord_t> self = {}) {
      std::function<void(TreeNode*, int x, int y)> fold = [&](TreeNode* n, int x, int y) {
        if (n == nullptr) {
          return;
        }
        else {
          self[n] = coord_t{x, y};
          fold(n->left, x - 1, y - 1);
          fold(n->right, x + 1, y - 1);
        }
      };
      return fold(root, 0, 0), self;
    }();


    auto sorter = [&](const std::pair<TreeNode*, int> &p1, const std::pair<TreeNode*, int>& p2) {
      if (p1.second == p2.second) {
        return p1.first->val < p2.first->val;
      }
      else {
        return p1.second > p2.second;
      }
    };

    auto value_getter = [&](const std::pair<TreeNode*, int>& x) {
      return (x.first)->val;
    };

    const auto candidate = [&](std::map<int, std::vector<std::pair<TreeNode*, int>>> self = {}) {
      for (const auto [n, coord] : coord_map) {
        self[coord.x].emplace_back(std::pair<TreeNode*, int>{n, coord.y});
      }
      for (auto & [_, y_and_nodes] : self) {
        std::sort(std::begin(y_and_nodes), std::end(y_and_nodes), sorter);
      }
      return self;
    }();

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      for (const auto & [x, y_and_nodes] : candidate) {
        auto& nodes = y_and_nodes; // as a fix for the gcc bug for not capturing structral binding
        self.emplace_back([&](std::vector<int> x = {}) {
          std::transform(std::begin(nodes), std::end(nodes), std::back_inserter(x), value_getter);
          return x;
        }());
      }
      return self;
    }();

    return solution;
  }
};
