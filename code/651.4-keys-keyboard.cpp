class Solution {
 public:
  int maxA(int N) {
    struct {
      mutable std::optional<int> f[55];
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
          else if (i == 2) {
            return 2;
          }
          else {
            return [&](int acc = INT_MIN) {
              // just type A
              acc = std::max(acc, f(i - 1) + 1);
              // copy paste
              for (int j = i - 2; j >= 2; --j) {
                acc = std::max(acc, f(j) * (i - (j + 2) + 1));
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f(N);
  }
};
