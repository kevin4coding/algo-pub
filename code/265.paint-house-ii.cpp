class Solution {
 public:
  int minCostII(vector<vector<int>> &costs) {
    if (std::empty(costs)) {
      return 0;
    }
    
    const int n = std::size(costs);
    const int k = std::size(costs[0]);
    
    static struct {
      mutable std::optional<int> f[100][100];
      mutable std::optional<std::vector<std::pair<int, int>>> g[100];

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          g[i].reset();
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    std::function<std::vector<std::pair<int, int>>(int)> g;
    std::function<int(int, int)> f;
    
    g = [&, memo = mempool.g](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          auto A = std::vector<std::pair<int, int>>{};
          for (int c = 0; c < k; ++c) {
            A.emplace_back(std::pair{f(i, c), c});
          }
          std::nth_element(std::begin(A), std::begin(A), std::end(A));
          const auto n1 = A[0];
          std::nth_element(std::begin(A), std::begin(A) + 1, std::end(A));
          const auto n2 = A[1];
          return std::vector{n1, n2};

        }());
      }
    };

    f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return costs[i][j];
          }
          else {
            const auto P = g(i - 1);
            const auto [fst_min, fst_min_id] = P[0];
            const auto [snd_min, snd_min_id] = P[1];
            if (fst_min_id == j) {
              return f(i - 1, snd_min_id) + costs[i][j];
            }
            else {
              return f(i - 1, fst_min_id) + costs[i][j];
            }
          }
        }());
      }
    };

    const auto solution = [&](int acc = INT_MAX) {
      mempool.reset(n, k);
      for (int c = 0; c < k; ++c) {
        acc = std::min(acc, f(n - 1, c));
      }
      return acc;
    }();

    return solution;
  }
};


