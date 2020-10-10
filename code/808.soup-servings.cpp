class Solution {
 public:
  double soupServings(int N) {
    struct {
      mutable std::unordered_map<int, std::unordered_map<int, std::optional<double>>> f = {};
    } mempool;

    std::function<double(int, int)> f = [&, &memo = mempool.f](int a, int b) {
      if (memo[a][b].has_value()) {
        return memo[a][b].value();
      }
      else {
        return memo[a][b].emplace([&] {
          if (a <= 0 and b <= 0) {
            return 0.5;
          }
          else if (a <= 0 and b > 0) {
            return 1.0;
          }
          else if (a > 0 and b <= 0) {
            return 0.0;
          }
          else {
            return 0.25 * (f(a - 100, b) + f(a - 75, b - 25) + f(a - 50, b - 50) + f(a - 25, b - 75));
          }
        }());
      }
    };

    if (N >= 6000) {
      return 1.0;
    }
    else {
      return f(N, N);
    }
  }
};

