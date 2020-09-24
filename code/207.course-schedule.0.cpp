class Solution {
 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {   
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(numCourses);
      for (const auto e : prerequisites) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    const auto indegree = [&](std::vector<int> self = {}) {
      self.resize(numCourses);
      for (int u = 0; u < numCourses; ++u) {
        for (const auto v : G[u]) {
          self[v]++;
        }
      }
      return self;
    }();

    const auto solution = [&](bool acc = true) {
      // mutable state
      auto Q = [&](std::deque<int> self = {}) {
        for (int i = 0; i < numCourses; ++i) {
          if (indegree[i] == 0) {
            self.emplace_back(i);
          }
        }
        return self;
      }();

      std::function<void(void)> bfs = [&, indegree = indegree, cnt = 0]() mutable {
        if (std::empty(Q)) {
          if (cnt != numCourses) {
            std::exchange(acc, false);
          }
          return;
        }
        else {
          const auto u = Q.front();
          Q.pop_front();
          ++cnt;
          for (const auto v : G[u]) {
            if (--indegree[v] == 0) {
              Q.emplace_back(v);
            }
          }
          bfs();
        }
      };

      return bfs(), acc;
    }();

    return solution;
  }
};

