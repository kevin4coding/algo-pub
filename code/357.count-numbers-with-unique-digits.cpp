class Solution {
 public:
  int countNumbersWithUniqueDigits(int n) {
    struct {
      std::optional<int> f[11] = {};
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else if (i == 1) {
            return 10;
          }
          else if (i == 2) {
            return 9 * 9;
          }
          else {
            return f(i - 1) * (10 - i + 1);
          }
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      if (n == 0) {
        return 1;
      }
      else {
        for (int i = 1; i <= n; ++i) {
          acc += f(i);
        }
        return acc;
      }
    };

    return solve();
  }
};
