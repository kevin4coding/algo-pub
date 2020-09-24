class Solution {
 public:
  string longestPalindrome(string s) {
    const int n = std::size(s);
    
    static struct {
      mutable std::optional<int> g[1000][1000];

      void clear(int n, int m) {
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            g[i][j].reset();
          }
        }
      }
    } mempool;

    mempool.clear(n, n);

    std::function<int(int, int)> g = [&, memo = mempool.g](int i, int j) {
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
          else {
            return s[i] == s[j] and g(i + 1, j - 1);
          }
        }());
      }
    };

    const auto solution = [&]() {
      // could be done using another recursion with backtrace. But it does not pass the OJ.
      struct {
        mutable std::pair<int, int> range = {};
        mutable int acc = 0;
      } ST;
      
      for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
          if (g(i, j) and j - i + 1 > ST.acc) {
            ST.acc = std::max(j - i + 1, ST.acc);
            ST.range = {i, j};
          }
        }
      }
      return s.substr(ST.range.first, ST.range.second - ST.range.first + 1);
    }();

    return solution;
  }
};
