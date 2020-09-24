class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    enum state_t {untouched, explore, done};
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(numCourses);
      for (const auto & e: prerequisites) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[v].emplace_back(u);
      }
      return self;
    }();

    const auto solution = [&](std::optional<std::vector<int>> self = std::make_optional(std::vector<int>{})) {
      auto state = std::vector<state_t>(numCourses, untouched);

      std::function<void(int)> fold = [&](int u) {
        if (state[u] == explore) {
          self.reset();
          return;
        }
        else {
          std::exchange(state[u], explore);
          for (const auto v : G[u]) {
            if (state[v] != done) {
              fold(v);
            }
          }
          std::exchange(state[u], done);
          if (self.has_value()) {
            self.value().emplace_back(u);
          }
        }
      };
      
      for (int u = 0; u < numCourses and self.has_value(); ++u) {
        if (state[u] == untouched) {
          fold(u);
        }
      }

      if (self.has_value()) {
        return std::reverse(std::begin(self.value()), std::end(self.value())), self.value();
      }
      else {
        return std::vector<int>{};
      }
    }();

    return solution;
  }
};
  
