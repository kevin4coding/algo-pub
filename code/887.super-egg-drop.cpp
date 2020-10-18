class Solution {
 public:
  int superEggDrop(int K, int N) {
    static struct {
      mutable std::optional<int> f[10005][105];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 or j == 0) {
            return 0;
          }
          else {
            return f(i - 1, j - 1) + f(i - 1, j) + 1;
          }
        }());
      }
    };

    auto solve = [&](std::optional<int> acc = {}) {
      mempool.reset(N, K);
      for (int i = 1; i <= N and not acc.has_value(); ++i) {
        if (f(i, K) >= N) {
          acc.emplace(i);
        }
      }
      return acc.value();
    };

    return solve();
  }
};
