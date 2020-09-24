class Solution {
 public:
  int minReorder(int n, vector<vector<int>>& connections) {
    const auto G = [&](std::vector<std::vector<pair<int, int>>> self = {}) {
      self.resize(n);
      for (const auto & e : connections) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v, 1);
        self[v].emplace_back(u, 0);
      }
      return self;
    }();

    const auto solution = [&](int acc = 0) {
      std::function<void(int)> fold = [&, visited = std::vector<bool>(n, false)](int u) mutable {
        visited[u] = true;
        for (const auto [v, w] : G[u]) {
          if (not visited[v]) {
            acc += w;
            fold(v);
          }
        }
      };
      return fold(0), acc;
    }();
    
    return solution;
  }
};
