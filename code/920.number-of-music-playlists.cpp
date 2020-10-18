class Solution {
 public:
  int numMusicPlaylists(int N, int L, int K) {
    using int64 = long long;

    const int64 mod = 1e9 + 7;
    
    struct {
      mutable std::optional<int64> f[105][105] = {};
    } mempool;

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 1) {
            return j == 1 ? int64(N) : 0;
          }
          else if (j == 0 or i < j) {
            return int64(0);
          }
          else {
            return (f(i - 1, j - 1) * (N - (j - 1)) + f(i - 1, j) * std::max(0, j - K)) % mod;
          }
        }());
      }
    };

    return f(L, N) % mod;
  }
};
