class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    struct state_t {
      mutable std::deque<Node*> Q;
      mutable int level_size;
    };

    const auto state = state_t {
      .Q = root == nullptr ? std::deque<Node*>{} : std::deque<Node*>{root},
      .level_size = root == nullptr ? 0 : 1
    };

    const auto solution = [&ST = state](std::vector<std::vector<int>> self = {}) {
      while (not std::empty(ST.Q)) {
        const auto cur_level_size = std::exchange(ST.level_size, 0);
        self.emplace_back(std::vector<int>{});
        for (int i = 0; i < cur_level_size; ++i) {
          const auto curr_node = ST.Q.front();
          ST.Q.pop_front();
          self.back().emplace_back(curr_node->val);
          for (const auto ch : curr_node->children) {
            ST.Q.emplace_back(ch);
            ++ST.level_size;
          }
        }
      }
      return self;
    }();
      
    return solution;
  }
};
