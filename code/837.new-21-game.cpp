class Solution {
 public:
  double new21Game(int N, int K, int W) {
    struct {
      mutable std::optional<double> f[30000] = {};
    } mempool;

    std::function<double(int)> f = [&, memo = mempool.f](int i) -> double {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i > std::min(N, K + W)) {
            return 0.0;
          }
          else if (i >= K and i <= std::min(N, K + W)) {
            return 1.0;
          }
          else if (i == K - 1) {
            return (std::min(N, K + W - 1) - K + 1) / double(W);
          }
          else if (i < K - 1) {
            return f(i + 1) + (1.0 / double(W)) * (f(i + 1) -  f(i + W + 1));
          }
          else throw;
        }());
      };
    };

    return f(0);
  }
};
