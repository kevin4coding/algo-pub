class Solution {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    static struct {
      mutable std::optional<bool> f[105][105];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;


    s1 = "#" + s1;
    s2 = "#" + s2;
    s3 = s3;

    const int n1 = std::size(s1);
    const int n2 = std::size(s2);
    const int n3 = std::size(s3);

    std::function<bool(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 and j == 0) {
            return true;
          }
          else if (i == 0 and j > 0) {
            return s3[j - 1] == s2[j] ? f(i, j - 1) : false;
          }
          else if (i > 0 and j == 0) {
            return s3[i - 1] == s1[i] ? f(i - 1, j) : false;
          }
          else if (s1[i] == s2[j]) {
            return s1[i] != s3[i + j - 1] ? false : (f(i - 1, j) or f(i, j - 1));
          }
          else if (s1[i] != s2[j] and s1[i] == s3[i + j - 1]) {
            return f(i - 1, j);
          }
          else if (s1[i] != s2[j] and s2[j] == s3[i + j - 1]) {
            return f(i, j - 1);
          }
          else if (s1[i] != s2[j] and s2[j] != s3[i + j - 1] and s1[i] != s3[i + j - 1]) {
            return false;
          }
          throw std::logic_error({});
        }());
      }
    };

    auto solve = [&]() {
      if (n1 + n2 != n3 + 2) {
        return false;
      }
      else {
        return mempool.reset(n1, n2), f(n1 - 1, n2 - 1);
      }
    };

    return solve();
  }
};
