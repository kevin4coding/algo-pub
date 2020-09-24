class Solution {
 public:
  int integerBreak(int n) {
    static struct {
      mutable std::optional<int> f[100];

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
          if (i == 1) {
            return 1;
          }
          else {
            return [&](int acc = INT_MIN) {
              for (int k = 1; k <= i - 1; ++k) {
                acc = std::max({acc, k * f(i - k), k * (i - k)});
              }
              return acc;
            }();
          }
        }());
      }
    };
  
    return (mempool.reset(n + 1), f(n));
  }
};
