class Solution {
 public:
  
  int numDecodings(string s) {
    struct {
      mutable std::optional<int> f[10005] = {};
    } mempool;

    const int n = std::size(s);

    using int64 = long long;

    const int64 mod = 1e9 + 7;

    std::function<int64(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            if (s[i] == '*') {
              return int64(9);
            }
            else if (s[i] == '0') {
              throw std::domain_error({});
            }
            else {
              return int64(1);
            }
                
          }
          else if (s[i] == '*') {
            if (s[i - 1] == '*') {
              return 9 * f(i - 1) + 15 * (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else if (s[i - 1] == '0') {
              return 9 * f(i - 1);
            }
            else if (s[i - 1] == '1') {
              return 9 * f(i - 1) + 9 * (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else if (s[i - 1] == '2') {
              return 9 * f(i - 1) + 6 * (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else {
              return 9 * f(i - 1);
            }
          }
          else if (s[i] == '0') {
            if (s[i - 1] == '*') {
              return 2 * (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else if (s[i - 1] != '1' and s[i - 1] != '2') {
              throw std::domain_error({});
            }
            else {
              return (i - 2 >= 0 ? f(i - 2) : 1);
            }
          }
          else if ('1' <= s[i] and s[i] <= '6') {
            if (s[i - 1] == '*') {
              return f(i - 1) + 2 * (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else if (s[i - 1] == '0') {
              return f(i - 1);
            }
            else if (s[i - 1] == '1' or s[i - 1] == '2') {
              return f(i - 1) + (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else {
              return f(i - 1);
            }
          }
          else if (s[i] > '6') {
            if (s[i - 1] == '*') {
              return f(i - 1) + (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else if (s[i - 1] == '0') {
              return f(i - 1);
            }
            else if (s[i - 1] == '1') {
              return f(i - 1) + (i - 2 >= 0 ? f(i - 2) : 1);
            }
            else {
              return f(i - 1);
            }
          }
          else throw;
        }());
      }
    };

    try {
      return f(n - 1) % mod;
    }
    catch (const std::exception& e) {
      return 0;
    }
  }
};
