
class Solution {
 public:
  int minCost(vector<vector<int>>& costs) {
    if (std::empty(costs)) {
      return 0;
    }
    
    static struct {
      mutable std::optional<int> f[500][3] = {};
      
      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    const int n = std::size(costs);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return costs[i][j];
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int color = 0; color < 3; ++color) {
                if (color != j) {
                  acc = std::min(acc, costs[i][j] + f(i - 1, color));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return mempool.reset(n, 3), std::min({f(n - 1, 0), f(n - 1, 1), f(n - 1, 2)});
  }
};
