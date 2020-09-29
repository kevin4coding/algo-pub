class Solution {
 public:
  string encode(string s) {
    struct {
      mutable std::optional<int> PI[200][200] = {};
      mutable std::optional<std::string> f[200][200] = {};
    } mempool;
    
    std::function<int(int, int)> PI = [&, memo = mempool.PI](int i, int j) {
      if (memo[i][j]) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (j == i) {
            return 0;
          }
          else {
            return [&](std::optional<int> acc = {}) {
              for (int k = PI(i, j - 1); k > 0 and not acc.has_value(); k = PI(i, i + k - 1)) {
                if (s[j] == s[i + k]) {
                  acc = k + 1;
                }
              }
              return acc.value_or(s[i] == s[j] ? 1 : 0);
            }();
          }
        }());
      }
    };

    const int n = std::size(s);

    auto compress = [&](int i, int j) -> int {
      const int L = j - i + 1;

      if (PI(i, j) == 0) {
        return -1;
      }
      else if (L % (L - PI(i, j)) == 0) {
        return L - PI(i, j);
      }
      else {
        return -1;
      }
    };

    std::function<std::string(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (j - i + 1 <= 4) {
            return s.substr(i, j - i + 1);
          }
          else {
            const auto m = compress(i, j);
            if (m != -1) {
              return std::to_string((j - i + 1) / m) + "[" + f(i, i + m - 1) + "]";
            }
            else {
              return [&, acc = s.substr(i, j - i + 1)]() mutable {
                for (int k = i + 1; k < j; ++k) {
                  if (std::size(f(i, k) + f(k + 1, j)) < std::size(acc)) {
                    acc = f(i, k) + f(k + 1, j);
                  }
                }
                return acc;
              }();
            }
          }
        }());
      }
    };
    
    return f(0, n - 1);
  }
};
