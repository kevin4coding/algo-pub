class Solution {
 public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto& e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    auto farthest = [&](int u) {
      struct {
        mutable std::deque<int> Q = {};
        mutable std::vector<std::optional<int>> D = {};
        mutable std::vector<std::optional<int>> prev = {};
        mutable std::pair<int, int> farleaf;
      } ST;

      auto init_ST = [&]() {
        ST.Q.emplace_back(u);
        ST.D.resize(n, std::optional<int>{});
        ST.D[u] = 1;
        ST.prev.resize(n);
      };

      std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
        if (std::empty(Q)) {
          const auto [maxd, maxd_id] = [&](int acc = INT_MIN, int acc_id = -1) {
            for (int i = 0; i < n; ++i) {
              if (D[i].has_value() and D[i].value() > acc) {
                acc = D[i].value();
                acc_id = i;
              }
            }
            return std::pair{acc, acc_id};
          }();
          std::exchange(ST.farleaf, std::pair{maxd, maxd_id});
          return;
        }
        else {
          const auto curr_level = ST.Q;
          ST.Q.clear();
          for (const auto u : curr_level) {
            for (const auto v : G[u]) {
              if (not D[v].has_value()) {
                D[v] = D[u].value() + 1;
                Q.emplace_back(v);
                ST.prev[v] = u;
              }
            }
          }
        }
        return bfs();
      };
      
      return (init_ST(), bfs(), ST);
    };

    const auto ST = farthest(farthest(0).farleaf.second);
      
    const auto longest_path = [&](std::vector<int> self = {}) {
      std::function<void(std::optional<int>)> fold = [&](std::optional<int> n) {
        if (not n.has_value()) {
          return;
        }
        else {
          self.emplace_back(n.value());
          return fold(ST.prev[n.value()]);
        }
      };
      return fold(std::make_optional(ST.farleaf.second)), self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      if (ST.farleaf.first % 2 == 0) {
        self.emplace_back(longest_path[ST.farleaf.first / 2 - 1]);
        self.emplace_back(longest_path[ST.farleaf.first / 2]);
      }
      else {
        self.emplace_back(longest_path[ST.farleaf.first / 2]);
      }
      return self;
    }();

    return solution;
  }
};
