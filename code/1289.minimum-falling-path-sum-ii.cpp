class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& arr) {
    
    auto& costs = arr;
    if (std::empty(costs)) {
      return 0;
    }

    
    static struct {
      mutable std::optional<int> f[1000][1000];

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;
    
    const int n = std::size(costs);
    const int k = std::size(costs[0]);
    

    // could be made in O(n) time but mehhh. Extra log factor doesn't matter that much
    const auto sorted_value_index_pair = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      self.resize(n, std::vector<std::pair<int, int>>{});
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
          self[i].emplace_back(std::pair{costs[i][j], j});
        }
        std::sort(std::begin(self[i]), std::end(self[i]), [&](auto &x, auto &y) {
          return x.first < y.first;
        });
      }
      return self;
    }();



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
            const auto [fst_min_val, fst_min_id] = sorted_value_index_pair[i - 1][0];
            const auto [snd_min_val, snd_min_id] = sorted_value_index_pair[i - 1][1];
            if (fst_min_id == j) {
              return f(i - 1, snd_min_id) + costs[i][j];
            }
            else {
              return std::min(f(i - 1, snd_min_id), f(i - 1, fst_min_id)) + costs[i][j];
            }
          }
        }());
      }
    };

    const auto solution = [&](int acc = INT_MAX) {
      mempool.reset(n, k);
      for (int i = 0; i < k; ++i) {
        acc = std::min(acc, f(n - 1, i));
      }
      return acc;
    }();

    return solution;
  }
};
