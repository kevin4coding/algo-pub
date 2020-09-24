class Solution {
 public:
  vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
    const int R = std::size(nums);
    
    struct node_t {
      int r;
      int c;
    };

    struct state_t {
      mutable std::deque<node_t> Q;
    };

    const auto state = state_t {
      .Q = std::deque<node_t>{node_t{0, 0}}
    };

    const auto solution = [&](std::vector<int> self = {}) {
      auto & Q = state.Q;
      while (not std::empty(Q)) {
        const auto [r, c] = Q.front();
        Q.pop_front();
        self.emplace_back(nums[r][c]);
        if (c == 0 and r + 1 < R)
          Q.emplace_back(node_t{r + 1, c});
        if (c + 1 < std::size(nums[r]))
          Q.emplace_back(node_t{r, c + 1});
      }
      return self;
    }();


    return solution;
    
  }
};
