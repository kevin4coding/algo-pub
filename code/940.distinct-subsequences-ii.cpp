class Solution {
 public:
  int distinctSubseqII(string S) {
    using int64 = long long;
    const static int64 mod = 1e9 + 7;
    const int n = std::size(S);
    
    struct {
      mutable std::optional<int> f[2005][26] = {};
    } mempool;

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int ch) {
      if (memo[i][ch].has_value()) {
        return memo[i][ch].value();
      }
      else {
        return memo[i][ch].emplace([&] {
          if (i == 0) {
            return S[i] - 'a' == ch ? int64(1) : int64(0);
          }
          else if (S[i] - 'a' != ch) {
            return f(i - 1, ch);
          }
          else {
            return [&](int64 acc = 0) {
              acc = (acc + 1) % mod;
              for (int k = 0; k < 26; ++k) {
                acc = (acc + f(i - 1, k)) % mod;
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int64 acc = 0) {
      for (int k = 0; k < 26; ++k) {
        acc = (acc + f(n - 1, k)) % mod;
      }
      return acc;
    };

    return solve();
    
  }
};
