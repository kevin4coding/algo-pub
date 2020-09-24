class Solution {
 public:
  int numWays(int n, int k) {
    if (n == 0) {
      return 0;
    }
    
    static struct {
      mutable std::optional<int> f[1000];

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return k;
          }
          else if (i == 1) {
            return k * k;
          }
          else if (i > 1) {
            return f(i - 1) * (k - 1) + f(i - 2) * (k - 1);
          }
          throw;
        }());
      }
    };

    return (mempool.reset(n), f(n - 1));

    
  }
};
