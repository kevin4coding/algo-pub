class Solution {
 public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
    const auto G = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      self.resize(n);
      for (const auto & e : red_edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v, 0);
      }

      for (const auto & e : blue_edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v, 1);
      }

      return self;
    }();

    struct {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> D[105][2];
    } ST;

    auto init_ST = [&]() {
      ST.Q.emplace_back(0, 0);
      ST.Q.emplace_back(0, 1);
      ST.D[0][0] = 0;
      ST.D[0][1] = 0;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q)) {
        return;
      }
      else {
        const auto [u, u_color] = Q.front();
        Q.pop_front();
        for (const auto [v, v_color] : G[u]) {
          if (v_color != u_color and not D[v][v_color].has_value()) {
            D[v][v_color] = D[u][u_color].value() + 1;
            Q.emplace_back(v, v_color);
          }
        }
        return bfs();
      }
    };

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(n);
      init_ST();
      bfs();
      
      for (int i = 0; i < n; ++i) {
        if (not ST.D[i][0].has_value() and not ST.D[i][1].has_value()) {
          self[i] = -1;
        }
        else {
          self[i] = std::min(ST.D[i][0].value_or(INT_MAX), ST.D[i][1].value_or(INT_MAX));
        }
      }

      return self;
    }();

    return solution;
    
  }
};
