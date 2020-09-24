class Solution {
 public:
  int countComponents(int n, vector<vector<int>>& edges) {
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto & e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    const auto solution = [&](int acc = 0) {
      // mutable state
      auto visited = std::vector<bool>(n, false);
      
      std::function<void(int)> fold = [&](int u) {
        visited[u] = true;
        for (const auto v : G[u]) {
          if (not visited[v]) {
            fold(v);
          }
        }
      };

      for (int u = 0; u < n; ++u) {
        if (not visited[u]) {
          ++acc;
          fold(u);
        }
      }

      return acc;
      
    }();

    return solution;
  }
};
