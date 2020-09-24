class Solution {
 public:
  int longestValidParentheses(string s) {
    // O(n^2) solution does not pass the test.
    const int n = std::size(s);
    
    static struct {
      mutable std::optional<int> f[5000][5000];

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
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
          if (i == j or (s[i] == ')' or s[j] == '(')) {
            return false;
          }
          else if (i + 1 == j) {
            return s[i] == '(' and s[j] == ')';
          }
          else {
            return [&](bool acc = false) {
              for (int k = i + 1; k < j - 1 and acc == false; ++k) {
                acc |= f(i, k) and f(k + 1, j);
              }
              return acc or f(i + 1, j - 1);
            }();
          }
        }());
      }
    };

    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (f(i, j)) {
            acc = std::max(acc, j - i  + 1);
          }
        }
      }
      return acc;
    }();

    return solution;
  }
};
