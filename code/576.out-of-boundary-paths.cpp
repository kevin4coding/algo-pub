class Solution {
 public:
  int findPaths(int m, int n, int N, int i, int j) {
    using int64 = long long;
    const struct {
      mutable std::optional<int64> f[50][50][50];
    } mempool;

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    const int64 mod = 1e9 + 7;
    
    auto inbound = [&](int r, int c) {
      return 0 <= r and r < m and 0 <= c and c < n;
    };

    auto count_ways = [&](int r, int c) {
      auto acc = int64(0);
      for (int i = 0; i < 4; ++i) {
        if (not inbound(r + dr[i], c + dc[i])) {
          ++acc;
        }
      }
      return acc;
    };

    std::function<int64(int, int, int)> f = [&, memo = std::ref(mempool.f)](int r, int c, int n) {
      if (memo[r][c][n].has_value()) {
        return memo[r][c][n].value();
      }
      else {
        return memo[r][c][n].emplace([&] {
          if (n == 1) {
            return count_ways(r, c);
          }
          else {
            return [&](int64 acc = 0) {
              for (int i = 0; i < 4; ++i) {
                const auto [nr, nc] = std::pair(r + dr[i], c + dc[i]);
                if (inbound(nr, nc)) {
                  acc = (acc + f(nr, nc, n - 1)) % mod;
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    const auto solution = [&](int64 acc = 0) {
      for (int n = 1; n <= N; ++n) {
        acc = (acc % mod + f(i, j, n) % mod) % mod;
      }
      return acc;
    }();

    return solution;
  }
};
