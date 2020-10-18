class Solution {
 public:
  int shortestPathLength(vector<vector<int>>& graph) {
    const int n = std::size(graph);
    
    struct {
      mutable std::optional<int> f[1 << 13][13] = {};
      mutable std::optional<int> d[13][13][13] = {};
    } mempool;


    auto test = [](int mask, int pos) {
      return (mask & (1 << pos)) > 0;
    };

    auto flip = [](int mask, int pos) {
      return mask | (1 << pos);
    };
    
    const auto w = [&](std::vector<std::vector<std::optional<int>>> self = {}) {
      self.resize(n, std::vector<std::optional<int>>(n, std::nullopt));
      for (int v = 0; v < n; ++v) {
        for (const auto u : graph[v]) {
          self[u][v] = 1;
          self[v][u] = 1;
        }
      }
      
      return self;
    }();

    std::function<int(int, int, int)> d = [&, memo = mempool.d](int i, int j, int k) {
      if (memo[i][j][k].has_value()) {
        return memo[i][j][k].value();
      }
      else {
        return memo[i][j][k].emplace([&] {
          if (k == 0) {
            return w[i][j].value_or(INT_MAX / 2);
          }
          else {
            return std::min(d(i, j, k - 1), d(i, k - 1, k - 1) + d(k - 1, j, k - 1));
          }
        }());
      }
    };


    auto D = [&](int i, int j) {
      return d(i, j, n);
    };

    std::function<int(int, int)> f = [&, memo = mempool.f](int mask, int v) {
      if (memo[mask][v].has_value()) {
        return memo[mask][v].value();
      }
      else {
        return memo[mask][v].emplace([&] {
          if (mask == ((1 << n) - 1)) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              for (int u = 0; u < n; ++u) {
                if (not test(mask, u)) {
                  acc = std::min(acc, D(v, u) + f(flip(mask, u), u));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };


    auto solve = [&](int acc = INT_MAX) {
      for (int v = 0; v < n; ++v) {
        acc = std::min(acc, f(flip(0, v), v));
      }
      return acc;
    }();

    return solve;
  }
};
