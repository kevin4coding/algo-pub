class Solution {
 public:
  int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
    const struct {
      mutable std::optional<int> f[100000];
      mutable std::optional<bool> g[100000];
    } mempool;


    const auto G_initial = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto & e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();

    const auto parent = [&](std::vector<int> self = {}) {
      self.resize(n);
      std::function<void(int)> fold = [&, visited = std::vector<bool>(n, false)](int u) mutable {
        if (std::size(G_initial[u]) == 1 and u != 0) {
          return;
        }
        else {
          visited[u] = true;
          if (u == 0) {
            self[u] = -1;
          }
          for (const auto v : G_initial[u]) {
            if (not visited[v]) {
              self[v] = u;
              fold(v);
            }
          }

        }
      };
      return fold(0), self;
    }();
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
          self[parent[i]].emplace_back(i);
        }
      }
      return self;
    }();


    std::function<bool(int)> g = [&, memo = std::ref(mempool.g)](int u) {
      if (memo[u].has_value()) {
        return memo[u].value();
      }
      else {
        return memo[u].emplace([&] {
          if (hasApple[u]) {
            return true;
          }
          else {
            return [&](bool acc = false) {
              for (const auto v : G[u]) {
                acc |= g(v);
              }
              return acc;
            }();
          }
        }());
      }
    };

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)] (int u) {
      if (memo[u].has_value()) {
        return memo[u].value();
      }
      else {
        return memo[u].emplace([&] {
          if (std::size(G[u]) == 0) {
            return 0;
          }
          else {
            return [&](int acc = 0) {
              for (const auto v : G[u]) {
                if (g(v)) {
                  acc += 2 + f(v);
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f(0);
  }
};
