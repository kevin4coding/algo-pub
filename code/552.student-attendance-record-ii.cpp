class Solution {
 public:
  int checkRecord(int n) {
    static struct {
      mutable std::optional<int> f[100005][3][3][2] = {};
    } mempool;
    
    const int P = 0;
    const int A = 1;
    const int L = 2;
    
    using int64 = long long;
    const int64 mod = 1e9 + 7;
    
    std::function<int64(int, int, int, int)> f = [&, memo = mempool.f](int i, int c, int l, int a) {
      if (memo[i][c][l][a].has_value()) {
        return memo[i][c][l][a].value();
      }
      else {
        return memo[i][c][l][a].emplace([&] {
          if (i == 0) {
            return int64(1);
          }
          else if (c == A) {
            return (f(i - 1, P, 2, 0) + (l >= 1 ? f(i - 1, L, l - 1, 0) : 0)) % mod ;
          }
          else if (c == P) {
            return (f(i - 1, P, 2, a) + f(i - 1, L, l - 1, a) + (a == 1 ? f(i - 1, A, 2, 0) : 0)) % mod;
          }
          else if (c == L) {
            return (f(i - 1, P, 2, a) + (a == 0 ? 0 : f(i - 1, A, 2, 0)) + (l >= 1 ? f(i - 1, L, l - 1, a) : 0)) % mod;
          }
          else throw;
        }());
      }
    };

    return (f(n - 1, A, 2, 0) + f(n - 1, P, 2, 1) + f(n - 1, L, 1, 1)) % mod;
    
  }
};
