class Solution {
 public:
  int treeDiameter(vector<vector<int>>& edges) {
    const int n_vertex = std::size(edges) + 1;

    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(std::size(edges) + 1);
      for (const auto & e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();
    
    auto farthest = [&](int v) {
      auto result = std::optional<std::pair<int, int>>{};
      // mutable states
      auto Q = std::deque<int>{v};
      std::optional<int> D[10000];
      std::exchange(D[v], 0);
      
      std::function<void(void)> bfs = [&]() {
        if (std::empty(Q)) {
          const auto maxd = [&](int acc = INT_MIN) {
            for (int i = 0; i < n_vertex; ++i) {
              acc = std::max(acc, D[i].value_or(INT_MIN));
            }
            return acc;
          }();
          
          const auto maxd_id = [&](std::optional<int> self = {}) {
            for (int i = 0; i < n_vertex and not self.has_value(); ++i) {
              if (D[i].value_or(INT_MIN) == maxd) {
                self.emplace(i);
              }
            }
            return self.value();
          }();
          result.emplace(std::pair{maxd_id, maxd});
          return;
        }
        else {
          const auto n = Q.front();
          Q.pop_front();
          for (const auto next_n : G[n]) {
            if (not D[next_n].has_value()) {
              D[next_n] = D[n].value() + 1;
              Q.emplace_back(next_n);
            }
          }
          bfs();
        }
      };
      
      return bfs(), result.value();
    };

    return farthest(farthest(0).first).second;
  }
};
