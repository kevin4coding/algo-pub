class Solution {
 public:
  int numberOfArithmeticSlices(vector<int>& A) {
    struct {
      mutable std::optional<int> f[10000] = {};
    } mempool;

    const int n = std::size(A);
    
    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i < 2) {
            return 0;
          }
          else if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
            return 1 + f(i - 1);
          }
          else if (A[i] - A[i - 1] != A[i - 1] - A[i - 2]) {
            return 0;
          }
          else throw;
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        acc += f(i);
      }
      return acc;
    };

    return solve();
  }
};
