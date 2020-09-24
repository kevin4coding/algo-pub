class Solution {
 public:
  bool validTree(int n, vector<vector<int>>& edges) {
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto & e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();

    const auto solution = [&](bool acc = true) {
      // mutable
      auto visited = std::vector<bool>(n, false);
      // check backedge
      std::function<void(int, std::optional<int>)> fold = [&](int u, std::optional<int> prev) {
        if (not acc) {
          return;
        }
        else {
          acc &= not visited[u];
          visited[u] = true;
          for (auto v : G[u]) {
            if (v != prev.value_or(~v)) {
              fold(v, u);
            }
          }
        }
      };

      if ((fold(0, std::optional<int>{}), acc) == true) {
        return std::find(std::begin(visited), std::end(visited), false) == std::end(visited);
      }
      else {
        return false;
      }
    }();
    return solution;
  }
};
