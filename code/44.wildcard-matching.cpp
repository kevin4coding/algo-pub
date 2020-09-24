class Solution {
 public:
  bool isMatch(string s, string p) {
    s = "#" + s;
    p = "#" + p;
    
    const int n1 = std::size(s);
    const int n2 = std::size(p);

    static struct {
      mutable std::optional<bool> f[4000][4000];
      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    mempool.reset(n1, n2);

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
            return p[j] == '*' and f(i, j - 1);
          }
          else if (i > 0 and j == 0) {
            return false;
          }
          else if (std::isalpha(p[j])) {
            return s[i] == p[j] ? f(i - 1, j - 1) : false;
          }
          else if (not std::isalpha(p[j])) {
            if (p[j] == '?') {
              return f(i - 1, j - 1);
            }
            else if (p[j] == '*') {
              const auto skip = f(i, j - 1);
              const auto match = [&](bool acc = false) {
                for (int k = 0; k < i and not acc; ++k) {
                  acc |= f(k, j - 1);
                }
                return acc;
              }();
              return skip or match;
            }
            throw std::domain_error({});
          }
          throw std::logic_error({});
        }());
      }
    };

    return f(n1 - 1, n2 - 1);
  }
};

