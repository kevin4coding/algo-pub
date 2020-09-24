class Solution {
 public:
  bool isMatch(string s, string p) {
    static struct {
      mutable std::optional<int> f[3000][3000];
      void clear(int n, int m) {
        for (int i = 0; i <= n; ++i) {
          for (int j = 0; j <= m; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    // open question: is there a way to not pad and not mess up the code?
    const int n1 = std::size(s);
    const int n2 = std::size(p);
    
    s = "#" + s;
    p = "#" + p;

    mempool.clear(n1, n2);
    
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
            return j == 1 ? p[j] == '*' : p[j] == '*' and f(i, j - 2);
          }
          else if (j == 0 and i > 0) {
            return false;
          }
          else if (std::isalpha(p[j])) {
            return p[j] == s[i] ? f(i - 1, j - 1) : false;
          }
          else {
            if (p[j] == '*') {
              if (p[j - 1] == s[i] or p[j - 1] == '.') {
                return f(i - 1, j) or f(i - 1, j - 2) or f(i, j - 2);
              }
              else {
                return f(i, j - 2);
              }
            }
            else if (p[j] == '.') {
              return f(i - 1, j - 1);
            }
            else throw std::logic_error({});
          }
        }());
      }
    };
    
    return f(n1, n2);
  }
};
