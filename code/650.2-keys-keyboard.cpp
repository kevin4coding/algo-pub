class Solution {
 public:
  int minSteps(int n) {
    struct {
      mutable std::optional<int> f[1005] = {};
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 1) {
            return 0;
          }
          else {
            return [&, acc = int(i)]() mutable {
              for (int j = 2; j <= i / 2; ++j) {
                if (i % j == 0) {
                  acc = std::min(acc, f(i / j) + j);
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
