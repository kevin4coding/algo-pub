class Solution {
 public:
  int numDistinct(string s, string t) {
    static struct {
      mutable std::optional<int> f[11000][1000];

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for( int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;


    s = "#" + s;
    t = "#" + t;

    const int n1 = std::size(s);
    const int n2 = std::size(t);
    
    mempool.reset(n1, n2);
    
    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 and j == 0) {
            return 1;
          }
          else if (i == 0 and j > 0) {
            return 0;
          }
          else if (i > 0 and j == 0) {
            return s[i] == t[j] ? 1 + f(i - 1, j) : f(i - 1, j);
          }
          else if (s[i] == t[j]) {
            return f(i - 1, j) + f(i - 1, j - 1);
          }
          else if (s[i] != t[j]) {
            return f(i - 1, j);
          }
          throw std::logic_error({});
        }());
      }
    };

    return f(n1 - 1, n2 - 1);
  }
};
