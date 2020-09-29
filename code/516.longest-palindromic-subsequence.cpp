class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    struct {
      mutable std::optional<int> f[1005][1005] = {};
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
            return s[i] == s[j] ? 2 : 1;
          }
          else if (s[i] == s[j]) {
            return 2 + f(i + 1, j - 1);
          }
          else if (s[i] != s[j]) {
            return std::max(f(i + 1, j), f(i, j - 1));
          }
          else throw;
        }());
      }
    };

    return f(0, n - 1);
  }
};
