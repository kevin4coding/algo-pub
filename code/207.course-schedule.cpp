class Solution {
 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    enum status_t {untouched, explore, done};
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(numCourses);
      for (const auto& e : prerequisites) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    
    const auto solution = [&](bool acc = true) {
      auto status = std::vector<status_t>(numCourses, untouched); 

      std::function<void(int)> fold = [&](int u) mutable {
        if (status[u] == explore) {
          acc = false;
          return;
        }
        else {
          std::exchange(status[u], explore);
          for (const auto v : G[u]) {
            if (status[v] != done) {
              fold(v);
            }
          }
          std::exchange(status[u], done);
        }
      };

      for (int i = 0; i < numCourses and acc == true; ++i) {
        if (status[i] == untouched) {
          fold(i);
        }
      }
      return acc;
    }();

    return solution;
  }
};


