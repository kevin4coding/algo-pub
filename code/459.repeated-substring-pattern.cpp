class Solution {
 public:

  bool repeatedSubstringPattern(string s) {
    const int n = s.size();

    // prefix function
    std::function<int(int)> f = [&, memo = std::vector<std::optional<int>>(n)](int i) mutable {
      if (memo[i].has_value()){ 
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 0;
          }
          else {
            return [&](std::optional<int> acc = {}) {
              for (int j = f(i - 1); j > 0 and not acc; j = f(j - 1)) {
                if (s[i] == s[j]) {
                  acc = j + 1;
                }
              }
              return acc.value_or(s[0] == s[i] ? 1 : 0);
            }();
          }
        }());
      }
    };

    if (f(n - 1) == 0) {
      return false;
    }
    else {
      return n % (n - f(n - 1)) == 0;
    }
  }
};
// leabbbbabbbb
