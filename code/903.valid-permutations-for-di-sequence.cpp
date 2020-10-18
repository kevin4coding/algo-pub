class Solution {
 public:
  int numPermsDISequence(string S) {
    using int64 = long long;
    const int64 mod = 1e9 + 7;
    const int n = std:: size(S) + 1;

    struct {
      mutable std::optional<int> f[205][205] = {};
    } mempool;

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return int64(1);
          }
          else if (S[i - 1] == 'D') {
            return [&](int64 acc = 0) {
              for (int k = j; k <= i - 1; ++k) {
                acc = (acc + f(i - 1, k)) % mod;
              }
              return acc;
            }();
          }
          else if (S[i - 1] == 'I') {
            return [&](int64 acc = 0) {
              for (int k = 0; k < j; ++k) {
                acc = (acc + f(i - 1, k)) % mod;
              }
              return acc;
            }();
          }
          else throw;
        }());
      }
    };

    auto solve = [&](int64 acc = 0) {
      for (int j = 0; j < n; ++j) {
        acc = (acc + f(n - 1, j)) % mod;
      }
      return acc;
    };


    return solve();
  }
};
