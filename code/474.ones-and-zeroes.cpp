static struct {
  mutable std::optional<int> f[600][105][105] = {};

  void reset(int r, int c, int l) {
    for (int i = 0; i <= r; ++i) {
      for (int j = 0; j <= c; ++j) {
        for (int k = 0; k <= l; ++k) {
          f[i][j][k].reset();
        }
      }
    }
  }
} mempool;

class Solution {
 public:
  int findMaxForm(vector<string>& strs, int M, int N) {
    const int k = std::size(strs);

    auto compute_cost = [](const std::string &s) -> std::array<int, 2> {
      auto acc = std::array<int, 2>{0, 0};
      for (const char ch : s) {
        if (ch == '1') {
          acc[1]++;
        }
        else if (ch == '0') {
          acc[0]++;
        }
      }
      return acc;
    };

    const auto costs = [&](std::vector<std::array<int, 2>> self = {}) {
      self.resize(k, std::array{0, 0});
      for (int i = 0; i < k; ++i) {
        self[i] = compute_cost(strs[i]);
      }
      return self;
    }();

    const int n = std::size(strs);

    std::function<int(int, int, int)> f = [&, memo = mempool.f](int i, int r1, int r0) {
      if (memo[i][r1][r0].has_value()) {
        return memo[i][r1][r0].value();
      }
      else {
        return memo[i][r1][r0].emplace([&]{
          if (i == 0) {
            return int(r0 - costs[i][0] >= 0 and r1 - costs[i][1] >=  0);
          }
          else if (r0 - costs[i][0] >= 0 and r1 - costs[i][1] >= 0) {
            return std::max(1 + f(i - 1, r1 - costs[i][1], r0 - costs[i][0]), f(i - 1, r1, r0));
          }
          else {
            return f(i - 1, r1, r0);
          }
        }());
      }
    };
    
    return mempool.reset(n - 1, N, M), f(n - 1, N, M);
  }
};
