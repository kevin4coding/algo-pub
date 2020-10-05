class Solution {
 public:
  int countPalindromicSubsequences(string S) {
    using int64 = long long;
    const int n = std::size(S);
    const int64 mod = 1e9 + 7;
      
    static struct {
      mutable std::optional<int> f[1005][1005] = {};

      void reset(int r, int c) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            f[i][j].reset();
          }
        }
      }      
    } mempool;

    mempool.reset(n, n);

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == j) {
            return int64(1);
          }
          else if (i + 1 == j) {
            return int64(2);
          }
          else if (S[i] != S[j]) {
            return (f(i + 1, j) + f(i, j - 1) - f(i + 1, j - 1) + mod) % mod;
          }
          else if (S[i] == S[j]) {
            const auto ll = [&](std::optional<int> self = {}) {
              for (int k = i + 1; k < j and not self.has_value(); ++k) {
                if (S[k] == S[i]) {
                  self.emplace(k);
                }
              }
              return self;
            }();

            const auto rr = [&](std::optional<int> self = {}) {
              for (int k = j - 1; k >= i + 1 and not self.has_value(); --k) {
                if (S[k] == S[j]) {
                  self.emplace(k);
                }
              }
              return self;
            }();

            if (not ll.has_value() and not rr.has_value()) {
              return (2 * f(i + 1, j - 1) + int64(2)) % mod;
            }
            else if (ll.value() == rr.value()) {
              return (2 * f(i + 1, j - 1) + int64(1)) % mod;
            }
            else if (ll.value() + 1 == rr.value()) {
              return (2 * f(i + 1, j - 1)) % mod;
            }
            else {
              return (2 * f(i + 1, j - 1) - f(ll.value() + 1, rr.value() - 1) + mod) % mod;
            }
          }
          else throw;
        }());
      }
    };

    return f(0, n - 1);
  }
};
 
