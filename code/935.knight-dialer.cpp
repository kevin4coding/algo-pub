class Solution {
 public:
  int knightDialer(int n) {
    using int64 = long long;
    const static int R = 4, C = 3;
    const static int board[R][C] = {{1, 2, 3},
                                    {4, 5, 6},
                                    {7, 8, 9},
                                    {-1, 0, -1}};
    const static int dr[8] = {1, 2, 1, 2, -1, -2, -1, -2};
    const static int dc[8] = {2, 1, -2, -1, -2, -1, 2, 1};
    const static int64 mod = 1e9 + 7;

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    struct {
      mutable std::optional<int> f[5005][4][3] = {};
    } mempool;

    std::function<int64(int, int, int)> f = [&, memo = mempool.f](int i, int r, int c) {
      if (memo[i][r][c].has_value()) {
        return memo[i][r][c].value();
      }
      else {
        return memo[i][r][c].emplace([&] {
          if (i == n) {
            return int64(1);
          }
          else {
            return [&](int64 acc = 0) {
              for (int k = 0; k < 8; ++k) {
                const auto [nr, nc] = std::pair{r + dr[k], c + dc[k]};
                if (inbound(nr, nc) and board[nr][nc] != -1) {
                  acc = (acc + f(i + 1, nr, nc)) % mod;
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int64 acc = 0) {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (board[r][c] != -1) {
            acc = (acc + f(1, r, c)) % mod;
          }
        }
      }
      return acc;
    };

    return solve();
    
  }
};
