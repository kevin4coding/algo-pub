class Solution {
 public:
  bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
    const int black = 0;
    const int white = 1;
    
    const struct {
      mutable std::deque<int> Q;
      mutable std::optional<int> color[2005];
      mutable std::optional<bool> is_bipartite;
    } ST;

    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(N + 1);
      for (const auto & e : dislikes) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();
    

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q) or ST.is_bipartite) {
        return;
      }
      else {
        const auto u = ST.Q.front();
        ST.Q.pop_front();
        for (const auto v : G[u]) {
          if (not ST.color[v].has_value()) {
            ST.color[v] = ~(ST.color[u].value());
            ST.Q.emplace_back(v);
          }
          else if (ST.color[v].value() == ST.color[u].value()) {
            ST.is_bipartite = false;
            return;
          }
          else if (ST.color[v].value() != ST.color[u].value()) {
            // do nothing
          }
        }
        return bfs();
      }
    };

    const auto solution = [&]() {
      for (int u = 1; u <= N; ++u) {
        if (not ST.color[u].has_value()) {
          ST.Q = std::deque<int>{u};
          ST.color[u] = black;
          bfs();
        }
      }
      return ST.is_bipartite.value_or(true);
    }();

    return solution;
  }
};
