class Solution {
 public:
  int kInversePairs(int n, int k) {
    static struct {
      mutable std::optional<int> f[1005][1005];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;
    
    using int64 = long long;
    const static int64 mod = 1000000007;

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 1) {
            return int64(j == 0 ? 1 : 0);
          }
          else if (j == 0) {
            return int64(1);
          }
          else if (i > j) {
            return (f(i, j - 1) + f(i - 1, j)) % mod;
          }
          else if (i <= j) {
            return ((f(i, j - 1) + f(i - 1, j) % mod) - f(i - 1, j - i) % mod + mod) % mod;
          }
          else throw;
        }());
      }
    };

    return (mempool.reset(n, k), f(n, k));
  }
};

