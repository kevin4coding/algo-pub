static const struct {
  mutable std::optional<int> f[102][102][102] = {};

  void reset(int r, int c, int l) const {
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
  int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
    using int64 = long;
    const int64 mod = 1e9 + 7;
    const int N = std::size(group);

    std::function<int64(int, int, int)> f = [&, memo = mempool.f](int i, int j, int k) {
      if (memo[i][j][k].has_value()) {
        return memo[i][j][k].value();
      }
      else {
        return memo[i][j][k].emplace([&] {
          if (i == 0) {
            return int64(k == 0) + int64(j >= group[i] and profit[i] >= k);
          }
          else {
            return [&](int64 acc = 0) {
              acc = (acc + f(i - 1, j, k)) % mod;
              if (j >= group[i]) {
                acc = (acc + f(i - 1, j - group[i], std::max(0, k - profit[i]))) % mod;
              }
              return acc;
            }();
          }
        }());
      }
    };

    return mempool.reset(N - 1, G, P), f(N - 1, G, P);
  }
};
