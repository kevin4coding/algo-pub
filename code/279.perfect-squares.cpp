class Solution {
 public:
  int numSquares(int n) {
    static struct {
      mutable std::optional<int> f[10000] = {};
      
      void reset(int n) {
        for (int i = 0; i < n; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    mempool.reset(n);

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int j = 1; j * j <= i; ++j) {
                if ((i - j * j) >= 0) { 
                  acc = std::min(acc, 1 + f(i - j * j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f(n);
  }
};
