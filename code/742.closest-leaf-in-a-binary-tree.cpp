class Solution {
 public:
  int findClosestLeaf(TreeNode* root, int k) {
    struct state_t {
      mutable std::unordered_map<TreeNode*, std::optional<int>> D;
      mutable std::deque<TreeNode*> Q;
    };

    const auto G = [&](std::unordered_map<TreeNode*, std::unordered_set<TreeNode*>> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (not self.count(n)) {
            std::exchange(self[n], std::unordered_set<TreeNode*>{});
          }
          if (n->left != nullptr) {
            self[n].emplace(n->left);
            self[n->left].emplace(n);
          }
          if (n->right != nullptr) {
            self[n].emplace(n->right);
            self[n->right].emplace(n);
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();


    const auto source = [&](TreeNode* self = nullptr) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr or self != nullptr) {
          return;
        }
        else {
          if (n->val == k) {
            std::exchange(self, n);
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();


    const auto ST = state_t {
      .Q = std::deque<TreeNode*>{source},
      .D = std::unordered_map<TreeNode*, std::optional<int>>{{source, std::make_optional(1)}}
    };


    auto is_leaf = [&](TreeNode* n) {
      return n->left == nullptr and n->right == nullptr;
    };

    int const a = 1;

    const auto solution = [&](std::optional<int> self = {}) {
      auto & Q = ST.Q;
      auto & D = ST.D;
      std::function<void(void)> bfs = [&]() mutable {
        if (std::empty(Q)) {
          return;
        }
        else {
          const auto n = Q.front();
          Q.pop_front();
          if (is_leaf(n)) {
            self.emplace(n->val);
            return;
          }
          for (const auto next_n : G.at(n)) {
            if (not D[next_n].has_value()) {
              Q.emplace_back(next_n);
              D[next_n].emplace(D[n].value() + 1);
              if (std::size(G.at(next_n)) == 1 and is_leaf(*std::begin(G.at(next_n)))) {
                self.emplace(next_n->val);
                return;
              }
            }
          }
          bfs();
        }
      };

      return bfs(), self.value_or(source->val);
    }();

    return solution;
  }
};
  
