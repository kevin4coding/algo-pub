class Solution {
 public:
  vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    struct state_t {
      mutable std::unordered_map<TreeNode*, std::optional<int>> D;
      mutable std::deque<TreeNode*> Q;
    };

    const auto ST = state_t {
      .D = std::unordered_map<TreeNode*, std::optional<int>>{{target, 0}},
      .Q = std::deque<TreeNode*>{target}
    };

    const auto G = [&](std::unordered_map<TreeNode*, std::unordered_set<TreeNode*>> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode *n) {
        if (n == nullptr) {
          return;
        }
        else {
          self.try_emplace(n, std::unordered_set<TreeNode*>{});
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
    
    const auto solution = [&](std::vector<int> self = {}) {
      auto & Q = ST.Q;
      auto & D = ST.D;
      
      std::function<void(void)> bfs = [&]() {
        if (std::empty(Q)) {
          return;
        }
        else {
          const auto n = Q.front();
          Q.pop_front();
          if (D[n].value() == K) {
            self.emplace_back(n->val);
          }
          for (const auto next_n : G.at(n)) {
            if (not D[next_n].has_value()) {
              std::exchange(D[next_n], D[n].value() + 1);
              if (D[next_n].value() < K) {
                Q.emplace_back(next_n);
              }
              else if (D[next_n].value() == K) {
                self.emplace_back(next_n->val);
              }
            }
          }
          bfs();
        }
      };
      return bfs(), self;
    }();

    return solution;
  }
};
