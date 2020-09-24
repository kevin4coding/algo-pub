class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(numCourses);
      for (const auto& e : prerequisites) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    const auto indegree = [&](std::vector<int> self = {}) {
      self.resize(numCourses, 0);
      for (int u = 0; u < numCourses; ++u) {
        for (const auto v : G[u]) {
          ++self[v];
        }
      }
      return self;
    }();
    
    const auto solution = [&](std::vector<int> self = {}) {
      // mutable states
      auto Q = [&](std::deque<int> self = {}) {
        for (int u = 0; u < numCourses; ++u) {
          if (indegree[u] == 0) {
            self.emplace_back(u);
          }
        }
        return self;
      }();

      std::function<void(void)> bfs = [&, indegree = indegree]() mutable {
        if (std::empty(Q)) {
          if ((int)std::size(self) != numCourses) {
            self.clear();
          }
          return;
        }
        else {
          const auto u = Q.front();
          Q.pop_front();
          self.emplace_back(u);
          for (const auto v : G[u]) {
            if (--indegree[v] == 0) {
              Q.emplace_back(v);
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
