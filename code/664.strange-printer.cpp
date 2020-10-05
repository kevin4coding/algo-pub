class Solution {
 public:
  int strangePrinter(string s) {
    if (std::empty(s)) {
      return 0;
    }
    
    struct {
      mutable std::optional<int> f[105][105];
    } mempool;

    const int n = std::size(s);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == j) {
            return 1;
          }
          else if (i + 1 == j) {
            return s[i] == s[j] ? 1 : 2;
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              // alone
              acc = std::min(acc, 1 + f(i + 1, j));
              // middle
              for (int k = i + 1; k <= j; ++k) {
                if (s[i] == s[k]) {
                  acc = std::min(acc, f(i, k - 1) + ((k == j) ? 0 : f(k + 1, j)));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f(0, n - 1);
  }
};

