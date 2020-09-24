class Solution {
 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    using node_t = std::tuple<int, int, int>;
    
    const auto G = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      self.resize(n);
      for (const auto & e : flights) {
        const auto [u, v, w] = std::tuple{e[0], e[1], e[2]};
        self[u].emplace_back(std::pair{v, w});
      }
      return self;
    }();

    struct {
      mutable std::priority_queue<node_t, std::vector<node_t>, std::greater<>> PQ = {};
      mutable std::optional<int> D[105][105] = {};
    } ST;

    auto init_ST = [&]() {
      ST.PQ.emplace(std::tuple<int, int, int>{0, 0, src});
      ST.D[src][0] = 0;
    };

    std::function<void(void)> dijkstra = [&, &PQ = ST.PQ, &D = ST.D]() {
      if (std::empty(PQ)) {
        return;
      }
      else {
        const auto [d_u, k_u, u] = PQ.top();
        PQ.pop();
        if (D[u][k_u].value_or(INT_MIN) > d_u) {
          return dijkstra();
        }
        else {
          for (const auto [v, w] : G[u]) {
            if (k_u + 1 <= K + 1 and D[v][k_u + 1].value_or(INT_MAX) > D[u][k_u].value() + w) {
              D[v][k_u + 1] = D[u][k_u].value() + w;
              PQ.emplace(std::tuple<int, int, int>{D[v][k_u + 1].value(), k_u + 1, v});
            }
          }
          return dijkstra();
        }
      }
    };

    const auto solution = [&](int acc = INT_MAX) {
      init_ST();
      dijkstra();
      for (int k = 1; k <= K + 1; ++k) {
        if (ST.D[dst][k].has_value()) {
          acc = std::min(ST.D[dst][k].value(), acc);
        }
      }
      return acc;
    }();


    return solution == INT_MAX ? -1 : solution;
  }
};

