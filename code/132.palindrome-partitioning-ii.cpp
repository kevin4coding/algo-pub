class Solution {
 public:
  int minCut(string s) {
    static const int maxn = 2005;
    
    static struct {
      mutable std::optional<int> f[maxn];
      mutable std::optional<bool> g[maxn][maxn];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          f[i].reset();
        }
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            g[i][j].reset();
          }
        }
      }
    } mempool;

    const int n = std::size(s);

    mempool.reset(n, n);

    std::function<bool(int, int)> g = [&, memo = mempool.g](int i, int j) {
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
            return g(i + 1, j - 1);
          }
          else {
            return false;
          }
        }());
      }
    };

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 0;
          }
          else if (i == 1) {
            return s[i] == s[i - 1] ? 0 : 1;
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int k = 0; k <= i and acc > 0; ++k) {
                if (g(k, i)) {
                  acc = std::min(acc, k == 0 ? 0 : 1 + f(k - 1));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };
    
    return f(n - 1);
    
  }
};
