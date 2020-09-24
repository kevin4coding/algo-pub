class Solution {
 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    const int N = std::size(quiet);
    
    const struct {
      mutable std::optional<int> f[500];
    } mempool;

    const auto quiet_map = [&](std::unordered_map<int, int> self = {}) {
      for (int i = 0; i < N; ++i) {
        self[quiet[i]] = i;
      }
      return self;
    }();
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(N);
      for (const auto & e : richer) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[v].emplace_back(u);
      }
      return self;
    }();

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int u) {
      if (memo[u].has_value()) {
        return memo[u].value();
      }
      else {
        return memo[u].emplace([&] {
          if (std::empty(G[u])) {
            return quiet[u];
          }
          else {
            return [&](int acc = INT_MAX) {
              for (const auto v : G[u]) {
                acc = std::min(acc, f(v));
              }
              acc = std::min(acc, quiet[u]);
              return acc;
            }();
          }
        }());
      }
    };

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(N);
      for (int i = 0; i < N; ++i) {
        self[i] = quiet_map.at(f(i));
      }
      return self;
    }();

    return solution;
  }
};
