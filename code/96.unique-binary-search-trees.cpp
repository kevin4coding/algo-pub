class Solution {
 public:
  int numTrees(int n) {
    const struct {
      mutable std::optional<int> G[20];
    } mempool;

    std::function<int(int)> G;
    std::function<int(int, int)> F;

    G = [&, memo = std::ref(mempool.G)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0 or i == 1) {
            return 1;
          }
          else {
            return [&](int acc = 0) {
              for (int k = 1; k <= i; ++k) {
                acc += F(k, i);
              }
              return acc;
            }();
          }
        }());
      }
    };

    F = [&](int k, int i) {
      return G(k - 1) * G(i - k);
    };

    return G(n);
  }
};
