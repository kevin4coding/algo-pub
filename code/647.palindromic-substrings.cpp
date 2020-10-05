class Solution {
 public:
  int countSubstrings(string s) {
    const int n = std::size(s);
    
    static struct {
      mutable std::optional<bool> f[1005][1005];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    mempool.reset(n, n);

    std::function<bool(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == j) {
            return true;
          }
          else if (i + 1 == j) {
            return s[i] == s[j];
          }
          else if (s[i] == s[j]) {
            return f(i + 1, j - 1);
          }
          else if (s[i] != s[j]) {
            return false;
          }
          else throw;
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
          if (f(i, j)) {
            ++acc;
          }
        }
      }
      return acc;
    };

    return solve();
    
  }
};
