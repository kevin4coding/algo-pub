class Solution {
 public:
  int longestValidParentheses(string s) {
    const int n = std::size(s);
    
    static struct {
      mutable std::optional<int> f[20000];

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    mempool.reset(n);

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0 or s[i] == '(') {
            return 0;
          }
          else if (i == 1) {
            return s[0] == '(' ? 2 : 0;
          }
          else if (s[i - 1] == '(') {
            return 2 + f(i - 2);
          }
          else if (s[i - 1] == ')' and s[i] == ')') {
            if (i - f(i - 1) - 1 < 0 or s[i - f(i - 1) - 1] == ')') {
              return 0;
            }
            else {
              return f(i - 1) + (i - f(i - 1) - 2 >= 0 ? f(i - f(i - 1) - 2) : 0) + 2;
            }
          }
          throw std::domain_error({});
        }());
      }
    };

    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        acc = std::max(acc, f(i));
      }
      return acc;
    }();

    return solution;
  }
};
