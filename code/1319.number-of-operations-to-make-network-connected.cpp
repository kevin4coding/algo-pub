class Solution {
 public:
  int makeConnected(int n, vector<vector<int>>& connections) {
    const struct {
      mutable std::vector<bool> vis;
      mutable int cc_cnt;
    } ST;

    auto init_ST = [&]() {
      ST.cc_cnt = 0;
      ST.vis.resize(n, false);
    };

    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto & e : connections) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();

    std::function<void(int)> fold = [&](int u) {
      ST.vis[u] = true;
      for (const auto v : G[u]) {
        if (not ST.vis[v]) {
          fold(v);
        }
      }
    };

    const auto solution = [&]() {
      if (std::size(connections) < n - 1) {
        return -1;
      }
      else {
        return [&]() {
          init_ST();
          for (int u = 0; u < n; ++u) {
            if (not ST.vis[u]) {
              ++ST.cc_cnt;
              fold(u);
            }
          }
          return ST.cc_cnt - 1;
        }();
      }
    }();

    return solution;
  }
};
