struct {
  mutable std::optional<int> f[2000][2000] = {};

  void reset(int r, int c) {
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        f[i][j].reset();
      }
    }
  }
} mempool;



class Solution {
 public:
  int getMoneyAmount(int n) {

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == j) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int k = i; k <= j; ++k) {
                if (k == i) {
                  acc = std::min(acc, k + f(k + 1, j));
                }
                else if (k == j) {
                  acc = std::min(acc, k + f(i, k - 1));
                }
                else {
                  acc = std::min(acc, k + std::max(f(k + 1, j), f(i, k - 1)));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return mempool.reset(0, n + 1), f(1, n);
  }
};
